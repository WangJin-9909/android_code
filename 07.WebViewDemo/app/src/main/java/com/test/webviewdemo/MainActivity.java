package com.test.webviewdemo;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.net.http.SslError;
import android.os.Bundle;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.webkit.ClientCertRequest;
import android.webkit.HttpAuthHandler;
import android.webkit.SslErrorHandler;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceError;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.Toast;


import java.io.IOException;

import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;

import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    WebView mWebView;
    Button mBtnLoad;
    WebViewClient mWebViewClient;
    private static final String TAG = "WebViewDemo";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        initData();
        initViews();


    }

    private void test() throws NoSuchAlgorithmException, KeyManagementException {
        SSLContext sslContext = SSLContext.getInstance("TLS");
        sslContext.init(null, null, null);


    }


    class CusWebViewClient extends WebViewClient {
        /**
         * 在加载超链接时回调过来；所以通过重写该方法，可以实现对网页中超链接的拦截
         *
         * @param view
         * @param url
         * @return
         */
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            Log.e(TAG, "url = " + url);
            return false;

            //return super.shouldOverrideUrlLoading(view, url);
        }

        /**
         * 在加载超链接时回调过来；所以通过重写该方法，可以实现对网页中超链接的拦截
         *
         * @param view
         * @param request
         * @return
         */
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, WebResourceRequest request) {
            Log.e(TAG, "request = " + request.getMethod());
            //return false;
            return super.shouldOverrideUrlLoading(view, request);
        }

        @Override
        public void onPageStarted(WebView view, String url, Bitmap favicon) {
            Log.e(TAG, "onPageStart....");
            super.onPageStarted(view, url, favicon);
        }

        @Override
        public void onPageFinished(WebView view, String url) {
            Log.e(TAG, "onPageFinished().....");
            super.onPageFinished(view, url);
        }

        @Override
        public void onLoadResource(WebView view, final String url) {

            Log.e(TAG, "onLoadResource()...." + url);

            super.onLoadResource(view, url);
        }

        @Override
        public void onPageCommitVisible(WebView view, String url) {
            Log.e(TAG, "onPageCommitVisible()...");
            super.onPageCommitVisible(view, url);
        }

        /**
         * 每一次请求资源时，都会通过这个函数回调
         *
         * @param view
         * @param
         * @return
         */
        @Override
        public WebResourceResponse shouldInterceptRequest(WebView view, WebResourceRequest request) {
            Log.e(TAG, "request = " + request.getUrl());
            Toast.makeText(MainActivity.this, "aaaaaaaaaaaaaaa", 1).show();
            /*if (false) {
                StringBuilder stringBuilder = new StringBuilder();
                BufferedReader bufferedReader = null;
                try {
                    URL url = new URL("https://m.baidu.com/");
                    HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();
                    httpURLConnection.setConnectTimeout(10 * 1000);
                    httpURLConnection.setReadTimeout(40 * 1000);
                    bufferedReader = new BufferedReader(new InputStreamReader(httpURLConnection.getInputStream()));
                    String line = "";
                    while ((line = bufferedReader.readLine()) != null)
                        stringBuilder.append(line);
                } catch (Exception e) {
                    e.printStackTrace();
                } finally {
                    if (bufferedReader != null)
                        try {
                            bufferedReader.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                }
                WebResourceResponse webResourceResponse = null;
                webResourceResponse = new WebResourceResponse("text/html", "utf-8", new ByteArrayInputStream(stringBuilder.toString().getBytes()));
                return webResourceResponse;
            }*/
            return super.shouldInterceptRequest(view, request);


        }

        @Override
        public WebResourceResponse shouldInterceptRequest(WebView view, String urlStr) {
            Log.e(TAG, "urlStr = " + urlStr);
            /*if (false) {
                StringBuilder stringBuilder = new StringBuilder();
                BufferedReader bufferedReader = null;
                try {
                    URL url = new URL("http://www.qq.com/");
                    HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();
                    httpURLConnection.setConnectTimeout(10 * 1000);
                    httpURLConnection.setReadTimeout(40 * 1000);
                    bufferedReader = new BufferedReader(new InputStreamReader(httpURLConnection.getInputStream()));
                    String line = "";
                    while ((line = bufferedReader.readLine()) != null)
                        stringBuilder.append(line);
                } catch (Exception e) {
                    e.printStackTrace();
                } finally {
                    if (bufferedReader != null)
                        try {
                            bufferedReader.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                }
                WebResourceResponse webResourceResponse = null;
                webResourceResponse = new WebResourceResponse("text/html", "utf-8", new ByteArrayInputStream(stringBuilder.toString().getBytes()));
                return webResourceResponse;
            }*/
            return super.shouldInterceptRequest(view, urlStr);

        }


        @Override
        public void onTooManyRedirects(WebView view, Message cancelMsg, Message continueMsg) {
            super.onTooManyRedirects(view, cancelMsg, continueMsg);
        }

        /**
         * 加载错误的时候会回调，在其中可做错误处理，比如再请求加载一次，或者提示404的错误页面
         *
         * @param view
         * @param errorCode
         * @param description
         * @param failingUrl
         */
        @Override
        public void onReceivedError(WebView view, int errorCode, String description, String failingUrl) {
            Log.e(TAG, "onReceivedError()..........");
            super.onReceivedError(view, errorCode, description, failingUrl);
        }

        /**
         * 加载错误的时候会回调，在其中可做错误处理，比如再请求加载一次，或者提示404的错误页面
         *
         * @param view
         * @param request
         * @param error
         */
        @Override
        public void onReceivedError(WebView view, WebResourceRequest request, WebResourceError error) {
            Log.e(TAG, "onReceivedError()........");

            super.onReceivedError(view, request, error);
        }

        @Override
        public void onReceivedHttpError(WebView view, WebResourceRequest request, WebResourceResponse errorResponse) {
            Log.e(TAG, "onReceivedHttpError()..........");
            super.onReceivedHttpError(view, request, errorResponse);
        }

        @Override
        public void onFormResubmission(WebView view, Message dontResend, Message resend) {
            Log.e(TAG, "onFormResubmission().........");
            super.onFormResubmission(view, dontResend, resend);
        }

        @Override
        public void doUpdateVisitedHistory(WebView view, String url, boolean isReload) {
            Log.e(TAG, "doUpdateVisitedHistory()........");
            super.doUpdateVisitedHistory(view, url, isReload);
        }

        /**
         * 当接收到https错误时，会回调此函数，在其中可以做错误处理
         *
         * @param view
         * @param handler
         * @param error
         */
        @Override
        public void onReceivedSslError(WebView view, SslErrorHandler handler, SslError error) {
            Log.e(TAG, "onReceivedSslError()........");
            //如果下面的代码注释掉，页面不会显示出来
            //handler.proceed();

            Toast.makeText(getApplicationContext(), "onReceiveSslError", Toast.LENGTH_SHORT).show();
            StackTraceElement stack[] = Thread.currentThread().getStackTrace();

            for (int i = 0; i < stack.length; i++) {
                Log.e(TAG,stack[i].getClassName() + " 。" + stack[i].getMethodName() + "-----");
            }

            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }



            try {
                if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.Q) {
                    X509Certificate x509Certificate = error.getCertificate().getX509Certificate();
                }
                throw new Exception("abcdefghijklmn");
            } catch (Exception e) {
                e.printStackTrace();
            }


            super.onReceivedSslError(view, handler, error);

        }

        @Override
        public void onReceivedClientCertRequest(WebView view, ClientCertRequest request) {
            Log.e(TAG, "onReceivedClientCertRequest().......");
            super.onReceivedClientCertRequest(view, request);
        }

        @Override
        public void onReceivedHttpAuthRequest(WebView view, HttpAuthHandler handler, String host, String realm) {
            Log.e(TAG, "onReceivedHttpAuthRequest().........");
            super.onReceivedHttpAuthRequest(view, handler, host, realm);
        }

        @Override
        public boolean shouldOverrideKeyEvent(WebView view, KeyEvent event) {
            Log.e(TAG, "shouldOverrideKeyEvent()..........");
            return super.shouldOverrideKeyEvent(view, event);
        }

        @Override
        public void onUnhandledKeyEvent(WebView view, KeyEvent event) {
            Log.e(TAG, "onUnhandledKeyEvent().......");
            super.onUnhandledKeyEvent(view, event);
        }

        @Override
        public void onScaleChanged(WebView view, float oldScale, float newScale) {
            Log.e(TAG, "onScaleChanged()........");
            super.onScaleChanged(view, oldScale, newScale);
        }

        @Override
        public void onReceivedLoginRequest(WebView view, String realm, @Nullable String account, String args) {
            Log.e(TAG, "onReceivedLoginRequest().........");
            super.onReceivedLoginRequest(view, realm, account, args);
        }
    }

    ;

    class CusWebChromClient extends WebChromeClient {
        @Override
        public void onReceivedTitle(WebView view, String title) {
            super.onReceivedTitle(view, title);
        }
    }

    private void initData() {
        mWebViewClient = new CusWebViewClient();

    }

    private void initViews() {

        setContentView(R.layout.activity_main);
        mBtnLoad = findViewById(R.id.btn_load);
        mWebView = findViewById(R.id.web_view);
        mWebView.setWebViewClient(mWebViewClient);
        //mWebView.loadUrl(url);


        findViewById(R.id.btn_local_cer).setOnClickListener(this);
        findViewById(R.id.btn_url_cer).setOnClickListener(this);
        findViewById(R.id.btn_load).setOnClickListener(this);
    }

    String url_1 = "https://118.89.58.21:8081/ssl1";
    String url_2 = "https://118.89.58.21:8082/ssl2";
    String url_3 = "https://mybank.icbc.com.cn/icbc/newperbank/perbank3/frame/frame_index.jsp";
    String url_4 = "http://sp0.baidu.com/";

    @Override
    public void onClick(View view) {
        final CerUtils cu = new CerUtils();
        switch (view.getId()) {
            case R.id.btn_load:
                mWebView.loadUrl(url_1);
                break;
            case R.id.btn_local_cer:
                try {
                    cu.getLocalCer(MainActivity.this, "server.cer");
                } catch (CertificateException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                break;
            //通过网络请求
            case R.id.btn_url_cer:
                new Thread() {
                    @Override
                    public void run() {
                        super.run();

                        try {
                            cu.getUrlCer(url_1);
                        } catch (IOException e) {
                            e.printStackTrace();
                        } catch (NoSuchAlgorithmException e) {
                            e.printStackTrace();
                        } catch (KeyManagementException e) {
                            e.printStackTrace();
                        }
                    }
                }.start();


                break;
        }
    }
}