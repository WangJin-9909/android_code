#include <jni.h>
#include <string>
#include <Android/log.h>
#include <openssl/hmac.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include <openssl/md5.h>


#if 1
#define TAG "cipher"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG ,__VA_ARGS__)
#else
#define LOGI(...)
#define LOGD(...)
#define LOGE(...)
#define LOGF(...)
#define LOGW(...)
#endif

extern "C"
JNIEXPORT jbyteArray

JNICALL
Java_com_example_administrator_oi_MainActivity_stringFromJNI(JNIEnv *env, jobject instance,
                                                             jbyteArray src_) {
    std::string hello = "Hello from C++";

    LOGI("HmacSHA1->HMAC: Hash-based Message Authentication Code，即基于Hash的消息鉴别码");
    const char *key = "alleyApp@22383243-335457968";
    jbyte *src = env->GetByteArrayElements(src_, NULL);
    jsize src_Len = env->GetArrayLength(src_);

    unsigned int result_len;
    unsigned char result[EVP_MAX_MD_SIZE];
    char buff[EVP_MAX_MD_SIZE];
    char hex[EVP_MAX_MD_SIZE];

    LOGI("HmacSHA1->调用函数进行哈希运算");
    HMAC(EVP_sha1(), key, strlen(key), (unsigned char *) src, src_Len, result, &result_len);

    strcpy(hex, "");
    LOGI("HmacSHA1->把哈希值按%%02x格式定向到缓冲区");
    for (int i = 0; i != result_len; i++) {
        sprintf(buff, "%02x", result[i]);
        strcat(hex, buff);
    }
    LOGI("HmacSHA1->%s", hex);

    LOGI("HmacSHA1->从jni释放数据指针");
    env->ReleaseByteArrayElements(src_, src, 0);

    jbyteArray signature = env->NewByteArray(strlen(hex));
    LOGI("HmacSHA1->在堆中分配ByteArray数组对象成功，将拷贝数据到数组中");
    env->SetByteArrayRegion(signature, 0, strlen(hex), (jbyte *) hex);

    return signature;

}
jstring stoJstringUtf(JNIEnv* env, const char* pat)
{
    int n;
    jclass strClass = env->FindClass( "java/lang/String" );
    jmethodID ctorID = env->GetMethodID( strClass, "<init>", "([BLjava/lang/String;)V" );
    n = strlen(pat);
    jbyteArray bytes = env->NewByteArray( n );
    env->SetByteArrayRegion( bytes, 0, n, (jbyte*)pat );
    jstring encoding = env->NewStringUTF( "utf-8" );
    jstring ret = (jstring)env->NewObject( strClass, ctorID, bytes, encoding );
    env->DeleteLocalRef( encoding );
    return ret;
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_administrator_oi_MainActivity_getVersion(JNIEnv *env, jobject thiz) {
    // TODO: implement getVersion()
    //constchar 转jString
    return stoJstringUtf(env, OPENSSL_VERSION_TEXT);

}

