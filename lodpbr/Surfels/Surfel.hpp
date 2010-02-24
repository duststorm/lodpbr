#ifndef SURFEL_HPP_
#define SURFEL_HPP_

/**
 *
 * Author:  Felipe Carvalho - Ricardo Marroquim
 *
 * Data created: 08-01-2008
 *
 * TODO : Still Under Construction. Take care =)
 *
 **/

#include <vector>
#include <list>
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>

#include <wrap/io_trimesh/import_ply.h>
#include <wrap/io_trimesh/export_ply.h>
#include <wrap/io_trimesh/io_ply.h>
#include <wrap/ply/plylib.h>

#include "Math/Point3.hpp"
#include "Math/Vector3.hpp"
#include "Math/Color.hpp"
#include "Math/Math.hpp"
#include "Math/BoundingBox3.hpp"

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

	typedef std::vector<Point3>       				VectorPoint3;
	typedef typename VectorPoint3::iterator  		VectorPoint3Iterator;

	// Each vector of Ellisoid is a Ring define by the function GeneratRings;
	typedef std::vector<std::vector<Point3> >       Ellipsoid;
	typedef typename Ellipsoid::iterator 			EllipsoidIterator;

	typedef ::vcg::ply::PropDescriptor PropDescriptor ;

/* IO PLY */

	enum IO_SURFEL
	{
		IOM_SURFEL = 0x10002
	};

	enum STATE
	{
		UPDATED_ELLIPSOID = 0x0001,
		OUTDATED_ELLIPSOID = 0x0002
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
	 Real 						Curvature			( ) const;
	 Real						SetCurvature 		( const Real c);
	 void 						SetMinorAxis		( const std::pair<Real,Vector3>& pMinorAxis );
	 void 						SetMajorAxis		( const std::pair<Real,Vector3>& pMajorAxis );
	 std::pair<Real,Vector3> 	MinorAxis			(  ) const;
	 std::pair<Real,Vector3> 	MajorAxis			(  ) const;

	 Real 						MaxError 			(  ) const;
	 void 						SetMaxError			( const Real& pMaxError ) const;
	 Real 						MinError 			(  ) const;
   	 void 						SetMinError 		( const Real& pMinError ) const;
   	 Real PerpendicularError 						( ) const;
   	 void SetPerpendicularError						( const Real& pPerpendicularError ) ;
   	 Real TangencialError 							( ) const;
   	 void SetTangencialError 								( const Real& pGeometricError );

	 Real 						Similarity 			(  ) const;
	 void 						SetSimilarity 		( const Real& pSimilarity );

	 Real 						Area				(  ) const;

	 Vector3 					Perpendicular		( const Vector3& pVector );
	 ListPoint3 				BoundariesSamples	( unsigned int pSteps = 4,const Real& pRadius = 1.0 ) const;
	 Ellipsoid 		 			GenerateRing		( unsigned int pSteps = 4, const int pRings = 0 ,const Real& pRadius = 1.0,const Real& pHeight = 0.0) const;
	 // Draw Fuctions
	 void						DrawEllpsoid		( int lats = 10,int longs = 10 ,const Real& pRadius = 1.0,const Real& pHeight = 0.01 );
	 void						DrawBox				( const Real& pHeight = 0.01);
	 void 					    DrawCenter			( const GLfloat& size = 1.0 );
	 void 						Draw				( int p = 8 ,const Real& pRadius = 1.0 );
	 void 						DrawTriangleFan		( int p = 8 ,const Real& pRadius = 1.0 );

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
	  Real mTangencialError;

	  Real mCurvature;

	  /// An identification number for the surfel
	  unsigned int mID;

	  //Cluster building
	  bool mMarked;
	  bool mExpansionMarked;
	  bool mSeedMarked;

	  Real mSimilarity;

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
	 mSimilarity 		= 9999;
	 mClusterID = 0;
}

