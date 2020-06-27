package com.example.p11_livedata;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;
import androidx.lifecycle.ViewModelProviders;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private TextView tv;
    private Button btnAdd, btnMinus;
    private MyViewModel myViewModel;
    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        initUi();

        initData();

    }


    private void initData() {

        myViewModel = ViewModelProviders.of(this).get(MyViewModel.class);
        /*设置观察数据的改变*/
        myViewModel.getNumber().observe(this, new Observer<Integer>() {
            @Override
            public void onChanged(Integer integer) {
                Log.e(TAG, "Model层数据改变了");
                tv.setText("改变后的数据 " + integer);
            }
        });

    }

    private void initUi() {
        setContentView(R.layout.activity_main);
        tv = findViewById(R.id.tv);
        btnAdd = findViewById(R.id.btn_add);
        btnMinus = findViewById(R.id.btn_minus);

        btnMinus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                myViewModel.minusNum(1);
            }
        });
        btnAdd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                myViewModel.addNum(1);
            }
        });
    }
}
