#ifndef LAL_VECTOR4_INLINE_HPP_
#define LAL_VECTOR4_INLINE_HPP_

//============================= LIFECYCLE ====================================

template<class Real>
Vector4<Real>::Vector4 ()
{
	this->mX = static_cast< Real > ( 0 );
	this->mY = static_cast< Real > ( 0 );
	this->mZ = static_cast< Real > ( 0 );
	this->mW = static_cast< Real > ( 1 );
};

template<class Real>
template < typename U >
Vector4<Real>::Vector4 (const U* u)
{
	assert(u);

	this->mX = static_cast< Real > ( u[0] );
	this->mY = static_cast< Real > ( u[1] );
	this->mZ = static_cast< Real > ( u[2] );
	this->mW = static_cast< Real > ( u[3] );

};

template<class Real>
Vector4<Real>::Vector4 ( const Vector4<Real>& vector)
{
	this->mX = vector.mX;
	this->mY = vector.mY;
	this->mZ = vector.mZ;
	this->mW = vector.mW;
};

template<class Real>
Vector4<Real>::Vector4 ( const Vector3<Real>& vector, const Real& w)
{
	this->mX = vector.mX;
	this->mY = vector.mY;
	this->mZ = vector.mZ;
	this->mW = w;
};

template<class Real>
Vector4<Real>::Vector4 ( const Vector3<Real>& vector)
{
	this->mX = vector.mX;
	this->mY = vector.mY;
	this->mZ = vector.mZ;
	this->mW = static_cast< Real > (1);
};

template<class Real>
Vector4<Real>::Vector4 ( const Real& pX, const Real& pY, const Real& pZ, const Real& pW)
{
	this->mX = pX;
	this->mY = pY;
	this->mZ = pZ;
	this->mW = pW;
};

//============================= ACESS ======================================

//Gets and Sets
template<class Real>
inline Real Vector4<Real>::x() const
{
	return ( this->mX );
};

template<class Real>
inline Real Vector4<Real>::y() const
{
	return ( this->mY );
};

template<class Real>
inline Real Vector4<Real>::z() const
{
	return ( this->mZ );
};

