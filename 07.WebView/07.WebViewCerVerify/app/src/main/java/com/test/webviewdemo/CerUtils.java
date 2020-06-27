package com.test.webviewdemo;


import android.content.Context;
import android.util.Log;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLPeerUnverifiedException;
import javax.net.ssl.SSLSession;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import java.security.PrivateKey;
import java.security.Provider;
import java.security.PublicKey;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.security.interfaces.RSAPublicKey;
import java.text.SimpleDateFormat;
import java.util.Base64;
import java.util.Date;

public class CerUtils {
    public static final String TAG = CerUtils.class.getSimpleName();
    public Context mContext;

    public void getLocalCer(Context context, String cerFile) throws CertificateException, IOException {
        this.mContext = context;
        X509Certificate x509Certificate = null;
        CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
        InputStream in = mContext.getAssets().open(cerFile);
        x509Certificate = (X509Certificate) certificateFactory.generateCertificate(in);
        in.close();

        Log.e(TAG, "x509Certificate_SerialNumber_序列号___:   " + x509Certificate.getSerialNumber());
        Log.e(TAG, "x509Certificate_getIssuerDN_发布方标识名___   :" + x509Certificate.getIssuerDN());
        Log.e(TAG, "x509Certificate_getSubjectDN_主体标识___:   " + x509Certificate.getSubjectDN());
        Log.e(TAG, "x509Certificate_getSigAlgOID_证书算法OID字符串___:   " + x509Certificate.getSigAlgOID());
        Log.e(TAG, "x509Certificate_getNotBefore_证书有效期___:   " + x509Certificate.getNotAfter());
        Log.e(TAG, "x509Certificate_getSigAlgName_签名算法___:   " + x509Certificate.getSigAlgName());
        Log.e(TAG, "x509Certificate_getVersion_版本号___:   " + x509Certificate.getVersion());
        Log.e(TAG, "x509Certificate_getPublicKey_公钥___:   " + x509Certificate.getPublicKey());
        RSAPublicKey publicKey = (RSAPublicKey) x509Certificate.getPublicKey();
        Log.e(TAG, "公钥    ：" + publicKey.getModulus().toString(16));


    }


    public void getUrlCer(String strUrl) throws IOException, NoSuchAlgorithmException, KeyManagementException {
        HttpsURLConnection.setDefaultHostnameVerifier(new NullHostNameVerifier());
        SSLContext sc = SSLContext.getInstance("TLS");
        sc.init(null, trustAllCerts, new SecureRandom());
        HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
        URL url = new URL(strUrl);
        // 打开restful链接
        HttpsURLConnection conn = (HttpsURLConnection) url.openConnection();
        conn.setRequestMethod("GET");// POST GET PUT DELETE
        // 设置访问提交模式，表单提交
        conn.setRequestProperty("Content-Type", "application/json;charset=utf-8");
        conn.setConnectTimeout(130000);// 连接超时 单位毫秒
        conn.setReadTimeout(130000);// 读取超时 单位毫秒
        // 读取请求返回值
        byte bytes[] = new byte[1024];
        InputStream inStream = conn.getInputStream();
        //inStream.read(bytes, 0, 1024);
        //Log.e(new String(bytes, "utf-8"));

        for (Certificate certificate : conn.getServerCertificates()) {
            // 第一个就是服务器本身证书，后续的是证书链上的其他证书
            X509Certificate x509Certificate = (X509Certificate) certificate;
            Log.e(TAG, x509Certificate.getSubjectDN() + "");
            Log.e(TAG, x509Certificate.getNotBefore() + "");// 有效期开始时间
            Log.e(TAG, x509Certificate.getNotAfter() + "");// 有效期结束时间
            Log.e(TAG, "x509Certificate_SerialNumber_序列号___:   " + x509Certificate.getSerialNumber());
            Log.e(TAG, "x509Certificate_getIssuerDN_发布方标识名___   :" + x509Certificate.getIssuerDN());
            Log.e(TAG, "x509Certificate_getSubjectDN_主体标识___:   " + x509Certificate.getSubjectDN());
            Log.e(TAG, "x509Certificate_getSigAlgOID_证书算法OID字符串___:   " + x509Certificate.getSigAlgOID());
            Log.e(TAG, "x509Certificate_getNotBefore_证书有效期___:   " + x509Certificate.getNotAfter());
            Log.e(TAG, "x509Certificate_getSigAlgName_签名算法___:   " + x509Certificate.getSigAlgName());
            Log.e(TAG, "x509Certificate_getVersion_版本号___:   " + x509Certificate.getVersion());
            Log.e(TAG, "x509Certificate_getPublicKey_公钥___:   " + x509Certificate.getPublicKey());
        }
        conn.disconnect();


    }

