#ifndef MERGEELLIPSE_HPP_
#define MERGEELLIPSE_HPP_


#include <list>
#include <algorithm>
#include <cassert>

#include "surfel.hpp"

#include "slal/Point3.hpp"
#include "slal/Vector3.hpp"
#include "slal/EigenSystem.hpp"


template <class Real> class MergeEllipses
{
public:
	
	typedef CGL::Point3<Real>    				Point3; 
	typedef CGL::Vector3<Real>   				Vector3;
	typedef CGL::Matrix3x3<Real> 				Matrix3x3;
	
	typedef CGL::Point3<Real>*					PtrPoint3;
	typedef std::list<Point3>					ListPoint3;
	typedef std::list<Point3* >       			ListPtrPoint3;
	typedef typename ListPtrPoint3::iterator   	ListPtrPoint3Iterator;
	
	typedef Surfel<Real>						  Surfel;
	typedef Surfel*								  PtrSurfel;
	typedef std::list<Surfel> 					  SurfelContainer;
	typedef std::list<PtrSurfel>				  PtrSurfelContainer;
	typedef typename SurfelContainer::iterator 	  SurfelIterator;
	typedef typename PtrSurfelContainer::iterator PtrSurfelIterator;
		
	MergeEllipses( const MergeEllipses<Real>& mMerge)
	{
		mEllipses 		= mMerge.mEllipses;

		mNewCenter 		= mMerge.mNewCenter;

		mNewNormal 		= mMerge.mNewNormal;

		mNewMinorAxis 	= mMerge.mNewMinorAxis;

		mNewMajorAxis 	= mMerge.mNewMajorAxis;

		mNewMinorValue 	= mMerge.mNewMinorValue;

		mNewMajorValue 	= mMerge.mNewMajorValue;
	}
	
	MergeEllipses( const PtrSurfelContainer& pEllipses , const Point3& pNewCenter , const Vector3& pNewNormal)
	: mEllipses(pEllipses)
	{
		mNewCenter = pNewCenter;
		mNewNormal = pNewNormal;
	};
	
	MergeEllipses( const PtrSurfelContainer& pEllipses )
	: mEllipses(pEllipses) 
	{
		
		NewCenterAndNormal();
		ProjectPoints();
		NewAxis();
					
	};
		
	Surfel NewSurfel()
	{
		return ( Surfel(mNewCenter,mNewNormal,mNewMinorAxis,mNewMajorAxis,1) );
	}
	
	Surfel * NewPtrSurfel()
	{

		return ( new Surfel(mNewCenter,mNewNormal,mNewMinorAxis,mNewMajorAxis,1) );
	}
	
	// functions
	void NewCenterAndNormal ()
	{
		Point3  lSomaCenterAreas;
		Vector3 lSomaNormalAreas;
		Real    lSomaAreas = 0.0;
		
			
		for (PtrSurfelIterator itEllipse = mEllipses.begin(); itEllipse != mEllipses.end(); ++itEllipse)
		{
			lSomaCenterAreas += (*itEllipse)->Area() * (*itEllipse)->Center();
			lSomaNormalAreas += (*itEllipse)->Area() * (*itEllipse)->Normal();
			lSomaAreas       += (*itEllipse)->Area();
			
		}
		
		if (lSomaAreas != 0)
		{
			mNewCenter = lSomaCenterAreas / lSomaAreas;
			mNewNormal = lSomaNormalAreas / lSomaAreas;
			mNewNormal.normalize();
		}
	};

	void ProjectPoints()
	{


		ListPtrPoint3 		lPoints;
		ListPtrPoint3 		lBoundariesPoints;
		PtrPoint3 			lPoint;


		for (PtrSurfelIterator itEllipse = mEllipses.begin(); itEllipse != mEllipses.end(); ++itEllipse)
		{
			lBoundariesPoints = (*itEllipse)->BoundariesSamples(8);

			for(ListPtrPoint3Iterator it = lBoundariesPoints.begin();it != lBoundariesPoints.end();++it)
			{

				lPoint = ProjectPointToPlane(mNewNormal,mNewCenter,(*(*it)) );
				lPoints.push_back ( lPoint );

			}

			lBoundariesPoints.clear();
		}

		mProjectedPoint.clear();
		mProjectedPoint = lPoints;
	}


	void NewAxis()
	{

		CGL::EigenSystem<Real> lEigen(mProjectedPoint,mNewCenter);

		mNewMinorAxis = lEigen.MinorAxis();
		mNewMajorAxis = lEigen.MajorAxis();

		mNewMinorAxis.second.normalize();
		mNewMajorAxis.second.normalize();

		Matrix3x3 m = Matrix3x3 (mNewMinorAxis.second,mNewMajorAxis.second,mNewNormal);
		std::list<Real> lFactors;
		Real lFactor = 0.0;

		Point3 lCenter = m*mNewCenter;
		Point3 lPoint;

		for(ListPtrPoint3Iterator it = mProjectedPoint.begin();it != mProjectedPoint.end();++it)
		{
			lPoint = m*(*(*it));

			lFactor = ( ( ( lPoint.x() - lCenter.x() ) * (lPoint.x() - lCenter.x() ) ) / (mNewMinorAxis.first) + 
						( ( lPoint.y() - lCenter.y() ) * (lPoint.y() - lCenter.y() ) ) / (mNewMajorAxis.first) );

			lFactors.push_back(lFactor);

		}

		typename std::list<Real>::const_iterator lD = std::max_element(lFactors.begin(),lFactors.end());

		mNewMinorValue = std::sqrt ( *lD / mNewMinorAxis.first );
		mNewMajorValue = std::sqrt ( *lD / mNewMajorAxis.first );

		mNewMinorAxis.first *= mNewMinorValue;
		mNewMajorAxis.first *= mNewMajorValue;
	}

	Point3 Mean (const std::list<Point3* >& pPoint3List)
	{

		Real lMean;

		for(ListPtrPoint3Iterator it = pPoint3List.begin();it != pPoint3List.end();++it)
		{
			lMean += (*(*it));
		}

		lMean /= pPoint3List.size();  

		return ( lMean );

	}

	Point3 * ProjectPointToPlane(const Vector3& pNormal,const Point3& pCenter,const Point3& pPoint) const
	{

		return  (new Point3 (  pPoint - ( (  (pPoint - pCenter) * pNormal  ) * pNormal)  ));
	}	

	 const Point3 Center () const 
	 { 
		 return  ( this->mNewCenter ) ; 
	 };
	 
	 const Vector3 Normal() const 
	 { 
		 return (this->mNewNormal); 
	 };
	 
	 std::pair<Real,Vector3> MinorAxis() const
	 {
		 return (this->mNewMinorAxis); 
	 }

	 std::pair<Real,Vector3> MajorAxis() const
	 {
		 return (this->mNewMajorAxis); 
	 }
	
	virtual ~MergeEllipses(){};
	std::list<Point3* > 		mProjectedPoint;
	
private:
	
	// Lista de Ellipses a sofrem "merge"
	PtrSurfelContainer 			mEllipses;

	Point3	 					mNewCenter;
	
	Vector3 					mNewNormal;
	
	std::pair<Real,Vector3> 	mNewMinorAxis;
	
	std::pair<Real,Vector3> 	mNewMajorAxis;
	
	Real 						mNewMinorValue;
	
	Real 						mNewMajorValue;
		

};

#endif /*MERGEELLIPSE_HPP_*/