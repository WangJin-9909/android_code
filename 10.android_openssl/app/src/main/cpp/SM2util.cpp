#include <string.h>
#include "SM2util.h"
#include"SM3.h"
void show_bignum(BIGNUM *bn, int point_byte_length)
{
	char *to = BN_bn2hex(bn);
	int len1 = strlen(to);
	int remain = point_byte_length % 4;
	int j;
	int count = 0;
	for (j = 0; j < point_byte_length - len1 / 2; j++)
	{
		// printf("00");

		count = count + 1;
		if (count == remain)
		{
			// printf(" ");
			count = 4;
		}
		else if (count % 4 == 0)
		{
			// printf(" ");
		}
	}
	for (j = 0; j < len1; j = j + 2)
	{
		// printf("%c%c", to[j], to[j+1]);
		count = count + 1;
		if (count == remain)
		{
			// printf(" ");
			count = 4;
		}
		else if (count % 4 == 0)
		{
			// printf(" ");
		}
	}
	OPENSSL_free(to);
}

void show_string(BYTE *string1, int length1)
{
	int j;
	for (j = 0; j < length1; j++)
	{
		// printf("%02X", string1[j]);
		if ((j+1) % 32 == 0 && (j+1) != length1)
		{
			// printf("\n");
		}
		else if ((j+1) % 4 == 0)
		{
			// printf(" ");
		}
	}
}
/*
5.4.3 密钥派生函数
	密钥派生函数的作用是从一个共享的秘密比特串中派生出密钥数据。
	在密钥协商过程中，密钥派 生函数作用在密钥交换所获共享的秘密比特串上，
	从中产生所需的会话密钥或进一步加密所需的密钥 数据。
	密钥派生函数需要调用密码杂凑函数。
	设密码杂凑函数为Hv( )，其输出是长度恰为v比特的杂凑值。 
	密钥派生函数KDF(Z, klen)： 
	输入：比特串Z，整数klen(表示要获得的密钥数据的比特长度，要求该值小于(232-1)v)。 
	输出：长度为klen的密钥数据比特串K。 
	a)初始化一个32比特构成的计数器ct=0x00000001； 
	b)对i从1到?klen/v?执行： 
		b.1)计算Hai=Hv(Z ∥ct)； 
		b.2) ct++； 
	c)若klen/v是整数，令Ha!?klen/v? = Ha?klen/v?，否则令Ha!?klen/v?为Ha?klen/v?最左边的(klen ? (v×?klen/v?))比特； 
	d)令K = Ha1||Ha2||···||Ha?klen/v??1||Ha!?klen/v?  

*/
BYTE *KDF(BYTE *str1, int klen, int strlen1)
{
	unsigned int ct = 0x00000001;
	int group_number = ((klen + (HASH_BIT_LENGTH - 1)) / HASH_BIT_LENGTH);
	BYTE *H = (BYTE *)OPENSSL_malloc(group_number * HASH_BYTE_LENGTH);
	int i;

	for (i = 0; i < group_number; i++)
	{
		//ct复制到字符串最后，big-endian
		str1[strlen1] = (ct >> 24) & 0xFF;
		str1[strlen1+1] = (ct >> 16) & 0xFF;
		str1[strlen1+2] = (ct >> 8) & 0xFF;
		str1[strlen1+3] = (ct >> 0) & 0xFF;

		CSM3 smtemp;
		smtemp.SM3_Init();
		smtemp.SM3_Update((BYTE *)str1, strlen1 + 4);
		smtemp.SM3_Final_byte((BYTE *)&H[i * HASH_BYTE_LENGTH]);
		//SM3_Init();
		//SM3_Update((BYTE *)str1, strlen1 + 4);
		//SM3_Final_byte((BYTE *)&H[i * HASH_BYTE_LENGTH]);
		//DEFINE_SHOW_STRING((BYTE *)H, 32);

		ct = ct + 1;
	}

	return H;
}

int sm2_hex2bin(BYTE *hex_string, BYTE *bin_string, int point_byte_length)              //16 bit to 2bit 
{
	BIGNUM *b;
	int ret;
	b = BN_new();
	BN_hex2bn(&b, (char *)hex_string);
	ret = sm2_bn2bin(b, bin_string, point_byte_length);
	BN_free(b);
	return ret;
}

int sm2_bn2bin(BIGNUM *bn, BYTE *bin_string, int point_byte_length)
{
	int ret;
	int len;
	if (point_byte_length < 0)
		return 0;
	if (point_byte_length > MAX_POINT_BYTE_LENGTH)
		return 0;

	len = point_byte_length - BN_num_bytes(bn);
	if (len > MAX_POINT_BYTE_LENGTH)
	{
		return 0;
	}
	if (len < 0)
	{
		len = 0;
	}
	if (len > 0)
	{
		memset(bin_string, 0, len);
	}
	ret = BN_bn2bin(bn, &bin_string[len]);
	return ret;
}
