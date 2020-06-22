package com.wangjin.banner.demo;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Spinner;

import com.wangjin.banner.App;
import com.wangjin.banner.loader.GlideImageLoader;
import com.wangjin.banner.R;
import com.wangjin.bannerlib.Banner;
import com.wangjin.bannerlib.BannerConfig;

import androidx.appcompat.app.AppCompatActivity;


public class BannerStyleActivity extends AppCompatActivity implements  AdapterView.OnItemSelectedListener {
    Banner banner;
    Spinner spinnerStyle;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_banner_style);
        banner = (Banner) findViewById(R.id.banner);
        spinnerStyle = (Spinner) findViewById(R.id.spinnerStyle);
        spinnerStyle.setOnItemSelectedListener(this);

        //默认是CIRCLE_INDICATOR
        banner.setImages(App.images)
                .setBannerTitles(App.titles)
                .setImageLoader(new GlideImageLoader())
                .start();
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        switch (position){
            case 0:
                banner.updateBannerStyle(BannerConfig.NOT_INDICATOR);
                break;
            case 1:
                banner.updateBannerStyle(BannerConfig.CIRCLE_INDICATOR);
                break;
            case 2:
                banner.updateBannerStyle(BannerConfig.NUM_INDICATOR);
                break;
            case 3:
                banner.updateBannerStyle(BannerConfig.NUM_INDICATOR_TITLE);
                break;
            case 4:
                banner.updateBannerStyle(BannerConfig.CIRCLE_INDICATOR_TITLE);
                break;
            case 5:
                banner.updateBannerStyle(BannerConfig.CIRCLE_INDICATOR_TITLE_INSIDE);
                break;
        }
    }

    @Override
    public void onNothingSelected(AdapterView<?> parent) {

    }
}