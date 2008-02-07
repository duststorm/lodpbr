#ifndef BOUNDINGBOX3_HPP_
#define BOUNDINGBOX3_HPP_

#include "Point3.hpp" 

namespace SLAL
{

template < class T> class BoundingBox3
{
private:
	
	Point3<T> min_;
	Point3<T> max_;
	
	inline const T& octMax(const T& a, const T& b) const
	{
	  return (a<b)? b:a;
	}

	inline const T& octMin (const T& a, const T& b) const 
	{
	  return (a<b)? a:b;
	}
	
    inline T distancePointToPoint( Point3<T>& q,  Point3<T>& p)
    {
        T a, b;
        a = (p[0] - q[0]);
        b = a * a;
        a = (p[1] - q[1]);
        b += a * a;
        a = (p[2] - q[2]);
        b += a * a;
        return sqrt( b );
    }
	
	
public:
	
	BoundingBox3 ( )
	{
		this->min_ = Point3<T> ();
		this->max_ = Point3<T> ();
	};
	
	BoundingBox3 ( const BoundingBox3<T>& box )
	{
		this->min_ = Point3<T> ( box.min() );
		this->max_ = Point3<T> ( box.max() );
	};
	
	BoundingBox3 ( const Point3<T>& pointMin, const Point3<T>& pointMax )
	{
		this->min_ = Point3<T> ( pointMin );
		this->max_ = Point3<T> ( pointMax );
	};
	
	BoundingBox3 ( const T& xMin, const T& yMin, const T& zMin,
				   const T& xMax, const T& yMax, const T& zMax )
	{
		this->min_ = Point3<T> ( xMin,yMin,zMin );
		this->max_ = Point3<T> ( xMax,yMax,zMax );
	};
	
	
	inline const T& xmin() const
	{
		return ( this->min_.x() );
	};
	
	inline const T& ymin() const
	{
		return ( this->min_.y() );
	};
	
	inline const T& zmin() const
	{
		return ( this->min_.z() );
	};
	
	inline const T& xmax() const
	{
		return ( this->max_.x() );
	};
	
	inline const T& ymax() const
	{
		return ( this->max_.y() );
	};
	
	inline const T& zmax() const
	{
		return ( this->max_.z() );
	};
	
	inline const Point3<T>& min() const
	{
		return ( this->min_);
	};
	
	inline const Point3<T>& max() const 
	{
		return ( this->max_ );
	};
	
	
	BoundingBox3<T> subOctant ( int sonIndex  )
	{
		
	    Point3<T> p = this->min_;
	    Point3<T> q = this->max_;
	    
	    double sonMin[3], sonMax[3];
	    double middle[3] = { (p[0] + q[0])*0.5, (p[1] + q[1])*0.5, (p[2] + q[2])*0.5};
	
	    int mult = 1;
	    
	    for (int i = 0; i < 3 ; i++){
	        if ((sonIndex & mult) == 0) {
	            sonMin[i] = p[i];
	            sonMax[i] = middle[i];
	        }
	        else {
	            sonMin[i] = middle[i];
	            sonMax[i] = q[i];
	        }
	        mult *= 2;
	    }
	    return BoundingBox3 (Point3<T>(sonMin[0], sonMin[1], sonMin[2]), 
	    					 Point3<T>(sonMax[0], sonMax[1], sonMax[2]) );

	};
	
	bool intersect (const Point3<T>& p) const 
	{
	    return ( ( p.x() >= this->xmin() ) and ( p.x() < this->xmax() ) and
	             ( p.y() >= this->ymin() ) and ( p.y() < this->ymax() ) and
	             ( p.z() >= this->zmin() ) and ( p.z() < this->zmax() )   );
	}
	
	
	bool intersect (const BoundingBox3<T>& box) const {
	  
	  Point3<T> Amin = this->min_;
	  Point3<T> Amax = this->max_;

	  Point3<T> Bmin = box.min();
	  Point3<T> Bmax = box.max(); 
	      
	  return (octMax (Amin.x(), Bmin.x()) < octMin(Amax.x(), Bmax.x()) and
	          octMax (Amin.y(), Bmin.y()) < octMin(Amax.y(), Bmax.y()) and
	          octMax (Amin.z(), Bmin.z()) < octMin(Amax.z(), Bmax.z())     );
	}
	
	T distance( Point3<T>& p) 
	{
	    T clsPt[3]; //closest point on the box's surface to the point p
	    for (int i = 0; i < 3; ++i)
	    {
	        if (p[i] < this->min()[i])
	            clsPt[i] = (this->min()[i]);
	        else if (p[i] > this->max()[i])
	            clsPt[i] = (this->max()[i]);
	        else
	            clsPt[i] = (p[i]);
	    }
	    Point3<T> cls(clsPt[0], clsPt[1], clsPt[2]);
 
	    
	    return distancePointToPoint( p, cls );
	}
	
	
	virtual ~BoundingBox3(){};
};

}

#endif /*BOUNDINGBOX3_HPP_*/
