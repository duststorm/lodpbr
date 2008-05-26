#ifndef LAL_VECTOR3_INLINE_HPP_
#define LAL_VECTOR3_INLINE_HPP_

//============================= LIFECYCLE ====================================

template<class Real>
Vector3<Real>::Vector3 ()
{
	this->x = static_cast< Real > ( 0 );
	this->y = static_cast< Real > ( 0 );
	this->z = static_cast< Real > ( 0 );
};

template<class Real>
template < typename U >
Vector3<Real>::Vector3 (const U* u)
{
	assert(u);

	this->x = static_cast< Real > ( u[0] );
	this->y = static_cast< Real > ( u[1] );
	this->z = static_cast< Real > ( u[2] );

};

template<class Real>
template < typename U >
Vector3<Real>::Vector3 ( const Vector3<U>& vector)
{
	this->x = static_cast< Real > (vector.x);
	this->y = static_cast< Real > (vector.y);
	this->z = static_cast< Real > (vector.z);
};


template<class Real>
Vector3<Real>::Vector3 ( const Vector3<Real>& vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
};

template<class Real>
Vector3<Real>::Vector3 ( const Real& pX, const Real& pY, const Real& pZ )
{
	this->x = pX;
	this->y = pY;
	this->z = pZ;
};

//============================= ACESS ======================================


template<class Real>
inline void Vector3<Real>::setValues(const Real& x, const Real& y, const Real& z) 
{
	this->x = x;
	this->y = y;
	this->z = z;
};

//Operator

template<class Real>
inline Vector3<Real>::operator Real * ()
{
	return xyz;
}

template<class Real>
inline Vector3<Real>::operator const Real * ()
{
	return xyz;
}

template<class Real>
inline Real Vector3<Real>::operator [] ( int i) const
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

template<class Real>
inline Real& Vector3<Real>::operator [] ( int i) 
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

//============================= OPERATORS ====================================

// Assignment Opertators
//With Scalar

template<class Real>
inline Vector3<Real> Vector3<Real>::operator+ ( )  const  
{
	return ( Vector3<Real> (this->x, this->y, this->z)  );
};


template<class Real>
inline Vector3<Real>  Vector3<Real>::operator- ( ) const
{

	return ( Vector3<Real> (-this->x, -this->y, -this->z) );

};

template<class Real>
const Vector3< Real >& Vector3<Real>::operator+= ( const Real&  factor ) 
{ 
	this->x += factor; 
	this->y += factor; 
	this->z += factor;

	return ( *this ); 
} 

template<class Real>
const Vector3< Real >& Vector3<Real>::operator-= ( const Real&  factor ) 
{ 
	this->x -= factor; 
	this->y -= factor; 
	this->z -= factor;

	return ( *this ); 
} 

template<class Real>
const Vector3< Real >& Vector3<Real>::operator*= ( const Real& factor ) 
{ 

	this->x  *= factor;
	this->y  *= factor;
	this->z  *= factor;

	return ( *this ); 
}

template<class Real>
const Vector3< Real >& Vector3<Real>::operator/= ( const Real& factor ) 
{ 
	Real lFactor = (Real)1 / factor;

	this->x *= lFactor;
	this->y *= lFactor; 
	this->z *= lFactor;

	return ( *this ); 
}


template<class Real>
inline Vector3<Real> operator* ( const Vector3<Real>& vector, const Real& factor ) 	
{

	return (  Vector3<Real>( vector.x * factor,
			vector.y * factor,
			vector.z * factor ) 
	);

};

template<class Real>
inline Vector3<Real> operator*	( const Real& factor, const Vector3<Real>& vector ) 
{
	return ( Vector3<Real>( vector.x * factor,
			vector.y * factor,
			vector.z * factor )
	);

};

template<class Real>
inline Vector3<Real> operator/ ( const Vector3<Real>& vector, const Real& factor ) 	
{

	return (  Vector3<Real>( vector.x / factor,
			vector.y / factor,
			vector.z / factor ) 
	);

};

