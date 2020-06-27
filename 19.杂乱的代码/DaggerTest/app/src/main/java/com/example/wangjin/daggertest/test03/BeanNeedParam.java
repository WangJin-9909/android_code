package com.example.wangjin.daggertest.test03;


public class BeanNeedParam {
    private String mName = null;


    public BeanNeedParam(String name) {
        this.mName = name;
    }

    public String getName() {
        return mName;
    }
}
