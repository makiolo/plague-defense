#ifndef __MATH_H__
#define __MATH_H__

#if defined(_WIN32) || defined(WIN32)
#ifdef myMath_EXPORTS
#define MYMATH_API __declspec(dllexport)
#else
#ifndef myMath_STATIC
#define MYMATH_API __declspec(dllimport)
#else
#define MYMATH_API
#endif
#endif
#else
#define MYMATH_API
#endif

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)

	typedef __int64				Int64;
	typedef signed int			Int32;
	typedef signed short		Int16;
	typedef signed char			Int8;

	typedef unsigned __int64	UInt64;
	typedef unsigned int		Uint32;
	typedef unsigned short		Uint16;
	typedef unsigned char		Uint8;

	typedef double				Real64;
	typedef float				Real32;

#else

	typedef long long			Int64;
	typedef signed int			Int32;
	typedef signed short		Int16;
	typedef signed char			Int8;

	typedef unsigned long long	UInt64;
	typedef unsigned int		Uint32;
	typedef unsigned short		Uint16;
	typedef unsigned char		Uint8;

	typedef double				Real64;
	typedef float				Real32;

#endif

// Hacer los tipos opacos
typedef Int32 Int;
typedef Uint32 Uint;
typedef Real32 Real;

// system
#include <cmath>
#include <tuple>
#include <utility> // std::pair
#include <complex> 
#include <cstring>

#include "Exceptions/h/Exceptions.h"

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#define PI_F32			3.14159265358979323846f
#define PI_HALF_F32		1.57079632679489661923f
#define PI_TWO_F32		6.28318530717958647692f
#define PI_INV_F32		0.31830988618379067154f
#define PI_F64			3.14159265358979323846
#define PI_HALF_F64		1.57079632679489661923
#define PI_TWO_F64		6.28318530717958647692
#define PI_INV_F64		0.31830988618379067154

#define DEG_TO_RAD (PI_F32 / Real(180.0))
#define RAD_TO_DEG (Real(180.0) / PI_F32)

#define EPSILON 0.0001f

#define Sq(exp) ((exp) * (exp))
#define Cub(exp) ((exp) * (exp) * (exp))

// #include <mmintrin.h>
#include <xmmintrin.h>

namespace dune {

#if 1
	inline float mmin(float a, float b)
	{
		// Branchless SSE min.
		_mm_store_ss(&a, _mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
		return a;
	}

	inline float mmax(float a, float b)
	{
		// Branchless SSE max.
		_mm_store_ss(&a, _mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
		return a;
	}

	inline float clamp(float val, float minval, float maxval)
	{
		_mm_store_ss(&val, _mm_min_ss(_mm_max_ss(_mm_set_ss(val), _mm_set_ss(minval)), _mm_set_ss(maxval)));
		return val;
	}

#else

	inline float clamp(Real x, Real a, Real b)
	{
		return x < a ? a : (x > b ? b : x);
	}

#endif

	// sign branching less
	template <typename T> int sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

	// abs branchless
	// http://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
	/*
	inline int absint(int v)
	{
#ifdef HAVE_SIGN_EXTENDING_BITSHIFT
		int const mask = v >> sizeof(int) * CHAR_BIT - 1;
#else
		int const mask = -((unsigned)v >> sizeof(int) * CHAR_BIT - 1);
#endif
		return (v + mask) ^ mask;
	}
	*/
}

// external
#include "Utils/h/Utils.h"

// class forward
namespace dune {
	class Plane;
	class Vector3;
	class Matrix4;
	class Quaternion;
	class Ray;
	class Collision;
	struct AABB;
	class Segment;
}

// internal
#include "Quaternion.h"
#include "Vector3.h"
#include "Plane.h"
#include "Ray.h"
#include "Matrix4.h"
#include "Collision.h"
#include "AABB.h"
#include "Segment.h"

#endif
