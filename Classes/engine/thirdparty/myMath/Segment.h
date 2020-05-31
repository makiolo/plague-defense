#pragma once
#ifndef __SEGMENT_H__
#define __SEGMENT_H__

namespace dune {

class MYMATH_API Segment
{
public:
	Segment(Vector3 vStart, Vector3 vEnd)
		: m_vStart(vStart)
		, m_vEnd(vEnd)
		, m_vDirection(vEnd - vStart)
	{
		m_fLength = m_vDirection.length();
		m_vDirection.normalise();
	}
	~Segment(void) {}

    const Vector3& UDir() const
    {
        return m_vDirection;
    }

     /*! Calcula el punto del segmento más cercano a un punto dado
	  * @param vPoint [in] punto respecto al cual buscamos el pto más cercano
	  * @param vNearest [out] punto más cercano del segmento a vPoint, PUEDE HACERSE vNearest = vPoint
	  * @return Proyección de vStartToPoint en dirección del segmento */
     Real GetNearestPoint( const Vector3& vPoint, Vector3& vNearest ) const
     {
		Vector3 vStartToPoint( vPoint - m_vStart );
		Real fProj = m_vDirection.dotProduct( vStartToPoint );

        if( fProj <= 0 )
        {
            vNearest = m_vStart;
        }
        else if( fProj >= m_fLength )
        {
            vNearest = m_vEnd;
        }
        else
        {
            vNearest = m_vStart;
            vNearest = vNearest + (m_vDirection * fProj);
        }
        return( fProj );
     }

	 /*
	 Distancia punto - recta
	 */
	Real GetDistance( const Vector3& vPoint ) const
    {
        Vector3 vNearest;
        GetNearestPoint( vPoint, vNearest );
		return( vPoint.distance( vNearest ) );
    }

	 /*
	 Distancia cuadrada punto - recta
	 */
	Real GetDistanceSq( const Vector3& vPoint ) const
    {
        Vector3 vNearest;
        GetNearestPoint( vPoint, vNearest );
		return( vPoint.squaredDistance( vNearest ) );
    }

	bool IsIntersecting( const AABB& aabb, Vector3& vIntersection ) const
    {
		return aabb.IsIntersecting( *this, vIntersection );
    }

	const Vector3& GetStart() const {return m_vStart;}
	const Vector3& GetEnd() const {return m_vEnd;}

 protected:

    Vector3 m_vStart;  //!< Extremo inicial del segmento
    Vector3 m_vEnd;    //!< Extremo final del segmento

private:
	Vector3 m_vDirection; // Direccion unitaria
	Real m_fLength;
};

}

#endif // __SEGMENT_H__
