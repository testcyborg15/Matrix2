#pragma once
#include <math.h>
#include <algorithm>
//////////////////////////////////////////////////////////////////////
// class CVector4D
//////////////////////////////////////////////////////////////////////

#define CMatrix1x4	CVector4D

using namespace std;

class CVector4D
{
// Constructors
public:
	CVector4D();
	CVector4D(double aX, double aY, double aZ);
	CVector4D(double aX, double aY, double aZ, double aW);
	//kopiujacy (konwertujacy?)
	CVector4D(const CVector4D& rSource);
	//Constructors to convert between 3 types of vectors
	//CVector4D(const CVector3D<double>& rSource);
	//CVector4D(const CVector3D<float>& rSource);
	

// Attributes
public:
	double X, Y, Z, W;

public:
	bool IsZero() const;
	bool IsEqual(const CVector4D& rVector) const;	
	CVector4D Abs() const;
	double Min() const;
	double Max() const;
	double Sum() const;
	double Length() const;
	double Length2D() const;												
// Operations
public:
	void Fill(double Scalar);
	void Zero()					{ Fill(0.0); }
	void Scale(double Factor);
	void Scale(double FactorX, double FactorY, double FactorZ);
	void Set(double X, double Y, double Z);
	void Normalize();
	
	friend CVector4D Cross(const CVector4D& rU, const CVector4D& rV);
	friend double Dot(const CVector4D& rU, const CVector4D& rV);
	
	friend double Dot2D(const CVector4D& rU, const CVector4D& rV);			
// Operators
public:
	bool operator ==(const CVector4D& rVector) const;
	bool operator !=(const CVector4D& rVector) const;	
	void operator +=(const CVector4D& rVector);
	void operator +=(double Scalar);
	void operator -=(const CVector4D& rVector);
	void operator -=(double Scalar);	
	void operator *=(double Scalar);
	void operator /=(const CVector4D& rVector);
	void operator /=(double Scalar);
	CVector4D operator -() const;
	CVector4D operator +(const CVector4D& rVector) const;
	CVector4D operator +(double Scalar) const;
	CVector4D operator -(const CVector4D& rVector) const;
	CVector4D operator -(double Scalar) const;	
	//CVector4D operator *(float Scalar) const;
	CVector4D operator /(const CVector4D& rVector) const;
	CVector4D operator /(double Scalar) const;

	friend CVector4D operator* (double fScalar, const CVector4D& rV)		{ return CVector4D(rV.X * fScalar, rV.Y * fScalar, rV.Z * fScalar); }
    friend CVector4D operator* (const CVector4D& rV, double fScalar)		{ return CVector4D(rV.X * fScalar, rV.Y * fScalar, rV.Z * fScalar); }	

};


//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

// Constructors
inline CVector4D::CVector4D()
	: X(0.0), Y(0.0), Z(0.0), W(1.0)
{
}


inline CVector4D::CVector4D(double aX, double aY, double aZ)
	: X(aX), Y(aY), Z(aZ), W(1.0)
{
}


inline CVector4D::CVector4D(double aX, double aY, double aZ, double aW)
	: X(aX), Y(aY), Z(aZ), W(aW)
{
}


inline CVector4D::CVector4D(const CVector4D& rSource)
	: X(rSource.X), Y(rSource.Y), Z(rSource.Z), W(rSource.W)
{
}

//Constructors to convert between 3 types of vectors
/*
inline CVector4D::CVector4D(const CVector3D<double>& rSource)
	: X(rSource.X), Y(rSource.Y), Z(rSource.Z), W(1.0)
{
}


inline CVector4D::CVector4D(const CVector3D<float>& rSource)
	: X(rSource.X), Y(rSource.Y), Z(rSource.Z), W(1.0f)
{
}
*/
// Attributes
inline bool CVector4D::IsZero() const
{
	return X * Y * Z == 0.0;
}


inline bool CVector4D::IsEqual(const CVector4D& rVector) const
{
	return X == rVector.X && Y == rVector.Y && Z == rVector.Z;
}


inline CVector4D CVector4D::Abs() const
{
	return CVector4D(fabs(X), fabs(Y), fabs(Z), fabs(W));
}


inline double CVector4D::Min() const
{
	return min(min(X, Y), Z);
}


inline double CVector4D::Max() const
{
	return max(max(X, Y), Z);
}


inline double CVector4D::Sum() const
{
	return X + Y + Z;
}


inline double CVector4D::Length() const
{
	return sqrt(X * X + Y * Y + Z * Z);
}


inline double CVector4D::Length2D() const
{
	return sqrt(X * X + Y * Y);
}
											