    public String getSerial(String strUrl) throws IOException, NoSuchAlgorithmException, KeyManagementException {
        HttpsURLConnection.setDefaultHostnameVerifier(new NullHostNameVerifier());
        SSLContext sc = SSLContext.getInstance("TLS");
        sc.init(null, trustAllCerts, new SecureRandom());
        HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());
        URL url = new URL(strUrl);
        // 打开restful链接
        HttpsURLConnection conn = (HttpsURLConnection) url.openConnection();
        conn.setRequestMethod("GET");// POST GET PUT DELETE
        // 设置访问提交模式，表单提交
        conn.setRequestProperty("Content-Type", "application/json;charset=utf-8");
        conn.setConnectTimeout(130000);// 连接超时 单位毫秒
        conn.setReadTimeout(130000);// 读取超时 单位毫秒
        // 读取请求返回值
        byte bytes[] = new byte[1024];
        InputStream inStream = conn.getInputStream();
        X509Certificate x509Certificate = (X509Certificate) conn.getServerCertificates()[0];
        Log.e(TAG, "服务器证书   ：   x509Certificate.getSerialNumber()");
        conn.disconnect();
        return x509Certificate.getSerialNumber() + "";

        /*for (Certificate certificate : conn.getServerCertificates()) {
            // 第一个就是服务器本身证书，后续的是证书链上的其他证书
            X509Certificate x509Certificate = (X509Certificate) certificate;
            Log.e(TAG, x509Certificate.getSubjectDN() + "");
            Log.e(TAG, x509Certificate.getNotBefore() + "");// 有效期开始时间
            Log.e(TAG, x509Certificate.getNotAfter() + "");// 有效期结束时间
            Log.e(TAG, "x509Certificate_SerialNumber_序列号___:   " + x509Certificate.getSerialNumber());
            Log.e(TAG, "x509Certificate_getIssuerDN_发布方标识名___   :" + x509Certificate.getIssuerDN());
            Log.e(TAG, "x509Certificate_getSubjectDN_主体标识___:   " + x509Certificate.getSubjectDN());
            Log.e(TAG, "x509Certificate_getSigAlgOID_证书算法OID字符串___:   " + x509Certificate.getSigAlgOID());
            Log.e(TAG, "x509Certificate_getNotBefore_证书有效期___:   " + x509Certificate.getNotAfter());
            Log.e(TAG, "x509Certificate_getSigAlgName_签名算法___:   " + x509Certificate.getSigAlgName());
            Log.e(TAG, "x509Certificate_getVersion_版本号___:   " + x509Certificate.getVersion());
            Log.e(TAG, "x509Certificate_getPublicKey_公钥___:   " + x509Certificate.getPublicKey());
        }
         conn.disconnect();
        */

    }


    private void trustEveryone() {
        try {
            HttpsURLConnection.setDefaultHostnameVerifier(new HostnameVerifier() {
                public boolean verify(String hostname, SSLSession session) {
                    return true;
                }
            });
            SSLContext context = SSLContext.getInstance("TLS");
            context.init(null, new X509TrustManager[]{new X509TrustManager() {
                public void checkClientTrusted(X509Certificate[] chain,
                                               String authType) throws CertificateException {
                }

                public void checkServerTrusted(X509Certificate[] chain,
                                               String authType) throws CertificateException {
                }

                public X509Certificate[] getAcceptedIssuers() {
                    return new X509Certificate[0];
                }
            }}, new SecureRandom());
            HttpsURLConnection.setDefaultSSLSocketFactory(
                    context.getSocketFactory());
        } catch (Exception e) { // should never happen
            e.printStackTrace();
        }
    }


    static class NullHostNameVerifier implements HostnameVerifier {
        @Override
        public boolean verify(String arg0, SSLSession arg1) {
            // TODO Auto-generated method stub
            return true;
        }
    }

    static TrustManager[] trustAllCerts = new TrustManager[]{new X509TrustManager() {
        @Override
        public void checkClientTrusted(X509Certificate[] chain, String authType) throws CertificateException {
            // TODO Auto-generated method stub
        }

        @Override
        public void checkServerTrusted(X509Certificate[] chain, String authType) throws CertificateException {
            // TODO Auto-generated method stub
        }

        @Override
        public X509Certificate[] getAcceptedIssuers() {
            // TODO Auto-generated method stub
            //   return null;
            return new X509Certificate[0];
        }
    }};
}
