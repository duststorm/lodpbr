#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <iostream>

#include "Vector3.hpp"

namespace SLAL
{

template <class T>	class Point3
{
	
	
private:
	
	T x;
	T y;
	T z;
	
public:
	
	friend class Vector3;
	
	Point3()
	{
		this->x = (T)0;
		this->y = (T)0;
		this->z = (T)0;
	};
	
	Point3 ( const T& x, const T& y, const T& z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};
	
	Point3 ( const Vector3<T>& u)
	{
		this->x = u.x();
		this->y = u.y();
		this->z = u.z();
	};
	
	Point3 ( const Point3<T>& p)
	{
		this->x = p.x();
		this->y = p.y();
		this->z = p.z();
	};
	
	inline const Point3 x() const
	{
		return ( this->x );
	}
	
	inline const Point3 y() const
	{
		return ( this->y );
	}
	
	inline const Point3 z() const
	{
		return ( this->z );
	}
	
	inline Point3<T>& operator= ( const Point3<T>& p)
	{
		this->x = p.x();
		this->y = p.y();
		this->z = p.z();
			
		return ( *this );
	};
	
	friend inline bool operator== ( const Point3<T>& p,const Point3<T>& q) const
	{
		return ( (p.x == q.x) and (p.y == q.y) and (p.z == q.z) );
	};	
	
	friend inline bool operator!= ( const Point3<T>& p, const Point3<T>& q)
	{
		return  !(p == q) ;
	};	
	
	inline Point3<T>  operator- ( ) const
	{
		Point3<T> r;
		 	
		r.x = -this->x; 
		r.y = -this->y;
		r.z = -this->z;
			
		return ( r );
	};
	
	inline friend const Vector3 operator- (const Point3& p, const Point3& q) 
	{
		Vector3<T> w;
		
		w.x = p.x - q.x;
		w.y = p.y - q.y;
		w.z = p.z - q.z;
		
		return ( w );
	};
	
	inline friend const Point3 operator- (const Point p, const Vector u) 
	{
		Point3 r;
		
		r.x = p.x - u.x;
		r.y = p.y - u.y;
		r.z = p.z - u.z;
		
	    return ( r );
	};
	
	inline friend const Point3 operator- (const Vector u,const Point p ) {
		Point3 r;
		
		r.x = u.x - p.x;
		r.y = u.y - p.y;
		r.z = u.z - p.z;
		
	    return ( r );
	};
	
	inline Point3<T>  operator+ ( ) const
	{
		return ( *this );
	};
	
	inline friend const Point3 operator+ (const Point p, const Vector u) 
	{
		Point3 r;
		
		r.x = p.x + u.x;
		r.y = p.y + u.y;
		r.z = p.z + u.z;
		
	    return ( r );
	};
	
	inline friend const Point operator+ (const Vector u,const Point p ) 
	{
		Point3 r;
		
		r.x = p.x + u.x;
		r.y = p.y + u.y;
		r.z = p.z + u.z;
		
	    return ( r );
	};
		
	
	friend inline std::ostream& operator<< (std::ostream & s, const Point3<T>& p)
	{
		s << "Point3" << " x = " << p.x << " ,y = " << p.y << " ,z = " << p.z << std::endl;
		
		return s;
	};
	
	virtual ~Point3(){};
	
};

} /* SLAL :: NAMESPACE */

#endif /*POINT3_HPP_*/
