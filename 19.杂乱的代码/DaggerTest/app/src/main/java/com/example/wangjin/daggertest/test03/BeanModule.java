package com.example.wangjin.daggertest.test03;

import dagger.Module;
import dagger.Provides;

@Module
public class BeanModule {

    @Provides
    public BeanNeedParam providerBean() {
        BeanNeedParam bean = new BeanNeedParam("BeanWithParam");
        return bean;
    }
}
