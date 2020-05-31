#ifndef _VECTOR3_
#define _VECTOR3_

// static functions (TODO move)
MYMATH_API int Round(Real32 number);
MYMATH_API int Round(Real64 number);
MYMATH_API Real32 Q_rsqrt(Real32 number);
MYMATH_API Real64 Q_rsqrt(Real64 number);

#include <LinearMath/btVector3.h>

namespace dune {

class MYMATH_API Vector3
{
public:
	// dont initialize the matrix for efficency
    inline Vector3()
    {
    }

	// special implicit constructor for bullet
	inline Vector3(const btVector3& bv)
		: x(bv.x()), y(bv.y()), z(bv.z())
	{
		
	}

	inline btVector3 as_bullet() const
	{
		return btVector3(x, y, z);
	}
	// end bullet

	inline Vector3( const Real fX, const Real fY, const Real fZ )
		: x( fX ), y( fY ), z( fZ )
	{
		;
	}

	inline Vector3(const Real* data)
		: x( data[0] )
		, y( data[1] )
		, z( data[2] )
	{
		;
	}

	~Vector3(void) {}

	/**
	Assigns the value of the other vector.
	*/
	inline Vector3& operator = ( const Vector3& rkVector )
	{
		x = rkVector.x;
		y = rkVector.y;
		z = rkVector.z;

		return *this;
	}

	/**
	Assigns to scalar
	*/
	inline Vector3& operator = ( const Real fScaler )
	{
		x = fScaler;
		y = fScaler;
		z = fScaler;

		return *this;
	}

	inline bool operator == ( const Vector3& rkVector ) const
	{
		return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
	}

	inline bool operator != ( const Vector3& rkVector ) const
	{
		return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
	}

	inline Vector3 operator + ( const Vector3& rkVector ) const
	{
		return Vector3(
			x + rkVector.x,
			y + rkVector.y,
			z + rkVector.z);
	}

	inline Vector3 operator += (const Vector3& rkVector) const
	{
		return Vector3(
			x + rkVector.x,
			y + rkVector.y,
			z + rkVector.z);
	}

	inline Vector3 operator - ( const Vector3& rkVector ) const
	{
		return Vector3(
			x - rkVector.x,
			y - rkVector.y,
			z - rkVector.z);
	}

	inline Vector3 operator * ( const Real fScalar ) const
	{
		return Vector3(
			x * fScalar,
			y * fScalar,
			z * fScalar);
	}

	inline Vector3 operator * ( const Vector3& rhs) const
	{
		return Vector3(
			x * rhs.x,
			y * rhs.y,
			z * rhs.z);
	}

	inline Vector3 operator *= (const Vector3& rhs) const
	{
		return Vector3(
			x * rhs.x,
			y * rhs.y,
			z * rhs.z);
	}

	inline Vector3 operator / ( const Real fScalar ) const
	{
		DUNE_ASSERT(fScalar != 0.0);

		Real fInv = 1.0f / fScalar;

		return Vector3(
			x * fInv,
			y * fInv,
			z * fInv);
	}

	inline Vector3 operator / ( const Vector3& rhs) const
	{
		return Vector3(
			x / rhs.x,
			y / rhs.y,
			z / rhs.z);
	}

	/**
	sign plus
	*/
	inline const Vector3& operator + () const
	{
		return *this;
	}

	/**
	sign minus
	*/
	inline Vector3 operator - () const
	{
		return Vector3(-x, -y, -z);
	}

	inline Real length () const
	{
		return 1.0f / Q_rsqrt( x * x + y * y + z * z );
	}

	inline Real length2D () const
	{
		return 1.0f / Q_rsqrt( x * x + z * z );
	}

	inline Real squaredLength () const
	{
		return x * x + y * y + z * z;
	}

	inline Real squaredLength2D () const
	{
		return x * x + z * z;
	}

	inline Real distance(const Vector3& rhs) const
	{
		return (*this - rhs).length();
	}

	inline Real distance2D(const Vector3& rhs) const
	{
		return (*this - rhs).length2D();
	}

	inline Real squaredDistance(const Vector3& rhs) const
	{
		return (*this - rhs).squaredLength();
	}

	inline Real squaredDistance2D(const Vector3& rhs) const
	{
		return (*this - rhs).squaredLength2D();
	}

