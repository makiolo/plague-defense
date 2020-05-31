#ifndef _RAY_
#define _RAY_

namespace dune {

class MYMATH_API Ray
{
public:
	Ray();
	~Ray();

	Vector3 _origin;
	Vector3 _direction;

	inline Vector3 getPoint(Real t) const
	{
		return Vector3(_origin + (_direction * t));
	}

	Vector3 operator*(Real t) const
	{
		return getPoint(t);
	}
};

}

#endif
