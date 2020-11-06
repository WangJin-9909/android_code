package com.wangjin.utils.activity;

import androidx.appcompat.app.AppCompatActivity;
import butterknife.BindView;
import butterknife.OnClick;

import android.app.Application;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.wangjin.utils.R;
import com.wangjin.utils.base.BaseActivity;
import com.wangjin.utils.utils.NetWorkUtils;

public class NetWorkActivity extends BaseActivity {
    /*@BindView(R.id.btn_det_5g)
    Button btn5G;*/

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_net_work;
    }

    Application

    @OnClick({R.id.btn_det_5g})
    public void onClick(View view){
        switch (view.getId()){
            case R.id.btn_det_5g:
                String netWorkClass = NetWorkUtils.GetNetworkType(getApplication());
                Toast.makeText(this, "netWorkClass = " + netWorkClass, Toast.LENGTH_SHORT).show();
//                NetWorkUtils.is5GNetWork(getApplication());

                break;

        }
    }
}
