//////////////////////////////////////////////////////////////////////
//ͷ�ļ���BigInt1.h
//���ߣ���ɫ��
//�汾��1.0
//˵����������MFC��1024λ����
//////////////////////////////////////////////////////////////////////
#pragma once

//��������1120λ�������ƣ����м���
//#include <windef.h>

#include "utils.h"
const int MAXLEN = 66 ;	//Ҫ��Ŀ����Կλ����������1024 bit /8 bit /4 byte ) �󼸸�ֵ


//���ô���Ϊ0x100000000����
#ifndef SYSTEM
#define SYSTEM 0x100000000
#endif

#define DEC 10
#define HEX 16
//typedef unsigned long       DWORD;
//typedef unsigned char       BYTE;
static unsigned long long Flag;

class CBigInt  
{
public:
	CBigInt();
	CBigInt( PBYTE pbyBuffer , DWORD dwBufferSize ) ;
	CBigInt( DWORD dwBufferSize , PBYTE pbyBuffer ) ;

	virtual ~CBigInt();
public:
	//�����ĳ���
	unsigned int m_nLength ;
	//�����Ĵ洢ֵ
	unsigned int m_nValue[ MAXLEN ] ;
public:
	//�����ĸ�ֵ�����
	CBigInt operator=(CBigInt Original);
	CBigInt operator=(unsigned long Original);
	//�����Ƚ������
	bool operator==(CBigInt Object);
	bool operator==(unsigned long Object);
	bool operator!=(CBigInt Object);
	bool operator!=(unsigned long Object);
	bool operator>(CBigInt Object);
	bool operator>(unsigned long Object);
	bool operator<(CBigInt Object);
	bool operator<(unsigned long Object);
	//�����ӡ������ˡ�����ģ����
	CBigInt operator+(CBigInt Addend);
	CBigInt operator+(unsigned long Addend);
	CBigInt operator-(CBigInt Subtrahend);
	CBigInt operator-(unsigned long Subtrahend);
	CBigInt operator*(CBigInt IER);
	CBigInt operator*(unsigned long IER);
	CBigInt operator/(CBigInt Divisor);
	CBigInt operator/(unsigned long Divisor);
	CBigInt operator%(CBigInt Divisor);
	CBigInt operator%(unsigned long Divisor);
	//����ƽ����ģ������
	CBigInt Power();
	CBigInt PowerMod(CBigInt Degree,CBigInt Modulus);
	CBigInt Reversion(CBigInt Modulus);
	bool IsPrime();
	CBigInt GetPrime(int len);

	void GetBytes( BYTE * pbyBuffer , DWORD dwBufferSize ) ;
	void GetBytes( DWORD dwBufferSize , BYTE * pbyBuffer ) ;
};

