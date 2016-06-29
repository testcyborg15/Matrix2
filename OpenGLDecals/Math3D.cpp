#include "Math3D.h"


bool CMath3D::ArePointsOverlapped(const CVector4D* pP0, const CVector4D* pP1)
{
	CVector4D Vec = *pP1 - *pP0;
	if(Vec.Length() <= fEPS_POINT)
		return true;
	else 
		return false;
}

bool CMath3D::ArePointsOverlapped(const CVector4D& rP0, const CVector4D& rP1)
{
	CVector4D Vec = rP1 - rP0;
	if(Vec.Length() <= fEPS_POINT)
		return true;
	else 
		return false;
}


