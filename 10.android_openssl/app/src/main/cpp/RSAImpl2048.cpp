#include "RSAImpl2048.h"
//#include <tchar.h>
//#include <WinCrypt.h>
////////////////////////////////////////////////////////////////////////////
///

//必须要有2位空间来根据交易类型填充 PADDING 头部，
//那么也就说密码长度最大 126 ，根据与密码服务平台的实际测试为99
//2010.07.21 朱丹提出需求密码框最大长度为12 ,1.2.0.7
//
//int CRSAImpl::s_nMaxPwdLen = RSA_MAX_DATA_SIZE - PADDING_HEAD_SIZE - 27 - 87;

//const UINT RSA_MAX_DATA_SIZE = 128 ;
const UINT RSA_MAX_DATA_SIZE = 256 ;

const UINT PADDING_HEAD_SIZE = 2 ;
const UINT COMMON_BUFFER_SIZE = 1024 ; 
const UINT RSA_KEY_SIZE = 128 ; 
const UINT BUF_SIZE_READ_FILE = 1024 ;
const UINT KEY_BLOBS_SIZE = 1024 ;

//最新最大值为99
int CRSAImpl2048::s_nMaxPwdLen = 99;
#define EXCEPTION_BAD_NEW_MEMORY  "申请内存失败，请检查您的电脑内存使用情况！"

CRSAImpl2048::CRSAImpl2048(void)
{
}


CRSAImpl2048::~CRSAImpl2048(void)
{
}


void * CRSAImpl2048::myZero(void * dest, char ch, size_t count)
{
	try
	{
		char *pDest=static_cast<char *>(dest);

		size_t nCount = 0 ;
		while( nCount < count )
		{
			myCopy( pDest + nCount , &ch , 1 ) ;

			nCount ++ ;
		}
		return pDest ;
	}
	catch( ... )
	{
		return NULL ;
	}
}


BOOL CRSAImpl2048::GetRandomBytes( int nRandomSize , BYTE * pbyRandom ) 
{
		try
		{
			char c = 0 ;
			BOOL bCtrl = TRUE ;

			for ( int j = 0 ; j < nRandomSize ; j++ )
			{
				while ( bCtrl ) 
				{					
					c = rand() % 127 ;
					if( (c >= 32  && c <= 126 ) )
					{
						bCtrl = FALSE ;
					}

				}			
				*(pbyRandom + j )= c ;				
				bCtrl = TRUE ;
			}
			return TRUE ;
		}
		catch ( ... )
		{
			return FALSE ;
		}
}

int CRSAImpl2048::ArrayReserv( PBYTE pbyBuffer ,DWORD dwBufferSize , int nBlockSize )
{
	try
	{
		//把整个Buffer 反序
		if( nBlockSize == 0 )
		{
			BYTE  byTemp		= '0' ;
			DWORD dwStep		= 0 ;

			DWORD dwArrayIndex	= dwBufferSize -1 ;
			DWORD dwIndex		= dwArrayIndex / 2 ;
				
			while( dwStep <= dwIndex )
			{
				byTemp = pbyBuffer[ dwStep ] ;
				pbyBuffer[ dwStep ] = pbyBuffer[ dwArrayIndex - dwStep ] ;
				pbyBuffer[ dwArrayIndex - dwStep ] = byTemp ;

				dwStep ++ ;
			}

			return  0 ;
		}

		//以 4byte 为单位，反序Buffer 
		else if( nBlockSize == 4 )
		{
			if( dwBufferSize % 4 != 0 )
			{ 
				return -1 ;
			}

			int nBlockNum = dwBufferSize / 4 ;

			while( nBlockNum >= 1 )
			{
				if( 0 != ArrayReserv( pbyBuffer + ( nBlockNum - 1 ) * 4  , 4 ) )
				{
					return -3 ;
				}
				nBlockNum -- ;
			}
		}

		//以 8byte 为单位，反序Buffer 
		else if( nBlockSize == 8 )
		{
			if( dwBufferSize % 8 != 0 )
			{
				return -1 ;
			}

			int nBlockNum = dwBufferSize / 8 ;

			while( nBlockNum >= 1 )
			{
				if( 0 != ArrayReserv( pbyBuffer + ( nBlockNum - 1 ) * 8  , 8 ) )
				{
					return -4 ;
				}
				nBlockNum -- ;
			}
		}
		else
		{
			//DoNothing 
			return -2 ;
		}
	}
	catch ( ... )
	{
		return -7 ;
	}
	return  0 ;
}


