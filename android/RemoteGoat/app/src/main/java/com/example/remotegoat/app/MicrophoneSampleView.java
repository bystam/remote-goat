package com.example.remotegoat.app;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

/**
 * Created by jensa on 17/05/2014.
 */
public class MicrophoneSampleView extends View{
    int amplitude = 0;
    int xCoord = 0;
    boolean animationRunning = false;

    //Constructor that is called when inflating a view from XML.
    public MicrophoneSampleView(Context context, AttributeSet attrs){
        super(context, attrs);
    }

    //Perform inflation from XML and apply a class-specific base style.
    public MicrophoneSampleView(Context context, AttributeSet attrs, int defStyle){
        super(context, attrs, defStyle);
    }

    public MicrophoneSampleView(Context context) {
        super(context);
    }

    public void startAnimation(){
        animationRunning = true;
    }

    public void updateAnimation(int amplitude){
        this.amplitude = amplitude;
        xCoord++;
    }

    public void stopAnimation(){
        animationRunning = false;
    }

    @Override
    public void onDraw(Canvas canvas){
        Paint color = new Paint();
        color.setColor(Color.BLACK);
        if(animationRunning){
            canvas.drawPoint(xCoord, amplitude, color);
        }
    }

    @Override
    public void onMeasure(int width, int height){
        super.onMeasure(width, height);
    }
}
