#include "SecurityUtils.h"
#include "time.h"
#include "sha1.h"
#include "sha256.h"
#include <android/log.h>
#include "SM4.h"
#include "RSAImpl2048.h"


CSecurityUtils::CSecurityUtils(void)
{
}

CSecurityUtils::~CSecurityUtils(void)
{
}

BOOL CSecurityUtils::GetHashSHA1(const UCHAR* pBuffer, ULONG BufferSize, CHAR chValue[20])
{	
	if(pBuffer == NULL || BufferSize < 1)
		return FALSE;

	ULONG OutSize=0;		
	SHA1_CTX ctx;
	SHA1Init( &ctx );		
	while(BufferSize>BUFFER_LEN)
	{		
		BufferSize-=BUFFER_LEN;		
		SHA1Update(&ctx, pBuffer, BUFFER_LEN);		
		pBuffer += BUFFER_LEN;			
	}	
	SHA1Update(&ctx, pBuffer, BufferSize);	
	SHA1Final((unsigned char*)chValue,&ctx);		
	
	return TRUE;
}

char* CSecurityUtils::GetHashSHA256(const UCHAR* pBuffer, ULONG BufferSize)
{
	if(pBuffer == NULL || BufferSize < 1)
		return NULL;

	unsigned char digest[SHA256::DIGEST_SIZE];
	memset(digest, 0, SHA256::DIGEST_SIZE);

	SHA256 ctx = SHA256();
	ctx.init();
	ctx.update(pBuffer, BufferSize);
	ctx.final((unsigned char*)digest);

	// char buf[2 * SHA256::DIGEST_SIZE + 1];
	char* buf = (char*)malloc((2 * SHA256::DIGEST_SIZE + 1)*sizeof(char));
	buf[2 * SHA256::DIGEST_SIZE] = 0;
	for (int i = 0; i < SHA256::DIGEST_SIZE; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);

	return buf;
}

BOOL CSecurityUtils::Encrypt3DES(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize)
{	
	if(pCiphertext == NULL)
	{
		 return FALSE;
	}
	
	//将原始内容进行补位算法，以便符合3DES加密对原始内容的字节要求
	unsigned len		=dwPlantextSize+8; //保险起见，以免未来出现内存溢出现象
	unsigned& padlen	=len;

	char *srcVal		= new char[len];
	memset(srcVal,0,len);

	char *padVal		= new char[len]; //补位后的结果buffer 
	memset(padVal,0,len);

	//strcpy(srcVal,(const char*)pPlaintext);
	mycopy(srcVal,pPlaintext, dwPlantextSize);

	//进行填充,注意有3种填充算法,我们需要使用第三种
	//if (!CDES::RunPad(2,(const char*) srcVal,strlen(srcVal),padVal,padlen))
	if (!CDES::RunPad(2,(const char*) srcVal,dwPlantextSize,padVal,padlen))
	{
		delete []srcVal;
		delete []padVal;
		return FALSE;
	}

	//进行加密
	char* destval	= (char*)malloc(sizeof(char)*(padlen+1)); //加密后的结果存放buffer。加密前后字节数不变，因此在destval中多一位，以便设定字符串的结束符\0。
	memset(destval,0,padlen+1);
	//destval[padlen] = '\0';
	if (!CDES::RunDes(0,0,padVal,destval,padlen,(const char*)pKey,(const unsigned char)dwKeySize)) 
	{
		delete []srcVal;
		delete []padVal;
		free(destval);
		return FALSE;
	}

	memset(pCiphertext, 0, dwCiphertextSize);
	mycopy(pCiphertext, destval, padlen);
	dwCiphertextSize	= padlen;
	
	delete []srcVal;
	delete []padVal;
	free(destval);

	return TRUE;
}

