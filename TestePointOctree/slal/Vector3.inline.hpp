#ifndef LAL_VECTOR3_INLINE_HPP_
#define LAL_VECTOR3_INLINE_HPP_

//============================= LIFECYCLE ====================================

template<class Real>
Vector3<Real>::Vector3 ()
{
	this->mX = static_cast< Real > ( 0 );
	this->mY = static_cast< Real > ( 0 );
	this->mZ = static_cast< Real > ( 0 );
};

template<class Real>
template < typename U >
Vector3<Real>::Vector3 (const U* u)
{
	assert(u);

	this->mX = static_cast< Real > ( u[0] );
	this->mY = static_cast< Real > ( u[1] );
	this->mZ = static_cast< Real > ( u[2] );

};

template<class Real>
template < typename U >
Vector3<Real>::Vector3 ( const Vector3<U>& vector)
{
	this->mX = static_cast< Real > (vector.mX);
	this->mY = static_cast< Real > (vector.mY);
	this->mZ = static_cast< Real > (vector.mZ);
};


template<class Real>
Vector3<Real>::Vector3 ( const Vector3<Real>& vector)
{
	this->mX = vector.mX;
	this->mY = vector.mY;
	this->mZ = vector.mZ;
};

template<class Real>
Vector3<Real>::Vector3 ( const Real& pX, const Real& pY, const Real& pZ )
{
	this->mX = pX;
	this->mY = pY;
	this->mZ = pZ;
};

//============================= ACESS ======================================

//Gets and Sets
template<class Real>
inline Real Vector3<Real>::x() const
{
	return ( this->mX );
};

template<class Real>
inline Real Vector3<Real>::y() const
{
	return ( this->mY );
};

template<class Real>
inline Real Vector3<Real>::z() const
{
	return ( this->mZ );
};

