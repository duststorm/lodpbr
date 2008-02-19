#ifndef BOUNDINGBOX3_HPP_
#define BOUNDINGBOX3_HPP_

#include "Point3.hpp" 

namespace SLAL
{

template < class Real> 
class BoundingBox3
{
private:
	
	Point3<Real> min_;
	Point3<Real> max_;
	
public:
	
	BoundingBox3 ( )
	{
		this->min_ = Point3<Real> ();
		this->max_ = Point3<Real> ();
	};
	
	BoundingBox3 ( const BoundingBox3<Real>& box )
	{
		this->min_ = Point3<Real> ( box.min() );
		this->max_ = Point3<Real> ( box.max() );
	};
	
	BoundingBox3 ( const Point3<Real>& pointMin, const Point3<Real>& pointMax )
	{
		this->min_ = Point3<Real> ( pointMin );
		this->max_ = Point3<Real> ( pointMax );
	};
	
	BoundingBox3 ( const Real& xMin, const Real& yMin, const Real& zMin,
				   const Real& xMax, const Real& yMax, const Real& zMax )
	{
		this->min_ = Point3<Real> ( xMin,yMin,zMin );
		this->max_ = Point3<Real> ( xMax,yMax,zMax );
	};
	
	
	inline const Real& xmin() const
	{
		return ( this->min_.x() );
	};
	
	inline const Real& ymin() const
	{
		return ( this->min_.y() );
	};
	
	inline const Real& zmin() const
	{
		return ( this->min_.z() );
	};
	
	inline const Real& xmax() const
	{
		return ( this->max_.x() );
	};
	
	inline const Real& ymax() const
	{
		return ( this->max_.y() );
	};
	
	inline const Real& zmax() const
	{
		return ( this->max_.z() );
	};
	
	inline const Point3<Real>& min() const
	{
		return ( this->min_);
	};
	
	inline const Point3<Real>& max() const 
	{
		
		return ( this->max_ );
	};
	
	
	inline bool operator==(const BoundingBox3<Real>& box) const
	{
	  return ( xmin() == box.xmin() and xmax() == box.xmax() and
	      	   ymin() == box.ymin() and ymax() == box.ymax() and
	           zmin() == box.zmin() and zmax() == box.zmax() );
	};
	
	inline bool operator!=(const BoundingBox3<Real>& box) const
	{
	  return  ! (box == *this);
	};
	
	inline BoundingBox3<Real>& operator= (const BoundingBox3<Real>& box)
	{
		this->min_ = box.min();
		this->max_ = box.max();
				
		return ( *this );
	};
	
	inline BoundingBox3<Real> operator+(const BoundingBox3<Real>& box) const
	{
	  return BoundingBox3<Real>((std::min)(xmin(), box.xmin()),
	                	  		(std::min)(ymin(), box.ymin()),
	                	  		(std::min)(zmin(), box.zmin()),
	                	  		(std::max)(xmax(), box.xmax()),
	                	  		(std::max)(ymax(), box.ymax()),
	                	  		(std::max)(zmax(), box.zmax()));	
	};	
	

	bool intersect (const Point3<Real>& p) const 
	{
	    return ( ( p.x() >= this->xmin() ) and ( p.x() < this->xmax() ) and
	             ( p.y() >= this->ymin() ) and ( p.y() < this->ymax() ) and
	             ( p.z() >= this->zmin() ) and ( p.z() < this->zmax() )   );
	}
	
	

	virtual ~BoundingBox3(){};
};

}

#endif /*BOUNDINGBOX3_HPP_*/
