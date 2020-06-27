package com.example.p11_livedata;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class MyViewModel extends ViewModel {
    /*管理一个LiveData类型，不同于普通类型*/
    private MutableLiveData<Integer> number;

    public MyViewModel() {
        number = new MutableLiveData<>();
        number.setValue(0);
    }


    public void addNum(int n) {
        this.number.setValue(this.number.getValue() + n);
    }

    public void minusNum(int n) {
        this.number.setValue(this.number.getValue() - n);
    }


    public MutableLiveData<Integer> getNumber() {
        return number;
    }
}
