#pragma once
#ifndef __PLANE_H__
#define __PLANE_H__

namespace dune {

class MYMATH_API Plane
{
public:
	Plane(void);
	~Plane(void);

	// un punto esta dentro del plano
	inline bool IsInside( const Vector3& vPoint ) const
	{
		return( GetSignedDistance( vPoint ) <= 0 );
	}

	// un punto esta fuera del plano
	inline bool IsOutside( const Vector3& vPoint ) const
	{
		return( GetSignedDistance( vPoint ) >  0 );
	}

    // Devuelve distancia signada ( + es hacia el lado de la normal o fuera ) de un punto al plano
    inline Real GetSignedDistance( const Vector3& vPoint ) const
    {
        return( m_vNormal.dotProduct( vPoint ) + m_fD );
    }

	// Devuelve true si parte o toda la caja está dentro del plano,
	bool IsIntersecting( const AABB& box ) const;

	std::pair<bool, Real> IsIntersecting(const Ray& ray) const;

	// por normal y desplazamiento
	void Set(const Vector3& vNormal, Real fD)
	{
		m_vNormal = vNormal;
		m_fD = fD;
	}

	// mediante 3 puntos
    void Set( const Vector3& va, const Vector3& vb, const Vector3& vc )
    {
        Vector3 vab = vb - va;
        Vector3 vac = vc - va;
        SetbyPointAndTwoVectors( va, vab, vac );
    }

	// mediante normal y un punto
    void Set( const Vector3& vNormal, const Vector3& vpoint )
    {
		// normal
        m_vNormal = vNormal;

		// calcular D
		m_fD = -m_vNormal.dotProduct( vpoint );
    }

    void SetbyPointAndTwoVectors( const Vector3& va, const Vector3& v1, const Vector3& v2 )
    {
		// calcular normal
		m_vNormal = v1.crossProduct( v2 );
		m_vNormal.normalise();

		// calcular D
		m_fD = -m_vNormal.dotProduct( va );
    }

	Vector3 m_vNormal;
	Real m_fD;
};

}

#endif // __PLANE_H__
