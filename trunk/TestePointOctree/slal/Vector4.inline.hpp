#ifndef LAL_VECTOR4_INLINE_HPP_
#define LAL_VECTOR4_INLINE_HPP_

//============================= LIFECYCLE ====================================

template<class Real>
Vector4<Real>::Vector4 ()
{
	this->x = static_cast< Real > ( 0 );
	this->y = static_cast< Real > ( 0 );
	this->z = static_cast< Real > ( 0 );
	this->w = static_cast< Real > ( 1 );
};

template<class Real>
template < typename U >
Vector4<Real>::Vector4 (const U* u)
{
	assert(u);

	this->x = static_cast< Real > ( u[0] );
	this->y = static_cast< Real > ( u[1] );
	this->z = static_cast< Real > ( u[2] );
	this->w = static_cast< Real > ( u[3] );

};

template<class Real>
Vector4<Real>::Vector4 ( const Vector4<Real>& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
};

template<class Real>
Vector4<Real>::Vector4 ( const Vector3<Real>& v, const Real& w)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
};

template<class Real>
Vector4<Real>::Vector4 ( const Vector3<Real>& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = static_cast< Real > (1);
};

template<class Real>
Vector4<Real>::Vector4 ( const Real& x, const Real& y, const Real& z, const Real& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
};

//============================= ACESS ======================================

//Operator

