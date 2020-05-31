#include "myMath.h"
//
namespace dune {

Plane::Plane(void)
{
}


Plane::~Plane(void)
{
}

std::pair<bool, Real> Plane::IsIntersecting(const Ray& ray) const
{
	Real denom = m_vNormal.dotProduct(ray._direction);
	if (std::abs(denom) < std::numeric_limits<Real>::epsilon())
	{
		// Parallel
		return std::pair<bool, Real>(false, 0.0f);
	}
	else
	{
		Real nom = m_vNormal.dotProduct(ray._origin) + m_fD;
		Real t = -(nom/denom);
		return std::pair<bool, Real>(t >= 0, t);
	}
}

bool Plane::IsIntersecting( const AABB& box ) const
{
	// coger el vertice de los 8 más cercano al plano
	// y cmprobar si esta dentro

	// http://fgiesen.wordpress.com/2010/10/17/view-frustum-culling/

	for(unsigned int i = 0; i < 8; ++i)
	{
		if( IsInside( box.getCorner(i) ) ) return true;
	}
	return false;
}

}
