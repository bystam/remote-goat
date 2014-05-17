package com.example.remotegoat.app;

import android.content.Context;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

/**
 * Created by jensa on 17/05/2014.
 */
public class MicrophoneSampleView {
    TextView debugOutput;

    public MicrophoneSampleView(TextView debug) {
        debugOutput = debug;
    }

    public void startAnimation(){
        debugOutput.setText("Starting animation");
    }

    public void updateAnimation(short[] amplitudes){
        int average = 0;
        for (int i=0;i< amplitudes.length;i++) {
            average += amplitudes[i];
            Log.d("update",""+amplitudes[i] );
        }
        average = average/amplitudes.length;
        debugOutput.setText("amplitude: " + average);
    }

    public void stopAnimation(){
        debugOutput.setText("Stopping animation");
    }
}
