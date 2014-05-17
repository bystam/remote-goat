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
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.MultipartEntityBuilder;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.CoreProtocolPNames;
import org.apache.http.util.EntityUtils;

import java.io.File;
import java.io.IOException;

/**
 * Created by SexOffender01 on 2014-05-17.
 */
public class PostSoundFileTask extends AsyncTask<String, Void, String> {

    private final String hostname = "http://46.59.25.115/";
    private Activity activity;

    public PostSoundFileTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected String doInBackground(String... params) {
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
        String filePath = Environment.getExternalStorageDirectory() + "/li_scaled_profile_picture.jpg";

        Log.d("file path", filePath);
        // the URL where the file will be posted

        HttpClient httpClient = new DefaultHttpClient();
        httpClient.getParams().setParameter(CoreProtocolPNames.USER_AGENT, "Custom user agent");
        HttpPost httpPost = new HttpPost(url);

        File file = new File(filePath);
        FileBody fileBody = new FileBody(file, "image/jpeg");

        MultipartEntityBuilder builder = MultipartEntityBuilder.create();
        MultipartEntity reqEntity = new MultipartEntity(HttpMultipartMode.BROWSER_COMPATIBLE);
        builder.setMode(HttpMultipartMode.BROWSER_COMPATIBLE);
        builder.addPart("file", fileBody);
        httpPost.setEntity(builder.build());

        // execute HTTP post request
        HttpResponse response = null;
        try {
            response = httpClient.execute(httpPost);
        } catch (IOException e) {
            e.printStackTrace();
        }
        HttpEntity resEntity = response.getEntity();

        if (resEntity != null) {

            String responseStr = null;
            try {
                responseStr = EntityUtils.toString(resEntity).trim();
            } catch (IOException e) {
                e.printStackTrace();
            }
            Log.v("Response", responseStr);
            return responseStr;
            // you can add an if statement here and do other actions based on the response
        }
        // TODO: JSON thingies
        return "Wat";
    }
}

