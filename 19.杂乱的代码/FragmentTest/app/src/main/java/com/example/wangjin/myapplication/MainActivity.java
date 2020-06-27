package com.example.wangjin.myapplication;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements MainFragment.OnFragmentInteractionListener {
    private FragmentManager fm;
    private Fragment mMainFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        initUI();

    }

    private void initUI() {
        setContentView(R.layout.activity_main);
        TextView tv = (TextView) findViewById(R.id.toolbar_title);
        tv.setText("使用支持库Fragment");
        findViewById(R.id.btn_use_std).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, Main2Activity.class));
            }
        });

        fm = getSupportFragmentManager();
        mMainFragment = fm.findFragmentById(R.id.fragment_main_container);
        if (mMainFragment == null) {
            mMainFragment = new MainFragment();
            fm.beginTransaction()
                    .add(R.id.fragment_main_container, mMainFragment)
                    .commit();
        }


    }

    @Override
    public void onFragmentInteraction(Uri uri) {

    }
}