// Add:2016.6.28 MaKai-[Encrypt hardwareInfo] Start
int CRSAImpl2048::DecryptByPublicKey(BYTE * pbyPlanText)
{
	if(NULL == pbyPlanText)
	{
		return 1;
	}
	ArrayReserv( pbyPlanText , RSA_KEY_SIZE_2 ) ;
	BYTE pchPublicModulus[ RSA_KEY_SIZE_2 ] = {
		0x9b, 0x1c, 0x7b, 0xc1, 0xd2, 0x73, 0xce, 0x5d, 0xfb, 0xe1, 0xe6, 0x7d, 0xa2, 0x6b, 0xe5, 0x2f,
		0x15, 0x26, 0x25, 0x12, 0x48, 0x1c, 0x32, 0x44, 0x79, 0x6a, 0xb0, 0x8b, 0xe4, 0x89, 0xf4, 0x97,
		0x01, 0x4c, 0x6c, 0xce, 0x69, 0x9e, 0x7a, 0x3d, 0x1b, 0x89, 0xb2, 0x79, 0x96, 0x31, 0x33, 0x01,
		0x1c, 0xf6, 0xf7, 0x3a, 0xbe, 0xd5, 0xa8, 0x5b, 0xfa, 0x94, 0xb7, 0x9f, 0x33, 0xb0, 0xee, 0x57,
		0xa5, 0x6f, 0x0b, 0xb7, 0xac, 0x72, 0xe2, 0x05, 0x42, 0x24, 0xa3, 0xf1, 0x19, 0x87, 0xf1, 0xca,
		0x76, 0xe2, 0xae, 0x6e, 0x39, 0xcc, 0x78, 0x90, 0x3c, 0x03, 0xeb, 0x41, 0x89, 0x32, 0xef, 0x9e,
		0x7b, 0xa0, 0x96, 0x12, 0x7c, 0xd2, 0x07, 0xec, 0xff, 0x45, 0x57, 0xbb, 0x8c, 0xd1, 0xf9, 0xd7,
		0x11, 0x48, 0x5c, 0xe6, 0xaa, 0xff, 0xb8, 0xd9, 0xd3, 0x14, 0x25, 0xac, 0x0b, 0xb3, 0x77, 0x15,
		0x83, 0x31, 0xbe, 0x27, 0xa7, 0x9f, 0x4c, 0x38, 0x2f, 0x53, 0xb9, 0x95, 0xf8, 0x5c, 0x55, 0xf5,
		0xcc, 0x07, 0xe8, 0xf3, 0xb9, 0xc8, 0x32, 0xf1, 0xbf, 0xae, 0xca, 0xe5, 0xf9, 0x43, 0xf0, 0x8b,
		0x8f, 0xb9, 0x12, 0x27, 0x05, 0xcf, 0xee, 0xf6, 0x11, 0x0c, 0x22, 0x6d, 0x3d, 0x39, 0xee, 0x0f,
		0xdd, 0x3f, 0xe0, 0x5c, 0x23, 0x2b, 0xb4, 0x93, 0xb6, 0xd8, 0x09, 0x20, 0x2a, 0x52, 0x7f, 0x27,
		0x63, 0x65, 0x6c, 0xf2, 0x63, 0xe0, 0xd4, 0x34, 0x78, 0x79, 0xeb, 0xc1, 0x8a, 0x4f, 0x9d, 0xbd,
		0x1b, 0x66, 0x8a, 0x7c, 0x68, 0x19, 0x3f, 0x9c, 0x6a, 0xa4, 0xee, 0x56, 0x6e, 0x25, 0x8d, 0x87,
		0x69, 0x9d, 0xb3, 0x70, 0xb0, 0x2d, 0x56, 0xf0, 0xd1, 0x1e, 0x8b, 0x1e, 0xd2, 0xb4, 0x72, 0xfc,
		0x66, 0xf2, 0x69, 0x56, 0xf0, 0xe0, 0x27, 0x93, 0x91, 0x03, 0x33, 0xd1, 0x16, 0x44, 0x0a, 0xbf
	};
	BYTE *pchMyModulus=NULL;
	ArrayReserv( (BYTE*) pchPublicModulus , RSA_KEY_SIZE_2 ) ;
	pchMyModulus = pchPublicModulus;
	//生成 Modulu 大数 -----------------------------------------------------------
	CBigInt *pbnModule = new CBigInt( (PBYTE)pchMyModulus, RSA_KEY_SIZE_2 ) ; 
	if( pbnModule == NULL )
	{ throw EXCEPTION_BAD_NEW_MEMORY ; }

	//生成 Exponet 大数-----------------------------------------------------------
	CBigInt bnExponent ;
	bnExponent = bnExponent + ( unsigned long )65537 ;
	if( bnExponent == NULL )
	{ throw EXCEPTION_BAD_NEW_MEMORY ; }

	//构造大整数前必须反序！！！！
	//CRSAImpl::ArrayReserv( pbyPlanText , RSA_KEY_SIZE ) ;

	CBigInt *pbnPlanText = new CBigInt( pbyPlanText, RSA_KEY_SIZE_2 ) ;
	if( pbnPlanText == NULL )
	{ throw EXCEPTION_BAD_NEW_MEMORY ; }

	//求模，即加密 --------------------------------------------------------------
	CBigInt bnCipterText=pbnPlanText->PowerMod(bnExponent,*pbnModule );

	//获取加密后的数据 ---------------------------------------------------------
	bnCipterText.GetBytes( pbyPlanText , RSA_KEY_SIZE_2 ) ;


	delete pbnPlanText ;
	pbnPlanText = NULL ;

	delete pbnModule ;
	pbnModule = NULL ;

	return 0;
}
// Add:2016.6.28 MaKai-[Encrypt hardwareInfo] End

