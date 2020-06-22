package com.wangjin.android.cusview;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import com.wangjin.bottomnavlib.BottomNavigation;
import com.wangjin.bottomnavlib.OnBottomNavSelectedListener;

public class BottomNavActivity extends AppCompatActivity implements OnBottomNavSelectedListener {
    private TextView mToolBarTitle;
    private BottomNavigation mBn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bottom_nav);
        initUi();
    }

    private void initUi() {
        mToolBarTitle = ((TextView) findViewById(R.id.toolbar_title));
        mToolBarTitle.setText("底部导航栏");
        mBn = ((BottomNavigation) findViewById(R.id.bn_test));
        mBn.setmSelectedListener(this);


    }

    @Override
    public void onValueSelected(int index) {
        Toast.makeText(this, "Radio Button被按下", Toast.LENGTH_SHORT).show();
    }
}
