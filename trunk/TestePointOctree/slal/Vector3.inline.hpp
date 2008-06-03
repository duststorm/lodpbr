#ifndef LAL_VECTOR3_INLINE_HPP_
#define LAL_VECTOR3_INLINE_HPP_

//============================= LIFECYCLE ====================================



template<class Real>
Vector3<Real>::Vector3()
{
	this->x = static_cast< Real > ( 0 );
	this->y = static_cast< Real > ( 0 );
	this->z = static_cast< Real > ( 0 );
};

template< class Real>
template< class T >
Vector3<Real>::Vector3( const T* v )
{
	assert(v);

	this->x = static_cast< Real > ( v[0] );
	this->y = static_cast< Real > ( v[1] );
	this->z = static_cast< Real > ( v[2] );

};

template< class Real>
template< class T >
Vector3<Real>::Vector3( const Vector3<T>& v )
{
	this->x = static_cast< Real > (v.x);
	this->y = static_cast< Real > (v.y);
	this->z = static_cast< Real > (v.z);
};


template<class Real>
Vector3<Real>::Vector3( const Vector3<Real>& v )
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
};

template<class Real>
Vector3<Real>::Vector3( const Real& x, const Real& y, const Real& z )
{
	this->x = x;
	this->y = y;
	this->z = z;
};

template<class Real>
inline Vector3<Real>& Vector3<Real>::operator=( const Vector3<Real>& v )
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;

	return ( *this );
};

template<class Real>
inline void Vector3<Real>::Set( const Real& x, const Real& y, const Real& z ) 
{
	this->x = x;
	this->y = y;
	this->z = z;
};

//============================= ACESS ======================================

//Operator

