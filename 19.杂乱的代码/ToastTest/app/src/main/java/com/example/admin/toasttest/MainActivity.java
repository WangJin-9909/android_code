package com.example.admin.toasttest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.Gravity;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private TextView mTvToolBarTitle;
    private Toolbar mTooBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initUI();

    }

    private void initUI() {
        setContentView(R.layout.activity_main);
        mTvToolBarTitle = ((TextView) findViewById(R.id.toolbar_title));
        mTooBar = (Toolbar) findViewById(R.id.toolbar);
        mTvToolBarTitle.setText("Toast演示");







        findViewById(R.id.btn_middle).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "在默认位置显示", Toast.LENGTH_SHORT).show();
            }
        });

        findViewById(R.id.btn_bottom).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast toast = Toast.makeText(MainActivity.this, "在bottom显示", Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.BOTTOM, 0, 0);
                toast.show();
            }
        });

        findViewById(R.id.btn_top).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast toast = Toast.makeText(MainActivity.this, "在bottom显示", Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.TOP, 0, 0);
                toast.show();
            }
        });
    }
}
