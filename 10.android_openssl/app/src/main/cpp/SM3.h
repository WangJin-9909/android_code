#ifndef _H_SM3_
#define _H_SM3_

typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
#define INFO 0
static unsigned long long total_length = 0;
static BYTE message_buffer[64] = {0};
static DWORD message_buffer_position = 0;
static DWORD hash[8] = {0};
static DWORD V_i[8] = {0};
static DWORD V_i_1[8] = {0};
static DWORD T_j[64] = {0};
static DWORD IV[8] = 
{
	0x7380166f, 
	0x4914b2b9, 
	0x172442d7, 
	0xda8a0600, 
	0xa96f30bc, 
	0x163138aa, 
	0xe38dee4d, 
	0xb0fb0e4e
};
class CSM3
{
public:
	CSM3(void);
	~CSM3(void);
	void SM3_Init(void);
	void SM3_Update(BYTE * message, DWORD length);
	void SM3_Final_dword(DWORD * out_hash);
	void SM3_Final_byte(BYTE * out_hash);
	void SM3_Final(DWORD * out_hash);
};


#endif //_H_SM3_