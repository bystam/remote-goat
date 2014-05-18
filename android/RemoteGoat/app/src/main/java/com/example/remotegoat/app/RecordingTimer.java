package com.example.remotegoat.app;

import android.app.Activity;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Environment;
import android.os.Handler;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.util.concurrent.ScheduledThreadPoolExecutor;

/**
 * Created by jensa on 17/05/2014.
 */
public class RecordingTimer {

    private static final int RECORDER_SAMPLERATE =  44100;
    private static final int BUFFER_SIZE = 1792 * 2;
    private static final int RECORDER_CHANNELS = AudioFormat.CHANNEL_IN_MONO;
    private static final int RECORDER_AUDIO_ENCODING = AudioFormat.ENCODING_PCM_16BIT;


    final int RECORDING_TIME = 1000; //ms

    private final int SESSION_MILLISECONDS = 5000;
    private final int ANIMATION_INTERVAL = 100;
    private final int RECORDING_DELAY = SESSION_MILLISECONDS - RECORDING_TIME;


    private AudioRecord recorder;
    private MicrophoneSampleView microphoneSampleView;
    private FilesystemRecorder filesystemRecorder;
    private ScheduledThreadPoolExecutor timer;
    private Handler animationUpdater;
    private long animationStart;

    private int currentAmplitude;
    private Activity activity;


    public RecordingTimer(MicrophoneSampleView micSampleView, FilesystemRecorder filesystemRecorder,
                          Activity activity){
        this.activity = activity;
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
        recorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        recorder.setAudioSamplingRate(RECORDER_SAMPLERATE);
        recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
        recorder.setAudioChannels(1);
        recorder.setAudioEncodingBitRate(44100 * 16);
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
        microphoneSampleView.startAnimation();
        animationUpdater = new Handler();
        animationUpdater.post(new IntervalAnimationUpdate());
    }

    private class AudioRecorder implements Runnable {

        @Override
        public void run() {
            try {
                record();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        private void record() throws IOException, InterruptedException {
            MediaRecorder mediaRecorder = getMediaRecorder(Environment.getExternalStorageDirectory().getAbsolutePath() + "/"+"recording.mp4");
            mediaRecorder.start();
            Thread.sleep(RECORDING_TIME);
            mediaRecorder.stop();
            mediaRecorder.release();
        }
    }

    private class IntervalAnimationUpdate implements Runnable {
        private boolean recorded = false;

        @Override
        public void run() {
            microphoneSampleView.updateAnimation(2);

            if(runningSession())
                animationUpdater.postDelayed(this, ANIMATION_INTERVAL);
            if(startRecording() && !recorded) {
                timer.execute(new AudioRecorder());
                recorded = true;
                microphoneSampleView.startRecordingPhase();
            }
            if(!runningSession()){
                microphoneSampleView.stopAnimation();
                Button sendFileButton = (Button) activity.findViewById(R.id.sendButton);
                sendFileButton.setEnabled(true);
                TextView fileStatus = (TextView) activity.findViewById(R.id.file_status);
                fileStatus.setText(activity.getString(R.string.file_ready));
            }
        }
    }

    private boolean startRecording(){
        long timePassed = System.currentTimeMillis() - animationStart;
        return timePassed > RECORDING_DELAY;
    }

    private boolean runningSession (){
        return System.currentTimeMillis() - animationStart < SESSION_MILLISECONDS;
    }

    private boolean preRecordingPhase() {
        return System.currentTimeMillis() - animationStart < RECORDING_DELAY;
    }


}
