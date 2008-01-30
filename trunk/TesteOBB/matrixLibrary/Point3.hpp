#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <iostream>

#include "Vector3.hpp"

namespace SLAL
{

template <class T>	class Point3
{
	
	
private:
	
	T x_;
	T y_;
	T z_;
	
public:
	
	 
	Point3()
	{
		this->x_ = (T)0;
		this->y_ = (T)0;
		this->z_ = (T)0;
	};
	
	Point3 ( const T& x, const T& y, const T& z )
	{
		this->x_ = x;
		this->y_ = y;
		this->z_ = z;
	};
	
	Point3 ( const Vector3<T>& u)
	{
		this->x_ = u.x();
		this->y_ = u.y();
		this->z_ = u.z();
	};
	
	Point3 ( const Point3<T>& p)
	{
		this->x_ = p.x();
		this->y_ = p.y();
		this->z_ = p.z();
	};
	
	inline const T& x() const
	{
		return ( this->x_ );
	};
	
	inline const T& y() const
	{
		return ( this->y_ );
	};
	
	inline const T& z() const
	{
		return ( this->z_ );
	};
	
	inline const T& operator [] ( int i)  
	{
		if ( (i > 2) or ( i < 0))
		{
			std::cerr << "[ERROR] Point3 operator[]"        << std::endl
				      << "        Out of the Point size. " << std::endl
				      << "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}
				
	    if (i == 0)
	    	return (this->x_);
	    if (i == 1)
	    	return (this->y_);
	    return (this->z_);
	};
	
	inline Point3<T>& operator= ( const Point3<T>& p)
	{
		this->x_ = p.x();
		this->y_ = p.y();
		this->z_ = p.z();
			
		return ( *this );
	};
	
	friend inline bool operator== ( const Point3<T>& p,const Point3<T>& q) 
	{
		return ( (p.x() == q.x()) and (p.y() == q.y()) and (p.z() == q.z()) );
	};	
	
	friend inline bool operator!= ( const Point3<T>& p, const Point3<T>& q)
	{
		return  !(p == q) ;
	};	
	
	inline Point3<T>  operator- ( ) const
	{
		Point3<T> r = Point3 (-this->x_, -this->y_, -this->z_);
			
		return ( r );
	};
	
	inline friend const Vector3<T> operator- (const Point3<T>& p, const Point3<T>& q)  
	{
		Vector3<T> w = Vector3<T>( p.x() - q.x(),
								   p.y() - q.y(),
								   p.z() - q.z());
		
		return ( w );
	};
	
	inline friend const Point3<T> operator- (const Point3<T>& p, const Vector3<T> u)  
	{
		Point3<T> r = Point3( p.x() - u.x(),
							  p.y() - u.y(),
							  p.z() - u.z() );
		
	    return ( r );
	};
	
	inline friend const Point3<T> operator- (const Vector3<T> u,const Point3<T> p )  
	{
		
		Point3<T> r = Point3( u.x() - p.x(),
							  u.y() - p.y(),
							  u.z() - p.z() );
		
	    return ( r );
	};
	
	inline Point3<T>  operator+ ( ) const
	{
		return ( *this );
	};
	
	inline friend const Point3<T> operator+ (const Point3<T> p, const Vector3<T> u)  
	{
		Point3<T> r = Point3 ( p.x() + u.x(),
				 			   p.y() + u.y(),
				 			   p.z() + u.z() );

	    return ( r );
	};
	
	inline friend  const Point3<T> operator+ (const Vector3<T> u,const Point3<T> p )  
	{
		Point3<T> r = Point3 ( p.x() + u.x(),
				 			   p.y() + u.y(),
				 			   p.z() + u.z() );

	    return ( r );
	};
		
	
	friend inline std::ostream& operator<< (std::ostream & s, const Point3<T>& p)
	{
		s << "Point3" << " x = " << p.x() << " ,y = " << p.y() << " ,z = " << p.z() << std::endl;
		
		
		return ( s );
	};
	
	virtual ~Point3(){};
	
};

} /* SLAL :: NAMESPACE */

#endif /*POINT3_HPP_*/
