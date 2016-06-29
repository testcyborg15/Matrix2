#pragma once

#include "Vector4D.h"

//////////////////////////////////////////////////////////////////////
// class CMatrix4x4
//////////////////////////////////////////////////////////////////////

class CMatrix4x4
{
// Constructors
public:
	CMatrix4x4();
	CMatrix4x4(double A11, double A12, double A13, double A14, double A21, double A22, double A23, double A24, double A31, double A32, double A33, double A34, double A41, double A42, double A43, double A44);
//	CMatrix4x4(const CMatrix4x4<T>& rSource);

// Attributes
public:	
	union
	{
		double Arr[16];
		struct {
			double	A11, A12, A13, A14,
					A21, A22, A23, A24,
					A31, A32, A33, A34,
					A41, A42, A43, A44;	
		};
	};

// Operations
public:
	void Fill(double Scalar);
	void Zero()					{ Fill(0.0); }
	void XRotate(double fAngleRad);
	void YRotate(double fAngleRad);
	void ZRotate(double fAngleRad);
	void Rotate(double fAngleRad, double X, double Y, double Z);
	void Identity();
	void XYZTranslate(double fX, double fY, double fZ);
	void XYZScale(double fXScale, double fYScale, double fZScale);
	void Transpose();
	/*
	void Invert();
	void Perspective();
	void Ortho2D();
	void Ortho();
	void Camera();
	*/
	
// Operators
public:
	
	CVector4D	operator* (const CVector4D& rV) const;		// M * V	
	CMatrix4x4	operator* (const CMatrix4x4& rM) const;	// M1 * M2		(this * Other)	
	

};

//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

// Constructors
inline CMatrix4x4::CMatrix4x4()
{
}


inline CMatrix4x4::CMatrix4x4(double A11, double A12, double A13, double A14, double A21, double A22, double A23, double A24, double A31, double A32, double A33, double A34, double A41, double A42, double A43, double A44)
{
	this->A11 = A11;	this->A12 = A12;	this->A13 = A13;	this->A14 = A14;
	this->A21 = A21;	this->A22 = A22;	this->A23 = A23;	this->A24 = A24;
	this->A31 = A31;	this->A32 = A32;	this->A33 = A33;	this->A34 = A34;
	this->A41 = A41;	this->A42 = A42;	this->A43 = A43;	this->A44 = A44;
}


inline void CMatrix4x4::Fill(double Scalar)
{
	A11 = A12 = A13 = A14 = A21 = A22 = A23 = A24 = A31 = A32 = A33 = A34 = A41 = A42 = A43 = A44 = Scalar;
}

//Setting Matrix
inline void CMatrix4x4::XRotate(double fAngleRad)
{
	A11 = 1.0;				A12 = 0.0;				A13 = 0.0;				A14 = 0.0;
	A21 = 0.0;				A22 = cos(fAngleRad);	A23 = -sin(fAngleRad);	A24 = 0.0;
	A31 = 0.0;				A32 = sin(fAngleRad);	A33 = cos(fAngleRad);	A34 = 0.0;
	A41 = 0.0;				A42 = 0.0;				A43 = 0.0;				A44 = 1.0;
}


inline void CMatrix4x4::YRotate(double fAngleRad)
{
	A11 = cos(fAngleRad);	A12 = 0.0;				A13 = sin(fAngleRad);	A14 = 0.0;
	A21 = 0.0;				A22 = 1.0;				A23 = 0.0;				A24 = 0.0;
	A31 = -sin(fAngleRad);	A32 = 0.0;				A33 = cos(fAngleRad);	A34 = 0.0;
	A41 = 0.0;				A42 = 0.0;				A43 = 0.0;				A44 = 1.0;
}


inline void CMatrix4x4::ZRotate(double fAngleRad)
{
	A11 = cos(fAngleRad);	A12 = -sin(fAngleRad);	A13 = 0.0;				A14 = 0.0;
	A21 = sin(fAngleRad);	A22 = cos(fAngleRad);	A23 = 0.0;				A24 = 0.0;
	A31 = 0.0;				A32 = 0.0;				A33 = 1.0;				A34 = 0.0;
	A41 = 0.0;				A42 = 0.0;				A43 = 0.0;				A44 = 1.0;
}

//CHECK !!
inline void CMatrix4x4::Rotate(double fAngleRad, double X, double Y, double Z)
{
	double C = cos(fAngleRad);
	double S = sin(fAngleRad);

	A11 = X*X*(1.0-C)+C;		A12 = Y*X*(1.0-C)-Z*S;		A13 = X*Z*(1.0-C)+Y*S;		A14 = 0.0;
	A21 = X*Y*(1.0-C)+Z*S;		A22 = Y*Y*(1.0-C)+C;		A23 = Y*Z*(1.0-C)-X*S;		A24 = 0.0;
	A31 = X*Z*(1.0-C)-Y*S;		A32 = Y*Z*(1.0-C)+X*S;		A33 = Z*Z*(1.0-C)+C;		A34 = 0.0;
	A41 = 0.0;					A42 = 0.0;					A43 = 0.0;					A44 = 1.0;
}


