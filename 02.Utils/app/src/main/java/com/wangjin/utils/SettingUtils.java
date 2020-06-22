package com.wangjin.utils;

import android.content.Context;
import android.content.Intent;
import android.provider.Settings;

/**
 * 页面跳转Utils
 */
public class SettingUtils {
    public static final String FLAG_SETTING_GPS = Settings.ACTION_LOCATION_SOURCE_SETTINGS;
    public static final String FLAG_SETTINT_WIFI = Settings.ACTION_WIFI_SETTINGS;


    public static void startSetting(Context context, String flag) {

        Intent intent = new Intent(flag);
        context.startActivities(new Intent[]{intent});

    }

}
