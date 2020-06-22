package com.wangjin.utils;

import androidx.appcompat.app.AppCompatActivity;
import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import butterknife.Unbinder;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.provider.Settings;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.wangjin.BaseActiivty;

import java.io.IOException;

public class AssetActivity extends BaseActiivty {
    Unbinder mUnbinder;
    @BindView(R.id.btn_asset_test)
    Button btnAssetTest;
    @BindView(R.id.tool_bar_title)
    TextView toolBatTitle;
    @BindView(R.id.btn_copy_mp3)
    Button btmCopyMp3;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initUi();


    }

    private void initUi() {
        setContentView(R.layout.activity_asset);
        mUnbinder = ButterKnife.bind(this);
        toolBatTitle.setText("Asset工具");
    }


    private void testAsset() {
        try {
            String[] fileListFromAsset = com.wangjin.glidedemo.utils.AssestUtils.getFileListFromAsset(this);
            Dialog dialog = new Dialog(this);
            dialog.setContentView(R.layout.dialoag_list);
            TextView tv = (TextView) dialog.findViewById(R.id.dialog_tv);
            for (String str : fileListFromAsset) {
                tv.append(str);
                tv.append(System.getProperty("line.separator"));
            }
            dialog.show();
        } catch (IOException e) {
            Toast.makeText(this, e.getMessage() + " ", Toast.LENGTH_SHORT).show();
        }
    }


    @OnClick({R.id.btn_asset_test, R.id.btn_linsi_test, R.id.btn_copy_mp3})
    public void onUiClick(View view) {
        switch (view.getId()) {
            case R.id.btn_asset_test:
                testAsset();
                break;
            case R.id.btn_linsi_test:
                testDialog();
                break;
            case R.id.btn_copy_mp3:
                copyMp3();
                break;

        }


    }

    private void copyMp3() {
        try {
            com.wangjin.glidedemo.utils.AssestUtils.copyAssetFileToDest(this, "mp3/test.mp3", Environment.getExternalStorageDirectory() + "/test.mp3");
        } catch (IOException e) {

            DialogUtils.showDialog(this, "复制出错", e.getMessage(), "确认", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss();
                }
            }, "取消", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss();
                }
            });
            e.printStackTrace();


        }


    }


    private void showDialog(String title, String content, String positiveTitle, DialogInterface.OnClickListener
            positiveListener, String negativeTitle, DialogInterface.OnClickListener negativeListener) {
        new AlertDialog.Builder(this)
                .setTitle(title)
                .setMessage(content)
                .setPositiveButton(positiveTitle, positiveListener)
                .setNegativeButton(negativeTitle, negativeListener).show();
    }


    private void testDialog() {
        showDialog("标题", "内容", "确认", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                SettingUtils.startSetting(AssetActivity.this, SettingUtils.FLAG_SETTINT_WIFI);
            }
        }, "取消", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.cancel();
            }
        });
    }


}























