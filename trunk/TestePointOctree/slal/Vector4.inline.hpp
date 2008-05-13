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
Vector4<Real>::Vector4 ( const Vector4<Real>& vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = vector.w;
};

template<class Real>
Vector4<Real>::Vector4 ( const Vector3<Real>& vector, const Real& w)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = w;
};

template<class Real>
Vector4<Real>::Vector4 ( const Vector3<Real>& vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = static_cast< Real > (1);
};

template<class Real>
Vector4<Real>::Vector4 ( const Real& pX, const Real& pY, const Real& pZ, const Real& pW)
{
	this->x = pX;
	this->y = pY;
	this->z = pZ;
	this->w = pW;
};

//============================= ACESS ======================================

//Operator

template<class Real>
inline Vector4<Real>::operator Real * ()
{
	return  xyzw;
}

template<class Real>
inline Real Vector4<Real>::operator [] ( int i) const
{
	if ( i > 3)
	{
		std::cerr << "[ERROR] Vector4 operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}

	return (xyzw[i]);

};

template<class Real>
inline Real& Vector4<Real>::operator [] ( int i) 
{
	if ( i > 3)
	{
		std::cerr << "[ERROR] Vector4 operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}


	return (xyzw[i]);

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
inline Vector4<Real> operator* ( const Vector4<Real>& vector, const Real& factor ) 	
{

	return (  Vector4<Real>( vector.x * factor,
			vector.y * factor,
			vector.z * factor,
			vector.w * factor) 
	);

};

template<class Real>
inline Vector4<Real> operator*	( const Real& factor, const Vector4<Real>& vector ) 
{
	return ( Vector4<Real>( vector.x * factor,
			vector.y * factor,
			vector.z * factor,
			vector.w * factor)
	);

};

template<class Real>
inline Vector4<Real> operator/ ( const Vector4<Real>& vector, const Real& factor ) 	
{

	return (  Vector4<Real>( vector.x / factor,
			vector.y / factor,
			vector.z / factor,
			vector.w / factor) 
	);

};

template<class Real>
inline Vector4<Real> operator+ (const Real& factor, const Vector4<Real>& vector )  
{
	return ( Vector4<Real> ( vector.x + factor,
			vector.y + factor,
			vector.z + factor,
			vector.w + factor)
	);

};

template<class Real>
inline Vector4<Real> operator+ (const Vector4<Real>& vector, const Real& factor )  
{
	return ( Vector4<Real> ( vector.x + factor,
			vector.y + factor,
			vector.z + factor,
			vector.w + factor)
	);

};

template<class Real>
inline Vector4<Real> operator- (const Real& factor, const Vector4<Real>& vector )  
{
	return ( Vector4<Real> ( factor - vector.x ,
			factor - vector.y,
			factor - vector.z,
			factor - vector.w)
	);

};

template<class Real>
inline Vector4<Real> operator- (const Vector4<Real>& vector, const Real& factor )  
{
	return ( Vector4<Real> ( vector.x - factor,
			vector.y - factor,
			vector.z - factor,
			vector.w - factor)
	);

};

// With Vector

template<class Real>
inline const Vector4<Real>& Vector4<Real>::operator= ( const Vector4<Real>& vector )
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = vector.w;

	return ( *this );
};

template<class Real>
const Vector4< Real >& Vector4<Real>::operator+= (  const Vector4<Real>& vector ) 
{ 
	this->x += vector.x; 
	this->y += vector.y; 
	this->z += vector.z;
	this->w += vector.w;

	return ( *this ); 
}

template<class Real>
const Vector4< Real >& Vector4<Real>::operator-= (  const Vector4<Real>& vector ) 
{ 
	this->x -= vector.x; 
	this->y -= vector.y; 
	this->z -= vector.z;
	this->w -= vector.w;

	return ( *this ); 
} 

template<class Real>
const Vector4< Real >& Vector4<Real>::operator/= ( const Vector4<Real>& vector ) 
{ 

	this->x /= vector.x;
	this->y /= vector.y; 
	this->z /= vector.z;
	this->w /= vector.w;

	return ( *this ); 
} 

template<class Real>
inline bool Vector4<Real>::operator== ( const Vector4<Real>& vector) const
{
	return ( ( this->x == vector.x ) and ( this->y == vector.y ) and ( this->z == vector.z ) and (this->w == vector.w) );
};	

template<class Real>
inline bool Vector4<Real>::operator!= ( const Vector4<Real>& vector) const
{
	return  !(*this == vector) ;
};	

template<class Real>
inline Vector4<Real>  Vector4<Real>::operator- ( const Vector4<Real>& vector) const
{

	return ( Vector4 ( this->x - vector.x,
			this->y - vector.y,
			this->z - vector.z,
			this->w - vector.w) 
	);
};

template<class Real>
inline Vector4<Real>  Vector4<Real>::operator+ ( const Vector4<Real>& vector)	const
{

	return ( Vector4 ( this->x + vector.x,
			this->y + vector.y,
			this->z + vector.z,
			this->w + vector.w)
	);

};

// Dot produt
template<class Real>
inline Real Vector4<Real>::operator* ( const Vector4<Real>& vector) const	
{

	return (  (vector.x * x ) +  ( vector.y * y ) + ( vector.z * z ) + (vector.w * w) );

};


template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Vector4<Real>& vector)
{
	s << "Vector4" << "  x = " << vector.x 
				   << " ,y = " << vector.y 
				   << " ,z = " << vector.z 
				   << " ,w = " << vector.w << std::endl;

	return s;
};

//============================= OPERATIONS ===================================

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector4<Real>::length ()
{
	return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w) );
};

template<class Real>
inline void Vector4<Real>::normalize ()
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
inline Vector4<Real> Vector4<Real>::norm ()
{
	Real factor = sqrt( (x * x) + (y * y) + (z * z) + (w * w) );

	assert (factor);

	Real lFactor = 1 / factor;

	return ( Vector4 (x * lFactor, y * lFactor, z * lFactor, w * lFactor) );

};
template <class Real>
Vector4<Real>::~Vector4 (){};
	
#endif
