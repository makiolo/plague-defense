#include "myMath.h"
//
#include "Vector3.h"

namespace dune {

const Vector3 Vector3::ZERO( 0, 0, 0 );
const Vector3 Vector3::UNIT_X( 1, 0, 0 );
const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
const Vector3 Vector3::NEGATIVE_UNIT_X( -1,  0,  0 );
const Vector3 Vector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
const Vector3 Vector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

}

int Round(Real32 number)
{
	return static_cast<int>(
		number < 0.0f ? std::ceil(number - 0.5f) : std::floor(number + 0.5f)
		);
}

int Round(Real64 number)
{
	return static_cast<int>(
		number < 0.0 ? std::ceil(number - 0.5) : std::floor(number + 0.5)
		);
}

Real32 Q_rsqrt( Real32 number )
{
	Int32 i;
	Real32 x2, y;
	const Real32 threehalfs = 1.5f;

	x2 = number * 0.5f;
	y = number;
	i = * ( Int32 * ) &y; // evil floating point bit level hacking
	i = 0x5f375a86 - ( i >> 1 ); // what the fuck?
	y = * ( Real32 * ) &i;
	y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
	// y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
	return y;
}

Real64 Q_rsqrt(Real64 number)
{
	Int64 i;
	Real64 x2, y;
	const Real64 threehalfs = 1.5;

	x2 = number * 0.5;
	y = number;
	i = * ( Int64 * ) &y;
	i = 0x5fe6eb50c7aa19f9 - ( i >> 1 );
	y = * ( Real64 * ) &i;
	y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
	return y;
} 

