#include "myMath.h"
//
#include "Quaternion.h"
//#include "Vector3.h"
//#include "Matrix4.h"
//

namespace dune {

const Real Quaternion::ms_fEpsilon = 1e-03f;
const Quaternion Quaternion::ZERO(0.0,0.0,0.0,0.0);
const Quaternion Quaternion::IDENTITY(1.0,0.0,0.0,0.0);

void Quaternion::FromRotationMatrix (const Matrix4& kRot)
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "Quaternion Calculus and Fast Animation".

	Real fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
	Real fRoot;

	if ( fTrace > 0.0 )
	{
		// |w| > 1/2, may as well choose w > 1/2
		Real fRootInverse = Q_rsqrt(fTrace + 1.0f);  // 2w
		fRoot = 1.0f / fRootInverse;  // 2w
		w = 0.5f*fRoot;
		fRoot = 0.5f/fRoot;  // 1/(4w)
		x = (kRot[2][1]-kRot[1][2])*fRoot;
		y = (kRot[0][2]-kRot[2][0])*fRoot;
		z = (kRot[1][0]-kRot[0][1])*fRoot;
	}
	else
	{
		// |w| <= 1/2
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if ( kRot[1][1] > kRot[0][0] )
			i = 1;
		if ( kRot[2][2] > kRot[i][i] )
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		Real fRootInverse = Q_rsqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
		fRoot = 1.0f / fRootInverse;
		Real* apkQuat[3] = { &x, &y, &z };
		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f/fRoot;
		w = (kRot[k][j]-kRot[j][k])*fRoot;
		*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
		*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
	}
}
//-----------------------------------------------------------------------
void Quaternion::ToRotationMatrix (Matrix4& kRot) const
{
    Real fTx  = x+x;
    Real fTy  = y+y;
    Real fTz  = z+z;
    Real fTwx = fTx*w;
    Real fTwy = fTy*w;
    Real fTwz = fTz*w;
    Real fTxx = fTx*x;
    Real fTxy = fTy*x;
    Real fTxz = fTz*x;
    Real fTyy = fTy*y;
    Real fTyz = fTz*y;
    Real fTzz = fTz*z;

    kRot[0][0] = 1.0f-(fTyy+fTzz);
    kRot[0][1] = fTxy-fTwz;
    kRot[0][2] = fTxz+fTwy;
    kRot[1][0] = fTxy+fTwz;
    kRot[1][1] = 1.0f-(fTxx+fTzz);
    kRot[1][2] = fTyz-fTwx;
    kRot[2][0] = fTxz-fTwy;
    kRot[2][1] = fTyz+fTwx;
    kRot[2][2] = 1.0f-(fTxx+fTyy);
}
//-----------------------------------------------------------------------
void Quaternion::FromAngleAxis (const Real& rfAngle, const Vector3& rkAxis)
{
    // assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    Real fHalfAngle = 0.5f*rfAngle;
    Real fSin = std::sin(fHalfAngle);
    w = std::cos(fHalfAngle);
    x = fSin*rkAxis.x;
    y = fSin*rkAxis.y;
    z = fSin*rkAxis.z;
}
//-----------------------------------------------------------------------
void Quaternion::ToAngleAxis (Real& rfAngle, Vector3& rkAxis) const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    Real fSqrLength = x*x+y*y+z*z;
    if ( fSqrLength > 0.0 )
    {
        rfAngle = 2.0f*std::acos(w);
        Real fInvLength = Q_rsqrt(fSqrLength);
        rkAxis.x = x*fInvLength;
        rkAxis.y = y*fInvLength;
        rkAxis.z = z*fInvLength;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        rfAngle = 0.0;
        rkAxis.x = 1.0;
        rkAxis.y = 0.0;
        rkAxis.z = 0.0;
    }
}
//---------------------------------------------------------------------------
Quaternion Quaternion::operator* (const Quaternion& rkQ) const
{
	// NOTE:  Multiplication is not generally commutative, so in most
	// cases p*q != q*p.

	return Quaternion
	(
		w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
		w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
		w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
		w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
	);
}
//----------------------------------------------------------------------------
Quaternion Quaternion::Inverse () const
{
	Real fNorm = w*w+x*x+y*y+z*z;
	if ( fNorm > 0.0 )
	{
		Real fInvNorm = 1.0f/fNorm;
		return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
	}
	else
	{
		// return an invalid result to flag the error
		return ZERO;
	}
}
//----------------------------------------------------------------------------
Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
	return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
}
//----------------------------------------------------------------------------
Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
	return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
}
//----------------------------------------------------------------------------
Quaternion Quaternion::operator- () const
{
	return Quaternion(-w,-x,-y,-z);
}
//----------------------------------------------------------------------------
Vector3 Quaternion::operator* (const Vector3& v) const
{
	// nVidia SDK implementation
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = qvec.crossProduct(v);
	uuv = qvec.crossProduct(uv);
	uv = uv * (2.0f * w);
	uuv = uuv * 2.0f;

	return v + uv + uuv;
}
//-----------------------------------------------------------------------
Real Quaternion::Norm () const
{
	return w*w+x*x+y*y+z*z;
}
//-----------------------------------------------------------------------
Real Quaternion::normalise(void)
{
    Real len = Norm();
    Real factor = Q_rsqrt(len);
    *this = *this * factor;
    return len;
}
//-----------------------------------------------------------------------
Quaternion operator* (Real fScalar, const Quaternion& rkQ)
{
    return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
        fScalar*rkQ.z);
}
//------------------------------------------------------------------------
Real Quaternion::Dot (const Quaternion& rkQ) const
{
	return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
}
//------------------------------------------------------------------------
Quaternion Quaternion::Slerp (Real fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath)
{
    Real fCos = rkP.Dot(rkQ);
    Quaternion rkT;

    // Do we need to invert rotation?
    if (fCos < 0.0f && shortestPath)
    {
        fCos = -fCos;
        rkT = -rkQ;
    }
    else
    {
        rkT = rkQ;
    }

#ifdef ANDROID
    if (fabsf(fCos) < 1 - ms_fEpsilon)
#else
    if (std::abs(fCos) < 1 - ms_fEpsilon)
#endif
    {
        // Standard case (slerp)

		Real fInverseSin = Q_rsqrt(1 - (fCos * fCos));
		Real fSin = 1.0f / fInverseSin;
        Real fAngle = std::atan2(fSin, fCos);
        Real fCoeff0 = std::sin((1.0f - fT) * fAngle) * fInverseSin;
        Real fCoeff1 = std::sin(fT * fAngle) * fInverseSin;
        return fCoeff0 * rkP + fCoeff1 * rkT;
    }
    else
    {
        // There are two situations:
        // 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
        //    interpolation safely.
        // 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
        //    are an infinite number of possibilities interpolation. but we haven't
        //    have method to fix this case, so just use linear interpolation here.
        Quaternion t = (1.0f - fT) * rkP + fT * rkT;
        // taking the complement requires renormalisation
        t.normalise();
        return t;
    }
}
//------------------------------------------------------------------------------
Quaternion Quaternion::nlerp(Real fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath)
{
	Quaternion result;
	Real fCos = rkP.Dot(rkQ);
	if (fCos < 0.0f && shortestPath)
	{
		result = rkP + fT * ((-rkQ) - rkP);
	}
	else
	{
		result = rkP + fT * (rkQ - rkP);
	}
	result.normalise();
	return result;
}
//-----------------------------------------------------------------------
Real Quaternion::getRoll(bool reprojectAxis) const
{
	if (reprojectAxis)
	{
		// roll = atan2(localx.y, localx.x)
		// pick parts of xAxis() implementation that we need
//			Real fTx  = 2.0*x;
		Real fTy  = 2.0f*y;
		Real fTz  = 2.0f*z;
		Real fTwz = fTz*w;
		Real fTxy = fTy*x;
		Real fTyy = fTy*y;
		Real fTzz = fTz*z;

		// Vector3(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);

		return std::atan2(fTxy+fTwz, 1.0f-(fTyy+fTzz));

	}
	else
	{
		return std::atan2(2*(x*y + w*z), w*w + x*x - y*y - z*z);
	}
}
//-----------------------------------------------------------------------
Real Quaternion::getPitch(bool reprojectAxis) const
{
	if (reprojectAxis)
	{
		// pitch = atan2(localy.z, localy.y)
		// pick parts of yAxis() implementation that we need
		Real fTx  = 2.0f*x;
//		Real fTy  = 2.0f*y;
		Real fTz  = 2.0f*z;
		Real fTwx = fTx*w;
		Real fTxx = fTx*x;
		Real fTyz = fTz*y;
		Real fTzz = fTz*z;

		// Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
		return std::atan2(fTyz+fTwx, 1.0f-(fTxx+fTzz));
	}
	else
	{
		// internal version
		return std::atan2(2*(y*z + w*x), w*w - x*x - y*y + z*z);
	}
}
//-----------------------------------------------------------------------
Real Quaternion::getYaw(bool reprojectAxis) const
{
	if (reprojectAxis)
	{
		// yaw = atan2(localz.x, localz.z)
		// pick parts of zAxis() implementation that we need
		Real fTx  = 2.0f*x;
		Real fTy  = 2.0f*y;
		Real fTz  = 2.0f*z;
		Real fTwy = fTy*w;
		Real fTxx = fTx*x;
		Real fTxz = fTz*x;
		Real fTyy = fTy*y;

		// Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

		return std::atan2(fTxz+fTwy, 1.0f-(fTxx+fTyy));

	}
	else
	{
		// internal version
		return std::asin(-2*(x*z - w*y));
	}
}


