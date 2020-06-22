package utils;

import android.content.Context;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.Buffer;

public class AssestUtils {


    /**
     * 拷贝/assest/下的文件到/data/data/xxx/data/目录下
     */
    public static void assestFileToData(Context context, String file, String dest) throws IOException {
        boolean isCony = true;
        AssetManager assetManager = context.getAssets();
        String[] fileLists = getFileListFromAsset(context);



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
        return assetManager.list(".");
    }






    /**
     * @param context
     * @return
     */
    public Resources getResouceFromContext(Context context) {
        return context.getResources();
    }


}
