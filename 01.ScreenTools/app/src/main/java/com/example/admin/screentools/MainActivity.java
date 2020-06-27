package com.example.admin.screentools;

import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ((TextView) findViewById(R.id.toolbar_title)).setText("屏幕相关工具");
        findViewById(R.id.btn_getdisplay_metric).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int sw = MainActivity.this.getResources().getConfiguration().smallestScreenWidthDp;
                showAlert("屏幕密度：", "sw = " + sw + "\n");

            }
        });


        findViewById(R.id.btn_getdisplay_pixel).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DisplayMetrics dm = MainActivity.this.getResources().getDisplayMetrics();
                int height = dm.heightPixels;
                int width = dm.widthPixels;
                showAlert("屏幕分辨率：", "width = " + width + "\n" + "height = " + height + "\n");
            }
        });


    }


    private void showAlert(String title, String msg) {
        AlertDialog.Builder b = new AlertDialog.Builder(this);
        b.setTitle(title);
        b.setMessage(msg);
        b.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        }).show();
    }
}
