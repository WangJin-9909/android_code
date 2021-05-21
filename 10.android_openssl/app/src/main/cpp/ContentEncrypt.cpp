#include "ContentEncrypt.h"
#include "SecurityUtils.h"
#include "Base64Coder.h"
#include "sha1.h"
#include "XyECPoint.h"
#include "SM2.h"
#include "SM2EcKey.h"
#include "SM3.h"
#include "RSAImpl2048.h"

CContentEncrypt::CContentEncrypt()
{
}

CContentEncrypt::~CContentEncrypt(void)
{
}

char *sm2_param_recommand2[] = {
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

// 生成验证调用的密钥
BOOL CContentEncrypt::GenerateVerifyCallerCryptKey(BYTE* pResult,DWORD& dwResultSize,char * UniqueID)
{
	int i = 0;
	int j = 0;
	char szName[]			= {'i','c','b','c','f','f','i','n','p','u','t','p','l','u','g','i','n',0};
	//_bstr_t bstrUniqueID	= _bstr_t(UniqueID);
	//_bstr_t bstrParam		= _bstr_t(szName);

	CSecurityUtils su;	
	//对随机数做SHA1处理得到result1
	char* buffer1		= UniqueID;
	char result1[20]	= { 0 };	
	if(!su.GetHashSHA1((const unsigned char*)buffer1,strlen(UniqueID),result1))
	{
		memset(pResult,0,1024);
		return FALSE;
	}
	// 取result1的前12位得到partResult1
	char partResult1[12]	= { 0 };
	for (i = 0; i < 12; i++)
		partResult1[i] = result1[i];


	// 对硬编码字符串“udicbcpininput”做SHA1处理
	char* buffer2		= (char*)szName;
	char result2[20]	= { 0 };
	if(!su.GetHashSHA1((const unsigned char*)buffer2, strlen(szName), result2))
	{		
		memset(pResult,0,1024);
		return FALSE;
	}
	// 取result2的前12位得到partResult2
	char partResult2[12]	= { 0 };
	for (i = 0; i < 12; i++)
		partResult2[i] = result2[i];

	// 3DES密钥的值=partResult2+partResult1
	char fullResult[24]	= { 0 };
	j = 0;	
	for (i = 0; i < 12; i++)
		fullResult[j++] = partResult2[i];
	for(i = 0; i < 12; i++)
		fullResult[j++] = partResult1[i];

	unsigned char *p2 = (unsigned char *)partResult2;
	unsigned char *p1 = (unsigned char *)partResult1;
	//xLog("npxxin:GenerateVerifyCallerCryptKey	k1	0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",p2[0],p2[1],p2[2],p2[3],p2[4],p2[5],p2[6],p2[7],p2[8],p2[9],p2[10],p2[11]);
	//xLog("npxxin:GenerateVerifyCallerCryptKey	k2	0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",p1[0],p1[1],p1[2],p1[3],p1[4],p1[5],p1[6],p1[7],p1[8],p1[9],p1[10],p1[11]);
	mycopy(pResult,fullResult,24);
	dwResultSize = 24;
	return TRUE;
}

//验证调用者的加密
BOOL CContentEncrypt::EncryptVerifyCaller(BYTE* pPlaintext,BYTE* pResult,DWORD& dwSize,char * UniqueID)
{	
	// 得到秘钥
	BYTE* pKey = new BYTE[1024];
	memset(pKey,0,1024);
	DWORD dwKeyLen = 0;
	GenerateVerifyCallerCryptKey(pKey,dwKeyLen,UniqueID);
	//xLog("npxxin:EncryptVerifyCaller:		k-1=k1+k2,dwKeyLen=%d\n",dwKeyLen);


	// 3DES加密，并得到密文	
	DWORD dwCipherLen	= 0;
	DWORD dwPlainlen	= (DWORD)strlen((const char*)pPlaintext);	
	CSecurityUtils su;
	if (!su.Encrypt3DES(pPlaintext, dwPlainlen, NULL, dwCipherLen,pKey,24))		
	{
		memset(pKey,0,1024);
		delete []pKey;
		return FALSE;
	}
	for (DWORD i=0;i<dwCipherLen;i++)
	{
		//xLog("npxxin:EncryptVerifyCaller:pCipherText[%d]=0x%x,dwCipherLen=%d\n",i,pPlaintext[i],dwCipherLen);
	}

	// 进行Base64处理，得到最终密文
	DWORD dwOut = 0;
	Base64Coder base64cdr;
	base64cdr.Encode64(pPlaintext, dwCipherLen,pPlaintext,dwOut);
	//xLog("npxxin:EncryptVerifyCaller:pPlaintext=%s,dwCipherLen=%d,dwOut=%d\n",pPlaintext,dwCipherLen,dwOut);

	mycopy(pResult,pPlaintext,dwOut);
	dwSize = dwOut;

	memset(pKey,0,1024);
	delete []pKey;	
	return TRUE;
}

//验证调用者的解密
BOOL CContentEncrypt::DecryptVerifyCaller(BYTE* pCiphertext,DWORD dwCiphertextlen,BYTE* pResult,DWORD& dwSize,char * UniqueID)
{	
	// 得到秘钥
	CSecurityUtils su;
	DWORD dwKeyLen	= 0;// 秘钥长度	
	BYTE* pKey		= new BYTE[1024];
	memset(pKey,0,1024);	
	GenerateVerifyCallerCryptKey(pKey,dwKeyLen,UniqueID);
	for (DWORD i=0;i<dwKeyLen;i++)
	{
		//xLog("npxxin:DecryptVerifyCaller:生产调用者验证的3DES密码：k-1		pKey[%d]=0x%x,dwKeyLen=%d\n",i,pKey[i],dwKeyLen);
	}

	// 3DES解密	
	//	DWORD dwCiplen = strlen((const char*)pCiphertext);
	//xLog("npxxin:DecryptVerifyCaller	开始3DES解密\n");
	if (!su.Decrypt3DES(pCiphertext, dwCiphertextlen, NULL, dwSize,pKey,24))
	{
		memset(pKey,0,1024);
		delete []pKey;
		//xLog("npxxin:DecryptVerifyCaller	解密失败\n");
		return FALSE;
	}
	else
	{
		//xLog("npxxin:DecryptVerifyCaller	解密完成\n");
	}
	//xLog("npxxin:DecryptVerifyCaller	结束3DES解密\n");
	for (DWORD i=0;i<dwSize;i++)
	{
		//xLog("npxxin:DecryptVerifyCaller:3DES解密后数据		pPlainText[%d]=0x%x,dwSize=%d\n",i,pCiphertext[i],dwSize);
	}
	memset(pResult,0,1024);
	mycopy(pResult,pCiphertext,dwSize);		

	memset(pKey,0,1024);
	delete []pKey;
	return TRUE;
}


//使用SHA算法生成20位的Key
BOOL CContentEncrypt::CryptGenSHAKey(const char *pValidID,char *pGenKey,int *pHashLen)
{

	BOOL bResult = TRUE;
	/* 由于有可能客户端没有正常安装微软默认的CSP，从而无法正常生成hash值，因此取消下面的代码，转而找到一段公开源代码加以实现。
	HCRYPTPROV hProv = NULL;
	HCRYPTKEY hKey = NULL;
	HCRYPTKEY hXchgKey = NULL;
	HCRYPTHASH hHash = NULL;
	DWORD dwLength;
	// Get handle to user default provider.
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0))
	{
	// Create hash object.
	if (CryptCreateHash(hProv, Algorithm, 0, 0, &hHash))
	{
	// Hash password string.
	dwLength = sizeof(TCHAR)*_tcslen(pValidID);
	if (CryptHashData(hHash, (BYTE *)pValidID, dwLength, 0))
	{
	CryptGetHashParam(hHash,2,(BYTE*)pGenKey,(DWORD*)pHashLen,0);
	}
	else
	{
	// Error during CryptHashData!
	bResult = FALSE;
	}
	CryptDestroyHash(hHash); // Destroy session key.
	}
	else
	{
	// Error during CryptCreateHash!
	bResult = FALSE;
	}
	CryptReleaseContext(hProv, 0);
	}
	*/

	SHA1_CTX ctx;

	SHA1Init( &ctx );
	SHA1Update( &ctx, (uint8 *) pValidID, strlen(pValidID));
	SHA1Final((uint8 *) pGenKey, &ctx);
	*pHashLen = 20;//必然为20字节


	return bResult;

}//*/

//使用sKeySeed生成加密密钥，然后对sContent进行3DES加密
//sContent = 要加密的原始内容。
//sKeySeed = 用于生成密钥的种子字符串
//sResult = 加密成功后的结果字符串
//return = 是否加密成功。 TRUE=成功
BOOL CContentEncrypt::EncryptIt(char* sContent, char* sKeySeed, char** sResult)
{
	*sResult = sContent;

	char* deskey=new char[24];
	int hashlen=24;
	//生成20位的Key
	if(!CryptGenSHAKey((const char*)sKeySeed,deskey,&hashlen ) )
	{
		return FALSE; //生成密钥失败
	}

	//把前四位补充到后4位，形成24位的DES3需要的加密的Key
	for (int j=0;j<4;j++)
	{
		deskey[20+j]=deskey[j];
	}

	//将原始内容进行补位算法，以便符合3DES加密对原始内容的字节要求
	unsigned len=strlen(sContent)+8; //保险起见，以免未来出现内存溢出现象
	unsigned& padlen=len;
	char *srcVal = new char[len];
	memset(srcVal,0,len);

	strcpy(srcVal,sContent);

	char *padVal = new char[len]; //补位后的结果buffer 
	memset(padVal,0,len);

	//进行填充,注意有3种填充算法,我们需要使用第三种
	if (!CDES::RunPad(2,(const char*) srcVal,strlen(srcVal),padVal,padlen))
	{
		return FALSE;
	}

	//进行加密
	char* destval=(char*)malloc(sizeof(char)*(padlen+1)); //加密后的结果存放buffer。加密前后字节数不变，因此在destval中多一位，以便设定字符串的结束符\0。
	memset(destval,0,padlen+1);
	//destval[padlen] = '\0';
	if (!CDES::RunDes(0,0,padVal,destval,padlen,(const char*)deskey,24)) 
	{
		return FALSE;
	}
	//进行编码，将二进制字符数组转换成BASE64字符串。避免"，'，\0的出现，造成的不良后果。
	/*
	CBase64 base64;
	sResult = base64.Encode(destval, padlen+1);
	char *out = new char[100];
	int df = base64.Decode((const char*)sdd, out);
	*/
	char* dd = destval;
	Base64Coder base64cdr;
	base64cdr.Encode((const PBYTE)destval, padlen);
	*sResult = (char*)base64cdr.EncodedMessage();
	//base64cdr.Decode(sRlt);
	//CString sRltdd = base64cdr.DecodedMessage();

	delete[] deskey;
	free(srcVal);
	free(padVal);
	free(destval);
	return TRUE;

}

void HexStringToBytes(char* szHex, PBYTE bytes, const unsigned char len )
{
	TCHAR tmpStr[5]="0x";
	LPTSTR lpEnd;
	tmpStr[4] = 0;
	memset(bytes,0,len);
	//ZeroMemory(bytes,len);
	for (int i = 0 ; i< len ; i++)
	{
		memcpy(tmpStr+2,szHex+2*i, 2);
		//CopyMemory(tmpStr+2,szHex+2*i, 2);
		bytes[i] = (BYTE)strtol( 
			tmpStr,&lpEnd, 16 );
	}
}

void UpperHexStrToByte(char* str_arr, BYTE *byte_arr)  
{  
	unsigned char ch1;  
	unsigned char ch2;  
	int k = 0;  
	int len = strlen(str_arr);
	for (int i=0; i<len; i = i+2)  
	{  
		ch1 = *(str_arr+i); 
		ch2 = *(str_arr+i+1);   
		if (ch1>=48 && ch1 <= 57)  
		{  
			ch1 &= 0x0F;  
		}  
		if (ch1>='A' && ch1 <='F')  
		{  
			ch1 &= 0x0F;  
			ch1 += 0x09;  
		}  
		if (ch2 >= 48 && ch2 <= 57)  
		{  
			ch2 &= 0x0F;  
		}  
		if (ch2>='A' && ch2 <='F')  
		{  
			ch2 &= 0x0F;  
			ch2 += 0x09;  
		}  
		ch1<<=4;  
		byte_arr[k] = ch1 + ch2;//int类型转byte类型，有问题

		k++;  
	}  
}  

void sm2_verify(ec_param *ecp, sm2_sign_st *sign)
{
	sm2_hash e;
	BIGNUM *e_bn;
	BIGNUM *t;
	BIGNUM *R;
	CXyECPoint result(ecp);
	CXyECPoint result1(ecp);
	CXyECPoint result2(ecp);
	CXyECPoint P_A(ecp);
	BIGNUM *r;
	BIGNUM *s;
	BIGNUM *P_x;
	BIGNUM *P_y;

	e_bn = BN_new();
	t = BN_new();
	R = BN_new();

	r = BN_new();
	s = BN_new();
	P_x = BN_new();
	P_y = BN_new();

	BN_bin2bn(sign->r, ecp->point_byte_length, r);
	BN_bin2bn(sign->s, ecp->point_byte_length, s);
	BN_bin2bn(sign->public_key.x, ecp->point_byte_length, P_x);
	BN_bin2bn(sign->public_key.y, ecp->point_byte_length, P_y);
	P_A.Init_xy(P_x, P_y, ecp);

	memset(&e, 0, sizeof(e));
	BUFFER_APPEND_STRING(e.buffer, e.position, HASH_BYTE_LENGTH, sign->Z);
	BUFFER_APPEND_STRING(e.buffer, e.position, sign->message_byte_length, (BYTE*)sign->message);
	CSM3 mysm3;
	mysm3.SM3_Init();
	mysm3.SM3_Update(e.buffer, e.position);
	mysm3.SM3_Final_byte(e.hash);
	BN_bin2bn(e.hash, HASH_BYTE_LENGTH, e_bn);

	BN_mod_add(t, r, s, ecp->n, ecp->ctx);
	result1.Mul_Bignum(ecp->G, s, ecp);
	result2.Mul_Bignum(P_A.xyp, t, ecp);
	result.Add_xy_Ecpoint(result1.xyp, result2.xyp, ecp);

	BN_mod_add(R, e_bn, result.xyp->x, ecp->n, ecp->ctx);

	sm2_bn2bin(R, sign->R, ecp->point_byte_length);

	BN_free(e_bn);
	BN_free(t);
	BN_free(R);
	BN_free(r);
	BN_free(s);
	BN_free(P_x);
	BN_free(P_y);
}

//SM2验签,Add Method from Dabing
BOOL CContentEncrypt::verifySignatureBySM2(char* data, char* keyX, char* keyY, char* strSignature){
	//__android_log_print( ANDROID_LOG_DEBUG, "getMiDsDt","chen_verify_start");
	BOOL bResult = TRUE;

	if(data == NULL || strlen(data) == 0){
		bResult = FALSE;
		return bResult;
	}
	if(keyX == NULL || strlen(keyX) == 0){
		bResult = FALSE;
		return bResult;
	}
	if(keyY == NULL || strlen(keyY) == 0){
		bResult = FALSE;
		return bResult;
	}
	if(strSignature == NULL || strlen(strSignature) == 0){
		bResult = FALSE;
		return bResult;
	}

	//if(strPlainText.GetLength() == 0 || strSignature.GetLength() == 0){
	//	return FALSE;
	//}
	sm2_hash Z_A;
	//明文数据
	//char* message_digest = strPlainText.GetBuffer();
	char* message_digest = data;
	char* id = "1234567812345678";
	//接收签名数据r+s
	BYTE byts[65] = {0};
	HexStringToBytes(strSignature, byts, 65);
	//前32位是r，后32位是s
	//解密得到Sm3摘要
	CSM2 smtest;
	//椭圆参数的初始化
	smtest.ecp->type=0;
	smtest.ecp->EC_GROUP_new_curve = EC_GROUP_new_curve_GFp;
	smtest.ecp->EC_POINT_set_affine_coordinates = EC_POINT_set_affine_coordinates_GFp;
	smtest.ecp->EC_POINT_get_affine_coordinates = EC_POINT_get_affine_coordinates_GFp;

	BN_hex2bn(&smtest.ecp->p, sm2_param_recommand2[0]);
	BN_hex2bn(&smtest.ecp->a, sm2_param_recommand2[1]);
	BN_hex2bn(&smtest.ecp->b, sm2_param_recommand2[2]);
	BN_hex2bn(&smtest.ecp->n, sm2_param_recommand2[5]);

	smtest.ecp->group = smtest.ecp->EC_GROUP_new_curve(smtest.ecp->p, smtest.ecp->a
		, smtest.ecp->b, smtest.ecp->ctx);

	CXyECPoint cxyecpointemp(smtest.ecp);
	BN_hex2bn(&cxyecpointemp.xyp->x, sm2_param_recommand2[3]);
	BN_hex2bn(&cxyecpointemp.xyp->y, sm2_param_recommand2[4]);
	smtest.ecp->G=cxyecpointemp.xyp;
	if (!smtest.ecp->EC_POINT_set_affine_coordinates(
		smtest.ecp->group,
		smtest.ecp->G->ec_point, smtest.ecp->G->x,
		smtest.ecp->G->y, 
		smtest.ecp->ctx));
	//ABORT

	smtest.ecp->point_bit_length = 256;
	smtest.ecp->point_byte_length = (256 + 7) / 8;
	////公钥的初始化
	CSM2EcKey sm2eckey(smtest.ecp);
	sm2eckey.EcKeyInit(keyX,keyY);
	//初始化签名数据结构
	sm2_sign_st sign;
	memset(&sign, 0, sizeof(sign));
	sign.message = (BYTE *)message_digest;
	sign.message_byte_length = strlen(message_digest);
	sign.ID = (BYTE *)id;
	sign.ENTL = strlen(id);
	memcpy(sign.r, byts, 32);
	memcpy(sign.s, byts+32, 32);
	sm2_bn2bin(sm2eckey.eck->P->x, sign.public_key.x, smtest.ecp->point_byte_length);
	sm2_bn2bin(sm2eckey.eck->P->y, sign.public_key.y, smtest.ecp->point_byte_length);
	memset(&Z_A, 0, sizeof(Z_A));
	Z_A.buffer[0] = ((sign.ENTL * 8) >> 8) & 0xFF;
	Z_A.buffer[1] = (sign.ENTL * 8) & 0xFF;
	Z_A.position = Z_A.position + 2;
	BUFFER_APPEND_STRING(Z_A.buffer, Z_A.position, sign.ENTL, sign.ID);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, smtest.ecp->point_byte_length, smtest.ecp->a);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, smtest.ecp->point_byte_length, smtest.ecp->b);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, smtest.ecp->point_byte_length, smtest.ecp->G->x);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, smtest.ecp->point_byte_length, smtest.ecp->G->y);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, smtest.ecp->point_byte_length, sm2eckey.eck->P->x);
	BUFFER_APPEND_BIGNUM(Z_A.buffer, Z_A.position, smtest.ecp->point_byte_length, sm2eckey.eck->P->y);
	//DEFINE_SHOW_STRING(Z_A.buffer, Z_A.position);
	CSM3 sm3;
	sm3.SM3_Init();
	sm3.SM3_Update(Z_A.buffer, Z_A.position);
	sm3.SM3_Final_byte(Z_A.hash);
	memcpy(sign.Z, Z_A.hash, HASH_BYTE_LENGTH);
	sm2_verify(smtest.ecp, &sign);
	int iRes = strcmp((const char*)sign.R, (const char*)sign.r);
	//__android_log_print( ANDROID_LOG_DEBUG, "getMiDsDt","chen_verify_end");
	return (iRes==0);

}