BOOL CSecurityUtils::Encrypt3DESByCbc(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize)
{	
	if(pCiphertext == NULL)
	{
		 return FALSE;
	}
	
	//将原始内容进行补位算法，以便符合3DES加密对原始内容的字节要求
	unsigned len		=dwPlantextSize+8; //保险起见，以免未来出现内存溢出现象
	unsigned& padlen	=len;

	char *srcVal		= new char[len];
	memset(srcVal,0,len);

	char *padVal		= new char[len]; //补位后的结果buffer 
	memset(padVal,0,len);

	//strcpy(srcVal,(const char*)pPlaintext);
	mycopy(srcVal,pPlaintext, dwPlantextSize);

	//进行填充,注意有3种填充算法,我们需要使用第三种
	//if (!CDES::RunPad(2,(const char*) srcVal,strlen(srcVal),padVal,padlen))
	if (!CDES::RunPad(2,(const char*) srcVal,dwPlantextSize,padVal,padlen))
	{
		delete []srcVal;
		delete []padVal;
		return FALSE;
	}

	//进行加密
	char* destval	= (char*)malloc(sizeof(char)*(padlen+1)); //加密后的结果存放buffer。加密前后字节数不变，因此在destval中多一位，以便设定字符串的结束符\0。
	memset(destval,0,padlen+1);
	//destval[padlen] = '\0';
	if (!CDES::RunDes(0,1,padVal,destval,padlen,(const char*)pKey,(const unsigned char)dwKeySize)) 
	{
		delete []srcVal;
		delete []padVal;
		free(destval);
		return FALSE;
	}
	
	memset(pCiphertext, 0, dwCiphertextSize);
	mycopy(pCiphertext, destval, padlen);
	dwCiphertextSize	= padlen;
	
	delete []srcVal;
	delete []padVal;
	free(destval);

	return TRUE;
}

BOOL CSecurityUtils::Decrypt3DES( BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize)
{	
	if(pCiphertext == NULL)
	{
		 return FALSE;
	}
	
	//将原始内容进行补位算法，以便符合3DES加密对原始内容的字节要求
	unsigned len		= dwPlantextSize+8; //保险起见，以免未来出现内存溢出现象
	unsigned& padlen	= len;
	char *srcVal		= new char[len];
	memset(srcVal,0,len);

	char *padVal		= new char[len]; //补位后的结果buffer 
	memset(padVal,0,len);

	//strcpy(srcVal,(const char*)pPlaintext);
	mycopy(srcVal,pPlaintext, dwPlantextSize);

	//进行填充,注意有3种填充算法,我们需要使用第三种
	//if (!CDES::RunPad(2,(const char*) srcVal,strlen(srcVal),padVal,padlen))
	if (!CDES::RunPad(2,(const char*) srcVal,dwPlantextSize,padVal,padlen))
	{
		delete []srcVal;
		delete []padVal;
		return FALSE;
	}
	//进行解密	
	char* destval		= (char*)malloc(sizeof(char)*(padlen+1)); //加密后的结果存放buffer。加密前后字节数不变，因此在destval中多一位，以便设定字符串的结束符\0。
	memset(destval,0,padlen+1);

	if (!CDES::RunDes(1,0,padVal,destval,padlen,(const char*)pKey,(const unsigned char)dwKeySize)) 
	{
		delete []srcVal;
		delete []padVal;
		free(destval);
		return FALSE;
	}
	if (NULL == destval)
	{
		return FALSE;
	}
	//destval[dwCiphertextSize]	= '\0';
	int destvalLegth = strlen(destval);
	for(int i=0; i<destvalLegth; i++)
	{
		if(destval[i]<9){
			destval[i] = '\0';
			dwCiphertextSize = i;
			break;
		}			
		continue;
	}
	//__android_log_print( ANDROID_LOG_DEBUG, "3DESTEST","destval : %s",  destval );
	memset(pCiphertext, 0, dwCiphertextSize);
	mycopy(pCiphertext, destval, dwCiphertextSize);
	//__android_log_print( ANDROID_LOG_DEBUG, "3DESTEST","pCiphertext : %s",  pCiphertext );
//	dwCiphertextSize			= strlen(destval);

	delete []srcVal;
	delete []padVal;
	free(destval);

	return TRUE;
}

