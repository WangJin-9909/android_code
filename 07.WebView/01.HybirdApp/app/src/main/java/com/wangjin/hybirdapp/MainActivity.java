package com.wangjin.hybirdapp;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.webkit.JavascriptInterface;
import android.webkit.JsPromptResult;
import android.webkit.JsResult;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceError;
import android.webkit.WebResourceRequest;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;

import java.util.Map;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private WebView mWebView;
    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initView();

    }

    private void initView() {
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_test_1).setOnClickListener(this);
        findViewById(R.id.btn_test_2).setOnClickListener(this);

        mWebView = findViewById(R.id.web_view);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_test_1:
                loadWebView();

                break;
            case R.id.btn_test_2:
                loadLocalWebView();
                break;
        }
    }

    /**
     * 加载本地Html文件
     */
    private void loadLocalWebView() {
        mWebView.loadUrl("file:///android_asset/index.html");
        mWebView.setWebChromeClient(wcClient);
        mWebView.setWebViewClient(wbClient);
        mWebView.getSettings().setJavaScriptEnabled(true);
        mWebView.addJavascriptInterface(new MJavaScriptInterface(this), "android");
    }

    /**
     * 载入WebView的方法有如下几种
     * 1.loadUrl()
     * |---加载本地页面,随着app打包昂;loadUrl("file:///android_asset/test.html")
     * |---加载服务器远程页面：如，loadUrl("http://www.baidu.com")
     * |---加载手机本地的页面，SD卡的页面
     * <p>
     * 2.loadData()
     * |---加载一段html代码
     */
    private void loadWebView() {
        mWebView.setWebChromeClient(wcClient);
        mWebView.setWebViewClient(wbClient);
        initWebViewSettings(mWebView.getSettings());
        mWebView.loadUrl("https://m.jd.com");

    }


    private WebViewClient wbClient = new WebViewClient() {
        @Override
        public void onLoadResource(WebView view, String url) {
            super.onLoadResource(view, url);
            Log.e(TAG, "---------------       onLoadResource()       ----------------");
            Log.e(TAG, "resource = " + url.toString());
        }

        @Override
        public void onPageStarted(WebView view, String url, Bitmap favicon) {
            super.onPageStarted(view, url, favicon);
            Log.e(TAG, "---------------       onPageStarted()       ----------------");

        }


        @Override
        public void onPageFinished(WebView view, String url) {
            super.onPageFinished(view, url);
            Log.e(TAG, "---------------       onPageFinished()       ----------------");
        }


        @Override
        public void onReceivedError(WebView view, WebResourceRequest request, WebResourceError error) {
            super.onReceivedError(view, request, error);
            Log.e(TAG, "---------------       onReceivedError()       ----------------");
        }


    };
    private WebChromeClient wcClient = new WebChromeClient() {

        @Override
        public void onProgressChanged(WebView view, int newProgress) {
            super.onProgressChanged(view, newProgress);
            Log.e(TAG, "newProgress = " + newProgress);
        }

        @Override
        public void onReceivedTitle(WebView view, String title) {
            super.onReceivedTitle(view, title);
            Log.e(TAG, "title = " + title);
        }

        @Override
        public boolean onJsAlert(WebView view, String url, String message, final JsResult result) {
            Log.e(TAG, "onJsAlert   --  message = " + message);
            new AlertDialog.Builder(MainActivity.this).setTitle("Java中设置标题").setMessage(message).setPositiveButton("确定_JIN", new AlertDialog.OnClickListener() {
                public void onClick(DialogInterface dialog, int which) {
                    result.confirm();
                }
            }).setCancelable(false).create().show();

            return true;

        }


        @Override
        public boolean onJsPrompt(WebView view, String url, String message, String defaultValue, JsPromptResult result) {
            Log.e(TAG, "onJsPrompt   --->  url = " + url + "message = " + message + "defaultValue = " + defaultValue);
            result.confirm("可以通过result设置JS的Prompt内容");
            return true;

        }
    };

    class MJavaScriptInterface {
        private Context mContext;

        public MJavaScriptInterface(Context mContext) {
            this.mContext = mContext;
        }

        @JavascriptInterface
        public void showToast(String str) {
            Toast.makeText(mContext, str, Toast.LENGTH_SHORT).show();
        }
    }

    private void initWebViewSettings(WebSettings settings) {
        //设置支持JavaScript
        settings.setJavaScriptEnabled(true);
        //设置自适应屏幕，下面2个合着用
        settings.setUseWideViewPort(true);//将图片调整合适WebView的大小
        settings.setLoadWithOverviewMode(true);//缩放至屏幕大小
        //设置缩放操作
        settings.setSupportZoom(true);//支持缩放，默认为true，是下面的前提
        settings.setBuiltInZoomControls(true);//设置内置控件缩放，false则表示webView不可缩放
        settings.setDisplayZoomControls(false);//隐藏原生的缩放控件
        //其它戏界操作
        settings.setCacheMode(WebSettings.LOAD_CACHE_ELSE_NETWORK);//关闭WebView缓冲
        settings.setAllowFileAccess(true);//设置可以访问文件
        settings.setJavaScriptCanOpenWindowsAutomatically(true);//支持通过js打开新窗口
        settings.setLoadsImagesAutomatically(true);//支持自动加载图片
        settings.setDefaultTextEncodingName("UTF-8");//设置编码格式


    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK && mWebView.canGoBack()) {
            mWebView.goBack();
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
}
