#include <string.h>
#include "SM2.h"
#include "SM3.h"
#include "XyECPoint.h"

CSM2::CSM2(void)
{
	ecp = (ec_param *)OPENSSL_malloc(sizeof(ec_param));
	ecp->ctx = BN_CTX_new();
	ecp->p = BN_new();
	ecp->a = BN_new();
	ecp->b = BN_new();
	ecp->n = BN_new();

}


CSM2::~CSM2(void)
{

}


int CSM2::Encrypt(ec_param * ecp, message_st * message_data)
{
	BIGNUM *P_x;
	BIGNUM *P_y;
	//BIGNUM *d;
	BIGNUM *k;
	//xy_ecpoint *P;
	//xy_ecpoint *xy1;
	//xy_ecpoint *xy2;
	int pos1;
	BYTE *t;
	int i;
	sm2_hash local_C_3;

	P_x = BN_new();
	P_y = BN_new();
	k = BN_new();
	//P = xy_ecpoint_new(ecp);
	//xy1 = xy_ecpoint_new(ecp);
	//xy2 = xy_ecpoint_new(ecp);
	CXyECPoint P(ecp);
	CXyECPoint xy1(ecp);
	CXyECPoint xy2(ecp);

	BN_bin2bn(message_data->public_key.x, ecp->point_byte_length, P_x);    //二进制转化成大数
	BN_bin2bn(message_data->public_key.y, ecp->point_byte_length, P_y);
	BN_bin2bn(message_data->k, ecp->point_byte_length, k);

	//xy_ecpoint_init_xy(P, P_x, P_y, ecp);                                 //初始化P点坐标
	P.Init_xy(P_x, P_y, ecp);
	//xy_ecpoint_mul_bignum(xy1, ecp->G, k, ecp);                           //初始化点 xy1 和 xy2 
	xy1.Mul_Bignum(ecp->G, k, ecp);
	//xy_ecpoint_mul_bignum(xy2, P, k, ecp);
	xy2.Mul_Bignum(P.xyp, k, ecp);

	pos1 = 0;
	message_data->C_1[0] = '\x04';
	pos1 = pos1 + 1;
	//BUFFER_APPEND_BIGNUM(message_data->C_1, pos1, ecp->point_byte_length, xy1->x);
	BUFFER_APPEND_BIGNUM(message_data->C_1, pos1, ecp->point_byte_length, xy1.xyp->x);
	//BUFFER_APPEND_BIGNUM(message_data->C_1, pos1, ecp->point_byte_length, xy1->y);
	BUFFER_APPEND_BIGNUM(message_data->C_1, pos1, ecp->point_byte_length, xy1.xyp->y);

	pos1 = 0;
	//BUFFER_APPEND_BIGNUM(message_data->C_2, pos1, ecp->point_byte_length, xy2->x);
	BUFFER_APPEND_BIGNUM(message_data->C_2, pos1, ecp->point_byte_length, xy2.xyp->x);
	//BUFFER_APPEND_BIGNUM(message_data->C_2, pos1, ecp->point_byte_length, xy2->y);
	BUFFER_APPEND_BIGNUM(message_data->C_2, pos1, ecp->point_byte_length, xy2.xyp->y);

	t = KDF((BYTE *)message_data->C_2, message_data->klen_bit, ecp->point_byte_length + ecp->point_byte_length);
	for (i = 0; i < message_data->message_byte_length; i++)
	{
		message_data->C_2[i] = t[i] ^ message_data->message[i];   //做异或运算
	}
	OPENSSL_free(t);

	//计算C_3
	memset(&local_C_3, 0, sizeof(local_C_3));
	//BUFFER_APPEND_BIGNUM(local_C_3.buffer, local_C_3.position, ecp->point_byte_length, xy2->x);
	BUFFER_APPEND_BIGNUM(local_C_3.buffer, local_C_3.position, ecp->point_byte_length, xy2.xyp->x);
	//BUFFER_APPEND_STRING(local_C_3.buffer, local_C_3.position, message_data->message_byte_length, message_data->message);
	BUFFER_APPEND_STRING(local_C_3.buffer, local_C_3.position, message_data->message_byte_length, message_data->message);
	//BUFFER_APPEND_BIGNUM(local_C_3.buffer, local_C_3.position, ecp->point_byte_length, xy2->y);
	BUFFER_APPEND_BIGNUM(local_C_3.buffer, local_C_3.position, ecp->point_byte_length, xy2.xyp->y);
	CSM3 mysm3;
	mysm3.SM3_Init();
	mysm3.SM3_Update((BYTE *)local_C_3.buffer, local_C_3.position);
	mysm3.SM3_Final_byte(local_C_3.hash);
	memcpy(message_data->C_3, (char *)local_C_3.hash, HASH_BYTE_LENGTH);

	pos1 = 0;
	BUFFER_APPEND_STRING(message_data->C, pos1, 1 + ecp->point_byte_length + ecp->point_byte_length
		, message_data->C_1);
	BUFFER_APPEND_STRING(message_data->C, pos1, message_data->message_byte_length
		, message_data->C_2);
	BUFFER_APPEND_STRING(message_data->C, pos1, HASH_BYTE_LENGTH
		, message_data->C_3);

	//printf("encrypt: \n");
    //DEFINE_SHOW_STRING(message_data->C_2, message_data->message_byte_length);

	BN_free(P_x);
	BN_free(P_y);
	BN_free(k);
	//xy_ecpoint_free(P);
	//xy_ecpoint_free(xy1);
	//xy_ecpoint_free(xy2);

	//return SUCCESS;
	return 0;
}

int CSM2::Decrypt(ec_param * ecp, message_st * message_data)
{

	return 0;
}