template<class Real>
Surfel<Real>::Surfel (const Surfel<Real>& pSurfel) :
										 mCenter		 	(pSurfel.mCenter),
  										 mNormal		 	(pSurfel.mNormal),
  									 	 mColor			 	(pSurfel.mColor),
  									 	 mSplatRadius	 	(pSurfel.mSplatRadius),
  										 mMinorAxis		 	(pSurfel.mMinorAxis),
  										 mMajorAxis		 	(pSurfel.mMajorAxis),
  		   								 mMaxError		 	(pSurfel.mMaxError),
  		   								 mMinError		 	(pSurfel.mMinError),
  		   								 mPerpendicularError(pSurfel.mPerpendicularError),
										 mTangencialError	(pSurfel.mTangencialError),
  										 mCurvature		 	(pSurfel.mCurvature),
  										 mID			 	(pSurfel.mID),
  										 mMarked		 	(pSurfel.mMarked),
  									     mExpansionMarked	(pSurfel.mExpansionMarked),
  									     mSeedMarked	 	(pSurfel.mSeedMarked),
  									     mSimilarity	 	(pSurfel.mSimilarity),
  										 mClusterID		 	(pSurfel.mClusterID)
{

};

template<class Real>
Surfel<Real>::Surfel (const Surfel<Real>* pSurfel) :
										 mCenter(pSurfel->mCenter),
  										 mNormal(pSurfel->mNormal),
  									 	 mColor(pSurfel->mColor),
  									 	 mSplatRadius(pSurfel->mSplatRadius),
  										 mMinorAxis(pSurfel->mMinorAxis),
  										 mMajorAxis(pSurfel->mMajorAxis),
  		   								 mMaxError(pSurfel->mMaxError),
  		   								 mMinError(pSurfel->mMinError),
  		  		   						 mPerpendicularError(pSurfel->mPerpendicularError),
  										 mTangencialError	(pSurfel->mTangencialError),
  										 mCurvature(pSurfel->mCurvature),
  										 mID(pSurfel->mID),
  										 mMarked(pSurfel->mMarked),
  									     mExpansionMarked(pSurfel->mExpansionMarked),
  									     mSeedMarked(pSurfel->mSeedMarked),
  									     mSimilarity(pSurfel->mSimilarity),
  										 mClusterID(pSurfel->mClusterID)
{

};

template<class Real>
Surfel<Real>::Surfel (const LoadPlySurfel& pSurfel) : mCenter(pSurfel.cx,pSurfel.cy,pSurfel.cz),
  										 mNormal(pSurfel.nx,pSurfel.ny,pSurfel.nz),
  									 	 mColor(pSurfel.r,pSurfel.g,pSurfel.b),
  									 	 mSplatRadius(0),
  		  								 mMinorAxis(std::pair<Real,Vector3>(pSurfel.minor_axis_size,
  		  								   		              Vector3(pSurfel.minor_axisx,
  		  										               		  pSurfel.minor_axisy,
  		  										               		  pSurfel.minor_axisz))),
  										 mMajorAxis(std::pair<Real,Vector3>(pSurfel.major_axis_size,
  												              Vector3(pSurfel.major_axisx,
  												            		  pSurfel.major_axisy,
  												            		  pSurfel.major_axisz))),
  										 mMaxError(pSurfel.max_error),
  										 mMinError(pSurfel.min_error),
  										 mCurvature(0),
  										 mID(0),
  										 mMarked(0),
  									     mExpansionMarked(0),
  									     mSeedMarked(0),
  									     mSimilarity(9999),
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
							   mSimilarity(9999),
							   mClusterID(0)
	  {
	 	mColor = Color(1.0,0.0,0.0);
		mMaxError = 0;
		mMinError = 0;
		mCurvature = 0;
		mSplatRadius = 0;
	  };

