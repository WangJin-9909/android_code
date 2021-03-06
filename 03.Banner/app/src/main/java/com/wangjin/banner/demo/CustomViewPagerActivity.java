package com.wangjin.banner.demo;

import android.os.Bundle;

import android.view.ViewGroup;
import android.widget.RelativeLayout;

import com.wangjin.banner.App;

import com.wangjin.banner.loader.GlideImageLoader;
import com.wangjin.banner.R;
import com.wangjin.bannerlib.Banner;
import com.wangjin.bannerlib.listener.OnBannerListener;

import androidx.appcompat.app.AppCompatActivity;


public class CustomViewPagerActivity extends AppCompatActivity implements OnBannerListener {
    Banner banner;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_custom_view_pager);

        banner = (Banner) findViewById(R.id.banner);
        banner.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, App.H / 4));
        //简单使用
        banner.setImages(App.images)
                .setImageLoader(new GlideImageLoader())
                .setOnBannerListener(this)
                .start();
    }

    @Override
    public void OnBannerClick(int position) {

    }

    //如果你需要考虑更好的体验，可以这么操作
    @Override
    protected void onStart() {
        super.onStart();
        //开始轮播
        banner.startAutoPlay();
    }

    @Override
    protected void onStop() {
        super.onStop();
        //结束轮播
        banner.stopAutoPlay();
    }
}
