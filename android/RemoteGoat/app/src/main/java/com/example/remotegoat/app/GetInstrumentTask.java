package com.example.remotegoat.app;

import android.app.Activity;
import android.content.Context;
import android.os.AsyncTask;
import android.widget.Toast;

import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by Dexter on 2014-05-17.
 */
public class GetInstrumentTask extends AsyncTask<String, Void, String> {

    private final String hostname = "http://jensarvidsson.se/";
    private Activity activity;

    public GetInstrumentTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected String doInBackground(String... params) {
        URL url = null;
        try {
            url = new URL(hostname);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
        return ResponseReader.getResponse(url);
    }

    @Override
    protected void onPostExecute(String response) {
        if (response == null) {
            //TODO: Somehow close the app or something who knows??!?!
        }
        //TODO: Call class that creates gui here
        Context context = activity.getApplicationContext();
        int duration = Toast.LENGTH_SHORT;
        CharSequence text;
        if (response.startsWith("False")){
            text = "Post failed";
            Toast toast = Toast.makeText(context, text, duration);
            toast.show();
        }else {
            text = response;
            Toast toast = Toast.makeText(context, text, duration);
            toast.show();
        }
    }
}