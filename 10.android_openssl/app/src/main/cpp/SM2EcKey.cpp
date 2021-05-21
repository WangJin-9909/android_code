#include <string.h>
#include "SM2EcKey.h"
#include "XyECPoint.h"

CSM2EcKey::CSM2EcKey(ec_param *ecp)
{
	eck = (sm2_ec_key *)OPENSSL_malloc(sizeof(sm2_ec_key));
	eck->P = (xy_ecpoint *)OPENSSL_malloc(sizeof(xy_ecpoint));
	eck->P->x = BN_new();
	eck->P->y = BN_new();
	eck->P->ec_point = EC_POINT_new(ecp->group);
}


CSM2EcKey::~CSM2EcKey(void)
{
	if (eck)
	{
		//BN_free(eck->d);
		//xy_ecpoint_free(eck->P);
		BN_free(eck->P->x);
		eck->P->x = NULL;
		BN_free(eck->P->y);
		eck->P->y = NULL;
		EC_POINT_free(eck->P->ec_point);
		eck->P->ec_point = NULL;
		OPENSSL_free(eck->P);
		OPENSSL_free(eck);
		eck = NULL;
	}
}


int CSM2EcKey::EcKeyInit(char *string_xvalue, char *string_yvalue)
{

	BN_hex2bn(&eck->P->x, string_xvalue);
	BN_hex2bn(&eck->P->y, string_yvalue);
	return 0;
}
