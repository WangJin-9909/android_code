package com.example.p12_databinding;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;


import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.p12_databinding.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    private Button btnAdd;
    private MyViewModle myViewModle;
    private TextView textView;
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initUi();
        initData();

    }

    private void initData() {
        myViewModle = ViewModelProviders.of(this).get(MyViewModle.class);
        myViewModle.getNumber().observe(this, new Observer<Integer>() {
            @Override
            public void onChanged(Integer integer) {
                binding.tv.setText("改变后的数据 ： " + integer);
            }
        });


    }

    private void initUi() {
        setContentView(R.layout.activity_main);
        //使用DataBinding需要配置gradle哦
        //将xml布局文件转换形式，
        //Activity调用ActivityMainBinding
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main);
        binding.button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                myViewModle.add(1);
            }
        });


    }
}
