package com.wangjin.bannerlib;


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

import androidx.viewpager.widget.ViewPager;

public class Transformer {
    public static Class<? extends ViewPager.PageTransformer> Default = DefaultTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> Accordion = AccordionTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> BackgroundToForeground = BackgroundToForegroundTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> ForegroundToBackground = ForegroundToBackgroundTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> CubeIn = CubeInTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> CubeOut = CubeOutTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> DepthPage = DepthPageTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> FlipHorizontal = FlipHorizontalTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> FlipVertical = FlipVerticalTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> RotateDown = RotateDownTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> RotateUp = RotateUpTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> ScaleInOut = ScaleInOutTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> Stack = StackTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> Tablet = TabletTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> ZoomIn = ZoomInTransformer.class;
    public static Class<? extends ViewPager.PageTransformer> ZoomOut = ZoomOutTranformer.class;
    public static Class<? extends ViewPager.PageTransformer> ZoomOutSlide = ZoomOutSlideTransformer.class;
}
