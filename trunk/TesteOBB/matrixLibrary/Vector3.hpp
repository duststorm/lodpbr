#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>

#include <cassert>
#include <cmath>


namespace SLAL { 

template <class T>	class Vector3
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
	
public:
	
	// VETOR COLUNA OU VETOR LINHA ??
	 
	Vector3 ()
	{
		this->x_ = (T)0;
		this->y_ = (T)0;
		this->z_ = (T)0;
	};
	 
	template < typename U >
	Vector3 (const U* u)
	{
		assert(u);
		
    	this->x_ = static_cast< T > ( u[0] );
    	this->y_ = static_cast< T > ( u[1] );
    	this->z_ = static_cast< T > ( u[2] );
	};
	
	Vector3 ( const Vector3<T>& u)
	{
		this->x_ = u.x();
		this->y_ = u.y();
		this->z_ = u.z();
	};
	
	Vector3 ( const T& x, const T& y, const T& z )
	{
		this->x_ = x;
		this->y_ = y;
		this->z_ = z;
	};
	
	//Gets and Sets
			
	inline T x() const
	{
		return ( this->x_ );
	};
	
	inline T y() const
	{
		return ( this->y_ );
	};
	
	inline T z() const
	{
		return ( this->z_ );
	};
	
	//Operator
	
