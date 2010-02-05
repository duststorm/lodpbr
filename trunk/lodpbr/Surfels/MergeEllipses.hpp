#ifndef MERGEELLIPSE_HPP_
#define MERGEELLIPSE_HPP_


#include <list>
#include <algorithm>
#include <cassert>

#include "Surfel.hpp"

#include "Math/Point3.hpp"
#include "Math/Vector3.hpp"
#include "Math/EigenSystem.hpp"


template <class Real> class MergeEllipses
{
public:

	typedef Celer::Point3<Real>    					Point3;
	typedef Celer::Vector3<Real>   					Vector3;
	typedef Celer::Matrix3x3<Real> 					Matrix3x3;


	typedef std::list<Point3>						ListPoint3;
	typedef typename ListPoint3::iterator   		ListPoint3Iterator;

	typedef Celer::Surfel<Real>   				  	Surfel;
	typedef std::list<Surfel>				  		SurfelList;
	typedef typename SurfelList::iterator 			SurfelListIterator;

	MergeEllipses( )
	{}

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

	MergeEllipses( const SurfelList& pEllipses , const Point3& pNewCenter , const Vector3& pNewNormal)
	: mEllipses(pEllipses)
	{
		mNewCenter = pNewCenter;
		mNewNormal = pNewNormal;
	};

	MergeEllipses( const SurfelList& pEllipses )
	: mEllipses(pEllipses)
	{

		NewCenterAndNormal();
		ProjectPoints();
		NewAxis();


	};

	Surfel NewSurfel()
	{
		Surfel s = Surfel(mNewCenter,mNewNormal,mNewMinorAxis,mNewMajorAxis,1);
		s.SetPerpendicularError(mNewPerpendicularError);
		return ( s );
	}

	Surfel*  NewPtrSurfel()
	{
		Surfel* s = new Surfel(mNewCenter,mNewNormal,mNewMinorAxis,mNewMajorAxis,1);
		s.SetPerpendicularError(mNewPerpendicularError);
		return (s );
	}

	void PerpendicularError()
	{
		Real factor   = 0.0;
		Real alfa	  = 0.0;
		Real beta 	  = 0.0;
	    Real maxError = 0.0;
	    Real error 	  = 0.0;
		Vector3 ray;
		for (SurfelListIterator itEllipse = mEllipses.begin(); itEllipse != mEllipses.end(); ++itEllipse)
		{
			if(  std::fabs((mNewNormal* itEllipse->MajorAxis.second)) > 1e-6f )
			{
				factor = ((mNewNormal*itEllipse->MajorAxis.second)* itEllipse->MajorAxis.first) / ((mNewNormal*itEllipse->MinorAxis.second)* itEllipse->MinorAxis.first);
				alfa = std::sqrt(1.0/(1.0+factor*factor));
                beta = factor*alfa;
		        ray = (itEllipse->MajorAxis.second*(alfa*itEllipse->MajorAxis.first)) + (itEllipse->MinorAxis.second*(beta*itEllipse->MinorAxis.first));

			}else
			{
				ray = itEllipse->MinorAxis.second;
			}

            error = std::fabs( (itEllipse->Center()-mNewCenter) * mNewNormal ) + std::fabs( ray* mNewNormal );

            if (error > maxError )
            {
                maxError = error;
            }

		}
		mNewPerpendicularError = maxError;
	}

	// functions
	void NewCenterAndNormal ()
	{
		Point3  lSomaCenterAreas;
		Vector3 lSomaNormalAreas;
		Real    lSomaAreas = 0.0;


		for (SurfelListIterator itEllipse = mEllipses.begin(); itEllipse != mEllipses.end(); ++itEllipse)
		{
			lSomaCenterAreas += itEllipse->Area() * itEllipse->Center();
			lSomaNormalAreas += itEllipse->Area() * itEllipse->Normal();
			lSomaAreas       += itEllipse->Area();

		}

		if (lSomaAreas != 0)
		{
			mNewCenter = lSomaCenterAreas / lSomaAreas;
			mNewNormal = lSomaNormalAreas / lSomaAreas;
			mNewNormal.Normalize();
		}
	};

	void ProjectPoints()
	{


		ListPoint3 	lPoints;
		ListPoint3 	lBoundariesPoints;
		Point3 		lPoint;

		for (SurfelListIterator itEllipse = mEllipses.begin(); itEllipse != mEllipses.end(); ++itEllipse)
		{
			lBoundariesPoints = itEllipse->BoundariesSamples(8);

			for(ListPoint3Iterator it = lBoundariesPoints.begin();it != lBoundariesPoints.end();++it)
			{

				lPoint = ProjectPointToPlane(mNewNormal,mNewCenter,(*it) );
				lPoints.push_back ( lPoint );

			}

			lBoundariesPoints.clear();
		}

		mProjectedPoint.clear();
		mProjectedPoint = lPoints;
	}

	void NewAxis()
	{

		Celer::EigenSystem<Real> lEigen(mProjectedPoint,mNewCenter);

		mNewMinorAxis = lEigen.MinorAxis();
		mNewMajorAxis = lEigen.MajorAxis();

		mNewMinorAxis.second.Normalize();
		mNewMajorAxis.second.Normalize();

		Matrix3x3 m = Matrix3x3 (mNewMinorAxis.second,mNewMajorAxis.second,mNewNormal);
		std::list<Real> lFactors;
		Real lFactor = 0.0;

		Point3 lCenter = m*mNewCenter;
		Point3 lPoint;

		for(ListPoint3Iterator it = mProjectedPoint.begin();it != mProjectedPoint.end();++it)
		{
			lPoint = m*(*it);

			lFactor = ( ( ( lPoint.x - lCenter.x ) * (lPoint.x - lCenter.x ) ) / (mNewMinorAxis.first) +
						( ( lPoint.y - lCenter.y ) * (lPoint.y - lCenter.y ) ) / (mNewMajorAxis.first) );

			lFactors.push_back(lFactor);

		}

		typename std::list<Real>::const_iterator lD = std::max_element(lFactors.begin(),lFactors.end());

		mNewMinorValue = std::sqrt ( *lD / mNewMinorAxis.first );
		mNewMajorValue = std::sqrt ( *lD / mNewMajorAxis.first );

		mNewMinorAxis.first *= mNewMinorValue;
		mNewMajorAxis.first *= mNewMajorValue;



	}

	Point3 Mean (const ListPoint3& pPoint3List)
	{

		Point3 lMean;

		for(ListPoint3Iterator it = pPoint3List.begin();it != pPoint3List.end();++it)
		{
			lMean += (*it);
		}

		lMean /= pPoint3List.size();

		return ( lMean );

	}

	Point3  ProjectPointToPlane(const Vector3& pNormal,const Point3& pCenter,const Point3& pPoint) const
	{

		return  ( Point3 (  pPoint - ( (  (pPoint - pCenter) * pNormal  ) * pNormal)  ));
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

	// Pontos Projetados no plano to novo splat
	ListPoint3		mProjectedPoint;

private:

	// Lista de Ellipses a sofrem "merge"
	SurfelList					mEllipses;

	Point3	 					mNewCenter;

	Vector3 					mNewNormal;

	std::pair<Real,Vector3> 	mNewMinorAxis;

	std::pair<Real,Vector3> 	mNewMajorAxis;

	Real 						mNewMinorValue;

	Real 						mNewMajorValue;

	Real 						mNewPerpendicularError;


};

#endif /*MERGEELLIPSE_HPP_*/