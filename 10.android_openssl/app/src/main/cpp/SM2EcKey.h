#ifndef _H_SM2ECKEY_
#define _H_SM2ECKEY_

#include "SM2util.h"
class CSM2EcKey
{
public:
	CSM2EcKey(ec_param *ecp);
	~CSM2EcKey(void);
	sm2_ec_key *eck;
	int EcKeyInit(char *string_xvalue, char *string_yvalue);
};

#endif //_H_SM2ECKEY_