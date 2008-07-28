#ifndef TRACKBALL_HPP_
#define TRACKBALL_HPP_

#include "math/Quaternion.hpp"
#include "math/Matrix4x4.hpp"


template < class Real>
	class Trackball
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
	};

#include "Trackball.inline.hpp"

#endif /*TRACKBALL_HPP_*/
