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

#include <wrap/io_trimesh/import_ply.h>
#include <wrap/io_trimesh/io_ply.h>
#include <wrap/ply/plylib.h>

#include "Math/Point3.hpp"
#include "Math/Vector3.hpp"
#include "Math/Color.hpp"
#include "Math/Math.hpp"

/**
 * Surfel class.
 * A surface element (surfel) is a sample point of the surface.
 * Also known as splats in some implementations.
 * The splat has an elliptical or circular form, and an estimated
 * surface normal at it's center.
 **/


namespace Celer{

template <class Real = float >
class Surfel
{
 public:

	typedef	Real		   						Type;
	typedef Surfel<Real>*						Pointer;
	typedef Surfel<Real>						This;
	typedef  Celer::Point3<Real>  				Point3;
	typedef  Celer::Vector3<Real>				Vector3;
	typedef  Celer::Color 		  				Color;

	typedef typename std::vector<This>				Vector;
	typedef typename Vector::iterator				VectorIterator;

	typedef std::vector<Pointer>					VectorPointers;
	typedef typename VectorPointers::iterator		VectorPointersIterator;

	typedef std::list<This>							List;
	typedef typename List::iterator					ListIterator;

	typedef std::list<Pointer>						ListPointers;
	typedef typename ListPointers::iterator			ListPointersIterator;

	typedef std::list<Point3>       				ListPoint3;
	typedef typename ListPoint3::iterator  			ListPoint3Iterator;

	typedef ::vcg::ply::PropDescriptor PropDescriptor ;

/* IO PLY */

	enum
	{
		IOM_SURFEL = 0x10002
	};

	struct LoadPlySurfel
	{
		float cx;
		float cy;
		float cz;
		float nx;
		float ny;
		float nz;
		float major_axisx;
		float major_axisy;
		float major_axisz;
		float major_axis_size;
		float minor_axisx;
		float minor_axisy;
		float minor_axisz;
		float minor_axis_size;
		float r;
		float g;
		float b;
		float max_error;
		float min_error;
		inline const LoadPlySurfel& operator= ( const Surfel<Real>& pSurfel)
		{

			this->cx    		= pSurfel.Center().x;
			this->cy    		= pSurfel.Center().y;
			this->cz    		= pSurfel.Center().z;
			this->nx    		= pSurfel.Normal().x;
			this->ny    		= pSurfel.Normal().y;
			this->nz    		= pSurfel.Normal().z;

			this->major_axisx  = pSurfel.MajorAxis().second.x;
			this->major_axisy  = pSurfel.MajorAxis().second.y;
			this->major_axisz  = pSurfel.MajorAxis().second.z;
			this->major_axis_size  = pSurfel.MajorAxis().first;

			this->minor_axisx  = pSurfel.MinorAxis().second.x;
			this->minor_axisy  = pSurfel.MinorAxis().second.y;
			this->minor_axisz  = pSurfel.MinorAxis().second.z;
			this->minor_axis_size  = pSurfel.MinorAxis().first;
			this->r	     		= pSurfel.ColorRGB().Red();
			this->g 				= pSurfel.ColorRGB().Green();
			this->b                = pSurfel.ColorRGB().Blue();
			this->max_error 		= pSurfel.MaxError();
			this->min_error 		= pSurfel.MinError();

			return ( *this );
		}
	};


	static const  PropDescriptor &SurfelDesc(int i)
	{
		static const PropDescriptor surfel[19] =
		{
				{"surfel","cx"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,cx)				,0,0,0,0,0  ,0},
				{"surfel","cy"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,cy)				,0,0,0,0,0  ,0},
				{"surfel","cz"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,cz)				,0,0,0,0,0  ,0},
				{"surfel","nx"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,nx)				,0,0,0,0,0  ,0},
				{"surfel","ny"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,ny)				,0,0,0,0,0  ,0},
				{"surfel","nz"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,nz)				,0,0,0,0,0  ,0},
				{"surfel","major_axisx"		,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,major_axisx)		,0,0,0,0,0  ,0},
				{"surfel","major_axisy"		,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,major_axisy)		,0,0,0,0,0  ,0},
				{"surfel","major_axisz"		,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,major_axisz)		,0,0,0,0,0  ,0},
				{"surfel","major_axis_size"	,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,major_axis_size)	,0,0,0,0,0  ,0},
				{"surfel","minor_axisx"		,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,minor_axisx)		,0,0,0,0,0  ,0},
				{"surfel","minor_axisy"		,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,minor_axisy)		,0,0,0,0,0  ,0},
				{"surfel","minor_axisz"  	,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,minor_axisz)		,0,0,0,0,0  ,0},
				{"surfel","minor_axis_size" ,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,minor_axis_size)	,0,0,0,0,0  ,0},
				{"surfel","r"	 			,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,r)					,0,0,0,0,0  ,0},
				{"surfel","g"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,g)					,0,0,0,0,0  ,0},
				{"surfel","b"				,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,b)					,0,0,0,0,0  ,0},
				{"surfel","max_error"		,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,max_error)			,0,0,0,0,0  ,0},
				{"surfel","min_error"		,vcg::ply::T_FLOAT,vcg::ply::T_FLOAT,offsetof(LoadPlySurfel,min_error)			,0,0,0,0,0  ,0}
		};
		return surfel[i];
	}
