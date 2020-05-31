#ifndef _QUATERNION_
#define _QUATERNION_

#include <LinearMath/btQuaternion.h>

namespace dune {

class MYMATH_API Quaternion
{
public:
	/**
	Estructura que define si los angulos de euler, van en grados o en radianes
	*/
	typedef enum
	{
		DEGREE,
		RADIAN
	} MeasureEnum;

	inline Quaternion (Real fW = 1.0, Real fX = 0.0, Real fY = 0.0, Real fZ = 0.0)
		: w(fW)
		, x(fX)
		, y(fY)
		, z(fZ)
	{
		;
	}

	// bullet specific
	inline Quaternion(const btQuaternion& quat)
		: w(quat.w())
		, x(quat.x())
		, y(quat.y())
		, z(quat.z())
	{
		;
	}

	inline btQuaternion as_bullet() const
	{
		return btQuaternion(x, y, z, w);
	}
	// end bullet

	~Quaternion(void) {}

	inline Quaternion(const Matrix4& rot)
	{
		this->FromRotationMatrix(rot);
	}

	inline Quaternion(const Real& rfAngle, const Vector3& rkAxis)
	{
		this->FromAngleAxis(rfAngle, rkAxis);
	}

	void FromRotationMatrix (const Matrix4& kRot);
	void ToRotationMatrix (Matrix4& kRot) const;
	void FromAngleAxis (const Real& rfAngle, const Vector3& rkAxis);
	void ToAngleAxis (Real& rfAngle, Vector3& rkAxis) const;

	Quaternion operator+ (const Quaternion& rkQ) const;
	Quaternion operator- (const Quaternion& rkQ) const;
	Quaternion operator* (const Quaternion& rkQ) const;
	friend Quaternion operator* (Real fScalar, const Quaternion& rkQ);
	Quaternion Inverse () const;
	Vector3 operator* (const Vector3& v) const;
	Quaternion operator- () const;

	static Quaternion Slerp(Real fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath = true);
	static Quaternion nlerp(Real fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath = true);

	Real getRoll(bool reprojectAxis = true) const;
	Real getPitch(bool reprojectAxis = true) const;
	Real getYaw(bool reprojectAxis = true) const;

    /// Normalises this quaternion, and returns the previous length
	Real Norm () const;
    Real normalise(void);

	inline Quaternion normalisedCopy(void) const
	{
		Quaternion ret = *this;
		ret.normalise();
		return ret;
	}

	Real Dot (const Quaternion& rkQ) const;

	/**
	Convierte un vector de angulos euler en un quaternion con orden ZYX
	*/
	static Quaternion fromEulerToQuaternion(const Vector3& rotation, MeasureEnum measure = DEGREE);

	/**
	Convierte un quaternion en angulos euler
	*/
	static Vector3 fromQuaternionToEuler(const Quaternion& rotation, MeasureEnum measure = DEGREE);

	/*
	Para extraer ejes
	*/
	Vector3 xAxis(void) const;
	Vector3 yAxis(void) const;
	Vector3 zAxis(void) const;
	void ToRotationMatrix (Real kRot[3][3]) const;
	void ToAxes (Vector3& xaxis, Vector3& yaxis, Vector3& zaxis) const;

	// componentes
	Real w, x, y, z;

	// cutoff for sine near zero
	static const Real ms_fEpsilon;

	// special values
	static const Quaternion ZERO;
	static const Quaternion IDENTITY;
};

}

#endif

