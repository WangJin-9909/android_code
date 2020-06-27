package com.test.webviewdemo;


import android.os.Bundle;
import android.webkit.WebViewClient;

import androidx.appcompat.app.AppCompatActivity;

public class CusWebViewActivity extends AppCompatActivity {
    private CusWebView mWebView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initViews();

    }

    private void initViews() {
        setContentView(R.layout.activity_cus_web_view);
        mWebView = findViewById(R.id.cus_web_view);
        mWebView.setWebViewClient(new WebViewClient());
        mWebView.loadUrl("https://www.qq.com");

    }
}
