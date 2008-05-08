#ifndef TRACKBALL_HPP_
#define TRACKBALL_HPP_

#include "Quaternion.hpp"
#include "Matrix4x4.hpp"


template < class Real>
	class Trackball 
	{
	  private:
		  
	    int width, height;
	
	    LAL::Quaternion<Real> orientation; 
	    LAL::Quaternion<Real> startOrientation;
	    
	    LAL::Vector3<Real> startVector;
	    LAL::Vector3<Real> endVector;
	    
	    void mapToSphere(LAL::Vector3<Real> &v);
	    
	  public:
	    Trackball(int w,  int h):width( w ), height( h ) {}
	
	    Trackball() {}
	    
	    void SetBounds (int pw, int ph)
	    {
	    	width = pw;
	    	height = ph;
	    }

	    void BeginTracking(int x, int y);
	    void Reset () { orientation.Identity(); }
	    void Tracking(int x, int y);
	    const LAL::Quaternion<Real>& Orientation() { return orientation; }
	    LAL::Matrix4x4<Real> To4x4RotationMatrix();
	    void toOpenGL();
	};

#include "Trackball.inline.hpp"

#endif /*TRACKBALL_HPP_*/
