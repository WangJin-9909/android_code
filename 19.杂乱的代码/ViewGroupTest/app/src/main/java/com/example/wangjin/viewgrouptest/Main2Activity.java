package com.example.wangjin.viewgrouptest;

import android.graphics.drawable.AnimationDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

public class Main2Activity extends AppCompatActivity {
    private TextView status_text;
    private ImageView ren;
    private ImageView hezi;
    private int viewHeight;
    private ImageView donghua;
    private AnimationDrawable drawable;
    private boolean isDown = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        status_text = (TextView) findViewById(R.id.status_test);
        ren = (ImageView) findViewById(R.id.ren);
        hezi = (ImageView) findViewById(R.id.hezi);
        donghua = (ImageView) findViewById(R.id.donghua);
        drawable = (AnimationDrawable) donghua.getDrawable();


        findViewById(R.id.btn_start).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                status_text.setText("松开刷新...");
                drawable.start();
                donghua.setVisibility(View.VISIBLE);
                ren.setVisibility(View.VISIBLE);
                hezi.setVisibility(View.VISIBLE);
            }
        });


        findViewById(R.id.btn_end).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                status_text.setText("更新中...");
                drawable.stop();
            }
        });


        findViewById(R.id.btn_test1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                drawable.start();
                donghua.setVisibility(View.VISIBLE);
                ren.setVisibility(View.VISIBLE);
                hezi.setVisibility(View.VISIBLE);
            }
        });

        findViewById(R.id.btn_test2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (isDown) {
                    status_text.setText("松开刷新...");
                } else {
                    status_text.setText("下拉刷新...");

                }
                isDown = !isDown;
            }
        });

        findViewById(R.id.btn_test3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ren.setVisibility(View.GONE);
                hezi.setVisibility(View.GONE);
                donghua.setVisibility(View.VISIBLE);
                drawable.start();
                status_text.setText("更新中...");
            }
        });

        findViewById(R.id.btn_test4).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });

        findViewById(R.id.btn_test5).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });
    }
}
