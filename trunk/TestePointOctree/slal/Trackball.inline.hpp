#ifndef TRACKBALL_INLINE_HPP_
#define TRACKBALL_INLINE_HPP_

#define  INVSQRT2 1.0f/std::sqrt(2.0)

#include "Trackball.hpp"

template < class Real>
void Trackball<Real>::mapToSphere(CGL::Vector3<Real> &v)
{
	Real len2;

	v[0] = (2*v.x())/Real(width-1)-1;
	v[1] = 1-(2*v.y())/Real(height-1);
	v[2] = 0;
	if((len2 = v.length2())<INVSQRT2)
		v[2] = std::sqrt(1.0f-len2); // We are on the sphere
	else
		v[2] = 1.0f/(2*std::sqrt(len2)); // On the hyperbole
}

template < class Real>
void Trackball<Real>::Tracking(int x, int y)
{

	CGL::Quaternion<Real> q;
	CGL::Vector3<Real> endVector(Real(x), Real(y), 0);

	mapToSphere(endVector);
	q.ToRotationArc(startVector, endVector);
	orientation = q * startOrientation;
		
	orientation.Normalize();
}

template < class Real>
void Trackball<Real>::BeginTracking(int x, int y)
{
	startVector = CGL::Vector3<Real>(Real(x), Real(y), 0);
	startOrientation = orientation;
	mapToSphere(startVector);

}
template < class Real>
CGL::Matrix4x4<Real> Trackball<Real>::To4x4RotationMatrix()
{
	return orientation.To4x4Matrix();
}


template < class Real> 
void Trackball<Real>::toOpenGL() 
{
	Real m[16];

	orientation.To4x4Matrix(m);

	glMultMatrixf((Real * )m);
	
}


#endif /*TRACKBALL_INLINE_HPP_*/
