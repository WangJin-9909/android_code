package com.wangjin.utils;

import android.content.Context;
import android.widget.Toast;

public class ToastUtils {

    /**
     * @param context
     * @param msg
     * @param flag
     */
    public static  void showToast(Context context, String msg, int flag) {
        Toast.makeText(context, msg, flag).show();
    }

    /**
     *
     * @param context
     * @param msg
     */
    public static  void showToast(Context context, String msg) {
        Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
    }
}
