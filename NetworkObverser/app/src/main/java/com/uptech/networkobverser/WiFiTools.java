package com.uptech.networkobverser;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;

import java.util.List;

public class WiFiTools {
    protected static String getSSID(Context context) {
        WifiManager wm = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        if (wm != null) {
            WifiInfo winfo = wm.getConnectionInfo();
            if (winfo != null) {
                String s = winfo.getSSID();
                if (s.length() > 2 && s.charAt(0) == '"' && s.charAt(s.length() - 1) == '"') {
                    return s;
                }
            }
        }
        return null;
    }

    public static String GetWifiEtType(Context ctx) {
        final String WPAPSK = "WPA_PSK";
        final String WPA2 = "WPA2";
        final String WEP = "WEP";
        final String none = "none";
        PackageManager pm = ctx.getPackageManager();
        final String pn = ctx.getPackageName();
        int isCheck = pm.checkPermission(Manifest.permission.ACCESS_WIFI_STATE, pn);
        if (isCheck != 0) {
            return none;
        }
        WifiManager manager = (WifiManager) ctx.getSystemService(Context.WIFI_SERVICE);
        if (manager == null) {
            return none;
        }
        String s = getSSID(ctx);
        if (s == null || s.equals("")) {
            return none;
        }
        List<WifiConfiguration> configurations = manager.getConfiguredNetworks();
        if (configurations == null || configurations.size() == 0) {
            return none;
        }
        WifiConfiguration config = null;
        for (WifiConfiguration configuration : configurations) {
            if (configuration != null && configuration.SSID != null) {
                if (configuration.SSID.equals(s)) {
                    config = configuration;
                    break;
                }
            }
        }
        if (config == null) {
            return none;
        }
        if (config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.WPA_PSK)) {
            return WPAPSK;
        }
        if (config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.WPA_EAP) || config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.IEEE8021X)) {
            return WPA2;
        }
        if (config.wepKeys[0] != null) {
            return WEP;
        }
        return none;
    }

    public static boolean GetProxyStates(Context ctx) {
        final boolean buildVersion = Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH;
        String proxyAddress;
        int proxyPort;
        if (buildVersion) {
            proxyAddress = System.getProperty("http.proxyHost");
            String portStr = System.getProperty("http.proxyPort");
            proxyPort = Integer.parseInt((portStr != null ? portStr : "-1"));
        } else {
            proxyAddress = android.net.Proxy.getHost(ctx);
            proxyPort = android.net.Proxy.getPort(ctx);
        }

        if (proxyAddress != null && proxyPort != -1) {
            return true;
        } else {
            return false;
        }
    }
}
