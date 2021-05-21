#include "../include/openssl/aes.h"
#include "utils.h"

class CAES128Impl{
public:
	CAES128Impl(void);
	~CAES128Impl(void);

	BOOL EncryptAES128ByECB(char* plainText, char* outText, char* keyCode);
	BOOL DecryptAES128ByECB(char* plainText, char* outText, char* keyCode);
	BOOL EncryptAES128ByCBC(char* plainText, char* outText, char* keyCode);
	BOOL DecryptAES128ByCBC(char* plainText, char* outText, char* keyCode);
};