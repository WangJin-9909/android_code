package com.wangjin.utils;

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

public class MainActivity extends AppCompatActivity {
    @BindView(R.id.btn_asset)
    Button btnAsset;
    @BindView(R.id.tool_bar_title)
    TextView tvToolTitle;
    @BindView(R.id.toolbar_main)
    Toolbar toolbar;
    Unbinder mUnBinder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        initUi();


    }

    private void initUi() {

        setContentView(R.layout.activity_main);
        mUnBinder = ButterKnife.bind(this);
        tvToolTitle.setText("工具大全");

    }

    @OnClick({R.id.btn_asset, R.id.toolbar_main})
    public void onUiClick(View view) {
        switch (view.getId()) {
            case R.id.btn_asset:
                startActivity(new Intent(this, AssetActivity.class));
                break;
            case R.id.btn_ui:
                break;
        }
    }
}