inline void CMatrix4x4::Identity()
{
	A11 = 1.0;		A12 = 0.0;		A13 = 0.0;		A14 = 0.0;
	A21 = 0.0;		A22 = 1.0;		A23 = 0.0;		A24 = 0.0;
	A31 = 0.0;		A32 = 0.0;		A33 = 1.0;		A34 = 0.0;
	A41 = 0.0;		A42 = 0.0;		A43 = 0.0;		A44 = 1.0;
}


inline void CMatrix4x4::XYZTranslate(double fX, double fY, double fZ)
{
	A11 = 1.0;		A12 = 0.0;		A13 = 0.0;		A14 = fX;
	A21 = 0.0;		A22 = 1.0;		A23 = 0.0;		A24 = fY;
	A31 = 0.0;		A32 = 0.0;		A33 = 1.0;		A34 = fZ;
	A41 = 0.0;		A42 = 0.0;		A43 = 0.0;		A44 = 1.0;
}


inline void CMatrix4x4::XYZScale(double fXScale, double fYScale, double fZScale)
{
	A11 = fXScale;	A12 = 0.0;		A13 = 0.0;		A14 = 0.0;
	A21 = 0.0;		A22 = fYScale;	A23 = 0.0;		A24 = 0.0;
	A31 = 0.0;		A32 = 0.0;		A33 = fZScale;	A34 = 0.0;
	A41 = 0.0;		A42 = 0.0;		A43 = 0.0;		A44 = 1.0;
}

// Operators
inline CVector4D CMatrix4x4::operator* (const CVector4D& rV) const
{
	return CVector4D( A11 * rV.X + A12 * rV.Y + A13 * rV.Z + A14 * rV.W,
					  A21 * rV.X + A22 * rV.Y + A23 * rV.Z + A24 * rV.W,
					  A31 * rV.X + A32 * rV.Y + A33 * rV.Z + A34 * rV.W,
					  A41 * rV.X + A42 * rV.Y + A43 * rV.Z + A44 * rV.W );
}


inline CMatrix4x4 CMatrix4x4::operator* (const CMatrix4x4& rM) const	// M1 * M2	(this * Other)
{
	return CMatrix4x4(	A11*rM.A11 + A12*rM.A21 + A13*rM.A31 + A14*rM.A41,	A11*rM.A12 + A12*rM.A22 + A13*rM.A32 + A14*rM.A42,	A11*rM.A13 + A12*rM.A23 + A13*rM.A33 + A14*rM.A43,	A11*rM.A14 + A12*rM.A24 + A13*rM.A34 + A14*rM.A44,
						A21*rM.A11 + A22*rM.A21 + A23*rM.A31 + A24*rM.A41,	A21*rM.A12 + A22*rM.A22 + A23*rM.A32 + A24*rM.A42,	A21*rM.A13 + A22*rM.A23 + A23*rM.A33 + A24*rM.A43,	A21*rM.A14 + A22*rM.A24 + A23*rM.A34 + A24*rM.A44,
						A31*rM.A11 + A32*rM.A21 + A33*rM.A31 + A34*rM.A41,	A31*rM.A12 + A32*rM.A22 + A33*rM.A32 + A34*rM.A42,	A31*rM.A13 + A32*rM.A23 + A33*rM.A33 + A34*rM.A43,	A31*rM.A14 + A32*rM.A24 + A33*rM.A34 + A34*rM.A44,
						A41*rM.A11 + A42*rM.A21 + A43*rM.A31 + A44*rM.A41,	A41*rM.A12 + A42*rM.A22 + A43*rM.A32 + A44*rM.A42,	A41*rM.A13 + A42*rM.A23 + A43*rM.A33 + A44*rM.A43,	A41*rM.A14 + A42*rM.A24 + A43*rM.A34 + A44*rM.A44 );
}


inline void CMatrix4x4::Transpose()
{
	CMatrix4x4 m;
	m.A11 = this->A11;	m.A12 = this->A12;	m.A13 = this->A13;	m.A14 = this->A14;
	m.A21 = this->A21;	m.A22 = this->A22;	m.A23 = this->A23;	m.A24 = this->A24;
	m.A31 = this->A31;	m.A32 = this->A32;	m.A33 = this->A33;	m.A34 = this->A34;
	m.A41 = this->A41;	m.A42 = this->A42;	m.A43 = this->A43;	m.A44 = this->A44;

	this->A11 = m.A11;	this->A12 = m.A21;	this->A13 = m.A31;	this->A14 = m.A41;
	this->A21 = m.A12;	this->A22 = m.A22;	this->A23 = m.A32;	this->A24 = m.A42;
	this->A31 = m.A13;	this->A32 = m.A23;	this->A33 = m.A33;	this->A34 = m.A43;
	this->A41 = m.A14;	this->A42 = m.A24;	this->A43 = m.A34;	this->A44 = m.A44;
}


