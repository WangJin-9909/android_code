#include "AES128Util.h"
#include "Base64Coder.h"
#include <android/log.h>

CAES128Impl::CAES128Impl(void){

}
CAES128Impl::~CAES128Impl(void){

}

bool RunPad(const char* In,unsigned datalen,char* Out,unsigned* padlen)
{
    int res = (datalen & 0x0000000F);
    
    
    if(*padlen< (datalen+16-res))
    {
        return false;
    }
    else
    {
  
        *padlen	=	(datalen+16-res);
        memcpy(Out,In,datalen);
      
    }
  
    memset(Out+datalen,16-res,16-res);
          
    return true;
}
char* mecopy(void *dest, const void *src, unsigned int  count)
{
    char *pDest=static_cast<char *>(dest);
    const char *pSrc=static_cast<const char *>(src);
    
    if( pDest>pSrc && pDest<pSrc+count )
    {
        for(size_t i=count-1; i<=0; ++i)
        {
            pDest[i]=pSrc[i];
        }
    }
    else
    {
        for(size_t i=0; i<count; ++i)
        {
            pDest[i]=pSrc[i];
        }
    }
    
    return pDest;
}

BOOL CAES128Impl::EncryptAES128ByECB(char* plainText, char* outText, char* keyCode){
	AES_KEY key;
	if(AES_set_encrypt_key((unsigned char*)keyCode, 128, &key) < 0){
		return false;
	}
	char outStr[1024] = {0};
	char* outData = outStr;
	int len1 = strlen(plainText);
	int end_len = 0;
	unsigned len = len1 + 160;
	unsigned& padlen = len;
	char* srcVal = (char*)malloc(len);
	memset(srcVal, 0, len);
	char* padVal = (char*)malloc(len);
	memset(padVal, 0, len);
	mecopy(srcVal, plainText, len1);
	//memcpy(srcVal, plainText, len1);
	if(!RunPad((const char*)srcVal, len1, padVal, &padlen)){
		delete[] srcVal;
		delete[] padVal;
		return false;
	}
	char* padVal1 = padVal;
	while(end_len < len){
		AES_ecb_encrypt((unsigned char*)padVal1, (unsigned char*)outData, &key, AES_ENCRYPT);

		padVal1 += AES_BLOCK_SIZE;
		outData += AES_BLOCK_SIZE;
		end_len += AES_BLOCK_SIZE;
	}
	Base64Coder base64cdr;
    base64cdr.Encode((const PBYTE)outStr, len);
    char* base64Str = (char*)base64cdr.EncodedMessage();
    memcpy(outText, base64Str, strlen(base64Str));
    //__android_log_print( ANDROID_LOG_DEBUG, "getAES128ByECB","chen_1 %s", base64Str);
    //free(outData);
    //outData = NULL;
    free(srcVal);
    srcVal = NULL;
    free(padVal);
    padVal = NULL;
    return true;
}

BOOL CAES128Impl::DecryptAES128ByECB(char* plainText, char* outText, char* keyCode){

	Base64Coder base64cdr;
    DWORD dwCipherLen = strlen(plainText);
    
    base64cdr.Decode((const PBYTE)plainText, dwCipherLen);
    
    char* base64Result = (char*)base64cdr.DecodedMessage();
    
    int len = strlen(plainText);
    int end_len = 0;
    char* pCipher = (char*)malloc(1024 * sizeof(char));
    memset(pCipher, 0, 1024);
    // pCipher = base64Result;

    int num = len/AES_BLOCK_SIZE;
    memcpy(pCipher, base64Result, num*AES_BLOCK_SIZE);
    
	AES_KEY key;
	if(AES_set_decrypt_key((unsigned char*)keyCode, 128, &key) < 0){
		return false;
	}
	
	char temparr[1024] = {0};
	char* strOut  = temparr;
	char* pCipherTemp = pCipher;
	while(end_len < len){
		AES_ecb_encrypt((unsigned char*)pCipherTemp, (unsigned char*)strOut, &key, AES_DECRYPT);

		pCipherTemp += AES_BLOCK_SIZE;
		strOut += AES_BLOCK_SIZE;
		end_len += AES_BLOCK_SIZE;
	}
	
	for(int ii=0;temparr[ii] != '\0'; ii++){
        if((BYTE)temparr[ii] < 17)
        {
            temparr[ii] = '\0';
            break;
        }
    }
    
    memcpy(outText, temparr, strlen(temparr));
    free(pCipher);
    pCipher = NULL;
    
    return true;


}

