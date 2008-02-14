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


#include "matrixLibrary/Point3.hpp"
#include "matrixLibrary/Vector3.hpp"

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
		
	 typedef SLAL::Point3<Real> Point3; 
	 typedef SLAL::Vector3<Real> Vector3;
		 
	 Surfel (const Point3& 	position, 
			 const Vector3& normal, 
			 const Real& 	radius, 
			 unsigned int 	id, 
			 const Real& 	pError)
	 {
		 this->position_ 	= position;
	     this->normal_	 	= normal;
	     this->splatRadius_  = radius;
	     this->ID_ 			= id;
	     this->pError_ 		= pError;
	    
	 };
	
	 Surfel (const Point3& 	position, 
			 const Vector3& normal, 
			 const Real& 	radius, 
			 unsigned int 	id )
	 {
		 this->position_ 		= position;
	     this->normal_ 		= normal;
	     this->splatRadius_ 	= radius;
	     this->ID_ 			= id;
	     this->pError_ 		= static_cast<Real> (0);
	    
	 };
	
    
	   
	 ~Surfel() {};
	
	 const Point3 position () const 
	 { 
		 return  ( this->position_ ) ; 
	 };
	 
	 Real position(const int axis)  const
	 { 
		 return ( this->position_[axis] ); 
	 };
	 
	 void setPosition(const Point3& position) 
	 { 
		 this->positon = Point3(position); 
	 };
	
	 const Vector3 normal(void) const 
	 { 
		 return (this->normal); 
	 };
	 
	 Real normal(int axis) const 
	 { 
		 return ( this->normal_[axis] ); 
	 };
	 
	 void setNormal (const Vector3& normal )
	 { 
		 this->normal_ = Vector3(normal); 
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
		 return this->splatRadius_; 
	 };
	 
	 void setRadius ( const Real& radius ) 
	 { 
		 this->splatRadius_ = radius; 
	 };
	  
	 Real perpendicularError () const 
	 { 
		 return ( this->pError_ ); 
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
	  Point3 position_;

	  /// Estimated surface normal at point sample

	  Vector3 normal_;
	  
	  /// Splat radius
	  Real splatRadius_;

	  /// Perpendicular error
	  Real pError_;
	  
	  /// An identification number for the surfel
	  unsigned int ID_;
	  
  
	  

};

#endif
