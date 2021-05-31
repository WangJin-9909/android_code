

#include "native-lib.h"
#include <jni.h>
#include <string>
#include <unistd.h>



extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


/**
 * char * 转jstring
 * @param env
 * @param pat
 * @return
 */
jstring stoJstringUtf(JNIEnv *env, const char *pat) {
    int n;
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    n = strlen(pat);
    jbyteArray bytes = env->NewByteArray(n);
    env->SetByteArrayRegion(bytes, 0, n, (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    jstring ret = (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
    env->DeleteLocalRef(encoding);
    return ret;
}

/**
 * jstring转char *
 * @param env
 * @param jstr
 * @return
 */
char *jstringTostring(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    if (jstr == NULL) {
        return rtn;
    }
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    env->DeleteLocalRef(strencode);
    return rtn;
}


jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("Jni库初始化.....");
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("Jni卸载.....");
}


void test() {
    char* encryptKey = (char*)malloc(25*sizeof(char));
    memset(encryptKey, 0, 25);
    for(int i = 0; i < 25;  i++)
    {
        encryptKey[i] = i;
    }
    LogOutHexString(encryptKey, 24);
}

void CharArrayToHexString(char *pOut, const char *pInput, const int nInLen) {
    const char *chHexList = "0123456789ABCDEF";
    int nIndex = 0;
    int i = 0, j = 0;

    for (i = 0, j = 0; i < nInLen; i++, j += 2) {
        nIndex = pInput[i] & 0xf;
        pOut[i * 2 + 1] = chHexList[nIndex];
        nIndex = ((pInput[i] >> 4) & 0xf);
        pOut[i * 2] = chHexList[nIndex];
    }
}

void LogOutHexString(char *data, int len) {
    int strlen = 2 * len + 1;
    char *STR = new char[strlen];
    memset(STR, 0, strlen);
    CharArrayToHexString(STR, data, len);
    //__android_log_print(ANDROID_LOG_INFO, "UDUNKEY", "%s", STR);
    LOGI("key = %s", STR);
    delete[] STR;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ndkdemo_MainActivity_test(JNIEnv *env, jobject ctx) {
   /* test();
    std::string hello = "normal";
    return env->NewStringUTF(hello.c_str());*/
    char *ret = NULL;
    ret = "1";
    jstring retStr = stoJstringUtf( env, ret );
    return retStr;
}





