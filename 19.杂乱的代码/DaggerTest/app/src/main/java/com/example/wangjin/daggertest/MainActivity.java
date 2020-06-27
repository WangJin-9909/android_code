package com.example.wangjin.daggertest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;


import com.example.wangjin.daggertest.test03.BeanNeedParam;
import com.example.wangjin.daggertest.test03.DaggerBeanTest03BeanComponent;
import com.example.wangjin.daggertest.test03.DaggerBeanTest03Component;

import javax.inject.Inject;

public class MainActivity extends AppCompatActivity {
    /* @Inject
     Pot pot;
     @Inject
     BeanForDagger beanForDagger;*/
    @Inject
    BeanNeedParam beanNeedParam;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        test03();
    }

/*    private void test01() {
        DaggerMainActivityComponent.create().injectInstance(this);
        String show = pot.show();
        Toast.makeText(MainActivity.this, show, Toast.LENGTH_SHORT).show();
    }

    private void test02() {
        DaggerBeanComponent.create().inject(this);
        String str = beanForDagger.getName();
        Toast.makeText(MainActivity.this, str, Toast.LENGTH_SHORT).show();

    }*/

    private void test03() {
        DaggerBeanTest03Component.create().injectTest03(this);

        String str = beanNeedParam.getName();
        Toast.makeText(MainActivity.this, str, Toast.LENGTH_SHORT).show();

    }
}
