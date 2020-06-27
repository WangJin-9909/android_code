package com.test.webviewdemo;

import android.content.Context;
import android.net.http.SslCertificate;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import java.security.cert.CertificateExpiredException;
import java.security.cert.CertificateNotYetValidException;

import androidx.annotation.Nullable;

public class CusWebView extends WebView {
    private static final String TAG = CusWebView.class.getSimpleName();
    public CusWebView(Context context) {
        super(context);
    }

    public CusWebView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public CusWebView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    public void setWebViewClient(WebViewClient client) {
        super.setWebViewClient(client);
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        Log.e(TAG, "-----------------event-----------------");
        Log.e(TAG, "url = " + getUrl());
        Log.e(TAG, "Ourl = " + getOriginalUrl());




        return super.onTouchEvent(event);
    }

    @Override
    public String getUrl() {
        Log.e(TAG, "url ==========================>" );
        return super.getUrl();
    }

    @Nullable
    @Override
    public SslCertificate getCertificate() {
        return super.getCertificate();
    }

    @Override
    public void loadUrl(String url) {
        super.loadUrl(url);


    }
}
