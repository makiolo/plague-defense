#include "myMath.h"
//
#include "Matrix4.h"

namespace dune {

const Matrix4 Matrix4::ZERO(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0 );

const Matrix4 Matrix4::IDENTITY(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 );

Matrix4 Matrix4::operator- () const
{
	// solo negamos el 3x3 (la orientacion)
	Matrix4 kNeg;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kNeg[iRow][iCol] = -m[iRow][iCol];
		}
	}
	return kNeg;
}

Matrix4 Matrix4::inverse() const
{
	Real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
	Real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
	Real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
	Real m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

	Real v0 = m20 * m31 - m21 * m30;
	Real v1 = m20 * m32 - m22 * m30;
	Real v2 = m20 * m33 - m23 * m30;
	Real v3 = m21 * m32 - m22 * m31;
	Real v4 = m21 * m33 - m23 * m31;
	Real v5 = m22 * m33 - m23 * m32;

	Real t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	Real t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	Real t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	Real t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

	Real invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

	Real d00 = t00 * invDet;
	Real d10 = t10 * invDet;
	Real d20 = t20 * invDet;
	Real d30 = t30 * invDet;

	Real d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Real d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Real d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Real d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;

	Real d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Real d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Real d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Real d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;

	Real d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Real d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Real d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Real d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	return Matrix4(
		d00, d01, d02, d03,
		d10, d11, d12, d13,
		d20, d21, d22, d23,
		d30, d31, d32, d33);
}

Matrix4 Matrix4::inverseAffine(void) const
{
	DUNE_ASSERT(isAffine());

	Real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2];
	Real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

	Real t00 = m22 * m11 - m21 * m12;
	Real t10 = m20 * m12 - m22 * m10;
	Real t20 = m21 * m10 - m20 * m11;

	Real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2];

	Real invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

	t00 *= invDet; t10 *= invDet; t20 *= invDet;

	m00 *= invDet; m01 *= invDet; m02 *= invDet;

	Real r00 = t00;
	Real r01 = m02 * m21 - m01 * m22;
	Real r02 = m01 * m12 - m02 * m11;

	Real r10 = t10;
	Real r11 = m00 * m22 - m02 * m20;
	Real r12 = m02 * m10 - m00 * m12;

	Real r20 = t20;
	Real r21 = m01 * m20 - m00 * m21;
	Real r22 = m00 * m11 - m01 * m10;

	Real m03 = m[0][3], m13 = m[1][3], m23 = m[2][3];

	Real r03 = - (r00 * m03 + r01 * m13 + r02 * m23);
	Real r13 = - (r10 * m03 + r11 * m13 + r12 * m23);
	Real r23 = - (r20 * m03 + r21 * m13 + r22 * m23);

	return Matrix4(
		r00, r01, r02, r03,
		r10, r11, r12, r13,
		r20, r21, r22, r23,
		0,   0,   0,   1);
}

void Matrix4::makeTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation)
{
	// Ordering:
	//    1. Scale
	//    2. Rotate
	//    3. Translate
	Matrix4 rotTemp;
	orientation.ToRotationMatrix(rotTemp);

	// Set up final matrix with scale, rotation and translation
	m[0][0] = scale.x * rotTemp[0][0]; m[0][1] = scale.y * rotTemp[0][1]; m[0][2] = scale.z * rotTemp[0][2]; m[0][3] = position.x;
	m[1][0] = scale.x * rotTemp[1][0]; m[1][1] = scale.y * rotTemp[1][1]; m[1][2] = scale.z * rotTemp[1][2]; m[1][3] = position.y;
	m[2][0] = scale.x * rotTemp[2][0]; m[2][1] = scale.y * rotTemp[2][1]; m[2][2] = scale.z * rotTemp[2][2]; m[2][3] = position.z;

	// No projection term
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}


