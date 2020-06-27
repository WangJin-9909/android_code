package com.example.wangjin.daggertest.test03;

import com.example.wangjin.daggertest.MainActivity;

import dagger.Component;

@Component(modules = BeanModule.class)
public interface BeanTest03Component {
    void injectTest03(MainActivity activity);
}
