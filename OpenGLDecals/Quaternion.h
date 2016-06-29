#pragma once
#include <math.h>
#include <algorithm>
#include "Vector4D.h"
#include "Matrix4x4.h"

using namespace std;

class CQuaternion
{
public:
	CQuaternion();
	CQuaternion( double w, double x, double y, double z );
	CQuaternion( double angle, CVector4D& axis );

	void XRotateQuat( double angle );
	void YRotateQuat( double angle );
	void ZRotateQuat( double angle );
	void RotateQuat( double angle, CVector4D& axis );
	void IdentityQuat();
	
	//void Conjugate();
	//void Norm();
	void Normalize();
	//void Inverse();

	CMatrix4x4 QuatToMatrix();

	CQuaternion	operator* ( const CQuaternion& q ) const;	// q1 * q2		(this * Other)	

private:
	CVector4D _q;
};


inline CQuaternion::CQuaternion()
{
	//konstruuje kwaternion jednostkowy
	_q.X = 0.0;
	_q.Y = 0.0;
	_q.Z = 0.0;
	_q.W = 1.0;
}


inline CQuaternion::CQuaternion( double w, double x, double y, double z )
{	
	_q.X = x;
	_q.Y = y;
	_q.Z = z;
	_q.W = w;
}


inline CQuaternion::CQuaternion( double angle, CVector4D& axis )
{
	_q.X = axis.X * sin( angle / 2.0 );
	_q.Y = axis.Y * sin( angle / 2.0 );
	_q.Z = axis.Z * sin( angle / 2.0 );
	_q.W = cos( angle / 2.0 );
}


inline void CQuaternion::XRotateQuat( double angle )
{
	_q.X = 1.0 * sin( angle / 2.0 );
	_q.Y = 0.0 * sin( angle / 2.0 );
	_q.Z = 0.0 * sin( angle / 2.0 );
	_q.W = cos( angle / 2.0 );
}


inline void CQuaternion::YRotateQuat( double angle )
{
	_q.X = 0.0 * sin( angle / 2.0 );
	_q.Y = 1.0 * sin( angle / 2.0 );
	_q.Z = 0.0 * sin( angle / 2.0 );
	_q.W = cos( angle / 2.0 );
}


inline void CQuaternion::ZRotateQuat( double angle )
{
	_q.X = 0.0 * sin( angle / 2.0 );
	_q.Y = 0.0 * sin( angle / 2.0 );
	_q.Z = 1.0 * sin( angle / 2.0 );
	_q.W = cos( angle / 2.0 );
}


inline void CQuaternion::RotateQuat( double angle, CVector4D& axis )
{
	_q.X = axis.X * sin( angle / 2.0 );
	_q.Y = axis.Y * sin( angle / 2.0 );
	_q.Z = axis.Z * sin( angle / 2.0 );
	_q.W = cos( angle / 2.0 );
}


inline void CQuaternion::IdentityQuat()
{
	_q.X = 0.0;
	_q.Y = 0.0;
	_q.Z = 0.0;
	_q.W = 1.0;
}

	
inline CMatrix4x4 CQuaternion::QuatToMatrix()
{
	Normalize();

	return CMatrix4x4( 1.0 - 2.0*_q.Y*_q.Y - 2.0*_q.Z*_q.Z, 2.0*_q.X*_q.Y - 2.0*_q.W*_q.Z,		 2.0*_q.X*_q.Z + 2.0*_q.W*_q.Y,		  0.0,
					   2.0*_q.X*_q.Y + 2.0*_q.W*_q.Z,		1.0 - 2.0*_q.X*_q.X - 2.0*_q.Z*_q.Z, 2.0*_q.Y*_q.Z - 2.0*_q.W*_q.X,		  0.0,
					   2.0*_q.X*_q.Z - 2.0*_q.W*_q.Y,		2.0*_q.Y*_q.Z + 2.0*_q.W*_q.X,		 1.0 - 2.0*_q.X*_q.X - 2.0*_q.Y*_q.Y, 0.0,
					   0.0,									0.0,								 0.0,								  1.0 );
}


inline CQuaternion CQuaternion::operator* ( const CQuaternion& q ) const
{
	return CQuaternion( _q.W * q._q.W - _q.X * q._q.X - _q.Y * q._q.Y - _q.Z * q._q.Z,
						_q.W * q._q.X + _q.X * q._q.W + _q.Y * q._q.Z - _q.Z * q._q.Y,
						_q.W * q._q.Y - _q.X * q._q.Z + _q.Y * q._q.W + _q.Z * q._q.X,
						_q.W * q._q.Z + _q.X * q._q.Y - _q.Y * q._q.X + _q.Z * q._q.W );
}


inline void CQuaternion::Normalize()
{
	double length = sqrt( _q.X * _q.X + _q.Y * _q.Y + _q.Z * _q.Z + _q.W * _q.W );
	_q.X /= length;
	_q.Y /= length;
	_q.Z /= length;
	_q.W /= length;
}