BOOL CSecurityUtils::Decrypt3DESByCbc( BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize)
{	
	if(pCiphertext == NULL)
	{
		 return FALSE;
	}
	
	//将原始内容进行补位算法，以便符合3DES加密对原始内容的字节要求
	unsigned len		= dwPlantextSize+8; //保险起见，以免未来出现内存溢出现象
	unsigned& padlen	= len;
	char *srcVal		= new char[len];
	memset(srcVal,0,len);

	char *padVal		= new char[len]; //补位后的结果buffer 
	memset(padVal,0,len);

	//strcpy(srcVal,(const char*)pPlaintext);
	mycopy(srcVal,pPlaintext, dwPlantextSize);

	//进行填充,注意有3种填充算法,我们需要使用第三种
	//if (!CDES::RunPad(2,(const char*) srcVal,strlen(srcVal),padVal,padlen))
	if (!CDES::RunPad(2,(const char*) srcVal,dwPlantextSize,padVal,padlen))
	{
		delete []srcVal;
		delete []padVal;
		return FALSE;
	}
	//进行解密	
	char* destval		= (char*)malloc(sizeof(char)*(padlen+1)); //加密后的结果存放buffer。加密前后字节数不变，因此在destval中多一位，以便设定字符串的结束符\0。
	memset(destval,0,padlen+1);

	if (!CDES::RunDes(1,1,padVal,destval,padlen,(const char*)pKey,(const unsigned char)dwKeySize)) 
	{
		delete []srcVal;
		delete []padVal;
		free(destval);
		return FALSE;
	}
	if (NULL == destval)
	{
		return FALSE;
	}
	//destval[dwCiphertextSize]	= '\0';
	int destvalLegth = strlen(destval);
	for(int i=0; i<destvalLegth; i++)
	{
		if(destval[i]<9){
			destval[i] = '\0';
			dwCiphertextSize = i;
			break;
		}			
		continue;
	}
	//__android_log_print( ANDROID_LOG_DEBUG, "3DESTEST","destval : %s",  destval );
	memset(pCiphertext, 0, dwCiphertextSize);
	mycopy(pCiphertext, destval, dwCiphertextSize);
	//__android_log_print( ANDROID_LOG_DEBUG, "3DESTEST","pCiphertext : %s",  pCiphertext );
//	dwCiphertextSize			= strlen(destval);

	delete []srcVal;
	delete []padVal;
	free(destval);

	return TRUE;
}
// Add:2016.6.6 MaKai-[SM2&SM4&openssl] Start
BOOL CSecurityUtils::EncryptSM4(BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize)
{	
	if(pCiphertext == NULL || dwKeySize == 0)
	{
		 return FALSE;
	}
	//将原始内容进行补位算法，以便符合SM4加密对原始内容的字节要求
	unsigned len		=dwPlantextSize+16; //保险起见，以免未来出现内存溢出现象
	unsigned& padlen	=len;

	char *srcVal		= new char[len];
	memset(srcVal,0,len);

	char *padVal		= new char[len]; //补位后的结果buffer 
	memset(padVal,0,len);

	//strcpy(srcVal,(const char*)pPlaintext);
	mycopy(srcVal,pPlaintext, dwPlantextSize);

	//进行填充,注意有3种填充算法,我们需要使用第三种
	//if (!CDES::RunPad(2,(const char*) srcVal,strlen(srcVal),padVal,padlen))
	if (!CSM4::RunPad(2,(const char*) srcVal,dwPlantextSize,padVal,padlen))
	{
		delete []srcVal;
		delete []padVal;
		return FALSE;
	}
	//进行加密
	char* destval	= (char*)malloc(sizeof(char)*(padlen+1)); //加密后的结果存放buffer。加密前后字节数不变，因此在destval中多一位，以便设定字符串的结束符\0。
	memset(destval,0,padlen+1);
	//destval[padlen] = '\0';

	if (!CSM4::Encrypt(0,0,padVal,destval,padlen,(const char*)pKey,(const unsigned char)dwKeySize)) 
	{
		delete []srcVal;
		delete []padVal;
		free(destval);
		return FALSE;
	}
	memset(pCiphertext, 0, dwCiphertextSize);
	mycopy(pCiphertext, destval, padlen);
	dwCiphertextSize	= padlen;
	
	delete []srcVal;
	delete []padVal;
	free(destval);

	return TRUE;
}
BOOL CSecurityUtils::DecryptSM4( BYTE* pPlaintext, DWORD dwPlantextSize, BYTE* pCiphertext, DWORD& dwCiphertextSize, BYTE* pKey, DWORD dwKeySize)
{	
	if(pCiphertext == NULL || dwKeySize == 0)
	{
		 return FALSE;
	}
	
	//将原始内容进行补位算法，以便符合3DES加密对原始内容的字节要求
	unsigned len		= dwPlantextSize+16; //保险起见，以免未来出现内存溢出现象
	unsigned& padlen	= len;
	char *srcVal		= new char[len];
	memset(srcVal,0,len);

	char *padVal		= new char[len]; //补位后的结果buffer 
	memset(padVal,0,len);

	//strcpy(srcVal,(const char*)pPlaintext);
	mycopy(srcVal,pPlaintext, dwPlantextSize);

	//进行填充,注意有3种填充算法,我们需要使用第三种
	//if (!CDES::RunPad(2,(const char*) srcVal,strlen(srcVal),padVal,padlen))
	if (!CSM4::RunPad(2,(const char*) srcVal,dwPlantextSize,padVal,padlen))
	{
		delete []srcVal;
		delete []padVal;
		return FALSE;
	}
	//进行解密	
	char* destval		= (char*)malloc(sizeof(char)*(padlen+1)); //加密后的结果存放buffer。加密前后字节数不变，因此在destval中多一位，以便设定字符串的结束符\0。
	memset(destval,0,padlen+1);

	if (!CSM4::Decrypt(1,0,padVal,destval,padlen,(const char*)pKey,(const unsigned char)dwKeySize)) 
	{
		delete []srcVal;
		delete []padVal;
		free(destval);
		return FALSE;
	}
	if (NULL == destval)
	{
		return FALSE;
	}
	//destval[dwCiphertextSize]	= '\0';
	int destvalLegth = strlen(destval);
	//debug
	//for(int i=0; i<destvalLegth; i++)
	//{
	//	__android_log_print( ANDROID_LOG_DEBUG, "DecryptSM4","destval[%d] is %x", i, destval[i]);

	//}
	//debug
	for(int i=0; i<destvalLegth; i++)
	{
		if(destval[i] < 0x11){
			destval[i] = '\0';
			dwCiphertextSize = i;
			//__android_log_print( ANDROID_LOG_DEBUG, "DecryptSM4","dwCiphertextSizeis %d", i, dwCiphertextSize);
			break;
		}			
		continue;
	}
	//__android_log_print( ANDROID_LOG_DEBUG, "DecryptSM4","destval : %s",  destval );
	memset(pCiphertext, 0, dwCiphertextSize);
	mycopy(pCiphertext, destval, dwCiphertextSize);
	//__android_log_print( ANDROID_LOG_DEBUG, "DecryptSM4","pCiphertext : %s",  pCiphertext );
//	dwCiphertextSize			= strlen(destval);

	delete []srcVal;
	delete []padVal;
	free(destval);

	return TRUE;
}
// Add:2016.6.6 MaKai-[SM2&SM4&openssl] End

