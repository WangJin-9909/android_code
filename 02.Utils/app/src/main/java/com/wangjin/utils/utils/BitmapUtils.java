package com.wangjin.utils.utils;

import android.graphics.BitmapFactory;

public class BitmapUtils {
    /**
     * 加载大图
     * https://www.iteye.com/blog/deep-fish-2021016
     * 根据要求计算
     * @param op
     * @param reqWidth
     * @param reqHeight
     * @return
     */
    public static  int calculateInSampleSize(BitmapFactory.Options op, int reqWidth, int reqHeight){
        int originalWidth = op.outWidth;
        int originalHeight = op.outHeight;
        int inSampleSize = -1;
        if(originalWidth > reqWidth || originalHeight > reqHeight){
            int halfWidth = originalWidth / 2;
            int halfHeight = originalHeight / 2;
            while((halfWidth / inSampleSize > reqWidth) && (halfHeight / inSampleSize > reqHeight)){
                inSampleSize *= 2;
            }
        }

        return inSampleSize;

    }

}