template<class Real>
Surfel<Real>::Surfel (const Point3& 	position,
		 const Vector3& normal,
		 const Real& 	radius,
		 unsigned int 	id,
		 const Real& 	pError ) : mCenter(position),
								   mNormal(normal),
								   mSplatRadius(radius),
								   mCurvature(pError),
								   mID(id),
								   mMarked(0),
								   mExpansionMarked(0),
								   mSeedMarked(0),
								   mSimilarity(9999),
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
		 						mCurvature(0),
		 						mID(id),
		 						mMarked(0),
								mExpansionMarked(0),
								mSeedMarked(0),
								mSimilarity(9999),
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
		 						mCurvature(0),
		 						mID(id),
		 						mMarked(0),
								mExpansionMarked(0),
								mSeedMarked(0),
								mSimilarity(9999),
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
	 this->mCenter    			= pSurfel.Center();
	 this->mNormal    			= pSurfel.Normal();
	 this->mMinorAxis 			= pSurfel.MinorAxis();
	 this->mMajorAxis 			= pSurfel.MajorAxis();
	 this->mMaxError 			= pSurfel.MaxError();
	 this->mMinError 			= pSurfel.MinError();
	 this->mCurvature			= pSurfel.Curvature();
	 this->mColor     			= pSurfel.ColorRGB();
	 this->mMarked    			= pSurfel.Marked();
	 this->mExpansionMarked 	= pSurfel.ExpansionMarked();
	 this->mSeedMarked			= pSurfel.SeedMarked();
	 this->mSimilarity			= pSurfel.Similarity();
	 this->mClusterID 			= pSurfel.ClusterID();
	 this->mPerpendicularError	= pSurfel.PerpendicularError();
	 this->mTangencialError		= pSurfel.TangencialError();
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
Real Surfel<Real>::Curvature () const
{
	 return ( this->mCurvature );
};

