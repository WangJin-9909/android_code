#pragma once
//#include "comutil.h"
//#include "Wincrypt.h"
//#include "atlcoll.h"
#include "DES3.h"

#define BUFFER_LEN			1024*200L
#define GD_REQUEST_CIPHER_TEXT_LEN 256

//struct GP
//{
//	BYTE group[8];
//};
//typedef CAtlArray<GP>CGPArray;


class CSecurityUtils
{
public:
	CSecurityUtils(void);
	~CSecurityUtils(void);

	BOOL GetHashSHA1(const UCHAR* pBuffer, ULONG BufferSize, CHAR chValue[20]);
	char* GetHashSHA256(const UCHAR* pBuffer, ULONG BufferSize);
	BOOL Encrypt3DES(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize);
	BOOL Encrypt3DESByCbc(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize);
	BOOL Decrypt3DES(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize);
	BOOL Decrypt3DESByCbc(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize);
	// Add:2016.6.6 MaKai-[SM2&SM4&openssl] Start
    BOOL EncryptSM4(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize);
	BOOL DecryptSM4(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize);
	// Add:2016.6.6 MaKai-[SM2&SM4&openssl] End

	// Add:2017.3.14 Dabing-[RSA] Start
	BOOL EncryptRSA2048(char* sContent, char* publicKey, char** sResult);
	//int ConvertAnsiToUnicode(char * pchSrc , DWORD dwSrcDataSize , wchar_t * pwchDest , DWORD dwLen );
	//int ConvertUnicodeToAnsi(wchar_t * pwchSrc , DWORD dwSrcDataSize , char * pchDest , DWORD dwLen );
	//void UpperHexStrToByte(string , BYTE*);
	//void LowerHexStrToByte(string , BYTE*);
	// Add:2017.3.14 Dabing-[RSA] End
};



