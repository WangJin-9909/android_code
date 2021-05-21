#ifndef _H_SM2_
#define _H_SM2_

#include "SM2util.h"
typedef struct 
{
	BYTE *message;
	int message_byte_length;
	BYTE *ID;
	int ENTL;
	BYTE k[MAX_POINT_BYTE_LENGTH];  //签名中产生随机数
	BYTE private_key[MAX_POINT_BYTE_LENGTH];
	struct 
	{
		BYTE x[MAX_POINT_BYTE_LENGTH];
		BYTE y[MAX_POINT_BYTE_LENGTH];
	}public_key;
	BYTE Z[HASH_BYTE_LENGTH];
	BYTE r[MAX_POINT_BYTE_LENGTH];
	BYTE s[MAX_POINT_BYTE_LENGTH];
	BYTE R[MAX_POINT_BYTE_LENGTH];
} sm2_sign_st;
class CSM2
{

public:
	CSM2();
	~CSM2(void);
public:
	ec_param *ecp;
	//sm2_ec_key *key_B;
	message_st message_data;                               //包括随机数 加密数据  等的结构体
public:
	static int Encrypt(ec_param * ecp, message_st * message_data);
	int Decrypt(ec_param * ecp, message_st * message_data);
};

#endif //_H_SM2_