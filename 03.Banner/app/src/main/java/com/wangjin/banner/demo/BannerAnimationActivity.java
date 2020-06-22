package com.wangjin.banner.demo;

import android.os.Bundle;

import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.wangjin.banner.App;

import com.wangjin.banner.SampleAdapter;
import com.wangjin.banner.loader.GlideImageLoader;
import com.wangjin.banner.R;
import com.wangjin.bannerlib.Banner;
import com.wangjin.bannerlib.listener.OnBannerListener;
import com.wangjin.bannerlib.transformer.AccordionTransformer;
import com.wangjin.bannerlib.transformer.BackgroundToForegroundTransformer;
import com.wangjin.bannerlib.transformer.CubeInTransformer;
import com.wangjin.bannerlib.transformer.CubeOutTransformer;
import com.wangjin.bannerlib.transformer.DefaultTransformer;
import com.wangjin.bannerlib.transformer.DepthPageTransformer;
import com.wangjin.bannerlib.transformer.FlipHorizontalTransformer;
import com.wangjin.bannerlib.transformer.FlipVerticalTransformer;
import com.wangjin.bannerlib.transformer.ForegroundToBackgroundTransformer;
import com.wangjin.bannerlib.transformer.RotateDownTransformer;
import com.wangjin.bannerlib.transformer.RotateUpTransformer;
import com.wangjin.bannerlib.transformer.ScaleInOutTransformer;
import com.wangjin.bannerlib.transformer.StackTransformer;
import com.wangjin.bannerlib.transformer.TabletTransformer;
import com.wangjin.bannerlib.transformer.ZoomInTransformer;
import com.wangjin.bannerlib.transformer.ZoomOutSlideTransformer;
import com.wangjin.bannerlib.transformer.ZoomOutTranformer;


import java.util.ArrayList;
import java.util.List;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

public class BannerAnimationActivity extends AppCompatActivity implements AdapterView.OnItemClickListener, OnBannerListener {
    Banner banner;
    List<Class<? extends ViewPager.PageTransformer>> transformers = new ArrayList<>();

    public void initData() {
        transformers.add(DefaultTransformer.class);
        transformers.add(AccordionTransformer.class);
        transformers.add(BackgroundToForegroundTransformer.class);
        transformers.add(ForegroundToBackgroundTransformer.class);
        transformers.add(CubeInTransformer.class);//兼容问题，慎用
        transformers.add(CubeOutTransformer.class);
        transformers.add(DepthPageTransformer.class);
        transformers.add(FlipHorizontalTransformer.class);
        transformers.add(FlipVerticalTransformer.class);
        transformers.add(RotateDownTransformer.class);
        transformers.add(RotateUpTransformer.class);
        transformers.add(ScaleInOutTransformer.class);
        transformers.add(StackTransformer.class);
        transformers.add(TabletTransformer.class);
        transformers.add(ZoomInTransformer.class);
        transformers.add(ZoomOutTranformer.class);
        transformers.add(ZoomOutSlideTransformer.class);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_banner_animation);
        initData();
        banner = (Banner) findViewById(R.id.banner);
        ListView listView = (ListView) findViewById(R.id.list);
        String[] data = getResources().getStringArray(R.array.anim);
        listView.setAdapter(new SampleAdapter(this, data));
        listView.setOnItemClickListener(this);

        banner.setImages(App.images)
                .setImageLoader(new GlideImageLoader())
                .setOnBannerListener(this)
                .start();

    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        banner.setBannerAnimation(transformers.get(position));
    }

    @Override
    public void OnBannerClick(int position) {
        Toast.makeText(getApplicationContext(), "你点击了：" + position, Toast.LENGTH_SHORT).show();
    }
}
