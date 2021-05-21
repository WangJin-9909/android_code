#ifndef _H_SM4_
#define _H_SM4_

#define SM4_ENCRYPT     1
#define SM4_DECRYPT     0
#include "utils.h"
class CSM4
{
public:
	CSM4(void);
	virtual ~CSM4(void);
	/**
	* \brief          SM4 context structure
	*/
	typedef struct
	{
		int mode;                   /*!<  encrypt/decrypt   */
		unsigned long sk[32];       /*!<  SM4 subkeys       */
	}sm4_context;

	//SM4算法的模式
	enum
	{
		ECB		=	0,	//ECB模式
		CBC				//CBC模式
	}desAlType;

	//Pad填充的模式
	enum
	{
		PAD_ISO_1 =	0,	//ISO_1填充：数据长度不足16 byte的倍数，以0x00补足，如果为16byte的倍数，补16个0x00
		PAD_ISO_2,		//ISO_2填充：数据长度不足16 byte的倍数，以0x80,0x00..补足，如果为16 byte的倍数，补0x80,0x00..0x00
		PAD_PKCS_7		//PKCS7填充：数据长度除16余数为n,以(16-n)补足为16的倍数
	}desPadtype;

/*******************************************************************/
/*
  函 数 名 称:	RunPad
  功 能 描 述：	根据协议对加密前的数据进行填充
  参 数 说 明：	bType	:类型：PAD类型
				In		:数据串指针
				Out		:填充输出串指针
				datalen	:数据的长度
				padlen	:(in,out)输出buffer的长度，填充后的长度

  返回值 说明：	bool	:是否填充成功

/*******************************************************************/
static bool	RunPad(int nType,const char* In,unsigned datalen,char* Out,unsigned& padlen);

/*******************************************************************/
/*
  函 数 名 称:	Encrypt
  功 能 描 述：	执行SM4算法对文本加解密
  参 数 说 明：	bType	:类型：加密ENCRYPT，解密DECRYPT
				bMode	:模式：ECB,CBC
				In		:待加密串指针
				Out		:待输出串指针
				datalen	:待加密串的长度，同时Out的缓冲区大小应大于或者等于datalen
				Key		:密钥长度只能为16 byte 密钥 
				keylen	:密钥长度，多出16 byte部分将被自动裁减
  返回值 说明：	bool	:是否加密成功

/*******************************************************************/
static bool Encrypt(bool bType,bool bMode,char* In,char* Out,unsigned datalen,const char* Key,const unsigned char keylen);

/*******************************************************************/
/*
  函 数 名 称:	Decrypt
  功 能 描 述：	执行SM4算法对文本加解密
  参 数 说 明：	bType	:类型：加密ENCRYPT，解密DECRYPT
				bMode	:模式：ECB,CBC
				In		:待加密串指针
				Out		:待输出串指针
				datalen	:待加密串的长度，同时Out的缓冲区大小应大于或者等于datalen
				Key		:密钥长度只能为16 byte 密钥 
				keylen	:密钥长度，多出16 byte部分将被自动裁减
  返回值 说明：	bool	:是否加密成功

/*******************************************************************/
static bool Decrypt(bool bType,bool bMode,char* In,char* Out,unsigned datalen,const char* Key,const unsigned char keylen);
	/**
 * \brief          SM4 key schedule (128-bit, encryption)
 *
 * \param ctx      SM4 context to be initialized
 * \param key      16-byte secret key
 */
static void sm4_setkey_enc( sm4_context *ctx, unsigned char key[16] );

/**
 * \brief          SM4 key schedule (128-bit, decryption)
 *
 * \param ctx      SM4 context to be initialized
 * \param key      16-byte secret key
 */
static void sm4_setkey_dec( sm4_context *ctx, unsigned char key[16] );

/**
 * \brief          SM4-ECB block encryption/decryption
 * \param ctx      SM4 context
 * \param mode     SM4_ENCRYPT or SM4_DECRYPT
 * \param length   length of the input data
 * \param input    input block
 * \param output   output block
 */
static void sm4_crypt_ecb( sm4_context *ctx,
				     int mode,
					 int length,
                     unsigned char *input,
                     unsigned char *output);

/**
 * \brief          SM4-CBC buffer encryption/decryption
 * \param ctx      SM4 context
 * \param mode     SM4_ENCRYPT or SM4_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
static void sm4_crypt_cbc( sm4_context *ctx,
                     int mode,
                     int length,
                     unsigned char iv[16],
                     unsigned char *input,
                     unsigned char *output );
};



#endif //_H_SM4_