package com.example;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.os.Handler;
import android.widget.TextView;

import com.example.baidupic.MainActivity;
import com.example.baidupic.R;

public class SplashActivity extends Activity {
    private MyCountDownTimer myCountDownTimer;
    private TextView mTv_Splash;
    private Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);
        mTv_Splash = ((TextView) findViewById(R.id.tv_splash));
        myCountDownTimer = new MyCountDownTimer(3000, 1000);
        myCountDownTimer.start();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(SplashActivity.this, MainActivity.class);
              //  startActivity(intent);
            }
        }, 3000);
    }

    class MyCountDownTimer extends CountDownTimer {
        /**
         *
         * @param millisInFuture
         *      表示以毫秒为单位 倒计时的总数
         *
         *      例如 millisInFuture=1000 表示1秒
         *
         * @param countDownInterval
         *      表示 间隔 多少微秒 调用一次 onTick 方法
         *
         *      例如: countDownInterval =1000 ; 表示每1000毫秒调用一次onTick()
         *
         */
        public MyCountDownTimer(long millisInFuture, long countDownInterval) {
            super(millisInFuture, countDownInterval);
        }

        public void onFinish() {
            mTv_Splash.setText("正在跳转");
        }

        public void onTick(long millisUntilFinished) {
            mTv_Splash.setText("倒计时(" + millisUntilFinished / 1000 + ")");
        }

    }
}