/* END */

	 Surfel ();

	 Surfel (const Surfel<Real>& pSurfel);

	 Surfel (const Surfel<Real>* pSurfel);

	 Surfel (const LoadPlySurfel& pSurfel);

	 Surfel (const Point3& 	center,
			 const Vector3& normal,
			 const std::pair<Real,Vector3>& pMinorAxis,
	 		 const std::pair<Real,Vector3>& pMajorAxis,
			 unsigned int 	id );

	 Surfel (const Point3& 	position,
			 const Vector3& normal,
			 const Real& 	radius,
			 unsigned int 	id,
			 const Real& 	pError );


	 Surfel (const Point3& 	position,
			 const Vector3& normal,
			 const Color&   color,
			 const Real& 	radius,
			 unsigned int 	id );

	 Surfel (const Point3& 	position,
			 const Vector3& normal,
			 const Real& 	radius,
			 unsigned int 	id );

	 inline const Surfel<Real>& operator= ( const Surfel<Real>& pSurfel);

	 Surfel (const Point3& 	position);
	 ~Surfel();

	 Point3  					Center 				(  ) const;
	 Real    					Center				( const int axis ) const;
	 void    					SetCenter			( const Point3& pCenter );

	 Vector3 	  				Normal				(  ) const;
	 Real    	  				Normal      		( int axis ) const;
	 void 	 	  				SetNormal   		( const Vector3& normal );

	 unsigned int 				ID 					(  ) const;
	 void 						SetID 				( unsigned int id );

	 Real 						Radius 				( void ) const;
	 void 						SetRadius 			( const Real& pRadius );

	 Color 						ColorRGB 			( void ) const;
	 void 						SetColorRGB 		( const Color& pColor );

	 bool 						Marked 				( void ) const;
	 void 						SetMarked 			( bool pMarked );

	 bool 						ExpansionMarked 	(void ) const;
	 void 						SetExpansionMarked 	( bool pMarked );


	 bool 						SeedMarked 			( void ) const;
	 void 						SetSeedMarked 		( bool pMarked	);

	 unsigned  int 				ClusterID 			( void ) const;
	 void 						SetClusterID 		( unsigned int pClusterID );
	 Real 						PerpendicularError  ( ) const;
	 void 						SetMinorAxis		( const std::pair<Real,Vector3>& pMinorAxis );
	 void 						SetMajorAxis		( const std::pair<Real,Vector3>& pMajorAxis );
	 std::pair<Real,Vector3> 	MinorAxis			(  ) const;
	 std::pair<Real,Vector3> 	MajorAxis			(  ) const;

	 Real 						MaxError 			(  ) const;
	 void 						SetMaxError			( const Real& pMaxError ) const;
	 Real 						MinError 			(  ) const;
   	 void 						SetMinError 		( const Real& pMinError ) const;
	 Real 						Cost 				(  ) const;
	 void 						SetCost 			( const Real& pCost );

	 Real 						Area				(  ) const;

	 Vector3 					Perpendicular		( const Vector3& pVector );
	 ListPoint3 				BoundariesSamples	( unsigned int pSteps,const Real& pRadius = 1.0 ) const;

	 static void 				DrawSurfel			(Surfel<Real>& s)
	 {
	 	 	glPushMatrix();
	 	 	glPointSize(1.0);
	 	 	glVertex3fv( s.Center().ToRealPtr());
	 	 	glPopMatrix();
	 }
	 void 					    DrawCenter			(const GLfloat& size = 1.0);
	 void 						Draw				( int p = 8 ,const Real& pRadius = 1.0);
	 void 						DrawTriangleFan		( int p = 8 ,const Real& pRadius = 1.0);

	 template <class T>
	 inline friend std::ostream& operator << 		( std::ostream& out, const Surfel<T> &s );

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

	  Real mMaxError;
	  Real mMinError;

	  /// Perpendicular error
	  Real mPerpendicularError;

	  /// An identification number for the surfel
	  unsigned int mID;

	  //Cluster building
	  bool mMarked;
	  bool mExpansionMarked;
	  bool mSeedMarked;

	  Real mCost;

	  unsigned  int mClusterID;


};


