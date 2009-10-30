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
#include <list>
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>

#include "Math/Point3.hpp"
#include "Math/Vector3.hpp"
#include "Math/Color.hpp"
#include "Math/Math.hpp"

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

namespace LAL{

template <class Real > class Surfel
{
 public:

	 typedef typename LAL::Point3<Real>  Point3;
	 typedef typename LAL::Vector3<Real> Vector3;
	 typedef typename LAL::Color         Color;


	 typedef std::list<Point3>       			ListPoint3;
	 typedef typename ListPoint3::iterator  	ListPoint3Iterator;
	 typedef std::list<Point3* >       			ListPtrPoint3;
	 typedef typename ListPtrPoint3::iterator  	ListPtrPoint3Iterator;


	 Surfel ()
	 {
   	     mCenter = Point3();
 		 mNormal = Vector3();

		 mMinorAxis = std::make_pair(0.0,Vector3());
		 mMajorAxis = std::make_pair(0.0,Vector3());
		 mMarked = 0;
		 mExpansionMarked = 0;
		 mSeedMarked = 0;
		 mCost 		= 9999;
		 mClusterID = 0;


	 }

	 Surfel (const Surfel<Real>& pSurfel) :  mCenter(pSurfel.mCenter),
	   										 mNormal(pSurfel.mNormal),
	   									 	 mColor(pSurfel.mColor),
	   									 	 mSplatRadius(pSurfel.mSplatRadius),
	   										 mMinorAxis(pSurfel.mMinorAxis),
	   										 mMajorAxis(pSurfel.mMajorAxis),
	   										 mPerpendicularError(0),
	   										 mID(pSurfel.mID),
	   										 mMarked(0),
	   									     mExpansionMarked(0),
	   									     mSeedMarked(0),
	   									     mCost(9999),
	   										 mClusterID(0)
	 {

	 };

	 Surfel (const Point3& 	center,
			 const Vector3& normal,
			 const std::pair<Real,Vector3>& pMinorAxis,
	 		 const std::pair<Real,Vector3>& pMajorAxis,
			 unsigned int 	id ) : mCenter(center),
	 							   mNormal(normal),
	 							   mMinorAxis(pMinorAxis),
	 							   mMajorAxis(pMajorAxis),
	 							   mID(id),
	 							   mMarked(0),
								   mExpansionMarked(0),
								   mSeedMarked(0),
								   mCost(9999),
	 							   mClusterID(0)
	 	  {
		 	mColor = Color(1.0,0.0,0.0);

	 	  };

	 Surfel (const Point3& 	position,
			 const Vector3& normal,
			 const Real& 	radius,
			 unsigned int 	id,
			 const Real& 	pError ) : mCenter(position),
	 								   mNormal(normal),
	 								   mSplatRadius(radius),
	 								   mPerpendicularError(pError),
	 								   mID(id),
	 								   mMarked(0),
 									   mExpansionMarked(0),
 									   mSeedMarked(0),
 									   mCost(9999),
	 								   mClusterID(0)
	 	  {
		 	mColor = Color(0.0,0.0,0.0);
		 	mNormal.Normalize();
		 	Vector3 lV = Perpendicular(mNormal);
		 	Vector3 lU = mNormal ^ lV;
		 	lU.Normalize();
		 	mMinorAxis = std::make_pair(mSplatRadius,lV);
		 	mMajorAxis = std::make_pair(mSplatRadius,lU);
	 	  };


	 Surfel (const Point3& 	position,
			 const Vector3& normal,
			 const Color&   color,
			 const Real& 	radius,
			 unsigned int 	id ) : 	mCenter(position),
			 						mNormal(normal),
			 						mColor(color),
			 						mSplatRadius(radius),
			 						mPerpendicularError(0),
			 						mID(id),
			 						mMarked(0),
									mExpansionMarked(0),
									mSeedMarked(0),
									mCost(9999),
			 						mClusterID(0)


		  {
		 	mNormal.Normalize();
		 	Vector3 lV = Perpendicular(mNormal);
		 	Vector3 lU = mNormal ^ lV;
		 	lU.Normalize();
		 	mMinorAxis = std::make_pair(mSplatRadius,lV);
		 	mMajorAxis = std::make_pair(mSplatRadius,lU);
		 	//std::cout << " Value " << mMajorAxis.first << " Vector " << mMajorAxis.second << std::endl;
		  };

	 Surfel (const Point3& 	position,
			 const Vector3& normal,
			 const Real& 	radius,
			 unsigned int 	id ) : 	mCenter(position),
			 						mNormal(normal),
			 						mSplatRadius(radius),
			 						mPerpendicularError(0),
			 						mID(id),
			 						mMarked(0),
									mExpansionMarked(0),
									mSeedMarked(0),
									mCost(9999),
			 						mClusterID(0)
		  {
		 	mColor = Color(0.0,0.0,0.0);
		 	mNormal.normalize();
		 	Vector3 lV = Perpendicular(mNormal);
		 	Vector3 lU = mNormal ^ lV;
		 	lU.normalize();
		 	mMinorAxis = std::make_pair(mSplatRadius,lV);
		 	mMajorAxis = std::make_pair(mSplatRadius,lU);
		  };

	 inline const Surfel<Real>& operator= ( const Surfel<Real>& pSurfel)
	 {
		 this->mCenter    		= pSurfel.Center();
		 this->mNormal    		= pSurfel.Normal();
		 this->mMinorAxis 		= pSurfel.MinorAxis();
		 this->mMajorAxis 		= pSurfel.MajorAxis();
		 this->mColor     		= pSurfel.color();
		 this->mMarked    		= pSurfel.Marked();
		 this->mExpansionMarked = pSurfel.ExpansionMarked();
		 this->mSeedMarked		= pSurfel.SeedMarked();
		 this->mCost			= pSurfel.Cost();
		 this->mClusterID 		= pSurfel.ClusterID();

   	  	return ( *this );
	 }

	 Surfel (const Point3& 	position)
	 {
		 this->mCenter 		= position;

	 };

	 ~Surfel() {};

	 Point3 Center () const
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

	 Vector3 Normal(void) const
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
		 return ( this->mID );
	 };