	inline Real dotProduct(const Vector3& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	inline Real normalise()
	{
		Real fInverseLength = Q_rsqrt( x * x + y * y + z * z );
		Real fLength = 1.0f / fInverseLength;

		// Will also work for zero-sized vectors, but will change nothing
		if ( fLength > 1e-08 )
		{
			x *= fInverseLength;
			y *= fInverseLength;
			z *= fInverseLength;
		}

		return fLength;
	}

	inline Vector3 crossProduct( const Vector3& rkVector ) const
	{
		return Vector3(
				y * rkVector.z - z * rkVector.y,
				z * rkVector.x - x * rkVector.z,
				x * rkVector.y - y * rkVector.x);
	}

	inline Vector3 midPoint( const Vector3& vec ) const
	{
		return Vector3(
			( x + vec.x ) * 0.5f,
			( y + vec.y ) * 0.5f,
			( z + vec.z ) * 0.5f );
	}

	inline Vector3 perpendicular() const
	{
		static const Real fSquareZero = (Real)(1e-06 * 1e-06);

		Vector3 perp = this->crossProduct( Vector3::UNIT_X );

		// Check length
		if( perp.squaredLength() < fSquareZero )
		{
			/* This vector is the Y axis multiplied by a scalar, so we have
			to use another axis.
			*/
			perp = this->crossProduct( Vector3::UNIT_Y );
		}
		perp.normalise();

		return perp;
	}

	/** Returns true if this vector is zero length. */
	inline bool isZeroLength(void) const
	{
		Real sqlen = (x * x) + (y * y) + (z * z);
		return (sqlen < (1e-06 * 1e-06));
	}

	inline Vector3 normalisedCopy(void) const
	{
		Vector3 ret = *this;
		ret.normalise();
		return ret;
	}

	inline Vector3 reflect(const Vector3& normal) const
	{
		return Vector3( *this - ( 2 * this->dotProduct(normal) * normal ) );
	}

	/** Gets the shortest arc quaternion to rotate this vector to the destination
		vector.
	@remarks
		If you call this with a dest vector that is close to the inverse
		of this vector, we will rotate 180 degrees around the 'fallbackAxis'
		(if specified, or a generated axiif not) since in this case
		ANY axis of rotation is valid.
	*/
	Quaternion getRotationTo(const Vector3& dest, const Vector3& fallbackAxis = Vector3::ZERO) const
	{
		// Based on Stan Melax's article in Game Programming Gems
		Quaternion q;
		// Copy, since cannot modify local
		Vector3 v0 = *this;
		Vector3 v1 = dest;
		v0.normalise();
		v1.normalise();

		Real d = v0.dotProduct(v1);
		// If dot == 1, vectors are the same
		if (d >= 1.0f)
		{
			return Quaternion::IDENTITY;
		}
		if (d < (1e-6f - 1.0f))
		{
			if (fallbackAxis != Vector3::ZERO)
			{
				// rotate 180 degrees about the fallback axis
				q.FromAngleAxis(PI_F32, fallbackAxis);
			}
			else
			{
				// Generate an axis
				Vector3 axis = Vector3::UNIT_X.crossProduct(*this);
				if (axis.isZeroLength()) // pick another if colinear
					axis = Vector3::UNIT_Y.crossProduct(*this);
				axis.normalise();
				q.FromAngleAxis(PI_F32, axis);
			}
		}
		else
		{
			Real inverseS = Q_rsqrt( (1+d)*2 );
			Real s = 1.0f / inverseS;

			Vector3 c = v0.crossProduct(v1);

    		q.x = c.x * inverseS;
			q.y = c.y * inverseS;
			q.z = c.z * inverseS;
			q.w = s * 0.5f;
			q.normalise();
		}
		return q;
	}

	/**
	Lo utiliza reflect
	*/
	inline friend Vector3 operator * ( const Real fScalar, const Vector3& rkVector )
	{
		return Vector3(
				fScalar * rkVector.x,
				fScalar * rkVector.y,
				fScalar * rkVector.z);
	}

	static Vector3 filterBilinear(	const Vector3& x, 
                                    const Vector3& y, 
                                    const Vector3& w, 
                                    const Vector3& z, 
											Real w1, Real w2)
	{
		Vector3 p1 = y * w1 + x * (1 - w1);
		Vector3 p2 = w * w1 + z * (1 - w1);
		Vector3 r = p2 * w2 + p1 * (1 - w2);
		return r;
	}

    /** Sets this vector's components to the minimum of its own and the
        ones of the passed in vector.
        @remarks
            'Minimum' in this case means the combination of the lowest
            value of x, y and z from both vectors. Lowest is taken just
            numerically, not magnitude, so -1 < 0.
    */
	// ojo quito el const
    inline void makeFloor( const Vector3& cmp )
    {
        if( cmp.x < x ) x = cmp.x;
        if( cmp.y < y ) y = cmp.y;
        if( cmp.z < z ) z = cmp.z;
    }

    /** Sets this vector's components to the maximum of its own and the
        ones of the passed in vector.
        @remarks
            'Maximum' in this case means the combination of the highest
            value of x, y and z from both vectors. Highest is taken just
            numerically, not magnitude, so 1 > -3.
    */
	// ojo quito el const
    inline void makeCeil( const Vector3& cmp )
    {
        if( cmp.x > x ) x = cmp.x;
        if( cmp.y > y ) y = cmp.y;
        if( cmp.z > z ) z = cmp.z;
    }

public:
	Real x, y, z;

	// special points
	static const Vector3 ZERO;
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
	static const Vector3 NEGATIVE_UNIT_X;
	static const Vector3 NEGATIVE_UNIT_Y;
	static const Vector3 NEGATIVE_UNIT_Z;
	static const Vector3 UNIT_SCALE;
};

}

#endif
