#include "myMath.h"
//

namespace dune {

bool AABB::IsIntersecting( const Segment& segment, Vector3& vIntersection ) const
{
    Real fParam;
    return( IsIntersecting( segment.GetStart(), segment.GetEnd(), vIntersection, fParam ) );
}

}
