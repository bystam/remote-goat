package com.example.remotegoat.app;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Environment;
import android.util.Log;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.HttpMultipartMode;
import org.apache.http.entity.mime.MultipartEntityBuilder;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.CoreProtocolPNames;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.util.EntityUtils;

import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;

/**
 * Created by SexOffender01 on 2014-05-17.
 */
public class PostSoundFileTask extends AsyncTask<String, Void, String> {

    private final String hostname;
    private Activity activity;

    public PostSoundFileTask(Activity activity, String host) {
        this.activity = activity;
        hostname = host;
    }

    @Override
    protected String doInBackground(String... params) {
        Log.d("Post", "Executed");
        String url = hostname + "sample";
        return post(url);
    }

    @Override
    protected void onPostExecute(String response) {
        String text;
        if (response == null) {
            //TODO: Somehow close the app or something who knows??!?!
            text = "Could not establish a connection";
        } else {
            text = response;
        }
        Log.d("Instrument response", text.toString());
    }

    public String post(String url) {
        // the file to be posted
        String filePath = Environment.getExternalStorageDirectory() + "/recording.mp4";

        // the URL where the file will be posted
        HttpClient httpClient = new DefaultHttpClient();
        HttpConnectionParams.setSoTimeout(httpClient.getParams(), 3000);
        httpClient.getParams().setParameter(CoreProtocolPNames.USER_AGENT, "Custom user agent");
        HttpPost httpPost = new HttpPost(url);

        File file = new File(filePath);
        FileBody fileBody = new FileBody(file);

        MultipartEntityBuilder builder = MultipartEntityBuilder.create();
        builder.setMode(HttpMultipartMode.BROWSER_COMPATIBLE);
        builder.addPart("audiofile", fileBody);
        GoatApplication goat = (GoatApplication) activity.getApplication();
        String instrumentId = goat.getInstrumentId();
        
        try {
            builder.addPart("id", new StringBody(instrumentId));
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        httpPost.setEntity(builder.build());

        // execute HTTP post request
        HttpResponse response = null;
        try {
            Log.d("Before client execute", "yup");
            response = httpClient.execute(httpPost);
            Log.d("After client execute", "jodu");
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (response != null) {

            HttpEntity resEntity = response.getEntity();
            String responseStr = null;
            try {
                responseStr = EntityUtils.toString(resEntity).trim();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return responseStr;
        }
        // TODO: JSON thingies
        return "Response was null";
    }
}

