//
// Created by wangJin on 2021/4/2.
//

#ifndef NDKDEMO_NATIVE_LIB_H
#define NDKDEMO_NATIVE_LIB_H

#include <jni.h>
#include <android/log.h>
#include <string>


//Log
#define TAG "JNI_DEBUG_wangJin" // 这个是自定义的LOG的标识
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)  // 定义LOGV类型
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

//Jni函数声明
#define PREFIX(func)       Java_com_example_ndkdemo_MainActivity_##func
//#define PREFIX(func)       Java_com_microsoft_Encrypt_##func


jstring stoJstringUtf(JNIEnv *env, const char *pat);

char *jstringTostring(JNIEnv *env, jstring jstr);

void LogOutHexString(char *data, int len);

void CharArrayToHexString(char *pOut, const char *pInput, const int nInLen);


#endif //NDKDEMO_NATIVE_LIB_H
