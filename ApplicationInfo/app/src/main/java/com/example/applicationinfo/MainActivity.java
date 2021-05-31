package com.example.applicationinfo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.annotation.Target;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button btn_1;
    private Button btn_2;
    private TextView tv_1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initUi();
        tv_1 = findViewById(R.id.tv_1);
        btn_1 = findViewById(R.id.btn_1);
        btn_2 = findViewById(R.id.btn_2);
        btn_1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                PackageManager packageManager = MainActivity.this.getPackageManager();
                List<ApplicationInfo> applicationInfoList = packageManager
                        .getInstalledApplications(PackageManager.GET_META_DATA);

                for (ApplicationInfo applicationInfo : applicationInfoList) {
                    Log.e("PACKAGE", applicationInfo.packageName);
                    tv_1.append("\r\n");
                    tv_1.append("包：" + applicationInfo.packageName);
                }
            }
        });
        btn_2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getImei();
            }
        });

    }

    private void initUi() {
        findViewById(R.id.btn_3).setOnClickListener(this);
        findViewById(R.id.btn_4).setOnClickListener(this);
        findViewById(R.id.btn_m1).setOnClickListener(this);
        findViewById(R.id.btn_m2).setOnClickListener(this);
        findViewById(R.id.btn_t1).setOnClickListener(this);


        findViewById(R.id.btn_5).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String str = Build.BRAND;
                Toast.makeText(getApplicationContext(), "str = " + str, Toast.LENGTH_SHORT).show();

            }
        });


    }


    private String getImei() {
        String strID = "";
        TelephonyManager manager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
        Class<? extends TelephonyManager> clazz = manager.getClass();
        Method getImei = null;//(int slotId)
        try {
            getImei = clazz.getDeclaredMethod("getImei");
            strID = (String) getImei.invoke(manager);
            showResult(strID);
        } catch (Exception e) {
            showToast(e.getMessage() + "", getApplicationContext());
            e.printStackTrace();
        }


        return strID;
    }


    private void showResult(String content) {
        tv_1.append("\r\n");
        tv_1.append("" + content);
    }


    private void showToast(String content, Context context) {
        Toast.makeText(getApplicationContext(), content, Toast.LENGTH_SHORT).show();
    }

    String shell[] = {" am start -n com.android.flysilkworm/com.android.flysilkworm.app.activity.FrameworkActivity"};

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_3:
                if (resolveIntent(BLUESTACE_PACK, BLUESTACE_ACT)) {
                    Toast.makeText(getApplicationContext(), "检测到蓝蝶", Toast.LENGTH_SHORT).show();
                }
                if (resolveIntent(YESHEN_PACK, YESHEN_ACT)) {
                    Toast.makeText(getApplicationContext(), " 检测到夜深", Toast.LENGTH_SHORT).show();
                }
                if (resolveIntent(LEIDIAN_PACK, LEIDIAN_ACT)) {
                    Toast.makeText(getApplicationContext(), " 检测到雷电", Toast.LENGTH_SHORT).show();
                }
              /*  if (resolveIntent(MUMU_PACK, MUMU_ACT)) {
                    Toast.makeText(getApplicationContext(), " 检测到木木", Toast.LENGTH_SHORT).show();
                }*/
                if (resolveIntent(XIAOYAO_PACK, XIAOYAO_ACT)) {
                    Toast.makeText(getApplicationContext(), "检测到逍遥 ", Toast.LENGTH_SHORT).show();
                }


                break;

            case R.id.btn_4:
                Toast.makeText(this, "---", Toast.LENGTH_SHORT).show();
                List simulatorInfo = CheckSimulator.getSimulatorInfo(this);
                for (int i = 0; i < simulatorInfo.size(); i++) {
                    tv_1.append("\r\n");
                    tv_1.append(simulatorInfo.get(i).toString());
                    Toast.makeText(this, simulatorInfo.get(i) + "", Toast.LENGTH_SHORT).show();
                }
                break;
            case R.id.btn_m1:
                Toast.makeText(this, "Gym ? " + isGenymotion(), Toast.LENGTH_SHORT).show();
                break;

            case R.id.btn_m2:
                Toast.makeText(this, "AS ? " + isASEmulator(), Toast.LENGTH_SHORT).show();
                break;


            case R.id.btn_t1:
                int emulatorBrand = getEmulatorBrand(getApplicationContext());
                Toast.makeText(getApplicationContext(), "em = " + emulatorBrand, Toast.LENGTH_SHORT).show();
                break;


        }

    }


    //----------------------------------------------------------------------------------------------------接口
    private static final String LEIDIAN = "雷电";
    private static final String YESHEN = "夜神";
    private static final String XIAOYAO = "逍遥";
    private static final String MUMU = "mumu";
    private static final int LEIDIANEMULATOR = 101;
    private static final int YESHENNEMULATOR = 102;
    private static final int XIAOYAONEMULATOR = 103;
    private static final int ASEMULATOR = 104;
    private static final int GENYMOTIONEMULATOR = 105;
    private static final int MUMUEMULATOR = 106;
    private static final int BLUESTACKEMULATOR = 107;

    private int getEmulatorBrand(Context context) {
        List simulatorInfo = CheckSimulator.getSimulatorInfo(context);
        String str = "";
        for (int i = 0; i < simulatorInfo.size(); i++) {
            str += simulatorInfo.get(i);
        }
        if (str.contains(YESHEN) || resolveIntent(YESHEN_PACK, YESHEN_ACT)) {
            return YESHENNEMULATOR;
        }
        if (str.contains(LEIDIAN) || resolveIntent(LEIDIAN_PACK, LEIDIAN_ACT)) {
            return LEIDIANEMULATOR;
        }
        if (str.contains(MUMU) /*|| resolveIntent(MUMU_PACK, MUMU_ACT)*/) {
            return MUMUEMULATOR;
        }
        if (str.contains(XIAOYAO) || resolveIntent(XIAOYAO_PACK, XIAOYAO_ACT)) {
            return XIAOYAONEMULATOR;
        }

        if (isASEmulator()) {
            return ASEMULATOR;
        }
        if (isGenymotion()) {
            return GENYMOTIONEMULATOR;
        }
        if (isBlueStackEmulator()) {
            return BLUESTACKEMULATOR;
        }

        return 0;

    }


    //判断genymotion模拟器
    //----------------------------------------------------------------------------------------------
    private static final String Genymotion = "Genymotion";
    private static final String genymotion = "genymotion";

    private boolean isGenymotion() {
        return isGenymotionProp() || isGenymotionManufacturer();
    }


    private boolean isGenymotionManufacturer() {
        return Build.MANUFACTURER.contains(Genymotion) ||
                Build.MANUFACTURER.contains(genymotion);

    }

    private boolean isGenymotionProp() {
        return getProp("ro.vendor.product.manufacturer").contains(genymotion) ||
                getProp("ro.vendor.product.manufacturer").contains(Genymotion) ||
                getProp("ro.vendor.product.model").contains(genymotion) ||
                getProp("ro.vendor.product.model").contains(Genymotion) ||
                getProp("ro.build.user").contains(Genymotion) ||
                getProp("ro.build.user").contains(genymotion);

    }

    public static String getProp(String propName) {
        Class<?> classType = null;
        String str = null;
        try {
            classType = Class.forName("android.os.SystemProperties");
            Method getMethod = classType.getDeclaredMethod("get", new Class<?>[]{String.class});
            str = (String) getMethod.invoke(classType, new Object[]{propName});
        } catch (Exception e) {
            e.printStackTrace();
        }
        return str;
    }

    //判断官方模拟器
    private static final String Google = "Google";
    private static final String google = "google";

    private boolean isASEmulator() {
        return isASManufacturer() || isASProp();
    }

    private boolean isASManufacturer() {
        return Build.MANUFACTURER.contains(Google) ||
                Build.MANUFACTURER.contains(google) ||
                Build.BRAND.contains(Google) ||
                Build.BRAND.contains(google);
    }

    private boolean isASProp() {
        return getProp("ro.product.vendor.brand").contains(Google) ||
                getProp("ro.product.vendor.brand").contains(google) ||
                getProp("ro.product.vendor.manufacturer").contains(Google) ||
                getProp("ro.product.vendor.manufacturer").contains(google) ||
                getProp("ro.product.product.brand").contains(Google) ||
                getProp("ro.product.product.brand").contains(google) ||
                getProp("ro.product.build.fingerprint").contains(Google) ||
                getProp("ro.product.build.fingerprint").contains(google) ||
                getProp("ro.build.fingerprint").contains(Google) ||
                getProp("ro.build.fingerprint").contains(google) ||
                getProp("ro.product.manufacturer").contains(Google) ||
                getProp("ro.product.manufacturer").contains(google);
    }

    //蓝蝶判断
    private boolean isBlueStackEmulator() {
        return onBlueStacks();
    }

    public static boolean onBlueStacks() {
        File sharedFolder = new File(Environment
                .getExternalStorageDirectory().toString()
                + File.separatorChar
                + "windows"
                + File.separatorChar
                + "BstSharedFolder");

        if (sharedFolder.exists()) {
            return true;
        }
        return false;
    }

    //木木、夜神、雷电、逍遥游模拟器判断
    public static final String YESHEN_PACK = "com.vphone.launcher";
    public static final String YESHEN_ACT = "com.vphone.launcher.Launcher";

    public static final String LEIDIAN_PACK = "com.android.flysilkworm";
    public static final String LEIDIAN_ACT = "com.android.flysilkworm.app.activity.FrameworkActivity";

    //public static final String MUMU_PACK = "";
    //public static final String MUMU_ACT = "";
    //蓝蝶
    public static final String BLUESTACE_PACK = "com.bluestacks.settings";
    public static final String BLUESTACE_ACT = "com.bluestacks.settings.SettingsActivity";

    public static final String XIAOYAO_PACK = "com.microvirt.launcher2";
    public static final String XIAOYAO_ACT = "com.microvirt.launcher.Launcher";

    //adb shell dumpsys window windows | grep mCurrent
    private boolean resolveIntent(String pack, String act) {
        Context context = getApplicationContext();
        Intent intent = new Intent();
        ComponentName cn = new ComponentName(pack, act);
        intent.setComponent(cn);
        return intent.resolveActivityInfo(context.getPackageManager(), 0) != null;
    }

}
