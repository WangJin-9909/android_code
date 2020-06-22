package com.wangjin.glidedemo.utils;

import android.content.Context;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class AssestUtils {
    private static final String TAG = AssestUtils.class.getSimpleName();

    /**
     * 拷贝/assest/下的文件到/data/data/xxx/data/目录下
     */
    public static void copyAssetFileToDest(Context context, String fileSource, String fileDest) throws IOException {
        if (new File(fileDest).exists()) {

        }

        InputStream is = context.getAssets().open(fileSource);
        FileOutputStream fos = new FileOutputStream(fileDest);
        int len = -1;
        byte[] buffer = new byte[1024];
        while ((len = is.read(buffer)) != -1) {
            fos.write(buffer, 0, len);
        }
        fos.close();
        is.close();
    }

    /**
     *
     * @param context
     * @param fileName
     * @return
     * @throws IOException
     */
    public static File getFileFromAsset(Context context, String fileName) throws IOException {

        return inputStreamToFile(context.getAssets().open(fileName));


    }

    /**
     * 从asset文件中读取image
     *
     * @param fileName
     * @return
     * @throws IOException
     */
    public static Bitmap getImageFromAssestsFile(Context context, String fileName) throws IOException {
        Bitmap imageBitmap = null;
        AssetManager assetManager = context.getResources().getAssets();

        InputStream is = assetManager.open(fileName);
        imageBitmap = BitmapFactory.decodeStream(is);
        is.close();

        return imageBitmap;


    }

    /**
     * 从Asset下读取文本文件
     *
     * @param fileName
     * @return
     * @throws IOException
     */
    public String getStringFromAsset(Context context, String fileName) throws IOException {
        StringBuilder stringBuilder = new StringBuilder();
        AssetManager assetManager = context.getAssets();
        BufferedReader bf = new BufferedReader(new InputStreamReader(assetManager.open(fileName)));
        String line;
        while ((line = bf.readLine()) != null) {
            stringBuilder.append(line);
        }

        return stringBuilder.toString();
    }


    /**
     * 列出Asset下的所有文件
     *
     * @param context
     * @return
     * @throws IOException
     */
    public static String[] getFileListFromAsset(Context context) throws IOException {
        AssetManager assetManager = context.getAssets();
        return assetManager.list("");
    }


    /**
     * 列出指定目录下的文件,asset下可以存放文件夹
     *
     * @param context
     * @param path
     * @return
     * @throws IOException
     */
    public static String[] getFielListsFromAsset(Context context, String path) throws IOException {
        AssetManager assetManager = context.getAssets();
        return assetManager.list(path);
    }


    /**
     * @param context
     * @return
     */
    public static Resources getResouceFromContext(Context context) {
        return context.getResources();
    }

    /**
     * InputStream转 File类型
     *
     * @param ins
     */
    public static File inputStreamToFile(InputStream ins) {
        File file = null;
        try {
            OutputStream os = new FileOutputStream(file);
            int bytesRead = 0;
            byte[] buffer = new byte[8192];
            while ((bytesRead = ins.read(buffer, 0, 8192)) != -1) {
                os.write(buffer, 0, bytesRead);
            }
            os.close();
            ins.close();

        } catch (Exception e) {
            e.printStackTrace();
        }

        return file;

    }


}
