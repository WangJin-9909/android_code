package com.example.ndkdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView tv_sample_text;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        initUi();


    }

    private void initUi() {
        findViewById(R.id.btn_c1).setOnClickListener(this);
        tv_sample_text = findViewById(R.id.sample_text);
        tv_sample_text.setText(stringFromJNI());

    }



    public native String stringFromJNI();
    public native String test();



    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_c1:
                String test = test();
                Toast.makeText(this, test, Toast.LENGTH_SHORT).show();

                break;
        }
    }
}