template<class Real>
Surfel<Real>::Surfel ()
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

template<class Real>
Surfel<Real>::Surfel (const Surfel<Real>& pSurfel) :  mCenter(pSurfel.mCenter),
  										 mNormal(pSurfel.mNormal),
  									 	 mColor(pSurfel.mColor),
  									 	 mSplatRadius(pSurfel.mSplatRadius),
  										 mMinorAxis(pSurfel.mMinorAxis),
  										 mMajorAxis(pSurfel.mMajorAxis),
  		   								 mMaxError(pSurfel.mMaxError),
  		   								 mMinError(pSurfel.mMinError),
  										 mPerpendicularError(pSurfel.mPerpendicularError),
  										 mID(pSurfel.mID),
  										 mMarked(pSurfel.mMarked),
  									     mExpansionMarked(pSurfel.mExpansionMarked),
  									     mSeedMarked(pSurfel.mSeedMarked),
  									     mCost(pSurfel.mCost),
  										 mClusterID(pSurfel.mClusterID)
{

};

template<class Real>
Surfel<Real>::Surfel (const Surfel<Real>* pSurfel) :  mCenter(pSurfel->mCenter),
  										 mNormal(pSurfel->mNormal),
  									 	 mColor(pSurfel->mColor),
  									 	 mSplatRadius(pSurfel->mSplatRadius),
  										 mMinorAxis(pSurfel->mMinorAxis),
  										 mMajorAxis(pSurfel->mMajorAxis),
  		   								 mMaxError(pSurfel->mMaxError),
  		   								 mMinError(pSurfel->mMinError),
  										 mPerpendicularError(pSurfel->mPerpendicularError),
  										 mID(pSurfel->mID),
  										 mMarked(pSurfel->mMarked),
  									     mExpansionMarked(pSurfel->mExpansionMarked),
  									     mSeedMarked(pSurfel->mSeedMarked),
  									     mCost(pSurfel->mCost),
  										 mClusterID(pSurfel->mClusterID)
{

};

template<class Real>
Surfel<Real>::Surfel (const LoadPlySurfel& pSurfel) : mCenter(pSurfel.cx,pSurfel.cy,pSurfel.cz),
  										 mNormal(pSurfel.nx,pSurfel.ny,pSurfel.nz),
  									 	 mColor(pSurfel.r,pSurfel.g,pSurfel.b),
  									 	 mSplatRadius(0),
  										 mMajorAxis(std::pair<Real,Vector3>(pSurfel.major_axis_size,
  												              Vector3(pSurfel.major_axisx,
  												            		  pSurfel.major_axisy,
  												            		  pSurfel.major_axisz))),
  								         mMinorAxis(std::pair<Real,Vector3>(pSurfel.minor_axis_size,
  								        		              Vector3(pSurfel.minor_axisx,
  												               		  pSurfel.minor_axisy,
  												               		  pSurfel.minor_axisz))),
  										 mMaxError(pSurfel.max_error),
  										 mMinError(pSurfel.min_error),
  										 mPerpendicularError(0),
  										 mID(0),
  										 mMarked(0),
  									     mExpansionMarked(0),
  									     mSeedMarked(0),
  									     mCost(9999),
  										 mClusterID(0)
{

};

template<class Real>
Surfel<Real>::Surfel (const Point3& 	center,
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
		mMaxError = 0;
		mMinError = 0;

	  };

template<class Real>
Surfel<Real>::Surfel (const Point3& 	position,
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
		mMaxError = 0;
		mMinError = 0;
	  };


template<class Real>
Surfel<Real>::Surfel (const Point3& 	position,
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
		mMaxError = 0;
		mMinError = 0;
	 	//std::cout << " Value " << mMajorAxis.first << " Vector " << mMajorAxis.second << std::endl;
	  };

template<class Real>
Surfel<Real>::Surfel (const Point3& 	position,
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
		mMaxError = 0;
		mMinError = 0;
	  };


template<class Real>
inline const Surfel<Real>& Surfel<Real>::operator= ( const Surfel<Real>& pSurfel)
{
	 this->mCenter    		= pSurfel.Center();
	 this->mNormal    		= pSurfel.Normal();
	 this->mMinorAxis 		= pSurfel.MinorAxis();
	 this->mMajorAxis 		= pSurfel.MajorAxis();
	 this->mMaxError 		= pSurfel.MaxError();
	 this->mMinError 		= pSurfel.MinError();
	 this->mColor     		= pSurfel.ColorRGB();
	 this->mMarked    		= pSurfel.Marked();
	 this->mExpansionMarked = pSurfel.ExpansionMarked();
	 this->mSeedMarked		= pSurfel.SeedMarked();
	 this->mCost			= pSurfel.Cost();
	 this->mClusterID 		= pSurfel.ClusterID();

	  	return ( *this );
}