	 void SetID (unsigned int id)
	 {
		 this->mID = id;
	 };

	 Real Radius (void) const
	 {
		 return this->mSplatRadius;
	 };

	 void SetRadius ( const Real& pRadius )
	 {
		 this->mSplatRadius = pRadius;
	 };

	 Color color (void) const
	 {
		 return this->mColor;
	 };

	 bool Marked (void) const
	 {
		 return this->mMarked;
	 };

	 void SetMarked ( bool pMarked)
	 {
		 this->mMarked = pMarked;
	 };

	 bool ExpansionMarked (void) const
	 {
		 return this->mExpansionMarked;
	 };

	 void SetExpansionMarked ( bool pMarked)
	 {
		 this->mExpansionMarked = pMarked;
	 };


	 bool SeedMarked (void) const
	 {
		 return this->mSeedMarked;
	 };

	 void SetSeedMarked ( bool pMarked)
	 {
		 this->mSeedMarked = pMarked;
	 };


	 unsigned long int ClusterID (void) const
	 {
		 return this->mClusterID;
	 };

	 void SetClusterID ( unsigned long int pClusterID)
	 {
		 this->mClusterID = pClusterID;
	 };

	 void SetColor ( const Color& pColor )
	 {
		 this->mColor = pColor;
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

	 std::pair<Real,Vector3> MinorAxis() const
	 {
		 return (this->mMinorAxis);
	 }

	 std::pair<Real,Vector3> MajorAxis() const
	 {
		 return (this->mMajorAxis);
	 }

	 void SetCost ( const Real& pCost )
	 {
		 this->mCost = pCost;
	 }

	 Real Cost ( ) const
	 {
		 return this->mCost;
	 }

	 /// I/O operator - output
	 inline friend std::ostream& operator << (std::ostream& out, const Surfel &s)
	 {
	    out << s.perpendicularError() << " " << s.Center.x << " "
	    	<< s.Center.y 	<< " " << s.Center.z << " "
	       	<< s.radius() 		<< " " << s.Normal.x << " "
	       	<< s.Normal.y 	<< " " << s.Normal.z;

	    return out;
	 };

	 Real Area() const
	 {
		 return (  (LAL::Math::kPi * mMinorAxis.first) * (LAL::Math::kPi * mMajorAxis.first) );
	 }



	 Vector3 Perpendicular( const Vector3& pVector)
	 {
		 //select the shortest of projections of axes on v
		 //(the closest to perpendicular to v),
		 //and project it to the plane defined by v
		 if ( fabs( pVector.x) < fabs( pVector.y) ) // x < y
		 {

			 if ( fabs( pVector.x) < fabs( pVector.z) )
			 {  // x < y && x < z
				 Vector3 lPerpendicularX (1.0 - (pVector.x * pVector.x),
						 				  -pVector.x * pVector.y,
						 				  -pVector.x * pVector.z );

				 return lPerpendicularX.Norm();
			 }
		 }
		 else
		 { //y <= x

			 if (fabs(pVector.y) < fabs(pVector.z) )
			 {  // y <= x && y < z
				 Vector3 lPerpendicularY( -pVector.y * pVector.x,
						 				  1.0 - (pVector.y * pVector.y),
						 				  -pVector.y * pVector.z );

				 return lPerpendicularY.Norm();

			 }
		 }
		 // z <= x && z <= y
		 Vector3 lPerpendicularZ(-pVector.z * pVector.x,
				 				 -pVector.z * pVector.y,
				 				 1.0 - (pVector.z * pVector.z));

		 return lPerpendicularZ.Norm();

	 }

	 std::list<Point3* > PtrBoundariesSamples(unsigned int pSteps) const
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

			 lAlpha = ( i / 180 ) * LAL::Math::kPi;
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

	 std::list<Point3> BoundariesSamples(unsigned int pSteps) const
	 {

		 if (pSteps == 0)
		 {
			 pSteps = 4;
		 }

		 std::list<Point3> lPoints;

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

			 lAlpha = ( i / 180 ) * LAL::Math::kPi;
			 lSinAlpha =  sin( lAlpha );
			 lCosAlpha =  cos( lAlpha );


			 lX = mMinorAxis.first * lCosAlpha;

			 lY = mMajorAxis.first * lSinAlpha;

			 lFactor = sqrt( lX*lX + lY*lY );

			 lCos = lX / lFactor;
			 lSin = lY / lFactor;

			 lDirection = (mMinorAxis.second * lCos) + (mMajorAxis.second * lSin);

			 lPoints.push_back( Point3( (mCenter + (lDirection * lFactor)) ) );

			 i = i + (360.0 / pSteps);

		 }

		 return lPoints;

	 }

