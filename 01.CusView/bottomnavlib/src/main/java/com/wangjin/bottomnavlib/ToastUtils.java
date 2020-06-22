package com.wangjin.bottomnavlib;

import android.content.Context;
import android.widget.Toast;

public class ToastUtils {
    private static Toast mToast;

    private ToastUtils() {

    }

    private static void showToast(Context context, String text) {
        if (null == context && null == mToast) {
            throw new UnsupportedOperationException("mToast and context maut not be null");
        }
        mToast.makeText(context, text, Toast.LENGTH_SHORT).show();
    }
}
