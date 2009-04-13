#ifndef TRACKBALL_HPP_
#define TRACKBALL_HPP_

#include "Math/Quaternion.hpp"
#include "Math/Matrix4x4.hpp"

#define  INVSQRT2 1.0f/std::sqrt(2.0)

namespace LAL
{
template < class Real>	class Trackball
	{
	private:

	    int width, height;

	    LAL::Quaternion<Real> mOrientation;
	    LAL::Quaternion<Real> startOrientation;

	    LAL::Vector3<Real> startVector;
	    LAL::Vector3<Real> endVector;

	    void MapToSphere(LAL::Vector3<Real> &v);

	  public:
	    Trackball(int w,  int h):width( w ), height( h ) {}

	    Trackball() {}

	    void SetBounds (int pw, int ph)
	    {
	    	width = pw;
	    	height = ph;
	    }

	    void BeginTracking(int x, int y);
	    void Reset () { mOrientation.Identity(); }
	    void Tracking(int x, int y);
	    const LAL::Quaternion<Real>& Orientation() { return mOrientation; }
	    LAL::Matrix4x4<Real> To4x4RotationMatrix();
	    void ToOpenGL();

	};//End Interface


	template < class Real>
	void Trackball<Real>::MapToSphere(LAL::Vector3<Real> &v)
	{
		Real len2;

		v[0] = (2*v.x)/Real(width-1)-1;
		v[1] = 1-(2*v.y)/Real(height-1);
		v[2] = 0;
		if((len2 = v.LengthSqr())<INVSQRT2)
			v[2] = std::sqrt(1.0f-len2); // We are on the sphere
		else
			v[2] = 1.0f/(2*std::sqrt(len2)); // On the hyperbole
	}

	template < class Real>
	void Trackball<Real>::Tracking(int x, int y)
	{

		LAL::Quaternion<Real> q;
		LAL::Vector3<Real> endVector(Real(x), Real(y), 0);

		MapToSphere(endVector);
		q.ToRotationArc(startVector, endVector);
		mOrientation = q * startOrientation;

		mOrientation.Normalize();
	}

	template < class Real>
	void Trackball<Real>::BeginTracking(int x, int y)
	{
		startVector = LAL::Vector3<Real>(Real(x), Real(y), 0);
		startOrientation = mOrientation;
		MapToSphere(startVector);

	}
	template < class Real>
	LAL::Matrix4x4<Real> Trackball<Real>::To4x4RotationMatrix()
	{
		return mOrientation.To4x4Matrix();
	}


	template < class Real>
	void Trackball<Real>::ToOpenGL()
	{
		Real m[16];

		mOrientation.To4x4Matrix(m);

		glMultMatrixf((Real * )m);

	}

} /* LAL :: NAMESPACE */

#endif /*TRACKBALL_HPP_*/