	 void Draw(int p = 8)
	 {

		 	ListPoint3 lBoundaries = this->BoundariesSamples(p);
		 	glPushMatrix();
		 	glPointSize(1.0);
			for(ListPoint3Iterator it = lBoundaries.begin();it != lBoundaries.end();++it)
			{
				glVertex3fv( it->ToRealPtr());
			}
		 	glPopMatrix();
	 }

	 void DrawTriangleFan(int p = 8)
	 {

		 	ListPoint3 lBoundaries = this->BoundariesSamples(p);
		 	glPushMatrix();
		 	glEnable (GL_BLEND);
		 	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		    glEnable(GL_POLYGON_OFFSET_FILL);
		    glPolygonOffset(1,1);
		    //glColor3f(0.0,0.5,0.5);
		 	glBegin (GL_POLYGON);
		 		for(ListPoint3Iterator it = lBoundaries.begin();it != lBoundaries.end();++it)
		 		{
		 			glNormal3fv (this->mNormal.ToRealPtr());
		 			glVertex3fv( it->ToRealPtr() );
		 		}
			glEnd();
			glDisable(GL_POLYGON_OFFSET_FILL);
			glDisable (GL_BLEND);


		    glDisable (GL_LIGHTING);
			glColor3f(0.0,0.0,0.0);
			glBegin(GL_LINES);
	 			for(ListPoint3Iterator it = lBoundaries.begin();it != lBoundaries.end();++it)
	 			{
	 				glVertex3fv( it->ToRealPtr() );
	 				glVertex3fv( this->mCenter.ToRealPtr());
	 			}
			glEnd();

			glBegin(GL_POINTS);
	 			glVertex3fv( this->mCenter.ToRealPtr());
	 		glEnd();

	 		glEnable (GL_LIGHTING);
	 		glPopMatrix();


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

	  bool mMarked;
	  bool mExpansionMarked;
	  bool mSeedMarked;

	  Real mCost;

	  unsigned long int mClusterID;


};
}
#endif
