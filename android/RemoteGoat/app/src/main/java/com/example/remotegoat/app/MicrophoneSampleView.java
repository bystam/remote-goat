package com.example.remotegoat.app;

import android.graphics.Color;
import android.widget.ProgressBar;

/**
 * Created by jensa on 17/05/2014.
 */
public class MicrophoneSampleView {
    ProgressBar view;

    //Constructor that is called when inflating a view from XML.
    public MicrophoneSampleView(ProgressBar output){
        view = output;
        view.getProgressDrawable().setColorFilter(Color.GREEN, android.graphics.PorterDuff.Mode.MULTIPLY);
    }

    public void updateAnimation(int increment){
        view.incrementProgressBy(increment);
    }

    public void stopAnimation(){
        view.setProgress(0);
    }

}

