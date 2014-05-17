package com.example.remotegoat.app;

import android.app.Application;

import com.nostra13.universalimageloader.core.ImageLoader;
import com.nostra13.universalimageloader.core.ImageLoaderConfiguration;

/**
 * Created by SexOffender01 on 2014-05-17.
 */
public class GoatApplication extends Application {
    private String instrumentId;

    @Override
    public void onCreate() {
        super.onCreate();

        // Create global configuration and initialize ImageLoader with this configuration
        ImageLoaderConfiguration config = new ImageLoaderConfiguration.Builder(getApplicationContext())
        .build();
        ImageLoader.getInstance().init(config);
    }

    public void setInstrumentId(String instrumentId){
        this.instrumentId = instrumentId;
    }

    public String getInstrumentId() {
        return instrumentId;
    }
}
