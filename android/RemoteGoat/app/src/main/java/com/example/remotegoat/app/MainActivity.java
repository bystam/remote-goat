package com.example.remotegoat.app;

import android.app.Activity;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends Activity {

    LinearLayout progressLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new GetInstrumentTask(this).execute();
        progressLayout =  (LinearLayout) findViewById(R.id.progressLayout);
        Typeface font = Typeface.createFromAsset(getAssets(), "8-BIT WONDER.TTF");
        TextView instrumentTitle = (TextView) findViewById(R.id.instrument_name);
        TextView fileStatus = (TextView) findViewById(R.id.file_status);
        fileStatus.setTypeface(font);
        instrumentTitle.setTypeface(font);
        Button recordingButton = (Button) findViewById(R.id.recordButton);
        recordingButton.setTypeface(font);
        int titleId = getResources().getIdentifier("action_bar_title", "id",
                "android");
        TextView title = (TextView) findViewById(titleId);
        title.setTypeface(font);

        recordingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startRecording();
            }
        });

        Button sendFileButton = (Button) findViewById(R.id.sendButton);
        sendFileButton.setTypeface(font);
        sendFileButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d("Send button", "clicked");
                new PostSoundFileTask(MainActivity.this).execute();
            }
        });
    }


    private void startRecording (){
        Log.d("STARTING", "starting recording sesh");
        try {
            new RecordingTimer(progressLayout, this).startRecordingSession();
        } catch (Exception e) {
            e.printStackTrace();
        }
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
