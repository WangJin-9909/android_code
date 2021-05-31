package com.example.pad;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Point;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.WindowManager;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.reflect.Method;
import java.math.BigDecimal;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private String TAG = "EMULATORTEST";
    private TextView tv_1;
    private TextView tv_2;
    private TextView tv_3;
    private TextView tv_model;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tv_1 = findViewById(R.id.tv_1);
        tv_model = findViewById(R.id.tv_model);
        tv_2 = findViewById(R.id.tv_2);
        tv_3 = findViewById(R.id.tv_3);
        tv_1.setText("  " + isPad(this));


        //获取设备型号
        String str = android.os.Build.BRAND + "   " + android.os.Build.MODEL + "    " + android.os.Build.VERSION.RELEASE;
        tv_model.setText(str);


        DisplayMetrics dm = new DisplayMetrics();
        WindowManager wm = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        wm.getDefaultDisplay().getMetrics(dm);

        tv_3.setText(dm.heightPixels + " x " + dm.widthPixels);




    }


    private static boolean isPad(Context context) {
        boolean b1 = isTabletDevice1(context);
        boolean b2 = isPadScreen(context);
        return b1 || b2;
    }

    private static boolean isTabletDevice1(Context context) {
        return (context.getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) >=
                Configuration.SCREENLAYOUT_SIZE_LARGE;
    }

    private static boolean isPadScreen(Context context) {
        DisplayMetrics dm = new DisplayMetrics();
        WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        wm.getDefaultDisplay().getMetrics(dm);
        float density = dm.density;
        boolean b1 = density < 2.8;
        boolean b2 = getScreenInchsNew(context) > 6.8;
        return b1 && b2;
    }


    private boolean isVendorDevice(Context context) {
        //*获取当前厂商*//*
        String vendor = android.os.Build.BRAND;
        Log.e(TAG, "vendor = " + vendor);
        if ("".equals(vendor) || null == vendor) {
            //Toast.makeText(context, "没有拿到厂商信息", Toast.LENGTH_SHORT).show();
        }
        //*获取所有包名*//*
        PackageManager packageManager = context.getPackageManager();
        List<ApplicationInfo> applicationInfoList = packageManager
                .getInstalledApplications(PackageManager.GET_META_DATA);
        for (ApplicationInfo applicationInfo : applicationInfoList) {
            //判断包名里是否包含vendor,todo:需要忽略大小写
            if (applicationInfo.packageName.toLowerCase().contains(vendor.toLowerCase())) {
                //Log.e(TAG, "匹配了厂商信息");
                //Toast.makeText(context, "匹配了厂商信息", Toast.LENGTH_SHORT).show();
                return true;
            }
        }
        return false;
    }


    public static double getScreenInchsNew(Context context) {
        double mInch = 0;
        try {
            int realWidth = 0, realHeight = 0;
            WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
            Display display = wm.getDefaultDisplay();
            //Display display = context.getWindowManager().getDefaultDisplay();
            DisplayMetrics metrics = new DisplayMetrics();
            display.getMetrics(metrics);
            if (android.os.Build.VERSION.SDK_INT >= 17) {
                Point size = new Point();
                display.getRealSize(size);
                realWidth = size.x;
                realHeight = size.y;
            } else if (android.os.Build.VERSION.SDK_INT < 17
                    && android.os.Build.VERSION.SDK_INT >= 14) {
                Method mGetRawH = Display.class.getMethod("getRawHeight");
                Method mGetRawW = Display.class.getMethod("getRawWidth");
                realWidth = (Integer) mGetRawW.invoke(display);
                realHeight = (Integer) mGetRawH.invoke(display);
            } else {
                realWidth = metrics.widthPixels;
                realHeight = metrics.heightPixels;
            }
            mInch = formatDouble(Math.sqrt((realWidth / metrics.xdpi) * (realWidth / metrics.xdpi) + (realHeight / metrics.ydpi) * (realHeight / metrics.ydpi)), 1);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return mInch;
    }

    private static double formatDouble(double d, int newScale) {
        BigDecimal bd = new BigDecimal(d);
        return bd.setScale(newScale, BigDecimal.ROUND_HALF_UP).doubleValue();
    }

}