template<class Real>
Surfel<Real>::Surfel (const Point3& 	position)
{
	 this->mCenter 		= position;

};

template<class Real>
Surfel<Real>::~Surfel() {};

template<class Real>
Point3<Real> Surfel<Real>::Center () const
{
	 return  ( this->mCenter ) ;
};

template<class Real>
Real Surfel<Real>::Center(const int axis)  const
{
	 return ( this->mCenter[axis] );
};

template<class Real>
void Surfel<Real>::SetCenter(const Point3& pCenter)
{
	 this->mCenter = Point3(pCenter);
};

template<class Real>
Vector3<Real> Surfel<Real>::Normal(void) const
{
	 return (this->mNormal);
};

template<class Real>
Real Surfel<Real>::Normal(int axis) const
{
	 return ( this->mNormal[axis] );
};

template<class Real>
void Surfel<Real>::SetNormal (const Vector3& normal )
{
	 this->mNormal = Vector3(normal);
};

template<class Real>
unsigned int Surfel<Real>::ID () const
{
	 return ( this->mID );
};

template<class Real>
void Surfel<Real>::SetID (unsigned int id)
{
	 this->mID = id;
};

template<class Real>
Real Surfel<Real>::Radius (void) const
{
	 return this->mSplatRadius;
};

template<class Real>
void Surfel<Real>::SetRadius ( const Real& pRadius )
{
	 this->mSplatRadius = pRadius;
};

template<class Real>
Color Surfel<Real>::ColorRGB (void) const
{
	 return this->mColor;
};

template<class Real>
void Surfel<Real>::SetColorRGB ( const Color& pColor )
{
	 this->mColor = pColor;
};

template<class Real>
bool Surfel<Real>::Marked (void) const
{
	 return this->mMarked;
};

template<class Real>
void Surfel<Real>::SetMarked ( bool pMarked)
{
	 this->mMarked = pMarked;
};

template<class Real>
bool Surfel<Real>::ExpansionMarked (void) const
{
	 return this->mExpansionMarked;
};

template<class Real>
void Surfel<Real>::SetExpansionMarked ( bool pMarked)
{
	 this->mExpansionMarked = pMarked;
};


template<class Real>
bool Surfel<Real>::SeedMarked (void) const
{
	 return this->mSeedMarked;
};

template<class Real>
void Surfel<Real>::SetSeedMarked ( bool pMarked)
{
	 this->mSeedMarked = pMarked;
};

template<class Real>
unsigned int Surfel<Real>::ClusterID (void) const
{
	 return this->mClusterID;
};

template<class Real>
void Surfel<Real>::SetClusterID ( unsigned int pClusterID)
{
	 this->mClusterID = pClusterID;
};

template<class Real>
Real Surfel<Real>::PerpendicularError () const
{
	 return ( this->mPerpendicularError );
};

template<class Real>
void Surfel<Real>::SetMinorAxis( const std::pair<Real,Vector3>& pMinorAxis)
{
	 this->mMinorAxis = pMinorAxis;
}

template<class Real>
void Surfel<Real>::SetMajorAxis( const std::pair<Real,Vector3>& pMajorAxis)
{
	 this->mMajorAxis = pMajorAxis;
}

template<class Real>
std::pair<Real,Vector3<Real> > Surfel<Real>::MinorAxis() const
{
	 return (this->mMinorAxis);
}

template<class Real>
std::pair<Real,Vector3<Real> > Surfel<Real>::MajorAxis() const
{
	 return (this->mMajorAxis);
}

template<class Real>
Real Surfel<Real>::MaxError () const
{
	 return ( this->mMaxError );
};

template<class Real>
void Surfel<Real>::SetMaxError (const Real& pMaxError) const
{
	 this->mMaxError = pMaxError;
};

template<class Real>
Real Surfel<Real>::MinError () const
{
	 return ( this->mMinError );
};

template<class Real>
void Surfel<Real>::SetMinError (const Real& pMinError) const
{
	 this->mMinError = pMinError;
};

template<class Real>
void Surfel<Real>::SetCost ( const Real& pCost )
{
	 this->mCost = pCost;
}

template<class Real>
Real Surfel<Real>::Cost ( ) const
{
	 return this->mCost;
}

