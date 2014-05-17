package com.example.remotegoat.app;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import android.os.Handler;

/**
 * Created by jensa on 17/05/2014.
 */
public class RecordingTimer {

    private static final int RECORDER_SAMPLERATE = 8000;
    private static final int RECORDER_CHANNELS = AudioFormat.CHANNEL_IN_MONO;
    private static final int RECORDER_AUDIO_ENCODING = AudioFormat.ENCODING_PCM_16BIT;

    public int BufferElements2Rec = 1024; // want to play 2048 (2K) since 2 bytes we use only 1024
    public int BytesPerElement = 2; // 2 bytes in 16bit format

    private final int SESSION_MILLISECONDS = 10000;
    private final int ANIMATION_INTERVAL = 1000;
    private final int RECORDING_DELAY = 3000;
    private final int RECORDING_INTERVAL = 100;

    private AudioRecord recorder;
    private MicrophoneSampleView microphoneSampleView;
    private FilesystemRecorder filesystemRecorder;
    private ScheduledThreadPoolExecutor timer;
    private Handler animationUpdater, filesystemUpdater;
    private long animationStart;

    private short[] recordingBuffer = new short[BufferElements2Rec * BytesPerElement];


    public RecordingTimer(MicrophoneSampleView micSampleView, FilesystemRecorder filesystemRecorder){
        timer = new ScheduledThreadPoolExecutor(2);
        this.recorder = getMediaRecorder();
        this.filesystemRecorder = filesystemRecorder;
        this.microphoneSampleView = micSampleView;
    }

    private AudioRecord getMediaRecorder (){
        AudioRecord recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
                RECORDER_SAMPLERATE, RECORDER_CHANNELS,
                RECORDER_AUDIO_ENCODING, BufferElements2Rec * BytesPerElement);
        return recorder;
    }

    public void startRecordingSession() throws Exception {
        new Thread(new AudioRecorder()).run();
        animationStart = System.currentTimeMillis();
        microphoneSampleView.startAnimation();
        animationUpdater = new Handler();
        animationUpdater.post(new IntervalAnimationUpdate());

        filesystemUpdater = new Handler();
        filesystemUpdater.postDelayed(new FileRecordingUpdate(), RECORDING_DELAY);

    }

    private class AudioRecorder implements Runnable {

        @Override
        public void run() {
            recorder.startRecording();
            int recordinginterval = 10;
            while (runningSession()){
                recorder.read(recordingBuffer, 0, BufferElements2Rec);
            }
            recorder.stop();
        }
    }

    private class IntervalAnimationUpdate implements Runnable {

        @Override
        public void run() {
            microphoneSampleView.updateAnimation(recordingBuffer);
            if(runningSession()) {
                animationUpdater.postDelayed(this, ANIMATION_INTERVAL);
            }
        }
    }

    private class FileRecordingUpdate implements Runnable{
        @Override
        public void run() {
            Log.d("INTERVAL", "file");
            filesystemRecorder.record(new int[5]);
            if(runningSession())
                filesystemUpdater.postDelayed(this, System.currentTimeMillis() + RECORDING_INTERVAL);
        }
    }

    private boolean runningSession (){
        return System.currentTimeMillis() - animationStart < SESSION_MILLISECONDS;
    }


}
