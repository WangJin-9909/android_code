#pragma once
#include "utils.h"
#include <android/log.h>
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)  
class CContentEncrypt
{
public:
	CContentEncrypt();
	~CContentEncrypt(void);

	BOOL GenerateVerifyCallerCryptKey(BYTE* pResult,DWORD& dwResultSize,char * UniqueID); // 生成密码加密秘钥，该秘钥在驱动中使用	
	BOOL DecryptVerifyCaller(BYTE* pCiphertext,DWORD dwCiphertextlen,BYTE* pResult,DWORD& dwSize,char * UniqueID); // 解密密码信息	
	BOOL EncryptVerifyCaller(BYTE* pPlaintext,BYTE* pResult,DWORD& dwSize,char * UniqueID);

	//for personal ebanking
	BOOL CryptGenSHAKey(const char *pValidID,char *pGenKey,int *pHashLen);
	BOOL EncryptIt(char* sContent, char* sKeySeed, char** sResult);
	BOOL verifySignatureBySM2(char* data, char* keyX, char* keyY, char* strSignature);
	BOOL verifySignatureByRSA(char* data, char* modulus, char* strSignature);
};
