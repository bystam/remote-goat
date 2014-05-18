package com.example.remotegoat.app;

import android.app.Activity;
import android.media.AudioFormat;
import android.media.MediaRecorder;
import android.os.Environment;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.io.IOException;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by jensa on 17/05/2014.
 */
public class RecordingTimer {

    private static final int RECORDER_SAMPLERATE =  44100;
    private static final int BUFFER_SIZE = 1792 * 2;
    private static final int RECORDER_CHANNELS = AudioFormat.CHANNEL_IN_MONO;
    private static final int RECORDER_AUDIO_ENCODING = AudioFormat.ENCODING_PCM_16BIT;


    private final int SESSION_MILLISECONDS = 2000;


    private LinearLayout recordingProgress;
    private ScheduledThreadPoolExecutor timer;
    private Handler animationUpdater;
    private long recordingStart;
    private Activity activity;


    public RecordingTimer(LinearLayout progress,
                          Activity activity){
        this.activity = activity;
        timer = new ScheduledThreadPoolExecutor(2);
        this.recordingProgress = progress;
    }

    private MediaRecorder getMediaRecorder (String outputFile){
        MediaRecorder recorder = new MediaRecorder();
        recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        recorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        recorder.setAudioEncodingBitRate(16);
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
        recordingStart = System.currentTimeMillis();
        timer.execute(new AudioRecorder());

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
            Thread.sleep(SESSION_MILLISECONDS);
            mediaRecorder.stop();
            mediaRecorder.release();
        }
    }

    private class IntervalAnimationUpdate implements Runnable {
        int progress = 0;

        @Override
        public void run() {
            progress++;
            if(progress < 5)
                writeProgress(progress);
            if(progress == 3){
                ScheduledThreadPoolExecutor executor = new ScheduledThreadPoolExecutor(2);
                executor.schedule(new AudioRecorder(), 700, TimeUnit.MILLISECONDS);
            }
            if(progress == 4){
                TextView fileStatus = (TextView) activity.findViewById(R.id.file_status);
                fileStatus.setText("RECORDING...");
            }
            if(progress == 5){
                resetProgress();
                Button sendFileButton = (Button) activity.findViewById(R.id.sendButton);
                sendFileButton.setEnabled(true);
                TextView fileStatus = (TextView) activity.findViewById(R.id.file_status);
                fileStatus.setText(activity.getString(R.string.file_ready));
            } else{
                animationUpdater.postDelayed(this, 1000);
            }
        }
    }

    private void resetProgress() {
        for (int i = 0; i <recordingProgress.getChildCount() ; i++) {
            recordingProgress.getChildAt(i).setVisibility(View.INVISIBLE);
        }
    }

    private void writeProgress(int progress) {
        for (int i = 0; i < progress ; i++) {
            recordingProgress.getChildAt(i).setVisibility(View.VISIBLE);
        }
    }

    private boolean runningSession (){
        return System.currentTimeMillis() - recordingStart < SESSION_MILLISECONDS;
    }


}
