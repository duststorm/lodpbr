#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <iostream>
#include <map>

#include <cmath>

#include "Vector3.hpp"

namespace SLAL
{

template <class T>	class Point3
{
	
private:
	
	union
	{
	
		struct
		{
			T x_;
			T y_;
			T z_;
		};
		
		T xyz[3];
		
	};
	
	union
	{
		struct
		{	
			T r_;
			T g_;
			T b_;
		};
		
		T rgb[3];
	};
	
	
public:
	
	friend class Vector3<T>;
	 
	Point3()
	{
		this->x_ = static_cast< T > (0);
		this->y_ = static_cast< T > (0);
		this->z_ = static_cast< T > (0);
		
		this->r_ = static_cast< T > (0);
		this->g_ = static_cast< T > (0);
		this->b_ = static_cast< T > (0);
	};
	
	Point3 ( const T& x, const T& y, const T& z )
	{
		this->x_ = x;
		this->y_ = y;
		this->z_ = z;
	};
	
	template < typename P >
	Point3 (const P* p)
	{
		assert(p);
		
    	this->x_ = static_cast< T > ( p[0] );
    	this->y_ = static_cast< T > ( p[1] );
    	this->z_ = static_cast< T > ( p[2] );
    	
	};
	
	Point3 ( const Vector3<T>& u)
	{
		this->x_ = u.x_;
		this->y_ = u.y_;
		this->z_ = u.z_;
	};
	
	Point3 ( const Point3<T>& p)
	{
		this->x_ = p.x();
		this->y_ = p.y();
		this->z_ = p.z();
	};
	
	template < typename C >
	inline void setRGB ( const C* c)
	{
    	this->r_ = static_cast< T > ( c[0] );
    	this->g_ = static_cast< T > ( c[1] );
    	this->b_ = static_cast< T > ( c[2] );
	};	
	
	inline void setRGB ( const T& r, const T& g, const T& b)
	{
		this->r_ = r;
		this->g_ = g;
		this->b_ = b;
	};
	
	inline void setR ( const T& r)
	{
		this->r_ = r;
	};
	
	inline void setG ( const T& g)
	{
		this->g_ = g;
	};
	
	inline void setB ( const T& b)
	{
		this->b_ = b;
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
	
	inline const T& r() const
	{
		return ( this->r_ );
	};
	
	inline const T& g() const
	{
		return ( this->g_ );
	};
	
	inline const T& b() const
	{
		return ( this->b_ );
	};

	inline  T operator [] ( int i)  const
	{
		if ( (i > 2) or ( i < 0))
		{
			std::cerr << "[ERROR] Point3 operator[]"        << std::endl
				      << "        Out of the Point size. " << std::endl
				      << "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}
		
	    return (xyz[i]);
	};
	
	inline  T operator [] ( int i)  

	{
		if ( (i > 2) or ( i < 0))
		{
			std::cerr << "[ERROR] Point3 operator[]"        << std::endl
				      << "        Out of the Point size. " << std::endl
				      << "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}
		  
	    return (xyz[i]);
	};
	
	inline Point3<T>& operator= ( const Point3<T>& p)
	{
		this->x_ = p.x();
		this->y_ = p.y();
		this->z_ = p.z();
			
		return ( *this );
	};
	
	
	// Assignment Opertators
	//With Scalar

	const Point3< T >& operator+= ( const T&  factor ) 
	{ 
	    this->x_ += factor; 
	    this->y_ += factor; 
	    this->z_ += factor;
	    
	    return ( *this ); 
	} 
	
	const Point3< T >& operator-= ( const T&  factor ) 
	{ 
	    this->x_ -= factor; 
	    this->y_ -= factor; 
	    this->z_ -= factor;
	    
	    return ( *this ); 
	} 
	
	const Point3< T >& operator*= ( const T& factor ) 
	{ 
	 	 	
	 	this->x_  *= factor;
	 	this->y_  *= factor;
	 	this->z_  *= factor;
						
	    return ( *this ); 
	}

	const Point3< T >& operator/= ( T factor ) 
	{ 
	    factor = (T)1 / factor;
	    
	    this->x_ *= factor;
	    this->y_ *= factor; 
	    this->z_ *= factor;
	    
	    return ( *this ); 
	}
	// With Vector
	const Point3< T >& operator+= (  const Point3<T>& u ) 
	{ 
	    this->x_ += u.x(); 
	    this->y_ += u.y(); 
	    this->z_ += u.z();
	    
	    return ( *this ); 
	}
	
	const Point3< T >& operator-= (  const Point3<T>& u ) 
	{ 
	    this->x_ -= u.x(); 
	    this->y_ -= u.y(); 
	    this->z_ -= u.z();
	    
	    return ( *this ); 
	} 


	const Point3< T >& operator/=( const Point3<T>& u ) 
	{ 
	    	    
	    this->x_ /= u.x();
	    this->y_ /= u.y(); 
	    this->z_ /= u.z();
	    
	    return ( *this ); 
	}
	
	
	inline bool operator== ( const Point3<T>& p) const
	{
		return ( ( this->x_ == p.x() ) and ( this->y_ == p.y() ) and ( this->z_ == p.z() ) );
	};	
	
	inline bool operator!= ( const Point3<T>& p) const
	{
		return  !(*this == p) ;
	};	
	
	inline Point3<T>  operator- ( ) const
	{
		
		return ( Point3 (-this->x_, -this->y_, -this->z_) );
			
	};
	
	inline friend const Vector3<T> operator- (const Point3<T>& p, const Point3<T>& q)  
	{
		return ( Vector3<T>( p.x_ - q.x_,
							 p.y_ - q.y_,
							 p.z_ - q.z_)
			    );
		
	};
	
	inline friend const Point3<T> operator- (const Point3<T>& p, const Vector3<T> u)  
	{
		return ( Point3<T>( p.x_ - u.x_,
						  	p.y_ - u.y_,
				  	  	    p.z_ - u.z_ )
			   );
	};
	
	inline friend const Point3<T> operator- (const Vector3<T> u,const Point3<T> p )  
	{
		
		return ( Point3<T>( u.x_ - p.x_,
							u.y_ - p.y_,
							u.z_ - p.z_ )
			    );
		    
	};
	
	inline Point3<T>  operator+ ( ) const
	{
		return ( *this );
	};
	
	inline friend const Point3<T> operator+ (const Point3<T> p, const Vector3<T> u)  
	{
		return ( Point3 ( p.x_ + u.x_,
				     	  p.y_ + u.y_,
				 		  p.z_ + u.z_ )
			    );
		
	};
	
	inline friend  const Point3<T> operator+ (const Vector3<T> u,const Point3<T> p )  
	{
		return ( Point3 ( p.x_ + u.x_,
					      p.y_ + u.y_,
				 		  p.z_ + u.z_ )
			    );
	    
	};
		
	
	friend inline std::ostream& operator<< (std::ostream & s, const Point3<T>& p)
	{
		s << "Point3" << " x = " << p.x() << " ,y = " << p.y() << " ,z = " << p.z() << std::endl;
		
		
		return ( s );
	};
	
	double squaredDistance ( const Point3<T> p ) const 
	{
	    return ( pow ( p.x() - this->x_, 2) + 
	    		 pow ( p.y() - this->y_, 2) + 
	    		 pow ( p.z() - this->z_, 2) );
	}
		
	virtual ~Point3(){};
	
};

} /* SLAL :: NAMESPACE */

#endif /*POINT3_HPP_*/