BOOL CContentEncrypt::verifySignatureByRSA(char* data, char* modulus, char* strSignature){
	BOOL bResult = TRUE;

	if(data == NULL || strlen(data) == 0){
		bResult = FALSE;
		return bResult;
	}
	if(modulus == NULL || strlen(modulus) == 0){
		bResult = FALSE;
		return bResult;
	}
	if(strSignature == NULL || strlen(strSignature) == 0){
		bResult = FALSE;
		return bResult;
	}
	BYTE byts[1024];
	UpperHexStrToByte(strSignature, byts);
	//BYTE* resBuf = new BYTE[520];
	//memset(resBuf, 0, 520);
	CRSAImpl2048 utils;
	BYTE publicModulus[256] ={0};
	//HexStringToBytes(modulus, publicModulus, 256);
	UpperHexStrToByte(modulus, publicModulus);
	// 通过公钥验签
	if(!utils.DecryptByPublicKey2((BYTE*)byts, (BYTE*)publicModulus)){
		char * pCh = (char*)byts;
		utils.ArrayReserv((BYTE*)byts, strlen(pCh));
		if(strlen(data) != strlen((char*)byts))
			return FALSE;
		for(int i=0; i<strlen((char*)byts); i++){
			if(*(data+i) == byts[i]){
				continue;
			}
			else{
				return FALSE;
			}
		}
	}
	return TRUE;
}