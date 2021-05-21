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
5.4.3 ��Կ��������
	��Կ���������������Ǵ�һ����������ܱ��ش�����������Կ���ݡ�
	����ԿЭ�̹����У���Կ�� ��������������Կ��������������ܱ��ش��ϣ�
	���в�������ĻỰ��Կ���һ�������������Կ ���ݡ�
	��Կ����������Ҫ���������Ӵպ�����
	�������Ӵպ���ΪHv( )��������ǳ���ǡΪv���ص��Ӵ�ֵ�� 
	��Կ��������KDF(Z, klen)�� 
	���룺���ش�Z������klen(��ʾҪ��õ���Կ���ݵı��س��ȣ�Ҫ���ֵС��(232-1)v)�� 
	���������Ϊklen����Կ���ݱ��ش�K�� 
	a)��ʼ��һ��32���ع��ɵļ�����ct=0x00000001�� 
	b)��i��1��?klen/v?ִ�У� 
		b.1)����Hai=Hv(Z ��ct)�� 
		b.2) ct++�� 
	c)��klen/v����������Ha!?klen/v? = Ha?klen/v?��������Ha!?klen/v?ΪHa?klen/v?����ߵ�(klen ? (v��?klen/v?))���أ� 
	d)��K = Ha1||Ha2||������||Ha?klen/v??1||Ha!?klen/v?  

*/
BYTE *KDF(BYTE *str1, int klen, int strlen1)
{
	unsigned int ct = 0x00000001;
	int group_number = ((klen + (HASH_BIT_LENGTH - 1)) / HASH_BIT_LENGTH);
	BYTE *H = (BYTE *)OPENSSL_malloc(group_number * HASH_BYTE_LENGTH);
	int i;

	for (i = 0; i < group_number; i++)
	{
		//ct���Ƶ��ַ������big-endian
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