Matrix4 Matrix4::buildProjectionOrthoMatrix(Real left, Real right, Real bottom, Real top,Real near, Real far)
{
	Matrix4 m;

	Real a = 2.0f / (right - left);
	Real b = 2.0f / (top - bottom);
	Real c = -2.0f / (far - near);

	Real tx = - (right + left)/(right - left);
	Real ty = - (top + bottom)/(top - bottom);
	Real tz = - (far + near)/(far - near);

	m.m[0][0] = a;			m.m[0][1] = 0.0f;	m.m[0][2] = 0.0f;		m.m[0][3] = tx;
	m.m[1][0] = 0.0f;		m.m[1][1] = b;		m.m[1][2] = 0.0f;		m.m[1][3] = ty;
	m.m[2][0] = 0.0f;		m.m[2][1] = 0.0f;	m.m[2][2] = c;			m.m[2][3] = tz;
	m.m[3][0] = 0.0f;		m.m[3][1] = 0.0f;	m.m[3][2] = 0.0f;		m.m[3][3] = 1.0f;

	return m;
}

// http://www.gamedev.net/topic/478055-perspective-projection-matrix/
// http://www.opengl.org/discussion_boards/ubbthreads.php?ubb=showflat&Number=251073

Matrix4 Matrix4::buildProjectionPerspectiveMatrix(Real near, Real far, Real aspect, Real fovy)
{
	Matrix4 m;

	Real f = 1.0f / std::tan(fovy/2.0f);

	m.m[0][0] = f/aspect;	m.m[0][1] = 0.0f;	m.m[0][2] = 0.0f;									m.m[0][3] = 0.0f;
	m.m[1][0] = 0.0f;		m.m[1][1] = f;		m.m[1][2] = 0.0f;									m.m[1][3] = 0.0f;
	m.m[2][0] = 0.0f;		m.m[2][1] = 0.0f;	m.m[2][2] = (far + near) / (near - far);	m.m[2][3] = (2.0f * far * near) / (near - far);
	m.m[3][0] = 0.0f;		m.m[3][1] = 0.0f;	m.m[3][2] = -1.0f;									m.m[3][3] = 0.0f;

	return m;
}

// http://iphonedevelopment.blogspot.com.es/2008/12/glulookat.html

Matrix4 Matrix4::buildViewMatrix(	Real eyex, Real eyey, Real eyez,
									Real centerx, Real centery, Real centerz,
									Real upx, Real upy, Real upz)
{
	Matrix4 m;
	Real x[3], y[3], z[3];
	Real mag;

	// Make rotation matrix

	// Z vector
	z[0] = eyex - centerx;
	z[1] = eyey - centery;
	z[2] = eyez - centerz;

	mag = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);

	if (mag)
	{
		z[0] /= mag;
		z[1] /= mag;
		z[2] /= mag;
	}

	// Y vector
	y[0] = upx;
	y[1] = upy;
	y[2] = upz;

	// X vector = Y cross Z
	x[0] = y[1] * z[2] - y[2] * z[1];
	x[1] = -y[0] * z[2] + y[2] * z[0];
	x[2] = y[0] * z[1] - y[1] * z[0];

	// Recompute Y = Z cross X
	y[0] = z[1] * x[2] - z[2] * x[1];
	y[1] = -z[0] * x[2] + z[2] * x[0];
	y[2] = z[0] * x[1] - z[1] * x[0];

	// cross product gives area of parallelogram, which is < 1.0 for
	// non-perpendicular unit-length vectors; so normalize x, y here

	mag = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);

	if (mag)
	{
		x[0] /= mag;
		x[1] /= mag;
		x[2] /= mag;
	}

	mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
	if (mag)
	{
		y[0] /= mag;
		y[1] /= mag;
		y[2] /= mag;
	}

#define M(row,col)  m._m[col*4+row]

	M(0, 0) = x[0];
	M(1, 0) = x[1];
	M(2, 0) = x[2];
	M(3, 0) = 0.0;
	M(0, 1) = y[0];
	M(1, 1) = y[1];
	M(2, 1) = y[2];
	M(3, 1) = 0.0;
	M(0, 2) = z[0];
	M(1, 2) = z[1];
	M(2, 2) = z[2];
	M(3, 2) = 0.0;
	M(0, 3) = 0.0;
	M(1, 3) = 0.0;
	M(2, 3) = 0.0;
	M(3, 3) = 1.0;

#undef M

	Matrix4 t;
	t.makeTrans(Vector3(-eyex, -eyey, -eyez));
	return m * t;
}


}

