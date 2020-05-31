#pragma once
#ifndef __AABB_H__
#define __AABB_H__

namespace dune {

struct MYMATH_API AABB
{
	enum CornersEnum
	{
		CORNER_TOP_MAX = 0,
		CORNER_TOP_MIN = 2,
		CORNER_DOWN_MAX = 4,
		CORNER_DOWN_MIN = 6
	};

	AABB()
	{
		// fast init
	}

	AABB(const Vector3& center) : _center(center), _half_widths( Vector3(0.5f, 0.5f, 0.5f) )
	{
		_max = getCorner( CORNER_TOP_MAX );
		_min = getCorner( CORNER_DOWN_MIN );
	}

	AABB(const Vector3& center, Vector3 halfWidths) : _center(center), _half_widths(halfWidths)
	{
		_max = getCorner( CORNER_TOP_MAX );
		_min = getCorner( CORNER_DOWN_MIN );
	}

	void Set(const Vector3& center, Vector3 halfWidths)
	{
		_center = center;
		_half_widths = halfWidths;

		_max = getCorner( CORNER_TOP_MAX );
		_min = getCorner( CORNER_DOWN_MIN );
	}

	inline Vector3& getMin() {return _min;}
	inline Vector3& getMax() {return _max;}

	bool IsIntersecting(const AABB& b)
	{
		// esta version es mas eficiente
		if(std::abs(_center.x - b._center.x) > (_half_widths.x + b._half_widths.x)) return false;
		if(std::abs(_center.y - b._center.y) > (_half_widths.y + b._half_widths.y)) return false;
		if(std::abs(_center.z - b._center.z) > (_half_widths.z + b._half_widths.z)) return false;
		return true;
	}

	inline bool IsInsideX( Real fX ) const
	{
		if (fX > _max.x) return false;
		if (fX < _min.x) return false;
		return true;
	}

	inline bool IsInsideY( Real fY ) const
	{
		if (fY > _max.y) return false;
		if (fY < _min.y) return false;
		return true;
	}

	inline bool IsInsideZ( Real fZ ) const
	{
		if (fZ > _max.z) return false;
		if (fZ < _min.z) return false;
		return true;
	}

	inline bool IsInside(const Vector3& pos)
	{
		// incluir min
		// excluir max
		/*
		if (pos.x >= m_vMax.x) return false;
		if (pos.x <= m_vMin.x) return false;
		if (pos.y >= m_vMax.y) return false;
		if (pos.y <= m_vMin.y) return false;
		if (pos.z >= m_vMax.z) return false;
		if (pos.z <= m_vMin.z) return false;
		*/
		// esta version es mas eficiente
		if (std::abs(_center.x - pos.x) > (_half_widths.x)) return false;
		if (std::abs(_center.y - pos.y) > (_half_widths.y)) return false;
		if (std::abs(_center.z - pos.z) > (_half_widths.z)) return false;
		return true;
	}

	/*
	Interseccion AABB vs segmento
	*/
	bool IsIntersecting(	const Vector3& vA,
							const Vector3& vB,
							Vector3& vIntersection,
							Real& fParam ) const
	{
		Real da;
		Real db;

		//x:
		if( vA.x < vB.x )
		{
			da = _min.x - vA.x;
			db = _min.x - vB.x;
		}
		else
		{
			da = vA.x - _max.x;
			db = vB.x - _max.x;
		}

		if( da > 0 )
		{
			if( db < 0 )
			{
				fParam = da / ( da - db );
			}
			else
			{
				return( false );
			}
		}
		else
		{
			fParam = 0.0f;
		}

		//y:
		if( vA.y < vB.y )
		{
			da = _min.y - vA.y;
			db = _min.y - vB.y;
		}
		else
		{
			da = vA.y - _max.y;
			db = vB.y - _max.y;
		}

		if( da > 0 )
		{
			if( db < 0 )
			{
				Real val = da / ( da - db );
				if(fParam < val)
					fParam = val;

				//Maximize( fParam, da / ( da - db ) );
			}
			else
			{
				return( false );
			}
		}

		//z:
		if( vA.z < vB.z )
		{
			da = _min.z - vA.z;
			db = _min.z - vB.z;
		}
		else
		{
			da = vA.z - _max.z;
			db = vB.z - _max.z;
		}

		if( da > 0 )
		{
			if( db < 0 )
			{
				Real val = da / ( da - db );
				if(fParam < val)
					fParam = val;

				//Maximize( fParam, da / ( da - db ) );
			}
			else
			{
				return( false );
			}
		}

		// InsideX:
		vIntersection.x = vA.x + ( vB.x - vA.x ) * fParam;
		if( !IsInsideX( vIntersection.x ) )
		{
			return( false );
		}

		// InsideY:
		vIntersection.y = vA.y + ( vB.y - vA.y ) * fParam;
		if( !IsInsideY( vIntersection.y ) )
		{
			return( false );
		}

		// InsideZ:
		vIntersection.z = vA.z + ( vB.z - vA.z ) * fParam;
		if( !IsInsideZ( vIntersection.z ) )
		{
			return( false );
		}

		return( true );
	}

	bool IsIntersecting( const Segment& segment, Vector3& vIntersection  ) const;


	AABB IntersectionResponse(AABB& b2)
	{
		// suponemos que los AABB son finitos y validos

		Vector3 intMin = getMin();
		Vector3 intMax = getMax();

		intMin.makeCeil( b2.getMin() );
		intMax.makeFloor( b2.getMax() );

		/*
		// Check intersection isn't null
		if (intMin.x < intMax.x &&
			intMin.y < intMax.y &&
			intMin.z < intMax.z)
		{
			ok = true;
		*/
			Vector3 center = (intMin - intMax) * 0.5f;
			Vector3 halfWidths = (intMax - intMin) * 0.5f;

			return AABB(center, halfWidths);
		/*
		}
		else
		{
			ok = false;
		}

		return AABB();
		*/
	}


	Vector3 getCorner(const unsigned int i) const
	{
		switch(i)
		{
			case CORNER_TOP_MAX:
				return _center + Vector3(+_half_widths.x, +_half_widths.y, +_half_widths.z);
				
			case 1:
				return _center + Vector3(-_half_widths.x, +_half_widths.y, +_half_widths.z);

			case CORNER_TOP_MIN:
				return _center + Vector3(-_half_widths.x, +_half_widths.y, -_half_widths.z);
				
			case 3:
				return _center + Vector3(+_half_widths.x, +_half_widths.y, -_half_widths.z);
				
			case CORNER_DOWN_MAX:
				return _center + Vector3(+_half_widths.x, -_half_widths.y, +_half_widths.z);
				
			case 5:
				return _center + Vector3(-_half_widths.x, -_half_widths.y, +_half_widths.z);
				
			case CORNER_DOWN_MIN:
				return _center + Vector3(-_half_widths.x, -_half_widths.y, -_half_widths.z);
				
			case 7:
				return _center + Vector3(+_half_widths.x, -_half_widths.y, -_half_widths.z);
		}
		return _center;
	}

	/// @brief	Centro del box
	Vector3 _center;

	/// @brief	Ancho (x) * Alto(z) en mitades (halfwidths)
	Vector3 _half_widths;

private:
	Vector3 _min;
	Vector3 _max;
};

}

#endif // __AABB_H__
