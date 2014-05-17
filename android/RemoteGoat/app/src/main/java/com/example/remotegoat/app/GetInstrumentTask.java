package com.example.remotegoat.app;

import android.app.Activity;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by Dexter on 2014-05-17.
 */
public class GetInstrumentTask extends AsyncTask<String, Void, String> {

    private String hostname = "http://192.168.43.6/";
    private Activity activity;

    public GetInstrumentTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected String doInBackground(String... params) {
        URL url = null;
        try {
            url = new URL(hostname+"instruments");
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
        return ResponseReader.getResponse(url);
    }

    @Override
    protected void onPostExecute(String response) {
        //TODO: Call class that creates gui here
        Context context = activity.getApplicationContext();
        int duration = Toast.LENGTH_SHORT;
        CharSequence text;
        if (response == null) {
            //TODO: Somehow close the app or something who knows??!?!
            text = "Could not establish a connection";
            return;
        } else {
            text = response;
        }
        try {
            JSONObject jObject = new JSONObject(text.toString());
            text = jObject.getString("name");
        } catch (JSONException e) {
            e.printStackTrace();
        }

        Toast toast = Toast.makeText(context, text, duration);
        toast.show();
        Log.d("Instrument response", text.toString());
    }
}