// Add:2017.3.14 Dabing-[RSA] Start

void LowerHexStrToByte(char* str_arr, BYTE *byte_arr)  
{  
	unsigned char ch1;  
	unsigned char ch2;  
	int k = 0;  
	for (int i=0; i<strlen(str_arr); i = i+2)  
	{  
		ch1 = *(str_arr+i); 
		ch2 = *(str_arr+i+1);  
		if (ch1>=48 && ch1 <= 57)  
		{  
			ch1 &= 0x0F;  
		}  
		if (ch1>='a' && ch1 <='f')  
		{  
			ch1 &= 0x0F;  
			ch1 += 0x09;  
		}  
		if (ch2 >= 48 && ch2 <= 57)  
		{  
			ch2 &= 0x0F;  
		}  
		if (ch2>='a' && ch2 <='f')  
		{  
			ch2 &= 0x0F;  
			ch2 += 0x09;  
		}  
		ch1<<=4;  
		byte_arr[k] = ch1 + ch2;//int类型转byte类型，有问题

		k++;  
	}  
}

/*int CSecurityUtils::ConvertAnsiToUnicode(char * pchSrc , DWORD dwSrcDataSize , wchar_t * pwchDest , DWORD dwLen )
{
	if( dwSrcDataSize > dwLen ) 
	{
		return -1 ;
	}
	DWORD nLength = 0 ;
	nLength = strlen(pchSrc);
	//nLength = MultiByteToWideChar( 0 , 0 , pchSrc , -1 , NULL , 0 ) ;
	if( nLength > dwLen )
	{
		return -2 ;
	}

	dwLen = strlen(pchSrc);
	//dwLen = MultiByteToWideChar( 0 , 0 , pchSrc , -1 , pwchDest , nLength ) ;
	if( dwLen != nLength )
	{
		return -3 ;
	}
	return 0 ;
}*/


int byteToHexStr2( PBYTE pbySrcBuffer , DWORD dwBufferSize ,PBYTE pbyHexBuffer )
{
	try
	{
		for( DWORD i = 0 ; i < dwBufferSize ; i++ )
		{
			char chHex1 = '0' ;
			char chHex2 = '0';

			//直接将unsigned char赋值给整型的值，系统会正动强制转换
			int nCh2IntValue=pbySrcBuffer[ i ] ; 

			int nQuotient = nCh2IntValue / 16 ;
			int nResidue  = nCh2IntValue % 16 ;

			//将商转成字母
			if( nQuotient >= 0  &&  nQuotient <= 9 )
				chHex1 = (char)( '0' + nQuotient ) ;
			else
				chHex1 = (char)( 'A' + ( nQuotient - 10 ) )  ;

			//将余数转成字母
			if( nResidue >= 0  &&  nResidue <=9 )
				chHex2 = (char)( '0'+ nResidue ) ;
			else
				chHex2 = (char)( 'A' + ( nResidue -10 ) ) ;

			//将Hex字母填充到Hex Buffer中
			pbyHexBuffer[ i * 2 ]	= chHex1 ;
			pbyHexBuffer[ i * 2 +1 ] = chHex2 ;
		}

		return 0 ;
	}
	catch ( ... )
	{
		return -7 ;
	}
}

