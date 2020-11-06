package com.wangjin.utils.utils;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Build;
import android.telephony.ServiceState;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.widget.Toast;

import java.lang.reflect.Method;


public class NetWorkUtils {
    private static final String TAG = NetWorkUtils.class.getSimpleName();

    public static String GetNetworkType(Context ctx) {
        String strNetworkType = "";
        ConnectivityManager connMgr = (ConnectivityManager) ctx
                .getSystemService(Context.CONNECTIVITY_SERVICE);
        if (connMgr == null) {
            return strNetworkType;
        }
        PackageManager pm = ctx.getPackageManager();
        final String pn = ctx.getPackageName();
        int isCheck = pm.checkPermission(Manifest.permission.ACCESS_NETWORK_STATE, pn);
        if (isCheck != 0) {
            return strNetworkType;
        }

        NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
        if (networkInfo != null && networkInfo.isConnected()) {
            if (networkInfo.getType() == ConnectivityManager.TYPE_WIFI) {
                strNetworkType = "WIFI";
            } else if (networkInfo.getType() == ConnectivityManager.TYPE_MOBILE) {
                String _strSubTypeName = networkInfo.getSubtypeName();

                // Log.i("chen", "Network getSubtypeName : " + _strSubTypeName);

                // TD-SCDMA networkType is 17
                int networkType = networkInfo.getSubtype();
                Toast.makeText(ctx, "networkType = " + networkType, Toast.LENGTH_SHORT).show();
                Toast.makeText(ctx, "strSubTypeName = " + _strSubTypeName, Toast.LENGTH_SHORT).show();

                switch (networkType) {
                    case TelephonyManager.NETWORK_TYPE_GPRS:
                    case TelephonyManager.NETWORK_TYPE_EDGE:
                    case TelephonyManager.NETWORK_TYPE_CDMA:
                    case TelephonyManager.NETWORK_TYPE_1xRTT:
                    case TelephonyManager.NETWORK_TYPE_IDEN: // api<8 : replace by
                        // 11
                        strNetworkType = "2G";
                        break;
                    case TelephonyManager.NETWORK_TYPE_UMTS:
                    case TelephonyManager.NETWORK_TYPE_EVDO_0:
                    case TelephonyManager.NETWORK_TYPE_EVDO_A:
                    case TelephonyManager.NETWORK_TYPE_HSDPA:
                    case TelephonyManager.NETWORK_TYPE_HSUPA:
                    case TelephonyManager.NETWORK_TYPE_HSPA:
                    case TelephonyManager.NETWORK_TYPE_EVDO_B: // api<9 : replace by
                        // 14
                    case TelephonyManager.NETWORK_TYPE_EHRPD: // api<11 : replace by
                        // 12
                    case TelephonyManager.NETWORK_TYPE_HSPAP: // api<13 : replace by
                        // 15
                        strNetworkType = "3G";
                        break;
                    case TelephonyManager.NETWORK_TYPE_LTE: // api<11 : replace by
                        // 13
                        strNetworkType = "4G";
                        break;
                    default:
                        strNetworkType = "nosignal";
                        break;
                }

            }
        } else {
            strNetworkType = "nosignal";
        }

        return strNetworkType;
    }


   /* public static void is5GNetWork(Context context) {
        TelephonyManager telephonyManager = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
        int networkType = telephonyManager.getNetworkType();
        Toast.makeText(context, "networkType " + networkType, Toast.LENGTH_SHORT).show();
        if (networkType == TelephonyManager.NETWORK_TYPE_NR) {// 对应的20 只有依赖为android 9.0才有此属性
            Log.i(TAG, "5G");
            Toast.makeText(context, "检测到5G网络", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(context, "未检测到5G", Toast.LENGTH_SHORT).show();
        }
    }*/

