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
#include "SM3.h"
#include "Base64Coder.h"
#include "ContentEncrypt.h"

typedef unsigned char *PBYTE;


extern "C"
JNIEXPORT jbyteArray

JNICALL
Java_com_example_openssl_MainActivity_stringFromJNI(JNIEnv *env, jobject instance,
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


char *sm2_param_recommand[] = {
        //p
        "FFFFFFFE" "FFFFFFFF" "FFFFFFFF" "FFFFFFFF" "FFFFFFFF" "00000000" "FFFFFFFF" "FFFFFFFF",
        //a
        "FFFFFFFE" "FFFFFFFF" "FFFFFFFF" "FFFFFFFF" "FFFFFFFF" "00000000" "FFFFFFFF" "FFFFFFFC",
        //b
        "28E9FA9E" "9D9F5E34" "4D5A9E4B" "CF6509A7" "F39789F5" "15AB8F92" "DDBCBD41" "4D940E93",
        //G_x
        "32C4AE2C" "1F198119" "5F990446" "6A39C994" "8FE30BBF" "F2660BE1" "715A4589" "334C74C7",
        //G_y
        "BC3736A2" "F4F6779C" "59BDCEE3" "6B692153" "D0A9877C" "C62A4740" "02DF32E5" "2139F0A0",
        //n
        "FFFFFFFE" "FFFFFFFF" "FFFFFFFF" "FFFFFFFF" "7203DF6B" "21C6052B" "53BBF409" "39D54123",
};


char *sm2_param_k[2] = {
        "4C62EEFD6ECFC2B95B92FD6C3D9575148AFA17425546D49018E5388D49DD7B4F",         //随机数k
        "6D3B497153E3E92524E5C122682DBDC8705062E20B917A5F8FCDB8EE4C66663D",
};
// Add:2016.6.2 Makai-[Add the static lib of openSSL] End


char *g_sm2PublicKeyX;
char *g_sm2PublicKeyY;


char *jstringTostring(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
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

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getVersion(JNIEnv *env, jobject thiz) {
    // TODO: implement getVersion()
    //constchar 转jString
    return stoJstringUtf(env, OPENSSL_VERSION_TEXT);

}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getSeaEt(JNIEnv *env, jobject obj, jint type,
                                               jstring data, jobject keycode) {
    int cType = type;
    jstring ret = stoJstringUtf(env, "");
    char *cData = jstringTostring(env, data);
    // char* cKeyCode = jstringTostring(env, keyCode);
    // --------------------------java object
    jclass MSCryptKey = env->GetObjectClass(keycode);
    jfieldID valueID = env->GetFieldID(MSCryptKey, "Ev", "Ljava/lang/String;");
    jstring keyValue = (jstring) env->GetObjectField(keycode, valueID);
    char *cKeyCode = jstringTostring(env, keyValue);
    // --------------------------java object
    if (cKeyCode == NULL || strlen(cKeyCode) == 0)
        return ret;
    if (strlen(cKeyCode) != 16)
        return ret;

    CAES128Impl utils;
    char *outStr = (char *) malloc(1024 * sizeof(char));
    memset(outStr, 0, 1024);
    if (cType == 1) {
        utils.EncryptAES128ByECB(cData, outStr, cKeyCode);
    } else {
        utils.EncryptAES128ByCBC(cData, outStr, cKeyCode);
    }

    ret = stoJstringUtf(env, outStr);
    if (cData != NULL) {
        free(cData);
        cData = NULL;
    }
    if (cKeyCode != NULL) {
        free(cKeyCode);
        cKeyCode = NULL;
    }
    free(outStr);
    outStr = NULL;
    return ret;
}

int byteToHexStr(PBYTE pbySrcBuffer, DWORD dwBufferSize, PBYTE pbyHexBuffer) {
    try {
        for (DWORD i = 0; i < dwBufferSize; i++) {
            char chHex1 = '0';
            char chHex2 = '0';

            //直接将unsigned char赋值给整型的值，系统会正动强制转换
            int nCh2IntValue = pbySrcBuffer[i];

            int nQuotient = nCh2IntValue / 16;
            int nResidue = nCh2IntValue % 16;

            //将商转成字母
            if (nQuotient >= 0 && nQuotient <= 9)
                chHex1 = (char) ('0' + nQuotient);
            else
                chHex1 = (char) ('A' + (nQuotient - 10));

            //将余数转成字母
            if (nResidue >= 0 && nResidue <= 9)
                chHex2 = (char) ('0' + nResidue);
            else
                chHex2 = (char) ('A' + (nResidue - 10));

            //将Hex字母填充到Hex Buffer中
            pbyHexBuffer[i * 2] = chHex1;
            pbyHexBuffer[i * 2 + 1] = chHex2;
        }

        return 0;
    }
    catch (...) {
        return -7;
    }
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_openssl_MainActivity_getInitKey(JNIEnv *env, jobject obj, jint type,
                                                 jstring data1, jstring data2) {
    char *cData1 = jstringTostring(env, data1);
    char *cData2 = jstringTostring(env, data2);
    // strcat(cData1, cData2);

    int iData1 = strlen(cData1);
    int iData2 = strlen(cData2);

    char *cData3 = (char *) malloc((iData1 + iData2 + 1) * sizeof(char));
    memset(cData3, 0, iData1 + iData2 + 1);
    memcpy(cData3, cData1, iData1);
    memcpy(cData3 + iData1, cData2, iData2);
    CSecurityUtils su;
    char result1[20] = {0};
    if (!su.GetHashSHA1((const unsigned char *) cData3, strlen(cData3), result1)) {
        return stoJstringUtf(env, "");
    }

    char *cStr = (char *) malloc(1024 * sizeof(char));
    memset(cStr, 0, 1024);
    byteToHexStr((PBYTE) result1, 20, (PBYTE) cStr);
    char *cData = NULL;
    if (type == 0) {
        cData = (char *) malloc(25 * sizeof(char));
        memset(cData, 0, 25);
        memcpy(cData, cStr, 24);
    } else if (type == 1) {
        cData = (char *) malloc(17 * sizeof(char));
        memset(cData, 0, 17);
        memcpy(cData, cStr, 16);
    } else {
        cData = (char *) malloc(1 * sizeof(char));
        memset(cData, 0, 1);
    }

    jstring ret2 = stoJstringUtf(env, cData);
    //jclass cryptKey = env->FindClass("com/icbc/ms/crypt/component/MSCryptKey");
    jclass cryptKey = env->FindClass("com/example/administrator/oi/MSCryptKey");
    if (cryptKey == NULL)
        return NULL;
    jmethodID initId = env->GetMethodID(cryptKey, "<init>",
                                        "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
    if (initId == NULL)
        return NULL;
    jobject ret = env->NewObject(cryptKey, initId, data1, data2, ret2, type);

    if (cData1 != NULL) {
        free(cData1);
        cData1 = NULL;
    }
    if (cData2 != NULL) {
        free(cData2);
        cData2 = NULL;
    }
    if (cData3 != NULL) {
        free(cData3);
        cData3 = NULL;
    }
    free(cStr);
    cStr = NULL;
    free(cData);
    cData = NULL;
    return ret;
}

BOOL EncryptSM2(PBYTE sContent, PBYTE sEncryptText) {

    PBYTE pbyPlanText = sContent;
    CSM2 smtest;
    //椭圆参数的初始化
    smtest.ecp->type = 0;
    smtest.ecp->EC_GROUP_new_curve = EC_GROUP_new_curve_GFp;
    smtest.ecp->EC_POINT_set_affine_coordinates = EC_POINT_set_affine_coordinates_GFp;
    smtest.ecp->EC_POINT_get_affine_coordinates = EC_POINT_get_affine_coordinates_GFp;

    BN_hex2bn(&smtest.ecp->p, sm2_param_recommand[0]);
    BN_hex2bn(&smtest.ecp->a, sm2_param_recommand[1]);
    BN_hex2bn(&smtest.ecp->b, sm2_param_recommand[2]);
    BN_hex2bn(&smtest.ecp->n, sm2_param_recommand[5]);

    smtest.ecp->group = smtest.ecp->EC_GROUP_new_curve(smtest.ecp->p, smtest.ecp->a, smtest.ecp->b,
                                                       smtest.ecp->ctx);

    CXyECPoint cxyecpointemp(smtest.ecp);
    BN_hex2bn(&cxyecpointemp.xyp->x, sm2_param_recommand[3]);
    BN_hex2bn(&cxyecpointemp.xyp->y, sm2_param_recommand[4]);
    smtest.ecp->G = cxyecpointemp.xyp;
    if (!smtest.ecp->EC_POINT_set_affine_coordinates(
            smtest.ecp->group,
            smtest.ecp->G->ec_point, smtest.ecp->G->x,
            smtest.ecp->G->y,
            smtest.ecp->ctx));


    smtest.ecp->point_bit_length = 256;
    smtest.ecp->point_byte_length = (256 + 7) / 8;

    ////公钥的初始化
    CSM2EcKey sm2eckey(smtest.ecp);

    if (strcmp(g_sm2PublicKeyX, "") && strcmp(g_sm2PublicKeyY, "")) {
        sm2eckey.EcKeyInit(g_sm2PublicKeyX, g_sm2PublicKeyY);
    } else {
        return FALSE;
    }


    //sm2eckey.EcKeyInit(pKeyX, pKeyY);
    memset(&smtest.message_data, 0, sizeof(smtest.message_data));
    smtest.message_data.message = (BYTE *) pbyPlanText;                                                                //要加密的明文
    smtest.message_data.message_byte_length = strlen(
            (char *) smtest.message_data.message);                        //要加密明文的长度
    smtest.message_data.klen_bit = smtest.message_data.message_byte_length *
                                   8;                                    //klen_bit 为密文的bit长度
    sm2_hex2bin((BYTE *) sm2_param_k[smtest.ecp->type], smtest.message_data.k,
                smtest.ecp->point_byte_length);    //给随机数K赋值
    sm2_bn2bin(sm2eckey.eck->P->x, smtest.message_data.public_key.x, smtest.ecp->point_byte_length);
    sm2_bn2bin(sm2eckey.eck->P->y, smtest.message_data.public_key.y, smtest.ecp->point_byte_length);

    ////开始加密
    smtest.message_data.decrypt = (BYTE *) OPENSSL_malloc(
            smtest.message_data.message_byte_length + 1);
    memset(smtest.message_data.decrypt, 0, smtest.message_data.message_byte_length + 1);

    smtest.Encrypt(smtest.ecp, &smtest.message_data);                     //start encrypt
    memset(&smtest.message_data.message, 0, sizeof(smtest.message_data.message));
    OPENSSL_free(smtest.message_data.decrypt);

    BYTE pbyCipter2Hex[(256 + 3) * 2] = {0};
    // 密文 + 校验结果 转换为 16进制 ------------------------------------------------------------------------------
    if (0 != byteToHexStr(smtest.message_data.C, smtest.message_data.message_byte_length + 97,
                          pbyCipter2Hex)) {
        return FALSE;
    }
    int k = strlen((const char *) pbyCipter2Hex);
    strncpy((char *) sEncryptText, (const char *) (pbyCipter2Hex + 2),
            (strlen((const char *) pbyCipter2Hex) - 2));
    return TRUE;
}

//SM2
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_openssl_MainActivity_getGmRiEt
        (JNIEnv *env, jobject obj, jstring plainText, jstring plainX, jstring plainY) {
    jstring ret = stoJstringUtf(env, "");
    BOOL enOk = FALSE;
    char *gmChar = jstringTostring(env, plainText);
    g_sm2PublicKeyX = jstringTostring(env, plainX);
    g_sm2PublicKeyY = jstringTostring(env, plainY);
    int sublen = 160;

    char *szNewChar = jstringTostring(env, plainText);
    int len = strlen(szNewChar);
    int lens = (len / 160 + 1) * 512 + 1;
    char *sumChar = (char *) malloc(lens * sizeof(char));
    memset(sumChar, 0, lens);
    //__android_log_print( ANDROID_LOG_DEBUG, "EncryptSM2","len = %d lens = %d", len, lens);
    PBYTE szPlainText = (PBYTE) malloc(600 * sizeof(BYTE));
    if (gmChar == NULL || strlen(gmChar) == 0)
        return ret;
    if (g_sm2PublicKeyX == NULL || strlen(g_sm2PublicKeyX) == 0)
        return ret;
    if (g_sm2PublicKeyY == NULL || strlen(g_sm2PublicKeyY) == 0)
        return ret;

    for (int i = 0; i < len; i = i + sublen) {

        if (i + sublen <= len) {
            char *subChar = (char *) malloc((sublen + 1) * sizeof(char));
            memset(subChar, 0, (sublen + 1));
            strncpy(subChar, szNewChar + i, sublen);
            // PBYTE szPlainText = (PBYTE)malloc(600*sizeof(BYTE));
            memset(szPlainText, 0, 600);
            enOk = EncryptSM2((PBYTE) subChar, szPlainText);
            strcat(sumChar, (char *) szPlainText);
            //__android_log_print( ANDROID_LOG_DEBUG, "EncryptSM2","sumChar = %s", sumChar);
            strcat(sumChar, "&&");
            if (subChar != NULL) {
                free(subChar);
                subChar = NULL;
            }
        } else {
            char *subChar = (char *) malloc((len - i + 1) * sizeof(char));
            memset(subChar, 0, (len - i + 1));
            strncpy(subChar, szNewChar + i, len - i);
            memset(szPlainText, 0, 600);
            enOk = EncryptSM2((PBYTE) subChar, szPlainText);
            strcat(sumChar, (char *) szPlainText);
            if (subChar != NULL) {
                free(subChar);
                subChar = NULL;
            }
        }
    }
    //__android_log_print( ANDROID_LOG_DEBUG, "EncryptSM2","final   sumChar = %s", sumChar);
    if (!enOk) {
        return ret;
    }
    jstring retStr = stoJstringUtf(env, (const char *) sumChar);
    if (gmChar != NULL) {
        free(gmChar);
        gmChar = NULL;
    }
    if (g_sm2PublicKeyX != NULL) {
        free(g_sm2PublicKeyX);
        g_sm2PublicKeyX = NULL;
    }
    if (g_sm2PublicKeyY != NULL) {
        free(g_sm2PublicKeyY);
        g_sm2PublicKeyY = NULL;
    }
    return retStr;
}

// SM3摘要处理
extern "C"
JNIEXPORT jstring JNICALL Java_com_example_openssl_MainActivity_getGmMiEt
        (JNIEnv *env, jobject obj, jstring plainText) {
    //__android_log_print( ANDROID_LOG_DEBUG, "EncryptSM3","chen_1");
    jstring ret = stoJstringUtf(env, "");
    char *str = jstringTostring(env, plainText);
    if (str == NULL || strlen(str) == 0)
        return ret;
    DWORD strLen = strlen(str);
    BYTE *strH = (BYTE *) malloc(32);
    CSM3 sm3;
    sm3.SM3_Init();
    sm3.SM3_Update((PBYTE) str, strLen);
    sm3.SM3_Final_byte((BYTE *) &strH[0]);
    BYTE pbyCipter2Hex[256] = {0};
    byteToHexStr(strH, 64, pbyCipter2Hex);
    char *sm3Result = (char *) malloc((256) * sizeof(char));
    memset(sm3Result, 0, 256);
    strncpy(sm3Result, (char *) pbyCipter2Hex, 64);
    jstring retStr2 = stoJstringUtf(env, sm3Result);

    if (str != NULL) {
        free(str);
        str = NULL;
    }
    if (sm3Result != NULL) {
        free(sm3Result);
        sm3Result = NULL;
    }
    if (strH != NULL) {
        free(strH);
        strH = NULL;
    }

    return retStr2;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getGmFaEt(JNIEnv *env, jobject obj, jstring plainText,
                                                jobject plainKey) {
    jstring ret = stoJstringUtf(env, "");
    char *gmChar = jstringTostring(env, plainText);
    if (gmChar == NULL || strlen(gmChar) == 0)
        return ret;

    // --------------------------java object
    jclass MSCryptKey = env->GetObjectClass(plainKey);
    jfieldID valueID = env->GetFieldID(MSCryptKey, "Ev", "Ljava/lang/String;");
    jstring keyValue = (jstring) env->GetObjectField(plainKey, valueID);
    char *cipherKey = jstringTostring(env, keyValue);
    // jmethodID methodId = env->GetMethodID(MSCryptKey, "<int>", "(ILjava/lang/String;)V");
    // __android_log_print( ANDROID_LOG_DEBUG, "getGmFaEt","chen %s", cipherKey);
    // --------------------------java object
    // char* cipherKey = jstringTostring(env, plainKey);
    if (cipherKey == NULL || strlen(cipherKey) == 0)
        return ret;
    if (strlen(cipherKey) != 16)
        return ret;

    char *gmEncryptText = (char *) malloc(2048 * sizeof(char));
    memset(gmEncryptText, 0, 2048);
    DWORD dwCipherLen = 2048;
    CSecurityUtils utils;
    utils.EncryptSM4((BYTE *) gmChar, strlen(gmChar), (BYTE *) gmEncryptText, dwCipherLen,
                     (BYTE *) cipherKey, 16);
    if (gmEncryptText == NULL)
        return ret;

    Base64Coder base64cdr;
    base64cdr.Encode((const PBYTE) gmEncryptText, dwCipherLen);
    char *base64Result = (char *) base64cdr.EncodedMessage();
    jstring ret2 = stoJstringUtf(env, base64Result);

    if (gmChar != NULL) {
        free(gmChar);
        gmChar = NULL;
    }
    if (cipherKey != NULL) {
        free(cipherKey);
        cipherKey = NULL;
    }
    free(gmEncryptText);
    gmEncryptText = NULL;

    return ret2;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getGmFaDt
        (JNIEnv *env, jobject obj, jstring plainText, jobject plainKey) {
    jstring ret = stoJstringUtf(env, "");
    char *gmChar = jstringTostring(env, plainText);
    if (gmChar == NULL || strlen(gmChar) == 0)
        return ret;
    // --------------------------java object
    jclass MSCryptKey = env->GetObjectClass(plainKey);
    jfieldID valueID = env->GetFieldID(MSCryptKey, "Ev", "Ljava/lang/String;");
    jstring keyValue = (jstring) env->GetObjectField(plainKey, valueID);
    char *cipherKey = jstringTostring(env, keyValue);
    // --------------------------java object
    if (cipherKey == NULL || strlen(cipherKey) == 0)
        return ret;
    if (strlen(cipherKey) != 16)
        return ret;

    DWORD dwCipherLen = strlen(gmChar);
    Base64Coder base64cdr;
    char *bOut = (char *) malloc(dwCipherLen * sizeof(char));
    memset(bOut, 0, dwCipherLen);
    base64cdr.Decode64((BYTE *) gmChar, dwCipherLen, (BYTE *) bOut, dwCipherLen);
    char *base64Result = (char *) base64cdr.DecodedMessage();

    CSecurityUtils utils;
    char *gmDecryptText = (char *) malloc(2048 * sizeof(char));
    memset(gmDecryptText, 0, 2048);
    utils.DecryptSM4((BYTE *) base64Result, dwCipherLen, (BYTE *) gmDecryptText, dwCipherLen,
                     (BYTE *) cipherKey, 16);

    jstring ret2 = stoJstringUtf(env, gmDecryptText);
    if (gmChar != NULL) {
        free(gmChar);
        gmChar = NULL;
    }
    if (cipherKey != NULL) {
        free(cipherKey);
        cipherKey = NULL;
    }
    free(bOut);
    bOut = NULL;
    free(gmDecryptText);
    gmDecryptText = NULL;

    return ret2;
}



extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getMiDsEt
        (JNIEnv *env, jobject obj, jint type, jstring data, jobject keycode) {
    jstring ret = stoJstringUtf(env, "");
    int cInt = type;
    char *cData = jstringTostring(env, data);
    // char* cKeyCode = jstringTostring(env, keycode);
    // --------------------------java object
    jclass MSCryptKey = env->GetObjectClass(keycode);
    jfieldID valueID = env->GetFieldID(MSCryptKey, "Ev", "Ljava/lang/String;");
    jstring keyValue = (jstring) env->GetObjectField(keycode, valueID);
    char *cKeyCode = jstringTostring(env, keyValue);
    // --------------------------java object
    if (cKeyCode == NULL || strlen(cKeyCode) == 0)
        return ret;
    if (strlen(cKeyCode) != 24)
        return ret;
    int cDataLen = strlen(cData);

    CSecurityUtils utils;
    char *szPlainText = (char *) malloc(cDataLen * sizeof(char) + 1);
    memset(szPlainText, 0, cDataLen + 1);
    memcpy(szPlainText, cData, cDataLen);
    char *encryptText = (char *) malloc(cDataLen * sizeof(char) + 64);
    memset(encryptText, 0, cDataLen + 64);
    DWORD dwCipherLen = cDataLen + 64;
    // 0代表CBC，1代表ECB
    if (cInt == 1) {
        if (!utils.Encrypt3DES((BYTE *) szPlainText, strlen(szPlainText), (BYTE *) encryptText,
                               dwCipherLen, (BYTE *) cKeyCode, 24)) {
            free(szPlainText);
            szPlainText = NULL;
            free(encryptText);
            encryptText = NULL;
            return ret;
        }
    } else {
        if (!utils.Encrypt3DESByCbc((BYTE *) szPlainText, strlen(szPlainText), (BYTE *) encryptText,
                                    dwCipherLen, (BYTE *) cKeyCode, 24)) {
            free(szPlainText);
            szPlainText = NULL;
            free(encryptText);
            encryptText = NULL;
            return ret;
        }
    }

    Base64Coder base64cdr;
    base64cdr.Encode((const PBYTE) encryptText, dwCipherLen);
    char *base64Result = (char *) base64cdr.EncodedMessage();
    ret = stoJstringUtf(env, base64Result);
    if (cData != NULL) {
        free(cData);
        cData = NULL;
    }
    if (cKeyCode != NULL) {
        free(cKeyCode);
        cKeyCode = NULL;
    }
    free(szPlainText);
    szPlainText = NULL;
    free(encryptText);
    encryptText = NULL;
    return ret;

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getMiDsDt
        (JNIEnv *env, jobject obj, jint type, jstring data, jobject keycode) {
    jstring ret = stoJstringUtf(env, "");
    int cInt = type;
    char *cData = jstringTostring(env, data);
    // char* cKeyCode = jstringTostring(env, keycode);
    // --------------------------java object
    jclass MSCryptKey = env->GetObjectClass(keycode);
    jfieldID valueID = env->GetFieldID(MSCryptKey, "Ev", "Ljava/lang/String;");
    jstring keyValue = (jstring) env->GetObjectField(keycode, valueID);
    char *cKeyCode = jstringTostring(env, keyValue);
    // --------------------------java object
    if (cKeyCode == NULL || strlen(cKeyCode) == 0)
        return ret;
    if (strlen(cKeyCode) != 24)
        return ret;

    Base64Coder base64cdr;
    DWORD dwCipherLen = 2048;
    char *cResult = (char *) malloc(2048 * sizeof(char));
    memset(cResult, 0, 2048);
    //base64cdr.Decode((const PBYTE)cData, strlen(cData));
    base64cdr.Decode64((const PBYTE) cData, strlen(cData), (const PBYTE) cResult, dwCipherLen);
    CSecurityUtils utils;
    char *encryptText = (char *) malloc(2048 * sizeof(char));
    memset(encryptText, 0, 2048);
    //DWORD dwCipherLen = 2048;
    // 0代表CBC，1代表ECB
    if (cInt == 1) {
        if (!utils.Decrypt3DES((BYTE *) cResult, dwCipherLen, (BYTE *) encryptText, dwCipherLen,
                               (BYTE *) cKeyCode, 24)) {
            free(cResult);
            cResult = NULL;
            free(encryptText);
            encryptText = NULL;
            return ret;
        }
    } else {
        if (!utils.Decrypt3DESByCbc((BYTE *) cResult, dwCipherLen, (BYTE *) encryptText,
                                    dwCipherLen, (BYTE *) cKeyCode, 24)) {
            free(cResult);
            cResult = NULL;
            free(encryptText);
            encryptText = NULL;
            return ret;
        }
    }

    ret = stoJstringUtf(env, encryptText);
    if (cData != NULL) {
        free(cData);
        cData = NULL;
    }
    if (cKeyCode != NULL) {
        free(cKeyCode);
        cKeyCode = NULL;
    }
    free(cResult);
    cResult = NULL;
    free(encryptText);
    encryptText = NULL;
    return ret;

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getBaseEt
        (JNIEnv *env, jobject obj, jstring data) {
    char *strData = jstringTostring(env, data);
    Base64Coder base64cdr;
    DWORD dwCipherLen = strlen(strData);
    base64cdr.Encode((const PBYTE) strData, dwCipherLen);
    char *base64Result = (char *) base64cdr.EncodedMessage();
    jstring ret = stoJstringUtf(env, base64Result);
    if (strData != NULL) {
        free(strData);
        strData = NULL;
    }
    return ret;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getBaseDt
        (JNIEnv *env, jobject obj, jstring data) {
    char *strData = jstringTostring(env, data);
    Base64Coder base64cdr;
    DWORD dwCipherLen = strlen(strData);
    base64cdr.Decode((const PBYTE) strData, dwCipherLen);
    char *base64Result = (char *) base64cdr.DecodedMessage();
    jstring ret = stoJstringUtf(env, base64Result);
    if (strData != NULL) {
        free(strData);
        strData = NULL;
    }
    return ret;
}

// SHA256信息摘要
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getHasSeEt
        (JNIEnv *env, jobject obj, jstring data) {
    char *strData = jstringTostring(env, data);
    CSecurityUtils utils;
    char *result = utils.GetHashSHA256((const unsigned char *) strData, strlen(strData));
    //std:: string etStr = sha256(strData);
    //char* strData2 = etStr.c_str();
    //BYTE pbyCipter2Hex[256] = {0};
    //byteToHexStr((PBYTE)result, 64, pbyCipter2Hex); 前面的结果已经转换过16进制，所以这里取消
    char *strHex = (char *) malloc((256) * sizeof(char));
    memset(strHex, 0, 256);
    strncpy(strHex, (char *) result, 64);
    jstring ret = stoJstringUtf(env, strHex);
    if (strData != NULL) {
        free(strData);
        strData = NULL;
    }
    free(result);
    result = NULL;
    free(strHex);
    strHex = NULL;
    return ret;
}

// SM2验签
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getGmRiYan
        (JNIEnv *env, jobject obj, jstring keyX, jstring keyY, jstring data, jstring strSignature) {
    char *charKeyX = jstringTostring(env, keyX);
    char *charKeyY = jstringTostring(env, keyY);
    char *charData = jstringTostring(env, data);
    char *charSig = jstringTostring(env, strSignature);
    jstring ret = stoJstringUtf(env, "");
    CContentEncrypt encryptUtils;
    if (encryptUtils.verifySignatureBySM2(charData, charKeyX, charKeyY, charSig)) {
        ret = stoJstringUtf(env, "1");
        return ret;
    }
    ret = stoJstringUtf(env, "0");
    if (charKeyX != NULL) {
        free(charKeyX);
        charKeyX = NULL;
    }
    if (charKeyY != NULL) {
        free(charKeyY);
        charKeyY = NULL;
    }
    if (charData != NULL) {
        free(charData);
        charData = NULL;
    }
    if (charSig != NULL) {
        free(charSig);
        charSig = NULL;
    }
    return ret;
}

// RSA加密算法
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getMiDsEtgetArsEt
        (JNIEnv *env, jobject obj, jstring data, jstring keycode) {

    char *charData = jstringTostring(env, data);
    char *charKeyCode = jstringTostring(env, keycode);
    jstring ret = stoJstringUtf(env, "");
    CSecurityUtils utils;
    char *charRet = (char *) malloc((2048) * sizeof(char));
    memset(charRet, 0, 2048);
    if (utils.EncryptRSA2048(charData, charKeyCode, &charRet)) {

        if (charRet != NULL) {
            ret = stoJstringUtf(env, charRet);
        }

    }
    if (charData != NULL) {
        free(charData);
        charData = NULL;
    }
    if (charKeyCode != NULL) {
        free(charKeyCode);
        charKeyCode = NULL;
    }
    free(charRet);
    charRet = NULL;
    return ret;
}
// AES128解密算法
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getSeaDt
        (JNIEnv *env, jobject obj, jint type, jstring data, jobject keycode) {

    int cType = type;

    jstring ret = stoJstringUtf(env, "");

    char *cData = jstringTostring(env, data);

    // char* cKeyCode = jstringTostring(env, keyCode);
    // --------------------------java object
    jclass MSCryptKey = env->GetObjectClass(keycode);

    jfieldID valueID = env->GetFieldID(MSCryptKey, "Ev", "Ljava/lang/String;");

    jstring keyValue = (jstring) env->GetObjectField(keycode, valueID);

    char *cKeyCode = jstringTostring(env, keyValue);

    // --------------------------java object
    if (cKeyCode == NULL || strlen(cKeyCode) == 0)
        return ret;
    if (strlen(cKeyCode) != 16)
        return ret;

    CAES128Impl utils;
    char *outStr = (char *) malloc(1024 * sizeof(char));
    memset(outStr, 0, 1024);

    if (cType == 1) {

        utils.DecryptAES128ByECB(cData, outStr, cKeyCode);
    } else {

        utils.DecryptAES128ByCBC(cData, outStr, cKeyCode);
    }

    ret = stoJstringUtf(env, outStr);
    if (cData != NULL) {
        free(cData);
        cData = NULL;
    }
    if (cKeyCode != NULL) {
        free(cKeyCode);
        cKeyCode = NULL;
    }
    free(outStr);
    outStr = NULL;

    return ret;
}

// RSA验签
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_openssl_MainActivity_getArsYan
        (JNIEnv *env, jobject obj, jstring data, jstring modulus, jstring strSignature) {
    char *cData = jstringTostring(env, data);
    char *cModulus = jstringTostring(env, modulus);
    char *cStrSig = jstringTostring(env, strSignature);
    jstring ret = stoJstringUtf(env, "");
    CContentEncrypt encryptUtils;
    if (encryptUtils.verifySignatureByRSA(cData, cModulus, cStrSig)) {
        ret = stoJstringUtf(env, "1");
        //__android_log_print( ANDROID_LOG_DEBUG, "getArsYan","ret1");
        return ret;
    }
    ret = stoJstringUtf(env, "0");
    //__android_log_print( ANDROID_LOG_DEBUG, "getArsYan","ret0");
    if (cData != NULL) {
        free(cData);
        cData = NULL;
    }
    if (cModulus != NULL) {
        free(cModulus);
        cModulus = NULL;
    }
    if (cStrSig != NULL) {
        free(cStrSig);
        cStrSig = NULL;
    }
    return ret;
}