int CRSAImpl2048::DecryptByPublicKey2(BYTE * pbyPlanText, BYTE* keyCode)
{
	if(NULL == pbyPlanText)
	{
		return 1;
	}
	BYTE *pchMyModulus=NULL;
	ArrayReserv( pbyPlanText , RSA_KEY_SIZE_2 ) ;
	ArrayReserv( keyCode , RSA_KEY_SIZE_2 ) ;
	pchMyModulus = keyCode;
	//生成 Modulu 大数 -----------------------------------------------------------
	CBigInt *pbnModule = new CBigInt( (PBYTE)pchMyModulus, RSA_KEY_SIZE_2 ) ; 
	if( pbnModule == NULL )
	{ throw EXCEPTION_BAD_NEW_MEMORY ; }
	//生成 Exponet 大数-----------------------------------------------------------
	CBigInt bnExponent ;
	bnExponent = bnExponent + ( unsigned long )65537 ;
	if( bnExponent == NULL )
	{ throw EXCEPTION_BAD_NEW_MEMORY ; }
	//构造大整数前必须反序！！！！
	//CRSAImpl::ArrayReserv( pbyPlanText , RSA_KEY_SIZE ) ;
	CBigInt *pbnPlanText = new CBigInt( pbyPlanText, RSA_KEY_SIZE_2 ) ;
	if( pbnPlanText == NULL )
	{ throw EXCEPTION_BAD_NEW_MEMORY ; }
	//求模，即加密 --------------------------------------------------------------
	CBigInt bnCipterText=pbnPlanText->PowerMod(bnExponent,*pbnModule );
	//获取加密后的数据 ---------------------------------------------------------
	bnCipterText.GetBytes( pbyPlanText , RSA_KEY_SIZE_2 ) ;

	delete pbnPlanText ;
	pbnPlanText = NULL ;

	delete pbnModule ;
	pbnModule = NULL ;

	return 0;
}


BOOL CRSAImpl2048::PaddingData_PKCS1(BYTE* InData, DWORD dwInLen, BYTE* OutData, DWORD& dwOutLen)
{
	if (dwInLen > RSA_MAX_DATA_SIZE-11)
	{
		return FALSE;
	}

	if (OutData == NULL || InData == NULL)
	{
		return FALSE;
	}

	int iRandomSize = RSA_MAX_DATA_SIZE - dwInLen -3;
	if (iRandomSize <8 )
	{
		return FALSE;
	}
	
	BYTE pbRandom[RSA_MAX_DATA_SIZE] = "\0";
	myZero(pbRandom, 0, RSA_MAX_DATA_SIZE);

	BOOL  bRet = GetRandomBytes(iRandomSize, pbRandom);
	if (!bRet)
	{
		myZero(pbRandom, 0, RSA_MAX_DATA_SIZE);
		return FALSE;
	}

	//GetPaddingData	
	BYTE head1[2] = {0x00,0x02};
	BYTE head2[1] = {0x00};
	myCopy(OutData, head1, 2);
	myCopy(OutData+2, pbRandom, iRandomSize);
	myCopy(OutData+2+iRandomSize, head2, 1);
	myCopy(OutData+2+iRandomSize+1, InData, dwInLen);
	
	dwOutLen = RSA_MAX_DATA_SIZE;

	return TRUE;
}


void * CRSAImpl2048::myCopy(void * dest, const void * src, size_t count)
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