BOOL CAES128Impl::EncryptAES128ByCBC(char* plainText, char* outText, char* keyCode){
	unsigned char iv[16] = {'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'};
	AES_KEY key;
	if(AES_set_encrypt_key((unsigned char*)keyCode, 128, &key) < 0){
		return false;
	}

	int end_len = 0;
	int len1 = strlen(plainText);

	unsigned len = len1 + 160;
	unsigned& padlen = len;

	char* srcVal = (char*)malloc(len);
	memset(srcVal, 0, len);
	char* padVal = (char*)malloc(len);
	memset(padVal, 0, len);
	//memcpy(srcVal, plainText, len1);
	mecopy(srcVal, plainText, len1);

	if(!RunPad((const char*)srcVal, len1, padVal, &padlen))
	{
		delete[] srcVal;
		delete[] padVal;
		return false;
	}
	char* padVal1 = padVal;
	char temparr[1024] = {0};
	char* outStr = temparr;
	while(end_len < padlen){
		AES_cbc_encrypt((unsigned char*)padVal1, (unsigned char*)outStr, AES_BLOCK_SIZE, &key, iv, AES_ENCRYPT);
		padVal1+=AES_BLOCK_SIZE;
        outStr+=AES_BLOCK_SIZE;
        end_len+=AES_BLOCK_SIZE;
	}

	Base64Coder base64cdr;
	DWORD dwCipherLen = strlen(temparr);
    base64cdr.Encode((const PBYTE)temparr, padlen);
    char* base64Str = (char*)base64cdr.EncodedMessage();
    memcpy(outText, base64Str, strlen(base64Str));
    free(srcVal);
    srcVal = NULL;
    free(padVal);
    padVal = NULL;
    return true;
	
}

BOOL CAES128Impl::DecryptAES128ByCBC(char* plainText, char* outText, char* keyCode){
	Base64Coder base64cdr;
    DWORD dwCipherLen = strlen(plainText);
    base64cdr.Decode((const PBYTE)plainText, dwCipherLen);
    char* base64Result = (char*)base64cdr.DecodedMessage();
	//__android_log_print( ANDROID_LOG_DEBUG, "DecryptAES128ByCBC","=============================================");

    int len = strlen(plainText);
    int end_len = 0;
    char* pCipher = (char*)malloc(1024 * sizeof(char));
    memset(pCipher, 0, 1024);
    int CipherPeace = len/20;
	//__android_log_print( ANDROID_LOG_DEBUG, "DecryptAES128ByCBC","len = %d  end_len = %d CipherPeace = %d sizeof(base64Result) = %d", len, end_len, CipherPeace, sizeof(base64Result));
	//__android_log_print( ANDROID_LOG_DEBUG, "DecryptAES128ByCBC","base64 = %s", base64Result);
	//将Base解码的内容，放到pCipher
    if(CipherPeace == 0){
    	memcpy(pCipher, base64Result, len);
    }
    else{
    	memcpy(pCipher, base64Result, CipherPeace*AES_BLOCK_SIZE);
    }
	unsigned char iv[16] = {'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'};
	AES_KEY key;
	if(AES_set_decrypt_key((unsigned char*)keyCode, 128, &key) < 0){
		return false;
	}
	char* pCipher1= pCipher;
	char temparr[1024]={0};
    char* strOut = temparr;
	while(end_len < CipherPeace*AES_BLOCK_SIZE){
		AES_cbc_encrypt((unsigned char*)pCipher1, (unsigned char*)strOut, AES_BLOCK_SIZE, &key, iv, AES_DECRYPT);

		pCipher1 += AES_BLOCK_SIZE;
		strOut += AES_BLOCK_SIZE;
		end_len += AES_BLOCK_SIZE;
	}

	int a = strlen(temparr);
	
	int b = temparr[a-1];
	//__android_log_print( ANDROID_LOG_DEBUG, "DecryptAES128ByCBC","temparr = %s a = %d  b = %d sizeof(strOut) = %d end_len = %d", temparr, a, b, strOut, end_len);
	//comment by wangJin 20200529
	/*for(int i = 0;i < a-b; i++){
		outText[i] = temparr[i];
	}*/
	//新增加的
	for(int i = 0;i < end_len; i++){
		//__android_log_print( ANDROID_LOG_DEBUG, "DecryptAES128ByCBC","i = %d temparr[i] = %d", i, temparr[i]);
		if(temparr[i] < 31){
			break;
		}
		//__android_log_print( ANDROID_LOG_DEBUG, "DecryptAES128ByCBC","i = %d temparr[i] = %d", i, temparr[i]);
		outText[i] = temparr[i];
	}


	/*for(int ii=0;outText[ii] != '\0'; ii++){
        if((BYTE)outText[ii] < 17)
        {
            outText[ii] = '\0';
            break;
        }
    }*/

    free(pCipher);
    pCipher = NULL;
    return true;
}