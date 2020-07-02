package com.uptech.networkobverser;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.LinkProperties;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkInfo;
import android.net.NetworkRequest;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class MainActivity extends AppCompatActivity {
    private static final int CELLULAR = 2;
    private static final int WIFI = 1;
    public static String sWifiAddr;
    public static String sMAC;
    public static String sBSSID;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView mtoolBarTitle = (TextView) findViewById(R.id.toolbar_title);
        mtoolBarTitle.setText("监控网络测试");
        initApp();

        findViewById(R.id.btn_get_mac).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, getMac(MainActivity.this), Toast.LENGTH_SHORT).show();
            }
        });

        findViewById(R.id.btn_get_network).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String s = GetNetworkType(MainActivity.this);
                Toast.makeText(MainActivity.this, s, Toast.LENGTH_SHORT).show();
            }
        });
        findViewById(R.id.btn_get_proc).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String s = getProp(MainActivity.this, "ro.build.version.release");
                Toast.makeText(MainActivity.this, s, Toast.LENGTH_SHORT).show();
            }
        });
        findViewById(R.id.btn_get_crc).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                long s = getCRC(MainActivity.this);
                Toast.makeText(MainActivity.this, "s = " + s, Toast.LENGTH_SHORT).show();
            }
        });
        findViewById(R.id.btn_exeShell).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String[] args = new String[]{"pm"};
                ArrayList<String> list = executeCommand(args);
                Toast.makeText(MainActivity.this, "s = " + list.get(0), Toast.LENGTH_SHORT).show();
            }
        });


    }

    private static ArrayList<String> executeCommand(String[] shellCmd) {
        String line = null;
        ArrayList<String> result = new ArrayList<String>();
        Process localProcess = null;
        try {
            localProcess = Runtime.getRuntime().exec(shellCmd);
        } catch (IOException e) {
            return null;
        }
        BufferedReader in = new BufferedReader(new InputStreamReader(localProcess.getInputStream()));
        try {
            while ((line = in.readLine()) != null) {
                result.add(line);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (in != null)
                    in.close();
                if (localProcess != null)
                    localProcess.destroy();
            } catch (IOException e) {

            }
        }
        return result;
    }

    public long getCRC(Context ctx) {
        if (ctx == null)
            return -1;

        try {
            ZipFile zf = new ZipFile(ctx.getApplicationContext().getPackageCodePath());
            ZipEntry ze = zf.getEntry("classes.dex");
            return ze.getCrc();
        } catch (Exception e) {
            return -1;
        }
    }

    private static String intToIp(int paramInt) {
        StringBuilder localStringBuilder = new StringBuilder();
        localStringBuilder.append(paramInt & 0xFF);
        localStringBuilder.append(".");
        localStringBuilder.append(0xFF & paramInt >> 8);
        localStringBuilder.append(".");
        localStringBuilder.append(0xFF & paramInt >> 16);
        localStringBuilder.append(".");
        localStringBuilder.append(0xFF & paramInt >> 24);
        return localStringBuilder.toString();
    }

    public static String getMac(Context paramContext) {
        try {
            WifiManager localWifiManager = (WifiManager) paramContext.getSystemService(Context.WIFI_SERVICE);
            if (localWifiManager.isWifiEnabled()) {
                WifiInfo localWifiInfo = localWifiManager.getConnectionInfo();
                sWifiAddr = intToIp(localWifiInfo.getIpAddress());
                sMAC = localWifiInfo.getMacAddress();
                sBSSID = localWifiInfo.getBSSID();
            }
        } catch (Throwable localThrowable) {
            localThrowable.printStackTrace();
        }
        return sMAC;
    }

    private void initApp() {
        if (Build.VERSION.SDK_INT >= 21) {
            final ConnectivityManager localConnectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
            localConnectivityManager.requestNetwork(new NetworkRequest.Builder().build(), new NetworkCallback() {
                @Override
                public void onAvailable(Network network) {
                    super.onAvailable(network);
                    String str;
                    if (localConnectivityManager.getNetworkCapabilities(network).hasTransport(NetworkCapabilities.TRANSPORT_WIFI))
                        str = "WIFI";
                    else
                        str = "移动网咯";
                    StringBuilder localStringBuilder1 = new StringBuilder();
                    localStringBuilder1.append("网络连接类型为  ");
                    localStringBuilder1.append(str);
                    StringBuilder localStringBuilder2 = new StringBuilder();
                    localStringBuilder2.append("正在使用  : ");
                    localStringBuilder2.append(str);
                    Toast.makeText(MainActivity.this, localStringBuilder2.toString(), Toast.LENGTH_SHORT).show();
                }

                @Override
                public void onLosing(Network network, int maxMsToLive) {

                    super.onLosing(network, maxMsToLive);
                }

                @Override
                public void onLost(Network network) {
                    Toast.makeText(MainActivity.this, "网络连接失败", Toast.LENGTH_SHORT).show();
                    super.onLost(network);
                }

                @Override
                public void onUnavailable() {
                    super.onUnavailable();
                }

                @Override
                public void onCapabilitiesChanged(Network network, NetworkCapabilities networkCapabilities) {
                    Log.e("NETWORK_WANGJIN", "onCapabilitiesChanged");
                    super.onCapabilitiesChanged(network, networkCapabilities);
                }

                @Override
                public void onLinkPropertiesChanged(Network network, LinkProperties linkProperties) {
                    super.onLinkPropertiesChanged(network, linkProperties);
                }
            });

        }
    }


    private static String getProp(Context ctx, String property) {
        try {
            ClassLoader cl = ctx.getClassLoader();
            Class<?> SystemProperties = cl.loadClass("android.os.SystemProperties");

            Method get = SystemProperties.getMethod("get", String.class);
            Object[] param = new Object[1];

            param[0] = new String(property);

            return (String) get.invoke(SystemProperties, param);

        } catch (Exception e) {
            return null;
        }
    }


    public String GetNetworkType(Context ctx) {
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
}
