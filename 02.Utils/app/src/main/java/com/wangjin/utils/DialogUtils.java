package com.wangjin.utils;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;

public class DialogUtils {

    /**
     * 显示对话框
     *
     * @param context
     * @param title
     * @param content
     * @param positiveTitle
     * @param positiveListener
     * @param negativeTitle
     * @param negativeListener
     */
    public static  void showDialog(Context context, String title, String content, String positiveTitle, DialogInterface.OnClickListener
            positiveListener, String negativeTitle, DialogInterface.OnClickListener negativeListener) {
        new AlertDialog.Builder(context)
                .setTitle(title)
                .setMessage(content)
                .setPositiveButton(positiveTitle, positiveListener)
                .setNegativeButton(negativeTitle, negativeListener).show();
    }


}
