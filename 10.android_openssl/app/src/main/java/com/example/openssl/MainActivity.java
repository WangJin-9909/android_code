package com.example.openssl;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.example.openssl.R;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initUi();

    }

    private void initUi() {
        setContentView(R.layout.activity_main);
        TextView tv_version = findViewById(R.id.openssl_version);
        tv_version.setText(getVersion());
        findViewById(R.id.btn_sm2).setOnClickListener(this);
        findViewById(R.id.btn_sm3).setOnClickListener(this);

    }

    public native byte[] stringFromJNI(byte[] src);


    public static final int CBC = 0;
    public static final int ECB = 1;

    private void test() {
        MSCryptKey keyStr12 = getInitKey(1, "aaaaaa", "123456");
        String getEt12 = getSeaEt(CBC, "231", keyStr12);
        Toast.makeText(getApplicationContext(), getEt12, Toast.LENGTH_SHORT).show();
    }


    //SM2
    private void test_sm2() {
        String str = "M123456789";
        String getEt = getGmRiEt(str, "84974f6ddea424d46112611b7502104df9ee9f05939463da07553b99c9ca5d77", "f289fda76c945850833c9dfcc495d769ba60c541589692bbcb084470639d01b3");
        Toast.makeText(getApplicationContext(), getEt, Toast.LENGTH_SHORT).show();
    }


    //openssl版本号
    public native String getVersion();

    public native String getSeaEt(int type, String data, MSCryptKey keyCode);

    public native String getGmRiEt(String data, String keyX, String keyY);

    public native MSCryptKey getInitKey(int type, String data1, String data2);

    public native String getGmMiEt(String data);

    public native String getGmFaEt(String data, MSCryptKey keyObject);

    public native String getGmFaDt(String data, MSCryptKey keyObject);

    public native String getMiDsEt(int type, String data, MSCryptKey keyObject);

    public native String getMiDsDt(int type, String data, MSCryptKey keyObject);

    public native String getBaseEt(String data);

    public native String getBaseDt(String data);

    public native String getHasSeEt(String data);

    public native String getGmRiYan(String keyX, String keyY, String data,
                                    String signature);



    public native String getSeaDt(int type, String data, MSCryptKey keyObject);

    public native String getArsYan(String data, String modulus, String sigStr);


    //SM3
    private void test_sm3() {
        String getEt = getGmMiEt("param1");
        Toast.makeText(this, getEt, Toast.LENGTH_SHORT).show();
    }

    private void test_sm4() {
        MSCryptKey keyStr = getInitKey(1, "aaaaaa", "123456");
        String getEt = getGmFaEt("123456", keyStr);
        Toast.makeText(this, getEt, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_sm2:
                test_sm2();
                break;
            case R.id.btn_sm3:
                test_sm3();
                break;

        }
    }
}
