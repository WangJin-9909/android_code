package com.wangjin.utils.activity;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import butterknife.Unbinder;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.wangjin.utils.R;
import com.wangjin.utils.activity.AssetActivity;
import com.wangjin.utils.activity.SecActivity;
import com.wangjin.utils.base.BaseActivity;

public class MainActivity extends BaseActivity {
    @BindView(R.id.btn_asset)
    Button btnAsset;
    @BindView(R.id.tool_bar_title)
    TextView tvToolTitle;
    @BindView(R.id.toolbar_main)
    Toolbar toolbar;


    @Override
    protected void initUi() {
        super.initUi();
        tvToolTitle.setText("工具大全");

    }

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_main;
    }

    @OnClick({R.id.btn_asset, R.id.toolbar_main, R.id.btn_det_emulator, R.id.btn_det_five_generation})
    public void onUiClick(View view) {
        switch (view.getId()) {
            case R.id.btn_asset:
                startActivity(new Intent(this, AssetActivity.class));
                break;
            case R.id.btn_ui:
                break;
            case R.id.btn_det_emulator:
                startActivity(new Intent(this, SecActivity.class));
                break;
            case R.id.btn_det_five_generation:
                startActivity(new Intent(this, NetWorkActivity.class));
                break;

        }
    }
}