template<class Real>
inline Real Vector3<Real>::operator[]( int index ) const
{
	if ( index > 2)
	{
		std::cerr << "[ERROR] Vector3 operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}

	return ( ( &x )[ index ] );

};

template<class Real>
inline Real& Vector3<Real>::operator[]( int index ) 
{
	if ( index > 2)
	{
		std::cerr << "[ERROR] Vector3 operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}


	return ( ( &x )[ index ] );

};

//============================= OPERATORS ====================================

// Assignment Opertators
//With Scalar

template<class Real>
inline Vector3<Real> Vector3<Real>::operator+()  const  
{
	return ( Vector3<Real> (this->x, this->y, this->z)  );
};


template<class Real>
inline Vector3<Real>  Vector3<Real>::operator-() const
{

	return ( Vector3<Real> (-this->x, -this->y, -this->z) );

};

template<class Real>
Vector3< Real >& Vector3<Real>::operator+=( const Real&  factor ) 
{ 
	this->x += factor; 
	this->y += factor; 
	this->z += factor;

	return ( *this ); 
} 

template<class Real>
Vector3< Real >& Vector3<Real>::operator-=( const Real&  factor ) 
{ 
	this->x -= factor; 
	this->y -= factor; 
	this->z -= factor;

	return ( *this ); 
} 

template<class Real>
Vector3< Real >& Vector3<Real>::operator*=( const Real& factor ) 
{ 

	this->x  *= factor;
	this->y  *= factor;
	this->z  *= factor;

	return ( *this ); 
}

template<class Real>
Vector3< Real >& Vector3<Real>::operator/=( const Real& factor ) 
{ 
	Real lFactor = (Real)1 / factor;

	this->x *= lFactor;
	this->y *= lFactor; 
	this->z *= lFactor;

	return ( *this ); 
}


template<class Real>
inline Vector3<Real> operator*( const Vector3<Real>& v, const Real& factor ) 	
{

	return (  Vector3<Real>( v.x * factor, v.y * factor, v.z * factor )	);

};

template<class Real>
inline Vector3<Real> operator*( const Real& factor, const Vector3<Real>& v ) 
{
	return ( Vector3<Real>( v.x * factor, v.y * factor, v.z * factor ) );

};

template<class Real>
inline Vector3<Real> operator/( const Vector3<Real>& v, const Real& factor ) 	
{

	return (  Vector3<Real>( v.x / factor, 	v.y / factor, v.z / factor ) );

};

template<class Real>
inline Vector3<Real> operator+( const Real& factor, const Vector3<Real>& v )  
{
	return ( Vector3<Real> ( v.x + factor, v.y + factor, v.z + factor ) );

};

template<class Real>
inline Vector3<Real> operator+( const Vector3<Real>& v, const Real& factor )  
{
	return ( Vector3<Real> ( v.x + factor, v.y + factor, v.z + factor ) );

};

template<class Real>
inline Vector3<Real> operator-( const Real& factor, const Vector3<Real>& v )  
{
	return ( Vector3<Real> ( factor - v.x , factor - v.y , factor - v.z  ) );

};

template<class Real>
inline Vector3<Real> operator-( const Vector3<Real>& v, const Real& factor )  
{
	return ( Vector3<Real> ( v.x - factor, 	v.y - factor, v.z - factor ) );

};

// With Vector


template<class Real>
Vector3< Real >& Vector3<Real>::operator+=(  const Vector3<Real>& v ) 
{ 
	this->x += v.x; 
	this->y += v.y; 
	this->z += v.z;

	return ( *this ); 
}

template<class Real>
Vector3< Real >& Vector3<Real>::operator-=( const Vector3<Real>& v ) 
{ 
	this->x -= v.x; 
	this->y -= v.y; 
	this->z -= v.z;

	return ( *this ); 
} 

template<class Real>
Vector3< Real >& Vector3<Real>::operator/=( const Vector3<Real>& v ) 
{ 

	this->x /= v.x;
	this->y /= v.y; 
	this->z /= v.z;

	return ( *this ); 
} 

template<class Real>
inline bool Vector3<Real>::operator==( const Vector3<Real>& v ) const
{
	return ( ( this->x == v.x ) and ( this->y == v.y ) and ( this->z == v.z ) );
};	

template<class Real>
inline bool Vector3<Real>::operator!=( const Vector3<Real>& v) const
{
	return  !(*this == v) ;
};	

template<class Real>
inline Vector3<Real>  Vector3<Real>::operator-( const Vector3<Real>& v ) const
{

	return ( Vector3 ( this->x - v.x, this->y - v.y, this->z - v.z) );
};

template<class Real>
inline Vector3<Real>  Vector3<Real>::operator+( const Vector3<Real>& v )	const
{

	return ( Vector3 ( this->x + v.x, this->y + v.y, this->z + v.z) );

};

template<class Real>
inline Real Vector3<Real>::operator*( const Vector3<Real>& v ) const	
{

	return (  (v.x * x ) +  ( v.y * y ) + ( v.z * z )  );

};

// Cross Product
template<class Real>
inline Vector3<Real>  Vector3<Real>::operator^( const Vector3<Real>& v ) const
{
	return ( Vector3<Real> ( y*v.z - z*v.y, 	z*v.x - x*v.z, 	x*v.y - y*v.x ) );

};

//============================= OPERATIONS ===================================

template<class Real>
inline std::ostream& operator<<( std::ostream & s, const Vector3<Real>& v )
{
	s << "Vector3"<< " x = " << v.x << " ,y = " << v.y << " ,z = " << v.z << std::endl;

	return s;
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector3<Real>::Length()
{
	return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector3<Real>::LengthSqr()
{
	return ( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
};


template<class Real>
inline void Vector3<Real>::Normalize()
{
	Real factor = std::sqrt( (x * x) + (y * y) + (z * z) );

	if (factor <= static_cast<Real>(0))
	{

	}
	else{
		Real d = 1 / factor;

		x *= d;
		y *= d;
		z *= d;


	}

};

template<class Real>
inline Vector3<Real> Vector3<Real>::Norm ()
{
	Real factor = sqrt( (x * x) + (y * y) + (z * z) );

	if (factor <= static_cast<Real>(0))
		return ( Vector3 (x, y, z) );


	Real d = 1 / factor;

	return ( Vector3<Real> (x * d, y * d, z * d) );

};

template<class Real>
const Real* Vector3<Real>::ToRealPtr( void ) const 
{
	return &x;
}

template<class Real>
Real* Vector3<Real>::ToRealPtr( void )
{
	return &x;
}

template <class Real>
Vector3<Real>::~Vector3 (){};


#endif