   /* public static int getCurrentNetType(Context context) {
        int type = 1;//默认wifi
        ConnectivityManager cm = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo info = cm.getActiveNetworkInfo();
        if (info == null) {
            type = 1;//wifi
        } else if (info.getType() == ConnectivityManager.TYPE_WIFI) {
            type = 1;//wifi
        } else if (info.getType() == ConnectivityManager.TYPE_MOBILE) {
            int subType = info.getSubtype();
            if (subType == TelephonyManager.NETWORK_TYPE_GSM ||
                    subType == TelephonyManager.NETWORK_TYPE_GPRS ||
                    subType == TelephonyManager.NETWORK_TYPE_CDMA ||
                    subType == TelephonyManager.NETWORK_TYPE_EDGE ||
                    subType == TelephonyManager.NETWORK_TYPE_1xRTT ||
                    subType == TelephonyManager.NETWORK_TYPE_IDEN
            ) {
                type = 2;//2G
            } else if (
                    subType == TelephonyManager.NETWORK_TYPE_TD_SCDMA ||
                            subType == TelephonyManager.NETWORK_TYPE_EVDO_A ||
                            subType == TelephonyManager.NETWORK_TYPE_UMTS ||
                            subType == TelephonyManager.NETWORK_TYPE_EVDO_0 ||
                            subType == TelephonyManager.NETWORK_TYPE_HSDPA ||
                            subType == TelephonyManager.NETWORK_TYPE_HSUPA ||
                            subType == TelephonyManager.NETWORK_TYPE_HSPA ||
                            subType == TelephonyManager.NETWORK_TYPE_EVDO_B ||
                            subType == TelephonyManager.NETWORK_TYPE_EHRPD ||
                            subType == TelephonyManager.NETWORK_TYPE_HSPAP
            ) {
                type = 3;//3G
            } else if (subType == TelephonyManager.NETWORK_TYPE_IWLAN ||
                    subType == TelephonyManager.NETWORK_TYPE_LTE) {// LTE是3g到4g的过渡，是3.9G的全球标准
                type = 4;//4G
            } else if (subType == TelephonyManager.NETWORK_TYPE_NR) { //api 29 时生效  为5G网络类型  值为20也是一样
                type = 5;//5G
            }
        }
        Toast.makeText(context, "" + "type===========" + type, Toast.LENGTH_SHORT).show();
        return type;
    }*/


    public static boolean is5GConnected(Context context){
        TelephonyManager telephonyManager = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
        if(Build.VERSION.SDK_INT >= 29){
            ServiceState serviceState = telephonyManager.getServiceState();
            try{
                Method hwOwnMethod = ServiceState.class.getMethod("getHwNetworkType");
                hwOwnMethod.setAccessible(true);
                int result = (int)hwOwnMethod.invoke(serviceState);
                Log.i("ALeeObj", "值为：" + result);
                if(result == 20){
                    return true;
                }else{
                    return false;
                }
            }catch (Exception e){
                Log.i("ALeeObj", e.toString());
            }
        }
        return false;
    }



   /* public static String getNetWorkClass(Context context) {
        TelephonyManager telephonyManager = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
        Log.e("5G_TEST", "telephonyManager = " + telephonyManager.getDataNetworkType());
        switch (telephonyManager.getNetworkType()) {
            case TelephonyManager.NETWORK_TYPE_GPRS:
            case TelephonyManager.NETWORK_TYPE_EDGE:
            case TelephonyManager.NETWORK_TYPE_CDMA:
            case TelephonyManager.NETWORK_TYPE_1xRTT:
            case TelephonyManager.NETWORK_TYPE_IDEN:
                return Constants.NETWORK_CLASS_2_G;

            case TelephonyManager.NETWORK_TYPE_UMTS:
            case TelephonyManager.NETWORK_TYPE_EVDO_0:
            case TelephonyManager.NETWORK_TYPE_EVDO_A:
            case TelephonyManager.NETWORK_TYPE_HSDPA:
            case TelephonyManager.NETWORK_TYPE_HSUPA:
            case TelephonyManager.NETWORK_TYPE_HSPA:
            case TelephonyManager.NETWORK_TYPE_EVDO_B:
            case TelephonyManager.NETWORK_TYPE_EHRPD:
            case TelephonyManager.NETWORK_TYPE_HSPAP:
                return Constants.NETWORK_CLASS_3_G;

            case TelephonyManager.NETWORK_TYPE_LTE:
                return Constants.NETWORK_CLASS_4_G;
            case TelephonyManager.NETWORK_TYPE_NR:
                return Constants.NETWORK_CLASS_5_G;
            default:
                return Constants.NETWORK_WIFI;
        }
    }*/

    class Constants {

        /**
         * wifi net work
         */
        public static final String NETWORK_WIFI = "wifi";

        /**
         * "2G" networks
         */
        public static final String NETWORK_CLASS_2_G = "2G";

        /**
         * "3G" networks
         */
        public static final String NETWORK_CLASS_3_G = "3G";

        /**
         * "4G" networks
         */
        public static final String NETWORK_CLASS_4_G = "4G";
        /**
         * "5G" networks
         */
        public static final String NETWORK_CLASS_5_G = "5G";

    }
}
