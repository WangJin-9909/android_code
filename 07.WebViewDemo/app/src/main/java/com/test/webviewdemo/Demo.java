package com.test.webviewdemo;

import android.content.Context;
import android.util.Base64;
import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.security.KeyStore;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManagerFactory;

public class Demo {
    private static final String TAG = "WebViewDemo";

    public void starHttpsCer(String urlStr, Context ctx) {
        HttpsURLConnection conn = null;
        try {
            URL url = new URL(urlStr);
            conn = (HttpsURLConnection) url.openConnection();
            conn.setSSLSocketFactory(setCertificates(ctx.getAssets().open("client.cer")));
            conn.connect();
            if (conn.getResponseCode() == 200) {
                InputStream is = conn.getInputStream();
                ByteArrayOutputStream bytestream = new ByteArrayOutputStream();
                int ch;
                while ((ch = is.read()) != -1) {
                    bytestream.write(ch);
                }
                is.close();
                conn.disconnect();
                byte[] result = bytestream.toByteArray();
                Log.e("result", new String(result));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public SSLSocketFactory setCertificates(InputStream... certificates) {
        try {
            //证书工厂。此处指明证书的类型
            CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
            //创建一个证书库
            KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
            keyStore.load(null);
            int index = 0;
            for (InputStream certificate : certificates) {
                String certificateAlias = Integer.toString(index++);
                //将证书导入证书库
                keyStore.setCertificateEntry(certificateAlias, certificateFactory.generateCertificate(certificate));

                try {
                    if (certificate != null)
                        certificate.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            //取得SSL的SSLContext实例
            SSLContext sslContext = SSLContext.getInstance("TLS");
            TrustManagerFactory trustManagerFactory = TrustManagerFactory.
                    getInstance(TrustManagerFactory.getDefaultAlgorithm());
            trustManagerFactory.init(keyStore);

//            //初始化keystore
//            KeyStore clientKeyStore = KeyStore.getInstance(KeyStore.getDefaultType());
//            clientKeyStore.load(getAssets().open("client.jks"), "123456".toCharArray());
//
//            KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance(KeyManagerFactory.getDefaultAlgorithm());
//            keyManagerFactory.init(clientKeyStore, "123456".toCharArray());

//            第一个参数是授权的密钥管理器，用来授权验证。TrustManager[]第二个是被授权的证书管理器，用来验证服务器端的证书。第三个参数是一个随机数值，可以填写null
            sslContext.init(null, trustManagerFactory.getTrustManagers(), new SecureRandom());
//            sslContext.init(null, null, new SecureRandom());
            return sslContext.getSocketFactory();


        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }


    /**
     * 获取公钥key的方法（读取.crt认证文件）
     */
    public  String getKeyFromCRT(Context context) {
        String key = "";
        CertificateFactory certificatefactory;
        X509Certificate Cert;
        InputStream bais;
        PublicKey pk;

        try {
            //若此处不加参数 "BC" 会报异常：CertificateException - OpenSSLX509CertificateFactory$ParsingException
            certificatefactory = CertificateFactory.getInstance("X.509");
            //读取放在项目中assets文件夹下的.crt文件；你可以读取绝对路径文件下的crt，返回一个InputStream（或其子类）即可。
            bais = context.getAssets().open("client.cer");
            Cert = (X509Certificate) certificatefactory.generateCertificate(bais);
            pk = Cert.getPublicKey();
            Base64.encode(pk.getEncoded(), 0);
            //key = bse.encode(pk.getEncoded());
            Log.e(TAG, "源key-----" + Cert.getPublicKey());
            Log.e(TAG, "加密key-----" + Base64.encode(pk.getEncoded(), 0));
        } catch (Exception e) {
            e.printStackTrace();
        }
        key = key.replaceAll("\\n", "").trim();//去掉文件中的换行符
        return key;
    }

}