// Operations
inline void CVector4D::Fill(double Scalar)
{
	X = Y = Z = Scalar;
}


inline void CVector4D::Scale(double Factor)
{
	Scale(Factor, Factor, Factor);
}


inline void CVector4D::Scale(double FactorX, double FactorY, double FactorZ)
{
	X *= FactorX;
	Y *= FactorY;
	Z *= FactorZ;
}


inline void CVector4D::Set(double X, double Y, double Z)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}


inline void CVector4D::Normalize()
{
	Scale(1.0 / Length());	
}

/*
template <class T>
inline CVector4D<T> Cross(const CVector4D<T>& rVector)
{
	return CVector4D(Y*rVector.Z - Z*rVector.Y, Z*rVector.X - X*rVector.Z, X*rVector.Y - Y*rVector.X);
}
*/
/*
template <class T>
inline T Dot(const CVector4D<T>& rVector)
{
	return X*rVector.X + Y*rVector.Y + Z*rVector.Z;
}
*/


inline CVector4D Cross(const CVector4D& rU, const CVector4D& rV)
{
	return CVector4D(rU.Y*rV.Z - rU.Z*rV.Y, rU.Z*rV.X - rU.X*rV.Z, rU.X*rV.Y - rU.Y*rV.X);
}


inline double Dot(const CVector4D& rU, const CVector4D& rV)
{
	return rU.X*rV.X + rU.Y*rV.Y + rU.Z*rV.Z;
}


inline double Dot2D(const CVector4D& rU, const CVector4D& rV)
{ 
	return rU.X*rV.X + rU.Y*rV.Y;
}


// Operators
inline bool CVector4D::operator == (const CVector4D& rVector) const
{
	return IsEqual(rVector);
}


inline bool CVector4D::operator != (const CVector4D& rVector) const
{
	return !IsEqual(rVector);
}


inline void CVector4D::operator += (const CVector4D& rVector)
{
	X += rVector.X;
	Y += rVector.Y;
	Z += rVector.Z;
}


inline void CVector4D::operator += (double Scalar)
{
	X += Scalar;
	Y += Scalar;
	Z += Scalar;
}


inline void CVector4D::operator -= (const CVector4D& rVector)
{
	X -= rVector.X;
	Y -= rVector.Y;
	Z -= rVector.Z;
}


inline void CVector4D::operator -= (double Scalar)
{
	X -= Scalar;
	Y -= Scalar;
	Z -= Scalar;
}


inline void CVector4D::operator *= (double Scalar)
{
	X *= Scalar;
	Y *= Scalar;
	Z *= Scalar;
}


inline void CVector4D::operator /= (const CVector4D& rVector)
{
	X /= rVector.X;
	Y /= rVector.Y;
	Z /= rVector.Z;
}


inline void CVector4D::operator /= (double Scalar)
{
	X /= Scalar;
	Y /= Scalar;
	Z /= Scalar;
}


inline CVector4D CVector4D::operator+ (const CVector4D& rVector) const
{
	return CVector4D(X + rVector.X, Y + rVector.Y, Z + rVector.Z);
}


inline CVector4D CVector4D::operator+ (double Scalar) const
{
	return CVector4D(X + Scalar, Y + Scalar, Z + Scalar);
}


inline CVector4D CVector4D::operator -() const
{
	return CVector4D(-X, -Y, -Z);
}


inline CVector4D CVector4D::operator- (const CVector4D& rVector) const
{
	return CVector4D(X - rVector.X, Y - rVector.Y, Z - rVector.Z);
}


inline CVector4D CVector4D::operator- (double Scalar) const
{
	return CVector4D(X - Scalar, Y - Scalar, Z - Scalar);
}

/*
inline CVector4D CVector4D::operator* (float Scalar) const
{
	return CVector4D(X * Scalar, Y * Scalar, Z * Scalar);
}
*/

inline CVector4D CVector4D::operator/ (const CVector4D& rVector) const
{
	return CVector4D(X / rVector.X, Y / rVector.Y, Z / rVector.Z);
}


inline CVector4D CVector4D::operator/ (double Scalar) const
{
	return CVector4D(X / Scalar, Y / Scalar, Z / Scalar);
}


/*
// Serialization
template <class T>
inline CArchive& AFXAPI operator <<(CArchive& ar, const CVector4D<T>& Vector)
{
	// Patch? see CExtPoint
	ar.Write(&Vector, sizeof(Vector));
	return ar;
}

template <class T>
inline CArchive& AFXAPI operator >>(CArchive& ar, CVector4D<T>& Vector)
{
	ar.Read(&Vector, sizeof(Vector));
	return ar;
}
*/