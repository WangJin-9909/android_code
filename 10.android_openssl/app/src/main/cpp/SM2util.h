#ifndef _H_SM2UTIL_
#define _H_SM2UTIL_

#include "../include/openssl/ec.h"

#define HASH_BYTE_LENGTH 32
#define HASH_BIT_LENGTH 256
#define MAX_POINT_BYTE_LENGTH 64                       //点中x, y的最大字节长度
typedef unsigned char       BYTE;
typedef struct                                         //设需要发送的消息为比特串M，klen为M的比特长度
{
	BYTE *message;                                     //需要加密的数据                      
	int message_byte_length;                           //加密数据的长度
	//BYTE *encrypt;
	BYTE *decrypt;                                      
	int klen_bit;

	BYTE k[MAX_POINT_BYTE_LENGTH];						//随机数
	//BYTE private_key[MAX_POINT_BYTE_LENGTH];            //私钥
	struct 
	{
		BYTE x[MAX_POINT_BYTE_LENGTH];
		BYTE y[MAX_POINT_BYTE_LENGTH];
	}public_key;                                        //公钥

	BYTE C[1024];										// C_1 || C_2 || C_3
	BYTE C_1[1024];
	BYTE C_2[1024];										//加密后的消息
	BYTE C_3[1024];

} message_st;

typedef struct                                           //HASH Value
{
	BYTE buffer[1024];
	int position;
	BYTE hash[HASH_BYTE_LENGTH];
} sm2_hash;

typedef struct {
	BIGNUM *x;
	BIGNUM *y;
	EC_POINT *ec_point;
} xy_ecpoint;

typedef struct {
	//BIGNUM *d;
	xy_ecpoint *P;
} sm2_ec_key;

typedef struct {
	BN_CTX *ctx;
	BIGNUM *p;
	BIGNUM *a;
	BIGNUM *b;
	BIGNUM *n;
	xy_ecpoint *G;
	EC_GROUP *group;
	int type;
	int point_bit_length;
	int point_byte_length;

	EC_GROUP *(*EC_GROUP_new_curve)(const BIGNUM *p, const BIGNUM *a, const BIGNUM *b, BN_CTX *ctx);
	int (*EC_POINT_set_affine_coordinates)(const EC_GROUP *group, EC_POINT *p,
		const BIGNUM *x, const BIGNUM *y, BN_CTX *ctx);
	int (*EC_POINT_get_affine_coordinates)(const EC_GROUP *group,
		const EC_POINT *p, BIGNUM *x, BIGNUM *y, BN_CTX *ctx);

} ec_param;

#define BUFFER_APPEND_BIGNUM(buffer1, pos1, point_byte_length, x) \
	BN_bn2bin(x, &buffer1[pos1 + point_byte_length - BN_num_bytes(x)]); \
	pos1 = pos1 + point_byte_length

#define BUFFER_APPEND_STRING(buffer1, pos1, length1, x) \
	memcpy(&buffer1[pos1], x, length1); \
	pos1 = pos1 + length1

void show_bignum(BIGNUM *bn, int point_byte_length);
void show_string(BYTE *string1, int length1);
BYTE *KDF(BYTE *str1, int klen, int strlen1);

int sm2_hex2bin(BYTE *hex_string, BYTE *bin_string, int point_byte_length);
int sm2_bn2bin(BIGNUM *bn, BYTE *bin_string, int point_byte_length);

#endif //_H_SM2UTIL_