template<class Real>
inline Real Vector4<Real>::operator [] ( int index ) const
{
	if ( index > 3)
	{
		std::cerr << "[ERROR] Vector4 operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}

	return ( ( &x )[ index ] );

};

template<class Real>
inline Real& Vector4<Real>::operator [] ( int index ) 
{
	if ( index > 3)
	{
		std::cerr << "[ERROR] Vector4 operator[]"        << std::endl
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
inline Vector4<Real> Vector4<Real>::operator+ ( )  const  
{
	return ( Vector4<Real> (this->x, this->y, this->z, this->w)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point3.
 */
template<class Real>
inline Vector4<Real>  Vector4<Real>::operator- ( ) const
{

	return ( Vector4<Real> (-this->x, -this->y, -this->z, -this->w) );

};

template<class Real>
const Vector4< Real >& Vector4<Real>::operator+= ( const Real&  factor ) 
{ 
	this->x += factor; 
	this->y += factor; 
	this->z += factor;
	this->w += factor;

	return ( *this ); 
} 

template<class Real>
const Vector4< Real >& Vector4<Real>::operator-= ( const Real&  factor ) 
{ 
	this->x -= factor; 
	this->y -= factor; 
	this->z -= factor;
	this->w -= factor;

	return ( *this ); 
} 

template<class Real>
const Vector4< Real >& Vector4<Real>::operator*= ( const Real& factor ) 
{ 

	this->x  *= factor;
	this->y  *= factor;
	this->z  *= factor;
	this->w  *= factor;

	return ( *this ); 
}

template<class Real>
const Vector4< Real >& Vector4<Real>::operator/= ( const Real& factor ) 
{ 
	Real lFactor = (Real)1 / factor;

	this->x *= lFactor;
	this->y *= lFactor; 
	this->z *= lFactor;
	this->w *= lFactor;

	return ( *this ); 
}


template<class Real>
inline Vector4<Real> operator* ( const Vector4<Real>& v, const Real& factor ) 	
{

	return (  Vector4<Real>( v.x * factor,
			v.y * factor,
			v.z * factor,
			v.w * factor) 
	);

};

template<class Real>
inline Vector4<Real> operator*	( const Real& factor, const Vector4<Real>& v ) 
{
	return ( Vector4<Real>( v.x * factor,
			v.y * factor,
			v.z * factor,
			v.w * factor)
	);

};

template<class Real>
inline Vector4<Real> operator/ ( const Vector4<Real>& v, const Real& factor ) 	
{

	return (  Vector4<Real>( v.x / factor,
			v.y / factor,
			v.z / factor,
			v.w / factor) 
	);

};

template<class Real>
inline Vector4<Real> operator+ (const Real& factor, const Vector4<Real>& v )  
{
	return ( Vector4<Real> ( v.x + factor,
			v.y + factor,
			v.z + factor,
			v.w + factor)
	);

};

template<class Real>
inline Vector4<Real> operator+ (const Vector4<Real>& v, const Real& factor )  
{
	return ( Vector4<Real> ( v.x + factor,
			v.y + factor,
			v.z + factor,
			v.w + factor)
	);

};

template<class Real>
inline Vector4<Real> operator- (const Real& factor, const Vector4<Real>& v )  
{
	return ( Vector4<Real> ( factor - v.x ,
			factor - v.y,
			factor - v.z,
			factor - v.w)
	);

};

template<class Real>
inline Vector4<Real> operator- (const Vector4<Real>& v, const Real& factor )  
{
	return ( Vector4<Real> ( v.x - factor,
			v.y - factor,
			v.z - factor,
			v.w - factor)
	);

};

// With Vector

template<class Real>
inline const Vector4<Real>& Vector4<Real>::operator= ( const Vector4<Real>& v )
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;

	return ( *this );
};

template<class Real>
const Vector4< Real >& Vector4<Real>::operator+= (  const Vector4<Real>& v ) 
{ 
	this->x += v.x; 
	this->y += v.y; 
	this->z += v.z;
	this->w += v.w;

	return ( *this ); 
}

template<class Real>
const Vector4< Real >& Vector4<Real>::operator-= (  const Vector4<Real>& v ) 
{ 
	this->x -= v.x; 
	this->y -= v.y; 
	this->z -= v.z;
	this->w -= v.w;

	return ( *this ); 
} 

template<class Real>
const Vector4< Real >& Vector4<Real>::operator/= ( const Vector4<Real>& v ) 
{ 

	this->x /= v.x;
	this->y /= v.y; 
	this->z /= v.z;
	this->w /= v.w;

	return ( *this ); 
} 

template<class Real>
inline bool Vector4<Real>::operator== ( const Vector4<Real>& v) const
{
	return ( ( this->x == v.x ) and ( this->y == v.y ) and ( this->z == v.z ) and (this->w == v.w) );
};	

template<class Real>
inline bool Vector4<Real>::operator!= ( const Vector4<Real>& v) const
{
	return  !(*this == v) ;
};	

template<class Real>
inline Vector4<Real>  Vector4<Real>::operator- ( const Vector4<Real>& v) const
{

	return ( Vector4 ( this->x - v.x,
			this->y - v.y,
			this->z - v.z,
			this->w - v.w) 
	);
};

template<class Real>
inline Vector4<Real>  Vector4<Real>::operator+ ( const Vector4<Real>& v)	const
{

	return ( Vector4 ( this->x + v.x,
			this->y + v.y,
			this->z + v.z,
			this->w + v.w)
	);

};

// Dot produt
template<class Real>
inline Real Vector4<Real>::operator* ( const Vector4<Real>& v) const	
{

	return (  (v.x * x ) +  ( v.y * y ) + ( v.z * z ) + (v.w * w) );

};


template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Vector4<Real>& v)
{
	s << "Vector4" << "  x = " << v.x 
				   << " ,y = " << v.y 
				   << " ,z = " << v.z 
				   << " ,w = " << v.w << std::endl;

	return s;
};

//============================= OPERATIONS ===================================

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector4<Real>::Length ()
{
	return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w) );
};

template<class Real>
inline Real Vector4<Real>::LengthSqr ()
{
	return ( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w) );
};

template<class Real>
inline void Vector4<Real>::Normalize ()
{
	Real factor = sqrt( (x * x) + (y * y) + (z * z) + (w * w) );

	assert (factor);

	Real lFactor = 1 / factor;

	x *= lFactor;
	y *= lFactor;
	z *= lFactor;
	w *= lFactor;

};

template<class Real>
inline Vector4<Real> Vector4<Real>::Norm ()
{
	Real factor = sqrt( (x * x) + (y * y) + (z * z) + (w * w) );

	assert (factor);

	Real lFactor = 1 / factor;

	return ( Vector4 (x * lFactor, y * lFactor, z * lFactor, w * lFactor) );

};

template<class Real>
const Real* Vector4<Real>::ToRealPtr( void ) const 
{
	return &x;
}

template<class Real>
Real* Vector4<Real>::ToRealPtr( void )
{
	return &x;
}

template <class Real>
Vector4<Real>::~Vector4 (){};
	
#endif
