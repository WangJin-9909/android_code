package com.wangjin.bottomnavlib;

import android.content.Context;
import android.provider.MediaStore;
import android.util.AttributeSet;
import android.view.View;
import android.widget.RadioButton;
import android.widget.RelativeLayout;

import androidx.appcompat.widget.AppCompatRadioButton;

public class BottomNavigation extends RelativeLayout {
    protected OnBottomNavSelectedListener mSelectedListener;
    private RadioButton mRadioButton1;
    private RadioButton mRadioButton2;
    private RadioButton mRadioButton3;
    private RadioButton mRadioButton4;

    public BottomNavigation(Context context) {
        super(context);
        initView(context);
    }

    public BottomNavigation(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView(context);
    }

    public BottomNavigation(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView(context);
    }

    private void initView(Context context) {
        View view = inflate(context, R.layout.bottom_navigation, this);
        mRadioButton1 = ((RadioButton) findViewById(R.id.rb_1));
        mRadioButton2 = ((RadioButton) findViewById(R.id.rb_2));
        mRadioButton3 = ((RadioButton) findViewById(R.id.rb_3));
        mRadioButton4 = ((RadioButton) findViewById(R.id.rb_4));

        mRadioButton1.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mSelectedListener.onValueSelected(0);
            }
        });

        mRadioButton2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mSelectedListener.onValueSelected(1);
            }
        });

        mRadioButton3.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mSelectedListener.onValueSelected(2);
            }
        });

        mRadioButton4.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                mSelectedListener.onValueSelected(3);
            }
        });
    }

    public void setmSelectedListener(OnBottomNavSelectedListener mSelectedListener) {
        this.mSelectedListener = mSelectedListener;
    }


}
