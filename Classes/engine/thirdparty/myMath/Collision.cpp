#include "myMath.h"
//
#include "Collision.h"
//
//#include "Engine/Common.h"

namespace dune {

Collision::Collision(void)
{
}


Collision::~Collision(void)
{
}

std::pair<bool, Real> Collision::intersects(const Ray& ray, const dune::Plane& plane)
{

	Real denom = plane.m_vNormal.dotProduct(ray._direction);
    if (std::abs(denom) < std::numeric_limits<Real>::epsilon())
    {
        // Parallel
        return std::pair<bool, Real>(false, 0.0f);
    }
    else
    {
		Real nom = plane.m_vNormal.dotProduct(ray._origin) + plane.m_fD;
        Real t = -(nom/denom);
        return std::pair<bool, Real>(t >= 0, t);
    }
        
}

// http://www.geometrictools.com/LibMathematics/Intersection/Intersection.html
// http://www.blackpawn.com/texts/pointinpoly/default.html
std::tuple<bool, Vector3, Real> Collision::intersects(		const Ray& ray, 
															const dune::Vector3& p0, 
															const dune::Vector3& p1, 
															const dune::Vector3& p2)
{
    // Compute the offset origin, edges, and normal.
	Vector3 diff = ray._origin - p0;
    Vector3 edge1 = p1 - p0;
    Vector3 edge2 = p2 - p0;
	Vector3 normal = edge1.crossProduct(edge2);
	Real ep = std::numeric_limits<Real>::epsilon();

    // Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
    // E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
    //   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
    //   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
    //   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
	Real DdN = ray._direction.dotProduct(normal);
    Real sign;
    if (DdN > ep)
    {
        sign = (Real)1;
    }
    else if (DdN < -ep)
    {
        sign = (Real)-1;
        DdN = -DdN;
    }
    else
    {
        // Ray and triangle are parallel, call it a "no intersection"
        // even if the ray does intersect.
		return std::tuple<bool, Vector3, Real>(false, Vector3::ZERO, 0.0f);
    }

	Real DdQxE2 = sign*ray._direction.dotProduct(diff.crossProduct(edge2));
    if (DdQxE2 >= (Real)0)
    {
        Real DdE1xQ = sign*ray._direction.dotProduct(edge1.crossProduct(diff));
        if (DdE1xQ >= (Real)0)
        {
            if (DdQxE2 + DdE1xQ <= DdN)
            {
                // Line intersects triangle, check if ray does.
                Real QdN = -sign*diff.dotProduct(normal);
                if (QdN >= (Real)0)
                {
					Real mRayParameter, mTriBary0, mTriBary1, mTriBary2;

                    // Ray intersects triangle.
                    Real inv = ((Real)1)/DdN;
                    mRayParameter = QdN*inv;
                    mTriBary1 = DdQxE2*inv;
                    mTriBary2 = DdE1xQ*inv;
                    mTriBary0 = (Real)1 - mTriBary1 - mTriBary2;

                    return std::tuple<bool, Vector3, Real>(true, Vector3(mTriBary0, mTriBary1, mTriBary2), mRayParameter);
                }
                // else: t < 0, no intersection
            }
            // else: b1+b2 > 1, no intersection
        }
        // else: b2 < 0, no intersection
    }
    // else: b1 < 0, no intersection

	return std::tuple<bool, Vector3, Real>(false, Vector3::ZERO, 0.0f);
}

Real Collision::distance(const Ray& ray, const Vector3& p)
{
	// Formula |(AP X n)| / |n|
	// cogemos un punto de la recta
	Vector3 a = ray._origin;
	// Calcular AP
	Vector3 ap = p - a;
	// aplicar formula
	return ap.crossProduct(ray._direction).length() / ray._direction.length();
}

Real Collision::distanceSquared(const Ray& ray, const Vector3& p)
{
	// Formula |(AP X n)| / |n|
	// cogemos un punto de la recta
	Vector3 a = ray._origin;
	// Calcular AP
	Vector3 ap = p - a;
	// aplicar formula
	return ap.crossProduct(ray._direction).squaredLength() / ray._direction.squaredLength();
}

Real Collision::distance(const Plane& plane, const Vector3& p)
{
	// Formula |(AP . n)| / |n|
	// aplicar formula
	return std::abs(plane.m_vNormal.dotProduct(p) + plane.m_fD) / std::abs(plane.m_vNormal.length());
}

Int8 Collision::getSide(const Plane& plane, const Vector3& p)
{
	// Formula |(AP . n)| / |n|
	// aplicar formula
	Real pseudoDist = plane.m_vNormal.dotProduct(p) + plane.m_fD;

	if ( pseudoDist < 0.0 )
		return -1;

	if ( pseudoDist > 0.0 )
		return 1;

	return 0;
}



}