Quaternion Quaternion::fromEulerToQuaternion(const Vector3& rotation, MeasureEnum measure)
{
	Quaternion ori_global;
	switch(measure)
	{
	case RADIAN:
		ori_global = ori_global * Quaternion(rotation.z, Vector3(0, 0, 1));
		ori_global = ori_global * Quaternion(rotation.y, Vector3(0, 1, 0));
		ori_global = ori_global * Quaternion(rotation.x, Vector3(1, 0, 0));
    	break;
	case DEGREE:
	default:
		ori_global = ori_global * Quaternion(rotation.z * DEG_TO_RAD, Vector3(0, 0, 1));
		ori_global = ori_global * Quaternion(rotation.y * DEG_TO_RAD, Vector3(0, 1, 0));
		ori_global = ori_global * Quaternion(rotation.x * DEG_TO_RAD, Vector3(1, 0, 0));
		break;
	}
	return ori_global;
}


Vector3 Quaternion::fromQuaternionToEuler(const Quaternion& rotation, MeasureEnum measure)
{
	Vector3 ori_global;
	switch(measure)
	{
	case RADIAN:
		ori_global.z = rotation.getRoll();
		ori_global.y = rotation.getYaw();
		ori_global.x = rotation.getPitch();
    	break;
	case DEGREE:
	default:
		ori_global.z = rotation.getRoll() * RAD_TO_DEG;
		ori_global.y = rotation.getYaw() * RAD_TO_DEG;
		ori_global.x = rotation.getPitch() * RAD_TO_DEG;
		break;
	}
	return ori_global;
}