template<class Real>
inline Real Vector4<Real>::w() const
{
	return ( this->mW );
};

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
	return ( Vector4<Real> (this->mX, this->mY, this->mZ, this->mW)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point3.
 */
template<class Real>
inline Vector4<Real>  Vector4<Real>::operator- ( ) const
{

	return ( Vector4<Real> (-this->mX, -this->mY, -this->mZ, -this->mW) );

};

template<class Real>
const Vector4< Real >& Vector4<Real>::operator+= ( const Real&  factor ) 
{ 
	this->mX += factor; 
	this->mY += factor; 
	this->mZ += factor;
	this->mW += factor;

	return ( *this ); 
} 

template<class Real>
const Vector4< Real >& Vector4<Real>::operator-= ( const Real&  factor ) 
{ 
	this->mX -= factor; 
	this->mY -= factor; 
	this->mZ -= factor;
	this->mW -= factor;

	return ( *this ); 
} 

template<class Real>
const Vector4< Real >& Vector4<Real>::operator*= ( const Real& factor ) 
{ 

	this->mX  *= factor;
	this->mY  *= factor;
	this->mZ  *= factor;
	this->mW  *= factor;

	return ( *this ); 
}

template<class Real>
const Vector4< Real >& Vector4<Real>::operator/= ( const Real& factor ) 
{ 
	Real lFactor = (Real)1 / factor;

	this->mX *= lFactor;
	this->mY *= lFactor; 
	this->mZ *= lFactor;
	this->mW *= lFactor;

	return ( *this ); 
}


template<class Real>
inline Vector4<Real> operator* ( const Vector4<Real>& vector, const Real& factor ) 	
{

	return (  Vector4<Real>( vector.mX * factor,
			vector.mY * factor,
			vector.mZ * factor,
			vector.mW * factor) 
	);

};

template<class Real>
inline Vector4<Real> operator*	( const Real& factor, const Vector4<Real>& vector ) 
{
	return ( Vector4<Real>( vector.mX * factor,
			vector.mY * factor,
			vector.mZ * factor,
			vector.mW * factor)
	);

};

template<class Real>
inline Vector4<Real> operator/ ( const Vector4<Real>& vector, const Real& factor ) 	
{

	return (  Vector4<Real>( vector.mX / factor,
			vector.mY / factor,
			vector.mZ / factor,
			vector.mW / factor) 
	);

};

template<class Real>
inline Vector4<Real> operator+ (const Real& factor, const Vector4<Real>& vector )  
{
	return ( Vector4<Real> ( vector.mX + factor,
			vector.mY + factor,
			vector.mZ + factor,
			vector.mW + factor)
	);

};

template<class Real>
inline Vector4<Real> operator+ (const Vector4<Real>& vector, const Real& factor )  
{
	return ( Vector4<Real> ( vector.mX + factor,
			vector.mY + factor,
			vector.mZ + factor,
			vector.mW + factor)
	);

};

template<class Real>
inline Vector4<Real> operator- (const Real& factor, const Vector4<Real>& vector )  
{
	return ( Vector4<Real> ( factor - vector.mX ,
			factor - vector.mY,
			factor - vector.mZ,
			factor - vector.mW)
	);

};

template<class Real>
inline Vector4<Real> operator- (const Vector4<Real>& vector, const Real& factor )  
{
	return ( Vector4<Real> ( vector.mX - factor,
			vector.mY - factor,
			vector.mZ - factor,
			vector.mW - factor)
	);

};

// With Vector

template<class Real>
inline const Vector4<Real>& Vector4<Real>::operator= ( const Vector4<Real>& vector )
{
	this->mX = vector.mX;
	this->mY = vector.mY;
	this->mZ = vector.mZ;
	this->mW = vector.mW;

	return ( *this );
};

template<class Real>
const Vector4< Real >& Vector4<Real>::operator+= (  const Vector4<Real>& vector ) 
{ 
	this->mX += vector.mX; 
	this->mY += vector.mY; 
	this->mZ += vector.mZ;
	this->mW += vector.mW;

	return ( *this ); 
}

template<class Real>
const Vector4< Real >& Vector4<Real>::operator-= (  const Vector4<Real>& vector ) 
{ 
	this->mX -= vector.mX; 
	this->mY -= vector.mY; 
	this->mZ -= vector.mZ;
	this->mW -= vector.mW;

	return ( *this ); 
} 

template<class Real>
const Vector4< Real >& Vector4<Real>::operator/= ( const Vector4<Real>& vector ) 
{ 

	this->mX /= vector.mX;
	this->mY /= vector.mY; 
	this->mZ /= vector.mZ;
	this->mW /= vector.mW;

	return ( *this ); 
} 

template<class Real>
inline bool Vector4<Real>::operator== ( const Vector4<Real>& vector) const
{
	return ( ( this->mX == vector.mX ) and ( this->mY == vector.mY ) and ( this->mZ == vector.mZ ) and (this->mW == vector.mW) );
};	

template<class Real>
inline bool Vector4<Real>::operator!= ( const Vector4<Real>& vector) const
{
	return  !(*this == vector) ;
};	

template<class Real>
inline Vector4<Real>  Vector4<Real>::operator- ( const Vector4<Real>& vector) const
{

	return ( Vector4 ( this->mX - vector.mX,
			this->mY - vector.mY,
			this->mZ - vector.mZ,
			this->mW - vector.mW) 
	);
};

template<class Real>
inline Vector4<Real>  Vector4<Real>::operator+ ( const Vector4<Real>& vector)	const
{

	return ( Vector4 ( this->mX + vector.mX,
			this->mY + vector.mY,
			this->mZ + vector.mZ,
			this->mW + vector.mW)
	);

};

// Dot produt
template<class Real>
inline Real Vector4<Real>::operator* ( const Vector4<Real>& vector) const	
{

	return (  (vector.mX * mX ) +  ( vector.mY * mY ) + ( vector.mZ * mZ ) + (vector.mW * mW) );

};


template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Vector4<Real>& vector)
{
	s << "Vector4" << "  x = " << vector.mX 
				   << " ,y = " << vector.mY 
				   << " ,z = " << vector.mZ 
				   << " ,w = " << vector.mW << std::endl;

	return s;
};

//============================= OPERATIONS ===================================

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector4<Real>::length ()
{
	return sqrt( (this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ) + (this->mW * this->mW) );
};

template<class Real>
inline void Vector4<Real>::normalize ()
{
	Real factor = sqrt( (mX * mX) + (mY * mY) + (mZ * mZ) + (mW * mW) );

	assert (factor);

	Real lFactor = 1 / factor;

	mX *= lFactor;
	mY *= lFactor;
	mZ *= lFactor;
	mW *= lFactor;

};

template<class Real>
inline Vector4<Real> Vector4<Real>::norm ()
{
	Real factor = sqrt( (mX * mX) + (mY * mY) + (mZ * mZ) + (mW * mW) );

	assert (factor);

	Real lFactor = 1 / factor;

	return ( Vector4 (mX * lFactor, mY * lFactor, mZ * lFactor, mW * lFactor) );

};
template <class Real>
Vector4<Real>::~Vector4 (){};
	
#endif