// Add:2016.6.30 MaKai[Encrypt hardwareInfo] Start
//RSA加密算法：C=M^E mod N	（C：密文，M：明文，E：公钥，N：模）
//RSA解密算法：M=C^D mod N	（M：明文，C：密文，D：私钥，N：模）
int CRSAImpl2048::Encrypt(BYTE * pbyPlanText ,DWORD &dwDataSize ,DWORD &dwBufferSize , DWORD &dwError ,BYTE *publicKey, BOOL IfPadding  )
{
	try
	{
		if( dwDataSize > RSA_MAX_DATA_SIZE_2 )
		{
			return -1 ;
		}

			BYTE *pchPublicModulus = publicKey;

			//构造大整数前必须反序！！！！
			ArrayReserv( (BYTE*) pchPublicModulus , RSA_KEY_SIZE_2 ) ;

			DWORD dwDataLen = dwDataSize  ;
			if( !IfPadding )
			{
				//生成 Modulu 大数 -----------------------------------------------------------
				CBigInt *pbnModule = new CBigInt( (PBYTE)pchPublicModulus , RSA_KEY_SIZE_2 ) ; 
				if( pbnModule == NULL ){ throw EXCEPTION_BAD_NEW_MEMORY ; }

				//生成 Exponet 大数-----------------------------------------------------------
				CBigInt bnExponent ;

				long pubKeyTmp = 65537;

				bnExponent = bnExponent + ( unsigned long )pubKeyTmp;//公钥

				//生成 PlanText （明文） 大数 -----------------------------------------------

				//构造大整数前必须反序！！！！
				ArrayReserv( pbyPlanText , RSA_KEY_SIZE_2 );

				CBigInt *pbnPlanText = new CBigInt( pbyPlanText , RSA_KEY_SIZE_2 ) ;
				if( pbnPlanText == NULL )
				{
					throw EXCEPTION_BAD_NEW_MEMORY ; 
				}

				//求模，即加密 C=M^E mod N--------------------------------------------------------------
				CBigInt bnCipterText = pbnPlanText->PowerMod( bnExponent , *pbnModule ) ;

				//获取加密后的数据 ---------------------------------------------------------
				bnCipterText.GetBytes( pbyPlanText , RSA_KEY_SIZE_2 ) ;
				dwDataSize = RSA_KEY_SIZE_2 ;

				delete pbnPlanText ;
				pbnPlanText = NULL ;

				delete pbnModule ;
				pbnModule = NULL ;
			}

			return 0 ;
	}
	catch( ... )
	{
		return -7 ;
	}		
}
// Add:2016.6.30 MaKai[Encrypt hardwareInfo] End
int CRSAImpl2048::Decrypt( DWORD &dwError ,BOOL IfPadding = FALSE ,int nPaddingType = 0 ) 
{
#ifdef _DEBUG
	HCRYPTKEY hRSAKey;
	HCRYPTPROV hCryptProv;

	if(!CryptAcquireContext( &hCryptProv, _T("TestContainerDecrypt"), MS_ENHANCED_PROV, PROV_RSA_FULL, 0))
	{
		dwError = GetLastError();
		if(NTE_BAD_KEYSET == dwError)
		{
			if(!CryptAcquireContext(&hCryptProv, _T("TestContainerDecrypt"), MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
			{
				dwError = GetLastError();
				return -1;
			}
		}
	}

	//read private key blob 
	DWORD dwBufLen = KEY_BLOBS_SIZE_2 ; 

#ifdef _DEBUG_RSA_KEY_FROM_FILE_
	char pPrivateKeyBlob[ KEY_BLOBS_SIZE ] = {0} ;
	CDebugHelper::ReadFile2Buffer( (TCHAR*)"c:\\PrivateKeyBlob.txt" , pPrivateKeyBlob , dwBufLen ) ;
#else
	char pPrivateKeyBlob[ KEY_BLOBS_SIZE_2 ] = {0} ;
#endif

	if (!CryptImportKey( hCryptProv,(BYTE*)pPrivateKeyBlob ,dwBufLen, NULL, CRYPT_EXPORTABLE, &hRSAKey))
	{
		dwError = GetLastError();
		return -1;
	}

	//DWORD	dwBufferSize						= BUF_SIZE_READ_FILE_2 ;
	DWORD	dwFileSize							= BUF_SIZE_READ_FILE_2 ;
	DWORD	dwErrorCode							= 0 ;
	BYTE	pbBuffer[ BUF_SIZE_READ_FILE_2 ]		= { 0 } ;

	if( !IfPadding )
	{
		if( !CryptDecrypt( hRSAKey , 0 ,TRUE , 0 ,pbBuffer ,&dwFileSize ) )
		{
			CryptReleaseContext( hCryptProv , 0 ) ;//20150204
			dwErrorCode = GetLastError() ;
			//CDebugHelper::ShowMessageBox( _T( "Error : \r\n if( !CryptDecrypt( hRSAKey , 0 ,TRUE , 0 ,pb " ) ) ;
			return -1 ;
		}
	}
	else
	{
		//CDebugHelper::ShowMessageBox( _T( "No Impl !" ) ) ;
		CryptDestroyKey( hRSAKey ) ;
		CryptReleaseContext( hCryptProv , 0 ) ;
		return -1 ;
	}

	CryptDestroyKey( hRSAKey ) ;
	CryptReleaseContext( hCryptProv, 0 ) ;
#endif
	return 0 ;
}
	

