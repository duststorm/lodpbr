#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <iostream>
#include <map>

#include <cmath>

#include "Vector3.hpp"

namespace SLAL
{

template <class Real>	class Point3
{

private:
	
	union
	{
	
		struct
		{
			Real x_;
			Real y_;
			Real z_;
		};
		
		Real xyz[3];
		
	};
	
	union
	{
		struct
		{	
			Real r_;
			Real g_;
			Real b_;
		};
		
		Real rgb[3];
	};
	
	
public:
	
	friend class Vector3<Real>;
	 
	Point3()
	{
		this->x_ = static_cast< Real > (0);
		this->y_ = static_cast< Real > (0);
		this->z_ = static_cast< Real > (0);
		
		this->r_ = static_cast< Real > (0);
		this->g_ = static_cast< Real > (0);
		this->b_ = static_cast< Real > (0);
	};
	
	Point3 ( const Real& x, const Real& y, const Real& z )
	{
		this->x_ = x;
		this->y_ = y;
		this->z_ = z;
	};
	
	template < typename P >
	Point3 (const P* p)
	{
		assert(p);
		
    	this->x_ = static_cast< Real > ( p[0] );
    	this->y_ = static_cast< Real > ( p[1] );
    	this->z_ = static_cast< Real > ( p[2] );
    	
	};
	
	Point3 ( const Vector3<Real>& u)
	{
		this->x_ = u.x_;
		this->y_ = u.y_;
		this->z_ = u.z_;
	};
	
	Point3 ( const Point3<Real>& p)
	{
		this->x_ = p.x();
		this->y_ = p.y();
		this->z_ = p.z();
	};
	
	template < typename C >
	inline void setRGB ( const C* c)
	{
    	this->r_ = static_cast< Real > ( c[0] );
    	this->g_ = static_cast< Real > ( c[1] );
    	this->b_ = static_cast< Real > ( c[2] );
	};	
	
	inline void setRGB ( const Real& r, const Real& g, const Real& b)
	{
		this->r_ = r;
		this->g_ = g;
		this->b_ = b;
	};
	
	inline void setR ( const Real& r)
	{
		this->r_ = r;
	};
	
	inline void setG ( const Real& g)
	{
		this->g_ = g;
	};
	
	inline void setB ( const Real& b)
	{
		this->b_ = b;
	};
		
	inline const Real& x() const
	{
		return ( this->x_ );
	};
	
	inline const Real& y() const
	{
		return ( this->y_ );
	};
	
	inline const Real& z() const
	{
		return ( this->z_ );
	};
	
	inline const Real& r() const
	{
		return ( this->r_ );
	};
	
	inline const Real& g() const
	{
		return ( this->g_ );
	};
	
	inline const Real& b() const
	{
		return ( this->b_ );
	};

	inline  Real operator [] ( int i)  const
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
	
	inline  Real operator [] ( int i)  

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
	
	inline Point3<Real>& operator= ( const Point3<Real>& p)
	{
		this->x_ = p.x();
		this->y_ = p.y();
		this->z_ = p.z();
			
		return ( *this );
	};
	
	
	// Assignment Opertators
	//With Scalar

	const Point3< Real >& operator+= ( const Real&  factor ) 
	{ 
	    this->x_ += factor; 
	    this->y_ += factor; 
	    this->z_ += factor;
	    
	    return ( *this ); 
	} 
	
	const Point3< Real >& operator-= ( const Real&  factor ) 
	{ 
	    this->x_ -= factor; 
	    this->y_ -= factor; 
	    this->z_ -= factor;
	    
	    return ( *this ); 
	} 
	
	const Point3< Real >& operator*= ( const Real& factor ) 
	{ 
	 	 	
	 	this->x_  *= factor;
	 	this->y_  *= factor;
	 	this->z_  *= factor;
						
	    return ( *this ); 
	}

	const Point3< Real >& operator/= ( Real factor ) 
	{ 
	    factor = (Real)1 / factor;
	    
	    this->x_ *= factor;
	    this->y_ *= factor; 
	    this->z_ *= factor;
	    
	    return ( *this ); 
	}
	// With Vector
	const Point3< Real >& operator+= (  const Point3<Real>& u ) 
	{ 
	    this->x_ += u.x(); 
	    this->y_ += u.y(); 
	    this->z_ += u.z();
	    
	    return ( *this ); 
	}
	
	const Point3< Real >& operator-= (  const Point3<Real>& u ) 
	{ 
	    this->x_ -= u.x(); 
	    this->y_ -= u.y(); 
	    this->z_ -= u.z();
	    
	    return ( *this ); 
	} 


	const Point3<Real>& operator/=( const Point3<Real>& u ) 
	{ 
	    	    
	    this->x_ /= u.x();
	    this->y_ /= u.y(); 
	    this->z_ /= u.z();
	    
	    return ( *this ); 
	}
	
	
	inline bool operator== ( const Point3<Real>& p) const
	{
		return ( ( this->x_ == p.x() ) and ( this->y_ == p.y() ) and ( this->z_ == p.z() ) );
	};	
	
	inline bool operator!= ( const Point3<Real>& p) const
	{
		return  !(*this == p) ;
	};	
	
	inline Point3<Real>  operator- ( ) const
	{
		
		return ( Point3<Real> (-this->x_, -this->y_, -this->z_) );
			
	};
	
	inline bool operator> ( const Point3<Real>& p) const
	{
		return ( ( this->x_ > p.x() ) and 
				 ( this->y_ > p.y() ) and
				 ( this->z_ > p.z() ) );
	};
	
	inline friend const Vector3<Real> operator- (const Point3<Real>& p, const Point3<Real>& q)  
	{
		return ( Vector3<Real>( p.x_ - q.x_,
								p.y_ - q.y_,
								p.z_ - q.z_)
			    );
		
	};
	
	inline friend const Point3<Real> operator- (const Point3<Real>& p, const Vector3<Real> u)  
	{
		return ( Point3<Real>( p.x_ - u.x_,
						  	p.y_ - u.y_,
				  	  	    p.z_ - u.z_ )
			   );
	};
	
	inline friend const Point3<Real> operator- (const Vector3<Real> u,const Point3<Real> p )  
	{
		
		return ( Point3<Real>( u.x_ - p.x_,
							   u.y_ - p.y_,
							   u.z_ - p.z_ )
			    );
		    
	};
	
	inline Point3<Real>  operator+ ( ) const
	{
		return ( *this );
	};
	
	inline friend const Point3<Real> operator+ (const Point3<Real> p, const Vector3<Real> u)  
	{
		return ( Point3<Real> ( p.x_ + u.x_,
				     	  		p.y_ + u.y_,
				     	  		p.z_ + u.z_ )
			    );
		
	};
	
	inline friend  const Point3<Real> operator+ (const Vector3<Real> u,const Point3<Real> p )  
	{
		return ( Point3<Real> ( p.x_ + u.x_,
					      		p.y_ + u.y_,
					      		p.z_ + u.z_ )
			    );
	    
	};
		
	
	friend inline std::ostream& operator<< (std::ostream & s, const Point3<Real>& p)
	{
		s << "Point3" << " x = " << p.x() << " ,y = " << p.y() << " ,z = " << p.z() << std::endl;
		
		
		return ( s );
	};
	
	double squaredDistance ( const Point3<Real> p ) const 
	{
	    return ( pow ( p.x() - this->x_, 2) + 
	    		 pow ( p.y() - this->y_, 2) + 
	    		 pow ( p.z() - this->z_, 2) );
	}
		
	virtual ~Point3(){};
	
};

} /* SLAL :: NAMESPACE */

#endif /*POINT3_HPP_*/
