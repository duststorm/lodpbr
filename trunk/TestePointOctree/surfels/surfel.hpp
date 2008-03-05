#ifndef SURFEL_HPP_
#define SURFEL_HPP_

/**
 * 
 * Author: Ricardo Marroquim, Felipe Moura
 *
 * Data created: 08-01-2008
 *
 **/

#include <vector>


#include "slal/Point3.hpp"
#include "slal/Vector3.hpp"
#include "slal/Color.hpp"

extern "C" 
{
	#include <stdio.h>

	#include <strings.h>

	#include "ply.h"
}


/**
 * Surfel class.
 * A surface element (surfel) is a sample point of the surface.
 * Also known as splats in some implementations.
 * The splat has an elliptical or circular form, and an estimated
 * surface normal at it's center.
 **/


template <class Real > class Surfel
{
 public:
		
	 typedef CGL::Point3<Real>  Point3; 
	 typedef CGL::Vector3<Real> Vector3;
	 typedef CGL::Color         Color;
		 
	 Surfel (const Point3& 	position, 
			 const Vector3& normal, 
			 const Real& 	radius, 
			 unsigned int 	id, 
			 const Real& 	pError ) : mPosition(position),
	 								   mNormal(normal),
	 								   mSplatRadius(radius),
	 								   mPerpendicularError(pError),
	 								   mID(id)
	 	  {
		 	mColor = Color(0.0,0.0,0.0); 
	 	  };	
	
	
	 Surfel (const Point3& 	position, 
			 const Vector3& normal,
			 const Color&   color,
			 const Real& 	radius,
			 unsigned int 	id ) : 	mPosition(position),
			 						mNormal(normal),
			 						mSplatRadius(radius),
			 						mPerpendicularError(0),
			 						mColor(color),
			 						mID(id)
		  {
		 
		  };
	  
	 Surfel (const Point3& 	position, 
			 const Vector3& normal, 
			 const Real& 	radius, 
			 unsigned int 	id ) : 	mPosition(position),
			 						mNormal(normal),
			 						mSplatRadius(radius),
			 						mPerpendicularError(0),
			 						mID(id)
		  {
		 	mColor = Color(0.0,0.0,0.0);
		  };
	
	 
	 Surfel (const Point3& 	position)
	 {
		 this->mPosition 		= position;
	         
	 };
	
    
	   
	 ~Surfel() {};
	
	 const Point3 position () const 
	 { 
		 return  ( this->mPosition ) ; 
	 };
	 
	 Real position(const int axis)  const
	 { 
		 return ( this->mPosition[axis] ); 
	 };
	 
	 void setPosition(const Point3& position) 
	 { 
		 this->positon = Point3(position); 
	 };
	
	 const Vector3 normal(void) const 
	 { 
		 return (this->mNormal); 
	 };
	 
	 Real normal(int axis) const 
	 { 
		 return ( this->mNormal[axis] ); 
	 };
	 
	 void setNormal (const Vector3& normal )
	 { 
		 this->mNormal = Vector3(normal); 
	 };
	
	 unsigned int ID () const 
	 { 
		 return ( this->ID_ ); 
	 };
	 
	 void setID (unsigned int id) 
	 {	
		 this->ID_ = id; 
	 };
	
	 Real radius (void) const 
	 { 
		 return this->mSplatRadius; 
	 };
	 
	 void setRadius ( const Real& radius ) 
	 { 
		 this->mSplatRadius = radius; 
	 };
	  
	 Real perpendicularError () const 
	 { 
		 return ( this->mPerpendicularError ); 
	 };
	
	  /// I/O operator - output
	 inline friend std::ostream& operator << (std::ostream& out, const Surfel &s) 
	 {
	    out << s.perpendicularError() << " " << s.position.x() << " " 
	    	<< s.position.y() 	<< " " << s.position.z() << " " 
	       	<< s.radius() 		<< " " << s.normal.x() << " " 
	       	<< s.normal.y() 	<< " " << s.normla.z();
	    
	    return out;
	 };

 
 private:
	  /// Point coordinates
	  Point3 mPosition;

	  /// Estimated surface normal at point sample

	  Vector3 mNormal;
	  
	  Color mColor;
	  
	  /// Splat radius
	  Real mSplatRadius;

	  /// Perpendicular error
	  Real mPerpendicularError;
	  
	  /// An identification number for the surfel
	  unsigned int mID;
	  
  
	  

};

#endif