	inline T& operator [] (const unsigned int i) 
	{
		if ( i > 2)
		{
			std::cerr << "[ERROR] Vector3 operator[]"        << std::endl
				      << "        Out of the vector size. " << std::endl
				      << "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}
			
		return (xyz[i]);
		
	};
	
	inline T& operator [] (const unsigned int i) const
	{
		if ( i > 2)
		{
			std::cerr << "[ERROR] Vector3 operator[]"        << std::endl
				      << "        Out of the vector size. " << std::endl
				      << "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}
			
		
		return (xyz[i]);

	};
	
	// Assignment Opertators
	//With Scalar
	inline Vector3<T>& operator= ( const Vector3<T>& u )
	{
		this->x_ = u.x_;
		this->y_ = u.y_;
		this->z_ = u.z_;
			
		return ( *this );
	};
	
	const Vector3< T >& operator+= ( const T&  factor ) 
	{ 
	    this->x_ += factor; 
	    this->y_ += factor; 
	    this->z_ += factor;
	    
	    return ( *this ); 
	} 
	
	const Vector3< T >& operator-= ( const T&  factor ) 
	{ 
	    this->x_ -= factor; 
	    this->y_ -= factor; 
	    this->z_ -= factor;
	    
	    return ( *this ); 
	} 
	
	const Vector3< T >& operator*= ( const T& factor ) 
	{ 
	 	 	
	 	this->x_  *= factor;
	 	this->y_  *= factor;
	 	this->z_  *= factor;
						
	    return ( *this ); 
	}

	const Vector3< T >& operator/= ( T factor ) 
	{ 
	    factor = (T)1 / factor;
	    
	    this->x_ *= factor;
	    this->y_ *= factor; 
	    this->z_ *= factor;
	    
	    return ( *this ); 
	}
	// With Vector
	const Vector3< T >& operator+= (  const Vector3<T>& u ) 
	{ 
	    this->x_ += u.x_; 
	    this->y_ += u.y_; 
	    this->z_ += u.z_;
	    
	    return ( *this ); 
	}
	
	const Vector3< T >& operator-= (  const Vector3<T>& u ) 
	{ 
	    this->x_ -= u.x_; 
	    this->y_ -= u.y_; 
	    this->z_ -= u.z_;
	    
	    return ( *this ); 
	} 


	const Vector3< T >& operator/=( const Vector3<T>& u ) 
	{ 
	    	    
	    this->x_ /= u.x_;
	    this->y_ /= u.y_; 
	    this->z_ /= u.z_;
	    
	    return ( *this ); 
	} 
	
	inline bool operator== ( const Vector3<T>& u) const
	{
		return ( ( this->x_ == u.x_ ) and ( this->y_ == u.y_ ) and ( this->z_ == u.z_ ) );
	};	
	
	inline bool operator!= ( const Vector3<T>& u) const
	{
		return  !(*this == u) ;
	};	
	
	inline Vector3<T>  operator- ( const Vector3<T>& u) const
	{
	
		return ( Vector3 ( this->x_ - u.x_,
						   this->y_ - u.y_,
						   this->z_ - u.z_) 
			   );
	};
	
	inline Vector3<T>  operator- ( ) const
	{
		 		
		return ( Vector3 (-this->x_, -this->y_, -this->z_) );
		
	};
	
	inline Vector3<T>  operator+ ( const Vector3<T>& u)	const
	{
	 	
		return ( Vector3 ( this->x_ + u.x_,
	 			     	   this->y_ + u.y_,
	 					   this->z_ + u.z_)
	 			);
		
	};
	
	inline Vector3<T>  operator+ ( ) const
	{
		return ( *this );
	};
	
	friend inline Vector3<T> operator* ( const Vector3<T>& u,const T& factor ) 	
	{
	 		
		return (  Vector3( u.x_ * factor,
						   u.y_ * factor,
					       u.z_ * factor ) 
			   );
		
	};
	
	friend inline Vector3<T> operator*	( const T& factor ,const Vector3<T>& u) 
	{
	 	return ( Vector3( u.x_ * factor,
	 					  u.y_ * factor,
	 					  u.z_ * factor )
	 			);

	};
	
	friend inline T operator* ( const Vector3<T>& u, const Vector3<T>& v) 	
	{
	 			
		return (  (u.x_ * v.x_ ) +  ( u.x_ * v.y_ ) + ( u.x_ * v.z_ )  );
		
	};

		
	inline Vector3<T>  operator^ (const Vector3<T>& u) const
	{
		return ( Vector3( this->y_ * u.z_ - this->z_ * u.y_,
		     			  this->z_ * u.x_ - this->x_ * u.z_,
						  this->x_ * u.y_ - this->y_ * u.x_ )
				);

		
	};
	
	friend inline std::ostream& operator<< (std::ostream & s, const Vector3<T>& u)
	{
		s << "Vector3"<< " x = " << u.x() << " ,y = " << u.y() << " ,z = " << u.z() << std::endl;
		
		return s;
	};
	
	// AUXILIAR FUNCTIONS
	
	inline T length ()
	{
		return sqrt( (this->x_ * this->x_) + (this->y_ * this->y_) + (this->z_ * this->z_) );
	};
	
	inline void normalize ()
	{
		T factor = sqrt( (this->x_ * this->x_) + (this->y_ * this->y_) + (this->z_ * this->z_) );
		
		assert (factor);
		
		T d = 1 / factor;
		
		this->x_ *= d;
		this->y_ *= d;
		this->x_ *= d;
			
	};
	
	inline Vector3<T> norm ()
	{
		T factor = sqrt( (this->x_ * this->x_) + (this->y_ * this->y_) + (this->z_ * this->z_) );
		
		assert (factor);
		
		T d = 1 / factor;
		
		return ( Vector3 (this->x_ * d, this->y_ * d, this->x_ * d) );
			
	};
	
	~Vector3 (){};
		

};


} // END NAMESPACE


#endif

// CASOS DE TESTE


/* Teste operator+ e operator-
SLAL::Vector3<double> v1(1.0,1.0,1.0);
SLAL::Vector3<double> v2(-1.0,-1.0,-1.0);
SLAL::Vector3<double> v3(0.0,0.0,0.0);

v3 = v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#v1+v2#"<<std::endl;
v3 = v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#v1-v2#"<<std::endl;
v3 = -v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#-v1-v2#"<<std::endl;
v3 = -v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#-v1+v2#"<<std::endl;
v3 = + v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#+v1-v2#"<<std::endl;
v3 = + v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#+v1+v2#"<<std::endl;
*/

/*Teste operator*
	SLAL::Vector3<double> v1(1.0,1.0,1.0);
	SLAL::Vector3<double> v3(0.0,0.0,0.0);
	
	v3 = 3.0 * v1;
	std::cout << v3.x << v3.y << v3.z << "#3*v1#"<<std::endl;
	v3 = 3.0 * (-v1);
	std::cout << v3.x << v3.y << v3.z << "#3*(-v1)#"<<std::endl;
	v3 = 3.0 * (+v1);
	std::cout << v3.x << v3.y << v3.z << "#3*(+v1)#"<<std::endl;
	v3 = (-v1) * 3.0;
	std::cout << v3.x << v3.y << v3.z << "#(-v1)*3#"<<std::endl;
	v3 = (+v1) * 3.0;
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*3#"<<std::endl;
	v3 = (+v1) * 0.0;
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*0.0#"<<std::endl;
	v3 = (+v1) * v2[1];
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*0.0#"<<std::endl;
*/

/* Teste operator* (puduto interno ou  produto escalar) 
SLAL::Vector3<double> v1(6.0,-1.0,0.0);
SLAL::Vector3<double> v2(0.5,-4.0,0.0);
double t = 0.0 ;
t = v1 * v2
std::cout << t << "#(v1)*(v2)#"<<std::endl;
v1[1] = v1*(-v2)
*/



/*
 * solucão para não ter warnning no retorno de uma referencia
inline Vector3<T>&  operator- ( const Vector3<T>& u) const
{
	Vector3<T> w;
	 	
	w.x = this->x - u.x;
	w.y = this->y - u.y;
	w.z = this->z - u.z;
		
	Vector3<T>& h = w;
	
	return ( h );
};
*/
