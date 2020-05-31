#ifndef _COLLISION_
#define _COLLISION_

//#include "Plane.h"
//#include "Ray.h"

namespace dune {

class MYMATH_API Collision
{
public:
	Collision(void);
	~Collision(void);

	// ray - plane
	static std::pair<bool, Real> intersects(const Ray& ray, const dune::Plane& plane);
	// ray - triangle
	static std::tuple<bool, Vector3, Real> intersects(const Ray& ray, const dune::Vector3& p0, const dune::Vector3& p1, const dune::Vector3& p2);
	// distancia punto-recta
	static Real distance(const Ray& ray, const Vector3& p);
	static Real distanceSquared(const Ray& ray, const Vector3& p);
	// distancia punto-plano
	static Real distance(const Plane& plane, const Vector3& p);
	static Int8 getSide(const Plane& plane, const Vector3& p);
};

}

#endif
