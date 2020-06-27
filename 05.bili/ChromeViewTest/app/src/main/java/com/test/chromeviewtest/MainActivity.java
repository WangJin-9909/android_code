package com.test.chromeviewtest;

import androidx.appcompat.app.AppCompatActivity;

import android.net.http.SslError;
import android.os.Bundle;
import android.webkit.SslErrorHandler;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private String version;
    private TextView tvVersion;
    private WebView mWeb;
    //private String url = "https://129.28.184.240:8443/icbc-captcha/demo.html";
    //private String url = "https://192.168.0.100:8443/icbc-captcha/demo.html";
    private String url = "https://192.168.31.165:8443/sensor_update/test.html";
    //private String url = "http://sp0.baidu.com/";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        version = new WebView(getApplicationContext()).getSettings().getUserAgentString();
        initUi();
        initData();
    }

    private void initData() {


    }

    private void initUi() {
        tvVersion = findViewById(R.id.tv_version);
        tvVersion.setText("WebView版本： " + version);
        mWeb = findViewById(R.id.web_view);
        mWeb.setWebViewClient(new WebViewClient() {
            @Override
            public void onReceivedSslError(WebView view, SslErrorHandler handler, SslError error) {
                handler.proceed();
            }
        });


        WebSettings webSettings = mWeb.getSettings();
        webSettings.setJavaScriptCanOpenWindowsAutomatically(true);
        webSettings.setJavaScriptEnabled(true);
        mWeb.setWebContentsDebuggingEnabled(true);
        webSettings.setJavaScriptCanOpenWindowsAutomatically(true);
        webSettings.setCacheMode(WebSettings.LOAD_NO_CACHE);
        mWeb.loadUrl(url);
    }
}
