package com.example.remotegoat.app;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Environment;
import android.util.Log;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.concurrent.ScheduledThreadPoolExecutor;

import android.os.Handler;

/**
 * Created by jensa on 17/05/2014.
 */
public class RecordingTimer {

    private static final int RECORDER_SAMPLERATE =  44100;
    private static final int BUFFER_SIZE = 1792 * 2;
    private static final int RECORDER_CHANNELS = AudioFormat.CHANNEL_IN_MONO;
    private static final int RECORDER_AUDIO_ENCODING = AudioFormat.ENCODING_PCM_16BIT;


    private final int SESSION_MILLISECONDS = 5000;
    private final int ANIMATION_INTERVAL = 50;
    private final int RECORDING_DELAY = 3000;

    private AudioRecord recorder;
    private MicrophoneSampleView microphoneSampleView;
    private FilesystemRecorder filesystemRecorder;
    private ScheduledThreadPoolExecutor timer;
    private Handler animationUpdater;
    private long animationStart;

    private int currentAmplitude;


    public RecordingTimer(MicrophoneSampleView micSampleView, FilesystemRecorder filesystemRecorder){
        timer = new ScheduledThreadPoolExecutor(2);
        this.recorder = getAudioRecorder();
        this.filesystemRecorder = filesystemRecorder;
        this.microphoneSampleView = micSampleView;
    }

    private AudioRecord getAudioRecorder(){
        AudioRecord recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
                RECORDER_SAMPLERATE, RECORDER_CHANNELS,
                RECORDER_AUDIO_ENCODING, BUFFER_SIZE);
        return recorder;
    }

    private MediaRecorder getMediaRecorder (String outputFile){
        MediaRecorder recorder = new MediaRecorder();
        recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
        recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
        recorder.setOutputFile(outputFile);
        try {
            recorder.prepare();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return recorder;
    }

    public void startRecordingSession() throws Exception {
        animationStart = System.currentTimeMillis();
        timer.execute(new AudioRecorder());
        microphoneSampleView.startAnimation();
        animationUpdater = new Handler();
        animationUpdater.post(new IntervalAnimationUpdate());
    }

    private class AudioRecorder implements Runnable {

        @Override
        public void run() {
            try {
                record();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        private void record() throws IOException {
            byte[] recordingBuffer = new byte[BUFFER_SIZE];
            recorder.startRecording();
            while (preRecordingPhase()){
                recorder.read(recordingBuffer, 0, BUFFER_SIZE);
                int average = 0;
                for (int i=0;i< recordingBuffer.length;i++) {
                    average += recordingBuffer[i];
                }
                currentAmplitude = average/recordingBuffer.length;
            }
            recordingBuffer = new byte[BUFFER_SIZE];
            ByteArrayOutputStream writer = new ByteArrayOutputStream();
            while (runningSession()){
                recorder.read(recordingBuffer, 0, BUFFER_SIZE);
                writer.write(recordingBuffer, 0, BUFFER_SIZE);
                int average = 0;
                for (int i=0;i< recordingBuffer.length;i++) {
                    average += recordingBuffer[i];
                }
                currentAmplitude = average/recordingBuffer.length;
            }
            recorder.stop();
            recorder.release();
            File file = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/"+"recordedbytes");
            if(file.exists())
                file.delete();
            file.createNewFile();
            FileOutputStream out = new FileOutputStream(file);
            out.write(writer.toByteArray(), 0, writer.size());
        }
    }

    private class IntervalAnimationUpdate implements Runnable {

        @Override
        public void run() {
            microphoneSampleView.updateAnimation(currentAmplitude);
            if(runningSession()) {
                animationUpdater.postDelayed(this, ANIMATION_INTERVAL);
            } else{
                microphoneSampleView.stopAnimation();
            }
        }
    }

    private boolean runningSession (){
        return System.currentTimeMillis() - animationStart < SESSION_MILLISECONDS;
    }

    private boolean preRecordingPhase() {
        return System.currentTimeMillis() - animationStart < RECORDING_DELAY;
    }


}
