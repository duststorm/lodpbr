#ifndef TRACKBALL_HPP_
#define TRACKBALL_HPP_

#include "Quaternion.hpp"
#include "Matrix4x4.hpp"


template < class Real>
	class Trackball 
	{
	  private:
		  
	    int width, height;
	
	    LAL::Quaternion<Real> mOrientation; 
	    LAL::Quaternion<Real> startOrientation;
	    
	    LAL::Vector3<Real> startVector;
	    LAL::Vector3<Real> endVector;
	    
	    void mapToSphere(LAL::Vector3<Real> &v);
	    
	  public:
	    Trackball(int w,  int h):width( w ), height( h ) {}
	
	    Trackball() {}
	    
	    void setBounds (int pw, int ph)
	    {
	    	width = pw;
	    	height = ph;
	    }

	    void beginTracking(int x, int y);
	    void reset () { mOrientation.Identity(); }
	    void tracking(int x, int y);
	    const LAL::Quaternion<Real>& orientation() { return mOrientation; }
	    LAL::Matrix4x4<Real> to4x4RotationMatrix();
	    void toOpenGL();
	};

#include "Trackball.inline.hpp"

#endif /*TRACKBALL_HPP_*/
