package com.example.remotegoat.app;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.Typeface;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends Activity {

    LinearLayout progressLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final String hostname = "192.168.43.218";
        AlertDialog.Builder alert = new AlertDialog.Builder(this);

        alert.setTitle("IP?");
        final EditText input = new EditText(this);
        input.setText(hostname);
        alert.setView(input);
        alert.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                String value = input.getText().toString();
                String host = "http://" + value + "/";
                buildGUI(host);
            }
        });

        alert.show();
    }

    public void buildGUI (final String host){
        new GetInstrumentTask(this, host).execute();
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
                new PostSoundFileTask(MainActivity.this, host).execute();
            }
        });
    }

    private void startRecording (){
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
