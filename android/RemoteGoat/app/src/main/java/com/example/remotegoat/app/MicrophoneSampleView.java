package com.example.remotegoat.app;

import android.content.Context;
import android.media.MediaRecorder;
import android.view.View;

/**
 * Created by jensa on 17/05/2014.
 */
public class MicrophoneSampleView extends View {
    MediaRecorder recorder;

    public MicrophoneSampleView(Context context, MediaRecorder recorder) {
        super(context);
        this.recorder = recorder;
    }

    public void startRecording (){

    }
}
