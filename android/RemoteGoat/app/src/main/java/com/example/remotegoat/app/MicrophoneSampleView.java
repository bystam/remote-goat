package com.example.remotegoat.app;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Point;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.ThreadPoolExecutor;

/**
 * Created by jensa on 17/05/2014.
 */
public class MicrophoneSampleView implements SurfaceHolder.Callback {
    int amplitude = 0;
    int xCoord = 0;
    SurfaceView view;
    static boolean animationRunning = false;
    Animator animator;

    //Constructor that is called when inflating a view from XML.
    public MicrophoneSampleView(SurfaceView output){
        view = output;
        SurfaceHolder holder = output.getHolder();
        holder.addCallback(this);
    }

    public void startAnimation(){
        Log.d("JORR", "Starting animation");
        animationRunning = true;
    }

    public void updateAnimation(int amplitude){
        this.amplitude = amplitude*20;
        xCoord++;
    }

    public void stopAnimation(){
        Log.d("JORR", "Stopping animation");
        animationRunning = false;
        xCoord = 0;
        animator.clear();
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        tryDrawing(holder);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int frmt, int w, int h) {
        tryDrawing(holder);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {}

    private void tryDrawing(SurfaceHolder holder) {
        ScheduledThreadPoolExecutor executor = new ScheduledThreadPoolExecutor(2);
        animator = new Animator(holder);
        executor.execute(animator);
    }

    private class Animator implements Runnable {
        private SurfaceHolder holder;
        private ArrayList<Line> points = new ArrayList<Line>();

        public Animator(SurfaceHolder hold) {
            holder = hold;
        }

        @Override
        public void run() {
            while (true) {
                Canvas canvas = holder.lockCanvas();
                if (canvas == null) {
                } else {
                    if (animationRunning)
                        drawAnimation(canvas);
                    else
                        points.clear();
                    holder.unlockCanvasAndPost(canvas);
                }
            }
        }

        private void drawAnimation(Canvas canvas) {

            Point next = new Point(xCoord + 150, amplitude + 100);
            Point reverse = new Point(xCoord + 150, -amplitude + 100);
            points.add(new Line(next, reverse));
            Paint color = new Paint();
            color.setColor(Color.BLACK);
            color.setStrokeWidth(10);
            canvas.drawRGB(255, 128, 128);
            for(Line line : points) {
                canvas.drawLine(line.start.x, line.start.y, line.end.x, line.end.y, color);
            }
        }

        public void clear (){
//            points.clear();
//            path.reset();
        }

    }

    private class Line {

        public Line(Point start, Point end){
            this.start = start;
            this.end = end;
        }
        public Point start;
        public Point end;
    }
}