BOOL CSecurityUtils::EncryptRSA2048(char* sContent, char* publicKey, char** sResult)
{	
	//sResult = sContent;
	try
	{
		BYTE RT [GD_REQUEST_CIPHER_TEXT_LEN] = { 0 } ;

		//CString szPlanText = sContent;
		BYTE *byte_arrT = new BYTE[520];
		memset(byte_arrT, 0, 520);
		LowerHexStrToByte(publicKey, byte_arrT);

		PBYTE pbyPlanText = (PBYTE)sContent;
		if( pbyPlanText == NULL )
		{
			return FALSE ;
		}
		else
		{
			memcpy( RT , pbyPlanText , strlen(sContent)) ;
		}
		//CString miwen(RT);
		//xLog("密文： %s\n",RT);
		DWORD dwBufferSize = GD_REQUEST_CIPHER_TEXT_LEN;
		DWORD dwErrorCode = 0;
		DWORD dwDataSize = strlen(sContent); 
		//szPlanText.Empty();//no use from now

#ifndef _DEBUG_RSA_MANUL_PADDING_  

		//为配合IBMJava服务器解密，需用PKCS1填充标准进行填充
		BYTE*  pRTPadding = new BYTE[ GD_REQUEST_CIPHER_TEXT_LEN ];	
		if( CRSAImpl2048::PaddingData_PKCS1(RT ,dwDataSize , pRTPadding ,dwDataSize ) == FALSE )
		{	
			//xLog( _T( "Error：对密码明文进行PADDING 失败！\n" ) ) ;

			delete []pRTPadding;
			return FALSE;
		}
		memcpy(RT,pRTPadding,dwDataSize);
		//memcpy_s(RT,GD_REQUEST_CIPHER_TEXT_LEN,pRTPadding,dwDataSize);
		delete []pRTPadding;
#endif

		//Encrypt ------------------------------------------------------------------------------------------------
		if( 0 != CRSAImpl2048::Encrypt( RT , dwDataSize , dwBufferSize , dwErrorCode, byte_arrT) )
		{
			return FALSE ;
		}
		if( 0 != CRSAImpl2048::ArrayReserv( RT , GD_REQUEST_CIPHER_TEXT_LEN ) )
		{
			//xLog( _T( "Error：加密数据反序失败！\n" ) ) ;
			return FALSE;
		}

		BYTE pbyCipter2Hex[ ( GD_REQUEST_CIPHER_TEXT_LEN * 2 + 1)] = { 0 } ;
		//memset(pbyCipter2Hex, 0, ( GD_REQUEST_CIPHER_TEXT_LEN * 2 + 1));
		// 密文 + 校验结果 转换为 16进制 ------------------------------------------------------------------------------
		if( 0 != byteToHexStr2( RT , GD_REQUEST_CIPHER_TEXT_LEN , pbyCipter2Hex ) )
		{
			return FALSE ;
		}
		//转换为UNICODE 
		wchar_t pbyCipter2Hex2UNICODE[ ( GD_REQUEST_CIPHER_TEXT_LEN * 2 + 1)] = { 0 } ;
		DWORD dwHex2Unicode = ( GD_REQUEST_CIPHER_TEXT_LEN * 2 + 1);

		//if( 0 != ConvertAnsiToUnicode( (char*)pbyCipter2Hex , GD_REQUEST_CIPHER_TEXT_LEN * 2 , pbyCipter2Hex2UNICODE , dwHex2Unicode ) ) 
		//{
		//	return FALSE ;
		//}
		pbyCipter2Hex2UNICODE[ ( GD_REQUEST_CIPHER_TEXT_LEN * 2 )] = L'\0' ;

		//拷贝数据到返回变量 -------------------------------------------------------------------------------
		//sResult = CString(pbyCipter2Hex2UNICODE);
		//sResult = (char*)pbyCipter2Hex;
		//pbyCipter2Hex[ ( GD_REQUEST_CIPHER_TEXT_LEN * 2 )] = L'\0' ;
		memcpy(*sResult, (char*)pbyCipter2Hex, ( GD_REQUEST_CIPHER_TEXT_LEN * 2 ));
		return TRUE;
	}
	catch ( ... )
	{
		return FALSE ;
	}
}
// Add:2017.3.14 Dabing-[RSA] End