/// I/O operator - output
template<class Real>
inline  std::ostream& operator << (std::ostream& out, const Surfel<Real> &s)
{
	 out 	 << "Center " << s.Center() << "\n"
			 <<	"Normal " << s.Normal() << "\n"
			 <<	"Radius " << s.Radius() << "\n"
			 <<	"MajorAxis "<< s.MajorAxis().first << " -  " << s.MajorAxis().second << "\n"
			 <<	"MinorAxis "<< s.MinorAxis().first << " -  " << s.MinorAxis().second << "\n"
			 <<	"Color "    << s.ColorRGB() << "\n"
			 <<	"MaxError " << s.MaxError() << "\n"
			 <<	"MinError " << s.MinError() << "\n"
			 <<	"ID       " << s.ID() << "\n";




   return out;
};

template<class Real>
Real Surfel<Real>::Area() const
{
	 return (  (Celer::Math::kPi * mMinorAxis.first) * (Celer::Math::kPi * mMajorAxis.first) );
}


template<class Real>
Vector3<Real> Surfel<Real>::Perpendicular( const Vector3& pVector)
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

template<class Real>
typename Surfel<Real>::ListPoint3 Surfel<Real>::BoundariesSamples(unsigned int pSteps,const Real& pRadius) const
{

	 if (pSteps == 0)
	 {
		 pSteps = 4;
	 }

	 ListPoint3 lPoints;

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

		 lAlpha = ( i / 180 ) * Celer::Math::kPi;
		 lSinAlpha =  sin( lAlpha );
		 lCosAlpha =  cos( lAlpha );


		 lX = pRadius * mMinorAxis.first * lCosAlpha;

		 lY = pRadius * mMajorAxis.first * lSinAlpha;

		 lFactor = sqrt( lX*lX + lY*lY );

		 lCos = lX / lFactor;
		 lSin = lY / lFactor;

		 lDirection = (mMinorAxis.second * lCos) + (mMajorAxis.second * lSin);

		 lPoints.push_back( Point3( (mCenter + (lDirection * lFactor)) ) );

		 i = i + (360.0 / pSteps);

	 }

	 return lPoints;

}

template<class Real>
void Surfel<Real>::DrawCenter(const GLfloat& size)
{
	 	glPushMatrix();
	 	glPointSize(size);
	 	glBegin(GL_POINTS);
			glVertex3fv( mCenter.ToRealPtr() );
		glEnd();
	 	glPopMatrix();
}

template<class Real>
void Surfel<Real>::Draw(int p,const Real& pRadius)
{

		ListPoint3 lBoundaries = this->BoundariesSamples(p,pRadius);
	 	glPushMatrix();
	 	glPointSize(1.0);
	 	glBegin(GL_POINTS);
		for(ListPoint3Iterator it = lBoundaries.begin();it != lBoundaries.end();++it)
		{
			glVertex3fv( it->ToRealPtr());
		}
		glEnd();
	 	glPopMatrix();
}

template<class Real>
void Surfel<Real>::DrawTriangleFan(int p,const Real& pRadius)
{

	 	ListPoint3 lBoundaries = this->BoundariesSamples(p,pRadius);
	 	glPushMatrix();
	 	glEnable (GL_BLEND);
	 	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	    glEnable(GL_POLYGON_OFFSET_FILL | GL_POLYGON_SMOOTH_HINT | GL_MULTISAMPLE);
	    glPolygonOffset(1,1);
	    glColor4f(0.0,0.5,0.5,0.5);
	 	glBegin (GL_POLYGON);
	 		for(ListPoint3Iterator it = lBoundaries.begin();it != lBoundaries.end();++it)
	 		{
	 			glNormal3fv (this->mNormal.ToRealPtr());
	 			glVertex3fv( it->ToRealPtr() );
	 		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL | GL_POLYGON_SMOOTH_HINT |  GL_MULTISAMPLE) ;
		glDisable (GL_BLEND);


	    glDisable (GL_LIGHTING);
		glColor3f(0.0,0.0,0.0);
		glEnable(GL_MULTISAMPLE) ;
//			glBegin(GL_LINES);
//	 			for(ListPoint3Iterator it = lBoundaries.begin();it != lBoundaries.end();++it)
//	 			{
//	 				glVertex3fv( it->ToRealPtr() );
//	 				glVertex3fv( this->mCenter.ToRealPtr());
//	 			}
//			glEnd();

		glBegin(GL_POINTS);
			glVertex3fv( this->mCenter.ToRealPtr());
		glEnd();

		glDisable(GL_MULTISAMPLE) ;
		glEnable (GL_LIGHTING);
		glPopMatrix();


}


}

#endif
