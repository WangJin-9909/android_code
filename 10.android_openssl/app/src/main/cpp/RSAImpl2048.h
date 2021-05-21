#pragma once

#include "BigInt.h"
#include <android/log.h>
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)

const int RSA_MAX_DATA_SIZE_2 = 256 ;
const int PADDING_HEAD_SIZE_2 = 2 ;
const int RSA_KEY_SIZE_2 = 256 ; 
const int BUF_SIZE_READ_FILE_2 = 2048 ;
const int KEY_BLOBS_SIZE_2 = 2048 ;


#ifdef _DEBUG_RSA_MANUL_PADDING 
#define _DEBUG_RSA_RONDOM_PADDING 
#endif

//非对称加密 RSA算法 密钥长度2048
class CRSAImpl2048
{
public:
	CRSAImpl2048(void);
	~CRSAImpl2048(void);
	
public:
	static int s_nMaxPwdLen ;
	// Add:2016.6.30 MaKai[Encrypt hardwareInfo] Start
	static int Encrypt(BYTE * pbyPlanText ,DWORD &dwDataSize ,DWORD &dwBufferSize , DWORD &dwError ,BYTE *publicKey, BOOL IfPadding = FALSE);
	// Add:2016.6.30 MaKai[Encrypt hardwareInfo] End
	static int Decrypt( DWORD &dwError ,BOOL IfPadding  ,int nPaddingType ) ;
	// Add:2016.6.28 MaKai-[Encrypt hardwareInfo] Start
	static int DecryptByPublicKey(BYTE * pbyPlanText);
	// Add:2016.6.28 MaKai-[Encrypt hardwareInfo] End
	static int DecryptByPublicKey2(BYTE * pbyPlanText, BYTE* keyCode);
 	static int ArrayReserv( PBYTE pbyBuffer ,DWORD dwBufferSize , int nBlockSize = 0 ) ;

	static BOOL PaddingData_PKCS1(BYTE* InData, DWORD dwInLen, BYTE* OutData, DWORD& dwOutLen);

	static void * myZero(void * dest, char ch, size_t count);

	static void * myCopy(void * dest, const void * src, size_t count);

	static BOOL GetRandomBytes( int nRandomSize , BYTE * pbyRandom );
public:
	BYTE m_chPublicModulus [ RSA_KEY_SIZE_2 ];
	int m_nPubKey;
private:
	static int GetRondomBytes( int nRondomSize , BYTE * pbyRondom ) ;
};
