package com.uptech.networkobverser;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.LinkProperties;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

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
}
