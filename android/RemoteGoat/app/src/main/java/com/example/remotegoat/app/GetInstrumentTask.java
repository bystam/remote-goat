package com.example.remotegoat.app;

import android.app.Activity;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.nostra13.universalimageloader.core.ImageLoader;

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
        Context context = activity.getApplicationContext();
        int duration = Toast.LENGTH_SHORT;
        CharSequence name;
        if (response == null) {
            //TODO: Somehow close the app or something who knows??!?!
            name = "Could not establish a connection";
            return;
        } else {
            name = response;
        }
        try {
            JSONObject jObject = new JSONObject(name.toString());
            name = jObject.getString("name");
            String imagePath = jObject.getString("img");
            ImageView instrumentImage = (ImageView) activity.findViewById(R.id.instrument_image);
            ImageLoader imageLoader = ImageLoader.getInstance();
            imageLoader.displayImage(hostname + imagePath, instrumentImage);
            TextView instrumentTitle = (TextView) activity.findViewById(R.id.instrument_name);
            instrumentTitle.setText(name.toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }

        Toast toast = Toast.makeText(context, name, duration);
        toast.show();
        Log.d("Instrument response", name.toString());
    }
}