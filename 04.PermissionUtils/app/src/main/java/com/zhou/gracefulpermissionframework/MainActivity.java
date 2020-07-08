package com.zhou.gracefulpermissionframework;

import android.Manifest;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends BaseActivity {
    public static final int CODE = 1;
    private EditText et;
    Uri uri = Uri.parse("content://sms");

    private SmsObserver smsObserver;
    private Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case CODE:
                    String code = (String) msg.obj;
                    Toast.makeText(MainActivity.this, "c =" + code, Toast.LENGTH_SHORT).show();
                    et.setText(code);
                    break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_location).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getLocationPermission();
            }
        });

        findViewById(R.id.btn_contact).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getContactPermission();
            }
        });
        findViewById(R.id.btn_sms).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getSmsPermission();
            }


        });

        et = (EditText) findViewById(R.id.et);
        smsObserver = new SmsObserver(this, mHandler);

        findViewById(R.id.btn_sms_register).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                registerSms();
            }
        });

    }

    private void registerSms() {
        //注册内容观察者
        getContentResolver().registerContentObserver(uri, true, smsObserver);

    }

    //Ok，就是这么一个普通的Activity，如果我需要 读取内部存储的权限。
    private void getContactPermission() {
        String[] permissions = new String[]{Manifest.permission.READ_CONTACTS, Manifest.permission.WRITE_CONTACTS};
        requestPermission(permissions, PermissionConst.REQUEST_CODE_CONTACT);
    }

    //Ok，就是这么一个普通的Activity，如果我需要 读取内部存储的权限。
    private void getLocationPermission() {
        String[] permissions = new String[]{Manifest.permission.ACCESS_FINE_LOCATION};
        requestPermission(permissions, PermissionConst.REQUEST_CODE_LOCATION);
    }

    private void getSmsPermission() {
        String[] permissions = new String[]{Manifest.permission.READ_SMS};
        requestPermission(permissions, PermissionConst.REQUEST_CODE_READ_SMS);
    }

    @Override
    public void granted(int requestCode) {
        if (PermissionConst.REQUEST_CODE_LOCATION == requestCode) {
            Log.e(TAG, "定位权限已经授予");
        } else if (PermissionConst.REQUEST_CODE_CONTACT == requestCode) {
            Log.e(TAG, "联系人权限已经授予");
        } else if (PermissionConst.REQUEST_CODE_READ_SMS == requestCode) {
            Log.e(TAG, "读取短信权限已经授予");
        }
    }

    @Override
    public void denied(int requestCode) {
        if (PermissionConst.REQUEST_CODE_LOCATION == requestCode) {
            Log.e(TAG, "定位权限被拒绝了");
            Toast.makeText(this, "拒绝权限导致的程序不能用昂", Toast.LENGTH_SHORT).show();
        } else if (PermissionConst.REQUEST_CODE_CONTACT == requestCode) {
            Log.e(TAG, "联系人权限被拒绝了");
            Toast.makeText(this, "拒绝权限导致的程序不能用昂", Toast.LENGTH_SHORT).show();
        } else if (PermissionConst.REQUEST_CODE_READ_SMS == requestCode) {
            Log.e(TAG, "联系人权限被拒绝了");
            Toast.makeText(this, "拒绝权限导致的程序不能用昂", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void deniedForever(int requestCode) {
        if (PermissionConst.REQUEST_CODE_LOCATION == requestCode) {
            Log.e(TAG, "定位权限被永久拒绝了");
        } else if (PermissionConst.REQUEST_CODE_CONTACT == requestCode) {
            Log.e(TAG, "联系人权限被永久拒绝了");
        } else if (PermissionConst.REQUEST_CODE_READ_SMS == requestCode) {
            Log.e(TAG, "短信权限被永久拒绝了");
        }
    }

    //所有的技术手段，无论是编程语言还是，代码框架，都是为了需求服务的，脱离需求谈技术，都是纸老虎！
    //那么，现在来总结一下，我们app开发的过程中，用到权限申请的时候，会有哪些实际需求呢?
    // 举个实际例子，我们需要向系统申请 定位权限。
}