template<class Real>
inline void Vector3<Real>::Set(const Real& x, const Real& y, const Real& z) 
{
	this->mX = x;
	this->mY = y;
	this->mZ = z;
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
	return ( Vector3<Real> (this->mX, this->mY, this->mZ)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point3.
 */
template<class Real>
inline Vector3<Real>  Vector3<Real>::operator- ( ) const
{

	return ( Vector3<Real> (-this->mX, -this->mY, -this->mZ) );

};

template<class Real>
const Vector3< Real >& Vector3<Real>::operator+= ( const Real&  factor ) 
{ 
	this->mX += factor; 
	this->mY += factor; 
	this->mZ += factor;

	return ( *this ); 
} 

template<class Real>
const Vector3< Real >& Vector3<Real>::operator-= ( const Real&  factor ) 
{ 
	this->mX -= factor; 
	this->mY -= factor; 
	this->mZ -= factor;

	return ( *this ); 
} 

template<class Real>
const Vector3< Real >& Vector3<Real>::operator*= ( const Real& factor ) 
{ 

	this->mX  *= factor;
	this->mY  *= factor;
	this->mZ  *= factor;

	return ( *this ); 
}

template<class Real>
const Vector3< Real >& Vector3<Real>::operator/= ( const Real& factor ) 
{ 
	Real lFactor = (Real)1 / factor;

	this->mX *= lFactor;
	this->mY *= lFactor; 
	this->mZ *= lFactor;

	return ( *this ); 
}


template<class Real>
inline Vector3<Real> operator* ( const Vector3<Real>& vector, const Real& factor ) 	
{

	return (  Vector3<Real>( vector.mX * factor,
			vector.mY * factor,
			vector.mZ * factor ) 
	);

};

template<class Real>
inline Vector3<Real> operator*	( const Real& factor, const Vector3<Real>& vector ) 
{
	return ( Vector3<Real>( vector.mX * factor,
			vector.mY * factor,
			vector.mZ * factor )
	);

};

template<class Real>
inline Vector3<Real> operator/ ( const Vector3<Real>& vector, const Real& factor ) 	
{

	return (  Vector3<Real>( vector.mX / factor,
			vector.mY / factor,
			vector.mZ / factor ) 
	);

};

template<class Real>
inline Vector3<Real> operator+ (const Real& factor, const Vector3<Real>& vector )  
{
	return ( Vector3<Real> ( vector.mX + factor,
			vector.mY + factor,
			vector.mZ + factor )
	);

};

template<class Real>
inline Vector3<Real> operator+ (const Vector3<Real>& vector, const Real& factor )  
{
	return ( Vector3<Real> ( vector.mX + factor,
			vector.mY + factor,
			vector.mZ + factor )
	);

};

template<class Real>
inline Vector3<Real> operator- (const Real& factor, const Vector3<Real>& vector )  
{
	return ( Vector3<Real> ( factor - vector.mX ,
			factor - vector.mY ,
			factor - vector.mZ  )
	);

};

template<class Real>
inline Vector3<Real> operator- (const Vector3<Real>& vector, const Real& factor )  
{
	return ( Vector3<Real> ( vector.mX - factor,
			vector.mY - factor,
			vector.mZ - factor )
	);

};

// With Vector

template<class Real>
inline const Vector3<Real>& Vector3<Real>::operator= ( const Vector3<Real>& vector )
{
	this->mX = vector.mX;
	this->mY = vector.mY;
	this->mZ = vector.mZ;

	return ( *this );
};

template<class Real>
const Vector3< Real >& Vector3<Real>::operator+= (  const Vector3<Real>& vector ) 
{ 
	this->mX += vector.mX; 
	this->mY += vector.mY; 
	this->mZ += vector.mZ;

	return ( *this ); 
}

template<class Real>
const Vector3< Real >& Vector3<Real>::operator-= (  const Vector3<Real>& vector ) 
{ 
	this->mX -= vector.mX; 
	this->mY -= vector.mY; 
	this->mZ -= vector.mZ;

	return ( *this ); 
} 

template<class Real>
const Vector3< Real >& Vector3<Real>::operator/= ( const Vector3<Real>& vector ) 
{ 

	this->mX /= vector.mX;
	this->mY /= vector.mY; 
	this->mZ /= vector.mZ;

	return ( *this ); 
} 

template<class Real>
inline bool Vector3<Real>::operator== ( const Vector3<Real>& vector) const
{
	return ( ( this->mX == vector.mX ) and ( this->mY == vector.mY ) and ( this->mZ == vector.mZ ) );
};	

template<class Real>
inline bool Vector3<Real>::operator!= ( const Vector3<Real>& vector) const
{
	return  !(*this == vector) ;
};	

template<class Real>
inline Vector3<Real>  Vector3<Real>::operator- ( const Vector3<Real>& vector) const
{

	return ( Vector3 ( this->mX - vector.mX,
			this->mY - vector.mY,
			this->mZ - vector.mZ) 
	);
};

template<class Real>
inline Vector3<Real>  Vector3<Real>::operator+ ( const Vector3<Real>& vector)	const
{

	return ( Vector3 ( this->mX + vector.mX,
			this->mY + vector.mY,
			this->mZ + vector.mZ)
	);

};

template<class Real>
inline Real Vector3<Real>::operator* ( const Vector3<Real>& vector) const	
{

	return (  (vector.mX * mX ) +  ( vector.mY * mY ) + ( vector.mZ * mZ )  );

};

// Cross Product
template<class Real>
inline Vector3<Real>  Vector3<Real>::operator^ (const Vector3<Real>& vector) const
{
	return ( Vector3<Real> ( 	mY*vector.z() - mZ*vector.y(),
			mZ*vector.x() - mX*vector.z(),
			mX*vector.y() - mY*vector.x())
	);

};

//============================= OPERATIONS ===================================

template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Vector3<Real>& vector)
{
	s << "Vector3"<< " x = " << vector.mX << " ,y = " << vector.mY << " ,z = " << vector.mZ << std::endl;

	return s;
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector3<Real>::length ()
{
	return sqrt( (this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ) );
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector3<Real>::length2 ()
{
	return ( (this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ) );
};


template<class Real>
inline void Vector3<Real>::normalize ()
{
	Real factor = sqrt( (mX * mX) + (mY * mY) + (mZ * mZ) );

	if (factor <= static_cast<Real>(0))
	{

	}
	else{
		Real d = 1 / factor;

		mX *= d;
		mY *= d;
		mZ *= d;


	}

};

template<class Real>
inline Vector3<Real> Vector3<Real>::norm ()
{
	Real factor = sqrt( (mX * mX) + (mY * mY) + (mZ * mZ) );

	if (factor <= static_cast<Real>(0))
		return ( Vector3 (mX, mY, mZ) );


	Real d = 1 / factor;

	return ( Vector3<Real> (mX * d, mY * d, mZ * d) );

};
template <class Real>
Vector3<Real>::~Vector3 (){};


#endif