template<class Real>
Real Surfel<Real>::SetCurvature ( const Real c)
{
	 this->mCurvature = c;
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
Real Surfel<Real>::PerpendicularError () const
{
	 return ( this->mPerpendicularError );
};

template<class Real>
void Surfel<Real>::SetPerpendicularError (const Real& pPerpendicularError)
{
	 this->mPerpendicularError = pPerpendicularError;
};

template<class Real>
Real Surfel<Real>::TangencialError () const
{
	 return ( this->mTangencialError );
};

template<class Real>
void Surfel<Real>::SetTangencialError (const Real& pTangencialError)
{
	 this->mTangencialError = pTangencialError;
};

template<class Real>
void Surfel<Real>::SetSimilarity ( const Real& pSimilarity )
{
	 this->mSimilarity = pSimilarity;
}

template<class Real>
Real Surfel<Real>::Similarity ( ) const
{
	 return this->mSimilarity;
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
typename Surfel<Real>::ListPoint3 Surfel<Real>::BoundariesSamples
																(unsigned int pSteps,
																 const Real& pRadius) const
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
	 Point3  lRingDirection	= Point3();

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

	 ListPoint3Iterator it = lPoints.begin();

	 Point3 p1 =  (*(it++));
	 Point3 p2 =  (*(it++));
	 Point3 p3=  (*(it));

	 Vector3 v1 = p2 - p1;
	 Vector3 v2 = p3 - p1;

	 Vector3 v3 = ( v1 ^ v2 );

	 if ((v3 * mNormal) < 0.0)
		 lPoints.reverse();
	 return lPoints;

}
/**
 * Cria um Anel em volta do centro da elipse com relação as eixos principais
 *
 * @param pSteps  quantos segmentos tera o anel
 * @param pRadius Fator de scalar do anel
 * @param Ring	  Quantos aneis tera o elipsoid
 *
 **/
template<class Real>
typename Surfel<Real>::Ellipsoid 	Surfel<Real>::GenerateRing	(unsigned int pSteps,
														         const int    pRings,
														         const Real& pRadius,
														         const Real& pHeight) const
{

	 if (pSteps == 0)
	 {
		 pSteps = 4;
	 }

	 VectorPoint3			lPoints;
	 Ellipsoid				lEllipsoid;

	 Real lAlpha 			= 0.0;
	 Real lSinAlpha 		= 0.0;
	 Real lCosAlpha 		= 0.0;

	 Real lX 				= 0.0;
	 Real lY 				= 0.0;
	 Real lFactor 			= 0.0;

	 Real lCos				= 0.0;
	 Real lSin				= 0.0;
	 Vector3 lDirection     = Vector3();
	 Point3  lRingDirection	= Point3 ();

	 int lRings = (-pRings);
	 Real cosTeta = static_cast<Real>(1.0/pRings);
	 Real sinTeta = 0.0;

	 while(lRings <= (pRings))
	 {
		 lPoints.clear();
		 Real i = 0;
		 while (i < 360)
		 	 {

		 		 lAlpha = ( i / 180 ) * Celer::Math::kPi;
		 		 lSinAlpha =  sin( lAlpha );
		 		 lCosAlpha =  cos( lAlpha );

		 		 sinTeta = sqrt( 1.0 - (lRings*cosTeta) * (lRings*cosTeta) );

		 		 lX = pRadius * mMinorAxis.first * lCosAlpha;

		 		 lY = pRadius * mMajorAxis.first * lSinAlpha;

		 		 lFactor = sqrt( lX*lX + lY*lY );

		 		 lCos = lX / lFactor;
		 		 lSin = lY / lFactor;

		 		 lDirection = (mMinorAxis.second * lCos) + (mMajorAxis.second * lSin);

		 		 Real lHeight = mMinorAxis.first * pHeight;

		 		 lRingDirection = Point3( (mCenter + (mNormal * (lHeight*(lRings*cosTeta)))) );

		 		 lPoints.push_back( Point3( (lRingDirection + (lDirection * lFactor*sinTeta )) ) );

		 		 i = i + (360.0 / pSteps);


		 	 }
		 lRings = lRings + 1;
		 lEllipsoid.push_back(lPoints);
	 }

	 return lEllipsoid;

}

// ============================ Draw Functions ============================= //

template<class Real>
void Surfel<Real>::DrawEllpsoid	( int pSegments,int pRings ,const Real& pRadius ,const Real& pHeight)
{
	Celer::BoundingBox3<Real> BBox;

	Ellipsoid  lEllipsoid = GenerateRing(pSegments,pRings,pRadius,pHeight);

 	glPushMatrix();
 	glEnable (GL_BLEND);
 	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
////
    glColor4f(1.0,0.5,0.5,0.5);
 	glPointSize(1.0);
    glBegin(GL_LINES);
	for( unsigned int i = 0  ; i <  lEllipsoid.size()-1; i++)
	{
		for(unsigned int j = 0 ; j < lEllipsoid[i].size(); j++ )
		{
			glVertex3fv( lEllipsoid[i][j].ToRealPtr());
			glVertex3fv( lEllipsoid[i+1][j].ToRealPtr());

			glVertex3fv( lEllipsoid[i][(j)%lEllipsoid[i].size()].ToRealPtr());
			glVertex3fv( lEllipsoid[i][(j+1)%lEllipsoid[i].size()].ToRealPtr());

		}


	}
    glEnd();
    glColor4f(0.0,0.5,0.5,0.5);
 	glBegin (GL_QUADS);
	for( unsigned int i = 0  ; i <  lEllipsoid.size()-1; i++)
	{
		for(unsigned int j = 0 ; j < lEllipsoid[i].size(); j++ )
		{
			glVertex3fv( lEllipsoid[i][j].ToRealPtr());
			glVertex3fv( lEllipsoid[i+1][j].ToRealPtr());

			glVertex3fv( lEllipsoid[i+1][(j+1)%lEllipsoid[i].size()].ToRealPtr());
			glVertex3fv( lEllipsoid[i][(j+1)%lEllipsoid[i].size()].ToRealPtr());
		}
	}
	glEnd();
	glDisable (GL_BLEND);
	glPopMatrix();

	//DrawBox(pHeight);


}
template<class Real>
void Surfel<Real>::DrawBox				( const Real& pHeight  )
{

	VectorPoint3 lVertices;



	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(-mMinorAxis.first))
									   + (mMajorAxis.second*(-mMajorAxis.first))
									   + (mNormal		   *(-mMinorAxis.first*pHeight)) ))));

	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(-mMinorAxis.first))
									   + (mMajorAxis.second*(-mMajorAxis.first))
									   + (mNormal		   *(pHeight*mMinorAxis.first)) ))));

	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(-mMinorAxis.first))
									   + (mMajorAxis.second*(mMajorAxis.first))
									   + (mNormal		   *(pHeight*mMinorAxis.first)) ))));

	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(-mMinorAxis.first))
									   + (mMajorAxis.second*(mMajorAxis.first))
									   + (mNormal		   *(-mMinorAxis.first*pHeight)) ))));
	 // ops
	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(mMinorAxis.first))
									   + (mMajorAxis.second*(-mMajorAxis.first))
									   + (mNormal		   *(-mMinorAxis.first*pHeight)) ))));

	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(mMinorAxis.first))
									   + (mMajorAxis.second*(-mMajorAxis.first))
									   + (mNormal		   *(mMinorAxis.first*pHeight)) ))));

	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(mMinorAxis.first))
									   + (mMajorAxis.second*(mMajorAxis.first))
									   + (mNormal		   *(mMinorAxis.first*pHeight)) ))));

	 lVertices.push_back(	Point3 ( (mCenter +((mMinorAxis.second*(mMinorAxis.first))
									   + (mMajorAxis.second*(mMajorAxis.first))
									   + (mNormal		   *(-mMinorAxis.first*pHeight)) ))));


	glPushMatrix();
 	glEnable (GL_BLEND);
 	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 	glColor4f(1.0,0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glVertex3fv(lVertices[0]);
	glVertex3fv(lVertices[1]);
	glVertex3fv(lVertices[2]);
	glVertex3fv(lVertices[3]);

	glVertex3fv(lVertices[4]);
	glVertex3fv(lVertices[5]);
	glVertex3fv(lVertices[6]);
	glVertex3fv(lVertices[7]);

	glVertex3fv(lVertices[1]);
	glVertex3fv(lVertices[0]);
	glVertex3fv(lVertices[4]);
	glVertex3fv(lVertices[5]);

	glVertex3fv(lVertices[3]);
	glVertex3fv(lVertices[2]);
	glVertex3fv(lVertices[6]);
	glVertex3fv(lVertices[7]);

	glVertex3fv(lVertices[2]);
	glVertex3fv(lVertices[1]);
	glVertex3fv(lVertices[5]);
	glVertex3fv(lVertices[6]);

	glVertex3fv(lVertices[3]);
	glVertex3fv(lVertices[0]);
	glVertex3fv(lVertices[4]);
	glVertex3fv(lVertices[7]);

	glEnd();
	glDisable (GL_BLEND);
	glPopMatrix();

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
	 	//glPushMatrix();
	    //glEnable(GL_POLYGON_OFFSET_FILL | GL_POLYGON_SMOOTH_HINT | GL_MULTISAMPLE);
	    //glPolygonOffset(1,1);
	 	//glEnable (GL_BLEND);
	 	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	 	glPushMatrix();
//			glColor4f(1.0,1.0,1.0,0.5);
//			glBegin(GL_LINES);
//				glVertex3fv(mCenter);
//				glVertex3fv(mCenter+(mMajorAxis.second*mMajorAxis.first*pRadius));
//				glVertex3fv(mCenter);
//				glVertex3fv(mCenter+(mMinorAxis.second*mMinorAxis.first*pRadius));
//				glVertex3fv(mCenter);
//				glVertex3fv(mCenter+(mNormal*mMinorAxis.first*pRadius));
//			glEnd();
//		glPopMatrix();
	 	//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	 	//glColor4f(0.5f,0.5f,0.5f,1.0f);
	 	//glColor4f(1.0,0.35,0.0,0.75);
	 	glBegin (GL_TRIANGLE_FAN);
			for(ListPoint3Iterator it = lBoundaries.begin();it != lBoundaries.end();++it)
			{
				glVertex3fv( *it );
			}
		glEnd();
		//glPopMatrix();
}

}

#endif
