#ifndef _H_XYECPOINT_
#define _H_XYECPOINT_

#include "SM2util.h"
class CXyECPoint
{
public:
	CXyECPoint(ec_param *ecp);
	~CXyECPoint(void);
	 xy_ecpoint *xyp;
	 int Mul_Bignum(xy_ecpoint *a, BIGNUM *number,ec_param *ecp);
	 int Add_xy_Ecpoint(xy_ecpoint *a, xy_ecpoint *b, ec_param *ecp);
	 int Init_xy(BIGNUM *x, BIGNUM *y,ec_param *ecp);
	 int Init_ec_point(EC_POINT *ec_point,ec_param *ecp);
};


#endif //_H_XYECPOINT_