template<class Real>
inline Vector3<Real> operator+ (const Real& factor, const Vector3<Real>& vector )  
{
	return ( Vector3<Real> ( vector.x + factor,
			vector.y + factor,
			vector.z + factor )
	);

};

template<class Real>
inline Vector3<Real> operator+ (const Vector3<Real>& vector, const Real& factor )  
{
	return ( Vector3<Real> ( vector.x + factor,
			vector.y + factor,
			vector.z + factor )
	);

};

template<class Real>
inline Vector3<Real> operator- (const Real& factor, const Vector3<Real>& vector )  
{
	return ( Vector3<Real> ( factor - vector.x ,
			factor - vector.y ,
			factor - vector.z  )
	);

};

template<class Real>
inline Vector3<Real> operator- (const Vector3<Real>& vector, const Real& factor )  
{
	return ( Vector3<Real> ( vector.x - factor,
			vector.y - factor,
			vector.z - factor )
	);

};

// With Vector

template<class Real>
inline const Vector3<Real>& Vector3<Real>::operator= ( const Vector3<Real>& vector )
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;

	return ( *this );
};

template<class Real>
const Vector3< Real >& Vector3<Real>::operator+= (  const Vector3<Real>& vector ) 
{ 
	this->x += vector.x; 
	this->y += vector.y; 
	this->z += vector.z;

	return ( *this ); 
}

template<class Real>
const Vector3< Real >& Vector3<Real>::operator-= (  const Vector3<Real>& vector ) 
{ 
	this->x -= vector.x; 
	this->y -= vector.y; 
	this->z -= vector.z;

	return ( *this ); 
} 

template<class Real>
const Vector3< Real >& Vector3<Real>::operator/= ( const Vector3<Real>& vector ) 
{ 

	this->x /= vector.x;
	this->y /= vector.y; 
	this->z /= vector.z;

	return ( *this ); 
} 

template<class Real>
inline bool Vector3<Real>::operator== ( const Vector3<Real>& vector) const
{
	return ( ( this->x == vector.x ) and ( this->y == vector.y ) and ( this->z == vector.z ) );
};	

template<class Real>
inline bool Vector3<Real>::operator!= ( const Vector3<Real>& vector) const
{
	return  !(*this == vector) ;
};	

template<class Real>
inline Vector3<Real>  Vector3<Real>::operator- ( const Vector3<Real>& vector) const
{

	return ( Vector3 ( this->x - vector.x,
			this->y - vector.y,
			this->z - vector.z) 
	);
};

template<class Real>
inline Vector3<Real>  Vector3<Real>::operator+ ( const Vector3<Real>& vector)	const
{

	return ( Vector3 ( this->x + vector.x,
			this->y + vector.y,
			this->z + vector.z)
	);

};

template<class Real>
inline Real Vector3<Real>::operator* ( const Vector3<Real>& vector) const	
{

	return (  (vector.x * x ) +  ( vector.y * y ) + ( vector.z * z )  );

};

// Cross Product
template<class Real>
inline Vector3<Real>  Vector3<Real>::operator^ (const Vector3<Real>& vector) const
{
	return ( Vector3<Real> ( 	y*vector.z - z*vector.y,
			z*vector.x - x*vector.z,
			x*vector.y - y*vector.x)
	);

};

//============================= OPERATIONS ===================================

template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Vector3<Real>& vector)
{
	s << "Vector3"<< " x = " << vector.x << " ,y = " << vector.y << " ,z = " << vector.z << std::endl;

	return s;
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector3<Real>::length ()
{
	return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector3<Real>::length2 ()
{
	return ( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
};


template<class Real>
inline void Vector3<Real>::normalize ()
{
	Real factor = sqrt( (x * x) + (y * y) + (z * z) );

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
inline Vector3<Real> Vector3<Real>::norm ()
{
	Real factor = sqrt( (x * x) + (y * y) + (z * z) );

	if (factor <= static_cast<Real>(0))
		return ( Vector3 (x, y, z) );


	Real d = 1 / factor;

	return ( Vector3<Real> (x * d, y * d, z * d) );

};
template <class Real>
Vector3<Real>::~Vector3 (){};


#endif
