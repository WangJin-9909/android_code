struct Header
{
	int disturb;
	int startPos;
};

struct keyHeader1
{
	int keyStart;
	int disturb;
	int keySize;
	short disturb1;
	int startNext;
};

struct keyHeader2
{
	int keyStart;
	int disturb;
	int disturb1;
	int keySize;
	short disturb2;
	int startNext;
};

struct keyHeader3
{
	int keyStart;
	short disturb;
	int keySize;
	int disturb1;
	int startNext;
};

struct rsaHeader1
{
	int keyStart;
	int disturb;
	int keySize;
	int disturb1;
	int startNext;
};

struct rsaHeader2
{
	int keyStart;
	short disturb;
	int keySize;
	short disturb1;
	int startNext;
};

struct rsaHeader3
{
	int keyStart;
	int disturb;
	int disturb1;
	int keySize;
	int disturb2;
	int disturb3;
	int startNext;
};

struct rsaHeader4
{
	int keyStart;
	int keySize;
	int pubExp;
	// Add:2016.6.6 MaKai-[SM2&SM4&openssl] Start
	int startNext;
	// Add:2016.6.6 MaKai-[SM2&SM4&openssl] End
};

// Add:2016.6.6 MaKai-[SM2&SM4&openssl] Start
struct rsa2Header1
{
	int keyStart;
	int disturb;
	int keySize;
	int disturb1;
	int startNext;
};

struct rsa2Header2
{
	int keyStart;
	short disturb;
	int keySize;
	short disturb1;
	int startNext;
};

struct rsa2Header3
{
	int keyStart;
	int disturb;
	int disturb1;
	int keySize;
	int disturb2;
	int disturb3;
	int startNext;
};

struct rsa2Header4
{
	int keyStart;
	int keySize;
	int pubExp;
	int startNext;
};

struct domainData
{
	short dataLen;
	short disturb;
	char* data;
};
// Add:2016.6.6 MaKai-[SM2&SM4&openssl] End