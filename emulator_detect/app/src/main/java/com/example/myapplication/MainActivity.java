package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.os.Debug;
import android.telephony.TelephonyManager;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.lang.reflect.Method;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

public class MainActivity extends AppCompatActivity {
    private Context context;
    private Button btn;
    private TextView tvResult;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initData();
        initUi();

    }

    private void initUi() {
        setContentView(R.layout.activity_main);
        btn = findViewById(R.id.btn_detect);
        tvResult = findViewById(R.id.tv_result);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                boolean r = isEmulator();
                if (r) {
                    tvResult.setText("设备是模拟器");

                } else {
                    tvResult.setText("设备不是模拟器");
                }
            }
        });

        findViewById(R.id.btn_get).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                String cpuName = CpuManager.getCpuName();
                //String cpuName = CpuManager.readCpuInfo();
                boolean b = CpuManager.isCpuNormal();
                Toast.makeText(MainActivity.this, "str = " + b, Toast.LENGTH_SHORT).show();
            }
        });
        findViewById(R.id.btn_get_ver).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String cpuName = HardwareInfo.getVersion();
                Toast.makeText(MainActivity.this, "str = " + cpuName, Toast.LENGTH_SHORT).show();
            }
        });
        findViewById(R.id.btn_get_eth0).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String b = HardwareInfo.hasEth0Interface();
                Toast.makeText(MainActivity.this, "str = " + b, Toast.LENGTH_SHORT).show();
            }
        });
    findViewById(R.id.btn_get_dial).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                boolean b = HardwareInfo.canDial(MainActivity.this);
                Toast.makeText(MainActivity.this, "可以电话否 = " + b, Toast.LENGTH_SHORT).show();
            }
        });
   findViewById(R.id.btn_get_sms).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                boolean b = HardwareInfo.canSendSms(MainActivity.this);
                Toast.makeText(MainActivity.this, "可以短信否 = " + b, Toast.LENGTH_SHORT).show();
            }
        });
   findViewById(R.id.btn_get_ble).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String b = HardwareInfo.hasBle();
                Toast.makeText(MainActivity.this, "ble = " + b, Toast.LENGTH_SHORT).show();
            }
        });

    }





    private void initData() {
        context = this;

    }


    public boolean isEmulator() {
        return /*hasEmulatorTelephonyProperty()
                ||*/  hasEmulatorBuildProp()
                || hasQemuBuildProps()
                || hasQemuCpuInfo()
                || hasQemuFile()
                || hasEth0Interface()
                || isNotUserBuild();
    }

    /**
     * 添加进入方法二，设备文件状态
     *
     * @return
     */
    private static boolean hasEth0Interface() {
       /* try {
            for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements(); ) {
                NetworkInterface intf = en.nextElement();
                if (intf.getName().equals("eth0"))
                    return true;
            }
        } catch (SocketException ex) {
        }*/
        return false;
    }

    /**
     * 添加进入方法三，检测设备驱动文件状态
     *
     * @return
     */
    private static boolean hasQemuCpuInfo() {
        try {
            BufferedReader cpuInfoReader = new BufferedReader(new FileReader("/proc/cpuinfo"));
            String line;
            while ((line = cpuInfoReader.readLine()) != null) {
                if (line.contains("Goldfish"))
                    return true;
            }
        } catch (Exception e) {
        }
        return false;
    }

    /**
     * 添加进入方法三，检测设备驱动文件状态。原有代码中包含
     *
     * @return
     */
    private static boolean hasQemuFile() {
        return new File("/init.goldfish.rc").exists()
                || new File("/sys/qemu_trace").exists()
                || new File("/system/bin/qemud").exists();

    }


    public static String getProp(String propName) {
        Class<?> classType = null;
        String buildVersion = null;
        try {
            classType = Class.forName("android.os.SystemProperties");
            Method getMethod = classType.getDeclaredMethod("get", new Class<?>[]{String.class});
            buildVersion = (String) getMethod.invoke(classType, new Object[]{propName});
        } catch (Exception e) {
            e.printStackTrace();
        }
        return buildVersion;
    }

    /**
     * 添加进入方法一，系统参数信息
     *
     * @return
     */
    private boolean hasQemuBuildProps() {
        return "goldfish".equals(getProp(/*context,*/ "ro.hardware"))
                || "ranchu".equals(getProp(/*context,*/ "ro.hardware"))
                || "generic".equals(getProp(/*context,*/ "ro.product.device"))
                || "1".equals(getProp(/*context,*/ "ro.kernel.qemu"))
                || "0".equals(getProp(/*context,*/ "ro.secure"));
    }

    /**
     * 添加进入方法一，系统参数信息
     *
     * @return
     */
    private boolean isNotUserBuild() {
        return !"user".equals(getProp(/*context,*/ "ro.build.type"));
    }


    /**
     * 添加进入方法一，系统参数信息
     *
     * @return
     */
    private boolean hasEmulatorBuildProp() {
        return Build.FINGERPRINT.startsWith("generic")
                || Build.FINGERPRINT.startsWith("unknown")
                || Build.MODEL.contains("google_sdk") || Build.MODEL.contains("sdk")
                || Build.MODEL.contains("Emulator")
                || Build.MODEL.contains("Android SDK built for x86")
                || Build.MANUFACTURER.contains("Genymotion")
                || (Build.BRAND.startsWith("generic") && Build.DEVICE.startsWith("generic"))
                || Build.PRODUCT.contains("google_sdk") || Build.PRODUCT.contains("sdk")
                || Build.HARDWARE.contains("goldfish")
                || Build.HARDWARE.contains("ranchu")
                || Build.BOARD.contains("unknown")
                || Build.ID.contains("FRF91")
                || Build.MANUFACTURER.contains("unknown")
                || Build.SERIAL == null
                || Build.TAGS.contains("test-keys")
                || Build.USER.contains("android-build")
                ;
    }
    /*
    private boolean hasEmulatorTelephonyProperty() {
        TelephonyManager tm = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
        return "Android".equals(tm.getNetworkOperatorName())
                || "Android".equals(tm.getSimOperator())
                || "000000000000000".equals(tm.getDeviceId()) || tm.getDeviceId().matches("^0+$")
                || tm.getLine1Number().startsWith("155552155")
                || tm.getSubscriberId().endsWith("0000000000")
                || "15552175049".equals(tm.getVoiceMailNumber())
                ;
    }*/
}
