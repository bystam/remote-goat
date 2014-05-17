package com.example.remotegoat.app;

import android.media.AudioRecord;

/**
 * Created by jensa on 17/05/2014.
 */
public class RecordingTimer {

    AudioRecord recorder;

    public RecordingTimer(AudioRecord recorder, MicrophoneSampleView micSampleView, FilesystemRecorder filesystemRecorder){
        this.recorder = recorder;

    }

    public void startRecordingSession(){

    }


}
