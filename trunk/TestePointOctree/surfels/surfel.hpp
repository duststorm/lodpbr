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
#include <cmath>

#include "slal/Point3.hpp"
#include "slal/Vector3.hpp"
#include "slal/Color.hpp"

extern "C" 
{
	#include <stdio.h>

	#include <strings.h>

	#include "ply.h"
}


#define PI 3.1415926535897932384626433832795

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
			 const Real& 	pError ) : mCenter(position),
	 								   mNormal(normal),
	 								   mSplatRadius(radius),
	 								   mPerpendicularError(pError),
	 								   mID(id)
	 	  {
		 	mColor = Color(0.0,0.0,0.0); 
		 	
		 	//mMinorAxis = std::make_pair(mSplatRadius,Vector)
	 	  };	
	
	
	 Surfel (const Point3& 	position, 
			 const Vector3& normal,
			 const Color&   color,
			 const Real& 	radius,
			 unsigned int 	id ) : 	mCenter(position),
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
			 unsigned int 	id ) : 	mCenter(position),
			 						mNormal(normal),
			 						mSplatRadius(radius),
			 						mPerpendicularError(0),
			 						mID(id)
		  {
		 	mColor = Color(0.0,0.0,0.0);
		  };
	
	 
	 Surfel (const Point3& 	position)
	 {
		 this->mCenter 		= position;
	         
	 };
	
    
	   
	 ~Surfel() {};
	
	 const Point3 Center () const 
	 { 
		 return  ( this->mCenter ) ; 
	 };
	 
	 Real Center(const int axis)  const
	 { 
		 return ( this->mCenter[axis] ); 
	 };
	 
	 void SetCenter(const Point3& pCenter) 
	 { 
		 this->mCenter = Point3(pCenter); 
	 };
	
	 const Vector3 Normal(void) const 
	 { 
		 return (this->mNormal); 
	 };
	 
	 Real Normal(int axis) const 
	 { 
		 return ( this->mNormal[axis] ); 
	 };
	 
	 void SetNormal (const Vector3& normal )
	 { 
		 this->mNormal = Vector3(normal); 
	 };
	
	 unsigned int ID () const 
	 { 
		 return ( this->ID_ ); 
	 };
	 
	 void SetID (unsigned int id) 
	 {	
		 this->ID_ = id; 
	 };
	
	 Real Radius (void) const 
	 { 
		 return this->mSplatRadius; 
	 };
	 
	 void SetRadius ( const Real& pRadius ) 
	 { 
		 this->mSplatRadius = pRadius; 
	 };
	  	  
	 Real perpendicularError () const 
	 { 
		 return ( this->mPerpendicularError ); 
	 };

	 void SetMinorAxis( const std::pair<Real,Vector3>& pMinorAxis)
	 {
		 this->mMinorAxis = pMinorAxis; 
	 }

	 void SetMajorAxis( const std::pair<Real,Vector3>& pMajorAxis)
	 {
		 this->mMajorAxis = pMajorAxis; 
	 }
	 
	 std::pair<Real,Vector3> MinorAxis() 
	 {
		 return (this->mMinorAxis); 
	 }

	 std::pair<Real,Vector3> MajorAxis() 
	 {
		 return (this->mMajorAxis); 
	 }
	 
	 /// I/O operator - output
	 inline friend std::ostream& operator << (std::ostream& out, const Surfel &s) 
	 {
	    out << s.perpendicularError() << " " << s.Center.x() << " " 
	    	<< s.Center.y() 	<< " " << s.Center.z() << " " 
	       	<< s.radius() 		<< " " << s.Normal.x() << " " 
	       	<< s.Normal.y() 	<< " " << s.Normal.z();
	    
	    return out;
	 };
	 
	 Real Area() const
	 {
		 return (  (PI * mMinorAxis.first) * (PI * mMajorAxis.first) );
	 }
	 
	 
	 
	 Vector3 Perpendicular( const Vector3& pVector)
	 {
		 //select the shortest of projections of axes on v
		 //(the closest to perpendicular to v),
		 //and project it to the plane defined by v
		 if ( fabs( pVector.x()) < fabs( pVector.y()) ) // x < y 
		 {

			 if ( fabs( pVector.x()) < fabs( pVector.z()) )
			 {  // x < y && x < z
				 Vector3 lPerpendicularX (1.0 - (pVector.x() * pVector.x()),
						 -pVector.x() * pVector.y(),
						 -pVector.x() * pVector.z() );
				 return lPerpendicularX;
			 }
		 }  
		 else
		 { //y <= x

			 if ( fabs(pVector.y()) < fabs(pVector.z()) )
			 {  // y <= x && y < z
				 Vector3 lPerpendicularY( -pVector.y() * pVector.x(), 
						 1.0 - (pVector.y() * pVector.y()), 
						 -pVector.y() * pVector.z() );
				 
				 return lPerpendicularY;

			 }
		 }
		 // z <= x && z <= y
		 Vector3 lPerpendicularZ(-pVector.z() * pVector.x(), 
				 				 -pVector.z() * pVector.y(), 
				 				 1.0 - (pVector.z() * pVector.z()));
		 return lPerpendicularZ;

	 }
	   
	   	 
	 std::list<Point3* > BoundariesSamples(unsigned int pSteps) const
	 { 

		 if (pSteps == 0)
		 {
			 pSteps = 4;
		 }
		 	 
		 std::list<Point3* > lPoints;

		 Real lAlpha 			= 0.0;     
		 Real lSinAlpha 		= 0.0;
		 Real lCosAlpha 		= 0.0;

		 Real lX 				= 0.0;
		 Real lY 				= 0.0;
		 Real lFactor 			= 0.0;

		 Real lCos				= 0.0;
		 Real lSin				= 0.0;
		 Vector3 lDirection     = Vector3();
		 
		 Real i = 0;

		 while (i < 360) 
		 {

			 lAlpha = ( i / 180 ) * PI;       
			 lSinAlpha =  sin( lAlpha );
			 lCosAlpha =  cos( lAlpha );


			 lX = mMinorAxis.first * lCosAlpha;

			 lY = mMajorAxis.first * lSinAlpha;

			 lFactor = sqrt( lX*lX + lY*lY );

			 lCos = lX / lFactor;
			 lSin = lY / lFactor;

			 lDirection = (mMinorAxis.second * lCos) + (mMajorAxis.second * lSin);
		 
			 lPoints.push_back( new Point3( (mCenter + (lDirection * lFactor)) ) );

			 i = i + (360.0 / pSteps);
			 
		 } 

		 return lPoints;

	 }

 private:
	 
	  /// Point coordinates
	  Point3 mCenter;

	  /// Estimated surface normal at point sample
	  Vector3 mNormal;
	  
	  Color mColor;
	  
	  /// Splat radius
	  Real mSplatRadius;

	  /// Minor Axis
	  std::pair<Real,Vector3> mMinorAxis;
	  
	  /// Major Axis
	  std::pair<Real,Vector3> mMajorAxis;
	  
	  /// Perpendicular error
	  Real mPerpendicularError;
	  
	  /// An identification number for the surfel
	  unsigned int mID;
	   

};

#endif
