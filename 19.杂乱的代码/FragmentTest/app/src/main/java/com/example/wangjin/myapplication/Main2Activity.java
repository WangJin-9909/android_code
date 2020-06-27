package com.example.wangjin.myapplication;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;

import android.os.Bundle;
import android.widget.TextView;

public class Main2Activity extends Activity {
    private FragmentManager fm;
    private Fragment mMainFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        initUi();


    }

    private void initUi() {
        setContentView(R.layout.activity_main2);
        TextView tv = (TextView) findViewById(R.id.toolbar_title);
        tv.setText("使用标准库实现");


        fm = getFragmentManager();
        mMainFragment = new Main2Fragment();
        if (mMainFragment == null) {
            mMainFragment = new Main2Fragment();
            fm.beginTransaction()
                    .add(R.id.fragment_main_container, mMainFragment)
                    .commit();
        }

    }
}
