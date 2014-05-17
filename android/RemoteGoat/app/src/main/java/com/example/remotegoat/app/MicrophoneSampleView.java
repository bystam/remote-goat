package com.example.remotegoat.app;

import android.util.Log;
import android.widget.ProgressBar;

/**
 * Created by jensa on 17/05/2014.
 */
public class MicrophoneSampleView {
    int amplitude = 0;
    int xCoord = 0;
    ProgressBar view;
    static boolean animationRunning = false;

    //Constructor that is called when inflating a view from XML.
    public MicrophoneSampleView(ProgressBar output){
        view = output;
    }

    public void startAnimation(){
        Log.d("JORR", "Starting animation");
        animationRunning = true;
    }

    public void updateAnimation(int amplitude){
        view.incrementProgressBy(amplitude);
    }

    public void stopAnimation(){
        view.setProgress(0);
    }

//    @Override
//    public void surfaceCreated(SurfaceHolder holder) {
//        tryDrawing(holder);
//    }
//
//    @Override
//    public void surfaceChanged(SurfaceHolder holder, int frmt, int w, int h) {
//        tryDrawing(holder);
//    }
//
//    @Override
//    public void surfaceDestroyed(SurfaceHolder holder) {}
//
//    private void tryDrawing(SurfaceHolder holder) {
//        ScheduledThreadPoolExecutor executor = new ScheduledThreadPoolExecutor(2);
//        animator = new Animator(holder);
//        executor.execute(animator);
//    }
//
//    private class Animator implements Runnable {
//        private SurfaceHolder holder;
//        public ConcurrentLinkedQueue<Line> points = new ConcurrentLinkedQueue<Line>();
//
//        public Animator(SurfaceHolder hold) {
//            holder = hold;
//        }
//
//        @Override
//        public void run() {
//            while (true) {
//                Bitmap bitmap = Bitmap.createBitmap(holder.getSurfaceFrame().width(), holder.getSurfaceFrame().height(), Bitmap.Config.ARGB_8888);
//                Canvas bitmapCanvas = new Canvas(bitmap);
//                drawAnimation(bitmapCanvas);
//                Canvas canvas = holder.lockCanvas();
//                if (canvas == null) {
//                } else {
////                    if (animationRunning) {
//                    Paint p = new Paint();
//                    p.setColor(Color.BLACK);
//                    canvas.drawBitmap(bitmap, 0, 0, p);
////                        drawAnimation(canvas);
////                    } else {
////                        }
////                    }
//                    holder.unlockCanvasAndPost(canvas);
//                }
//            }
//        }
//
//        private void drawAnimation(Canvas canvas) {
//            canvas.drawARGB(255, 255, 128, 128);
//            Paint color = new Paint();
//            color.setColor(Color.BLACK);
//            color.setStrokeWidth(10);
//            for(Line line : points) {
//                canvas.drawLine(line.start.x, line.start.y, line.end.x, line.end.y, color);
//            }
//        }
//
//        public void clear (){
//            points.clear();
//            Canvas canvas = holder.lockCanvas();
//            canvas.drawARGB(255, 255, 128, 128);
//            holder.unlockCanvasAndPost(canvas);
////            path.reset();
//        }
//
//    }
//
//    private class Line {
//
//        public Line(Point start, Point end){
//            this.start = start;
//            this.end = end;
//        }
//        public Point start;
//        public Point end;
//    }
}

