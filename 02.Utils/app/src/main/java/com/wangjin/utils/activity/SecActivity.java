package com.wangjin.utils.activity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.snail.antifake.jni.EmulatorDetectUtil;
import com.wangjin.utils.base.BaseActivity;
import com.wangjin.utils.R;

import androidx.annotation.Nullable;
import butterknife.BindView;
import butterknife.OnClick;

public class SecActivity extends BaseActivity {


    @Override
    protected int getLayoutResId() {
        return R.layout.activity_sec;


    }

    @OnClick({R.id.btn_get_emulator})
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_get_emulator:
                boolean emulator = EmulatorDetectUtil.isEmulator(SecActivity.this);
                Toast.makeText(SecActivity.this, "em = " + emulator, Toast.LENGTH_SHORT).show();
                break;
        }
    }


}
