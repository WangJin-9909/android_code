//////////////////////////////////////////////////////////////////////
//头文件：BigInt1.h
//作者：灰色海
//版本：1.0
//说明：适用于MFC，1024位运算
//////////////////////////////////////////////////////////////////////
#pragma once

//允许生成1120位（二进制）的中间结果
//#include <windef.h>

#include "utils.h"
const int MAXLEN = 66 ;	//要比目标密钥位数（假设是1024 bit /8 bit /4 byte ) 大几个值


//设置大数为0x100000000进制
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
	//大数的长度
	unsigned int m_nLength ;
	//大数的存储值
	unsigned int m_nValue[ MAXLEN ] ;
public:
	//大数的赋值运算符
	CBigInt operator=(CBigInt Original);
	CBigInt operator=(unsigned long Original);
	//大数比较运算符
	bool operator==(CBigInt Object);
	bool operator==(unsigned long Object);
	bool operator!=(CBigInt Object);
	bool operator!=(unsigned long Object);
	bool operator>(CBigInt Object);
	bool operator>(unsigned long Object);
	bool operator<(CBigInt Object);
	bool operator<(unsigned long Object);
	//大数加、减、乘、除、模运算
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
	//大数平方、模幂运算
	CBigInt Power();
	CBigInt PowerMod(CBigInt Degree,CBigInt Modulus);
	CBigInt Reversion(CBigInt Modulus);
	bool IsPrime();
	CBigInt GetPrime(int len);

	void GetBytes( BYTE * pbyBuffer , DWORD dwBufferSize ) ;
	void GetBytes( DWORD dwBufferSize , BYTE * pbyBuffer ) ;
};

