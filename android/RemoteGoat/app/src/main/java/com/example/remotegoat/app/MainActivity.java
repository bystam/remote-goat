package com.example.remotegoat.app;

import android.app.Activity;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends Activity {

    private MicrophoneSampleView micSampleView;
    private FilesystemRecorder filesystemRecorder = new FilesystemRecorder();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new GetInstrumentTask(this).execute();
        LinearLayout mainLayout = (LinearLayout) findViewById(R.id.mainLayout);
//        micSampleView = new MicrophoneSampleView(this);
        micSampleView = (MicrophoneSampleView) findViewById(R.id.micSample);
        Button recordingButton = (Button) findViewById(R.id.recordButton);

        recordingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startRecording();
            }
        });

        Button sendFileButton = (Button) findViewById(R.id.sendButton);
        sendFileButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new PostSoundFileTask(MainActivity.this).execute();
            }
        });
    }


    private void startRecording (){
        Log.d("STARTING", "starting recording sesh");
        try {
            new RecordingTimer(micSampleView, filesystemRecorder).startRecordingSession();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

}
