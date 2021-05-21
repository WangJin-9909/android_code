//
// Created by wangJin on 2021/5/14.
//

#ifndef INC_10_ANDROID_OPENSSL_NATIVE_LIB_H
#define INC_10_ANDROID_OPENSSL_NATIVE_LIB_H

#if 0
#define TAG "cipher"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG ,__VA_ARGS__)
#endif
typedef unsigned char *PBYTE;
#define APP_PACKNAME  com_example_administrator_oi_;


#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "SM2.h"
#include "SM4.h"
#include "SM2EcKey.h"
#include "XyECPoint.h"
#include "sha1.h"
#include "AES128Util.h"
#include "SecurityUtils.h"







#endif //INC_10_ANDROID_OPENSSL_NATIVE_LIB_H