Vector3 Quaternion::xAxis(void) const
{
	//Real fTx  = 2.0*x;
	Real fTy  = 2.0f*y;
	Real fTz  = 2.0f*z;
	Real fTwy = fTy*w;
	Real fTwz = fTz*w;
	Real fTxy = fTy*x;
	Real fTxz = fTz*x;
	Real fTyy = fTy*y;
	Real fTzz = fTz*z;

	return Vector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
}
//-----------------------------------------------------------------------
Vector3 Quaternion::yAxis(void) const
{
	Real fTx  = 2.0f*x;
	Real fTy  = 2.0f*y;
	Real fTz  = 2.0f*z;
	Real fTwx = fTx*w;
	Real fTwz = fTz*w;
	Real fTxx = fTx*x;
	Real fTxy = fTy*x;
	Real fTyz = fTz*y;
	Real fTzz = fTz*z;

	return Vector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
}
//-----------------------------------------------------------------------
Vector3 Quaternion::zAxis(void) const
{
	Real fTx  = 2.0f*x;
	Real fTy  = 2.0f*y;
	Real fTz  = 2.0f*z;
	Real fTwx = fTx*w;
	Real fTwy = fTy*w;
	Real fTxx = fTx*x;
	Real fTxz = fTz*x;
	Real fTyy = fTy*y;
	Real fTyz = fTz*y;

	return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
}
//-----------------------------------------------------------------------

void Quaternion::ToRotationMatrix (Real kRot[3][3]) const
{
	Real fTx  = x+x;
	Real fTy  = y+y;
	Real fTz  = z+z;
	Real fTwx = fTx*w;
	Real fTwy = fTy*w;
	Real fTwz = fTz*w;
	Real fTxx = fTx*x;
	Real fTxy = fTy*x;
	Real fTxz = fTz*x;
	Real fTyy = fTy*y;
	Real fTyz = fTz*y;
	Real fTzz = fTz*z;

	kRot[0][0] = 1.0f-(fTyy+fTzz);
	kRot[0][1] = fTxy-fTwz;
	kRot[0][2] = fTxz+fTwy;
	kRot[1][0] = fTxy+fTwz;
	kRot[1][1] = 1.0f-(fTxx+fTzz);
	kRot[1][2] = fTyz-fTwx;
	kRot[2][0] = fTxz-fTwy;
	kRot[2][1] = fTyz+fTwx;
	kRot[2][2] = 1.0f-(fTxx+fTyy);
}

void Quaternion::ToAxes (Vector3& xaxis, Vector3& yaxis, Vector3& zaxis) const
{
	Real kRot[3][3];

	ToRotationMatrix(kRot);

	xaxis.x = kRot[0][0];
	xaxis.y = kRot[1][0];
	xaxis.z = kRot[2][0];

	yaxis.x = kRot[0][1];
	yaxis.y = kRot[1][1];
	yaxis.z = kRot[2][1];

	zaxis.x = kRot[0][2];
	zaxis.y = kRot[1][2];
	zaxis.z = kRot[2][2];
}

}
