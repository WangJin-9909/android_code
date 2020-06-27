package com.example.p12_databinding;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class MyViewModle extends ViewModel {
    /*要管理的变量*/
    private MutableLiveData<Integer> number;

    public MyViewModle() {
        number = new MutableLiveData<>();
        number.setValue(0);
    }

    public MutableLiveData<Integer> getNumber() {
        return number;
    }

    public void add(int n) {
        this.number.setValue(number.getValue() + n);
    }
}
