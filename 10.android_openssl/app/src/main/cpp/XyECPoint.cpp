#include "XyECPoint.h"


CXyECPoint::CXyECPoint(ec_param *ecp)
{
	//xy_ecpoint *xyp;
	xyp = (xy_ecpoint *)OPENSSL_malloc(sizeof(xy_ecpoint));
	xyp->x = BN_new();
	xyp->y = BN_new();
	xyp->ec_point = EC_POINT_new(ecp->group);
}


CXyECPoint::~CXyECPoint(void)
{
	if (xyp)
	{
		BN_free(xyp->x);
		xyp->x = NULL;
		BN_free(xyp->y);
		xyp->y = NULL;
		EC_POINT_free(xyp->ec_point);
		xyp->ec_point = NULL;
		OPENSSL_free(xyp);
	}
}


int CXyECPoint::Mul_Bignum(xy_ecpoint *a, BIGNUM *number,ec_param *ecp)
{
	EC_POINT_mul(ecp->group, xyp->ec_point, NULL, a->ec_point, number, ecp->ctx);
	ecp->EC_POINT_get_affine_coordinates(ecp->group
		, (xyp)->ec_point
		, (xyp)->x
		, (xyp)->y
		, ecp->ctx);
	return 0;
}


int CXyECPoint::Add_xy_Ecpoint(xy_ecpoint *a, xy_ecpoint *b, ec_param *ecp)
{
	EC_POINT_add(ecp->group, (xyp)->ec_point, a->ec_point, b->ec_point, ecp->ctx);
	ecp->EC_POINT_get_affine_coordinates(ecp->group, (xyp)->ec_point
		, (xyp)->x, (xyp)->y
		, ecp->ctx);
	return 0;
}


int CXyECPoint::Init_xy(BIGNUM *x, BIGNUM *y,ec_param *ecp)
{
	//设置ec_point
	ecp->EC_POINT_set_affine_coordinates(ecp->group, (xyp)->ec_point
		, x, y
		, ecp->ctx);

	//获取x, y
	ecp->EC_POINT_get_affine_coordinates(ecp->group, (xyp)->ec_point
		, (xyp)->x, (xyp)->y
		, ecp->ctx);
	return 0;
}


int CXyECPoint::Init_ec_point(EC_POINT *ec_point, ec_param *ecp)
{
	//获取x, y
	ecp->EC_POINT_get_affine_coordinates(ecp->group, ec_point
		, (xyp)->x, (xyp)->y
		, ecp->ctx);

	//设置ec_point
	ecp->EC_POINT_set_affine_coordinates(ecp->group, (xyp)->ec_point
		, (xyp)->x, (xyp)->y
		, ecp->ctx);
	return 0;
}
