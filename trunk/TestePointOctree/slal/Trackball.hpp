#ifndef TRACKBALL_HPP_
#define TRACKBALL_HPP_

#include "Quaternion.hpp"
#include "Matrix4x4.hpp"


template < class Real>
	class Trackball 
	{
	  private:
		  
	    int width, height;
	
	    CGL::Quaternion<Real> orientation; 
	    CGL::Quaternion<Real> startOrientation;
	    
	    CGL::Vector3<Real> startVector;
	    CGL::Vector3<Real> endVector;
	    
	    void mapToSphere(CGL::Vector3<Real> &v);
	    
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
	    const CGL::Quaternion<Real>& Orientation() { return orientation; }
	    CGL::Matrix4x4<Real> To4x4RotationMatrix();
	    void toOpenGL();
	};

#include "Trackball.inline.hpp"

#endif /*TRACKBALL_HPP_*/
