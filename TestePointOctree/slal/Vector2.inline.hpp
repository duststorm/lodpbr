#ifndef LAL_INLINE_VECTOR2_HPP_
#define LAL_INLINE_VECTOR2_HPP_

template<class Real>
Vector2<Real>::Vector2 ()
{
	this->mX = static_cast< Real > ( 0 );
	this->mY = static_cast< Real > ( 0 );
};

template<class Real>
template < typename U >
Vector2<Real>::Vector2 (const U* u)
{
	assert(u);

	this->mX = static_cast< Real > ( u[0] );
	this->mY = static_cast< Real > ( u[1] );

};

template<class Real>
Vector2<Real>::Vector2 ( const Vector2<Real>& u)
{
	this->mX = u.mX;
	this->mY = u.mY;
};

template<class Real>
Vector2<Real>::Vector2 ( const Real& pX, const Real& pY)
{
	this->mX = pX;
	this->mY = pY;
};

//Gets and Sets
template<class Real>
inline Real Vector2<Real>::x() const
{
	return ( this->mX );
};

template<class Real>
inline Real Vector2<Real>::y() const
{
	return ( this->mY );
};

//Operator

template<class Real>
inline Vector2<Real>::operator Real * ()
{
	return xy;
}

template<class Real>
inline Vector2<Real>::operator const Real * ()
{
	return xy;
}

template<class Real>
inline Real Vector2<Real>::operator [] ( unsigned int i) const
{
	if ( i > 1)
	{
		std::cerr << "[ERROR] Vector2 operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}

	return (xy[i]);

};

template<class Real>
inline Real& Vector2<Real>::operator [] ( unsigned int i) 
{
	if ( i > 1)
	{
		std::cerr << "[ERROR] Vector2 operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}


	return (xy[i]);

};

// Assignment Opertators
//With Scalar

template<class Real>
inline Vector2<Real> Vector2<Real>::operator+ ( )  const  
{
	return ( Vector2<Real> (this->mX, this->mY)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point3.
 */
template<class Real>
inline Vector2<Real>  Vector2<Real>::operator- ( ) const
{

	return ( Vector2<Real> (-this->mX, -this->mY) );

};

template<class Real>
const Vector2< Real >& Vector2<Real>::operator+= ( const Real&  factor ) 
{ 
	this->mX += factor; 
	this->mY += factor; 

	return ( *this ); 
} 

template<class Real>
const Vector2< Real >& Vector2<Real>::operator-= ( const Real&  factor ) 
{ 
	this->mX -= factor; 
	this->mY -= factor; 

	return ( *this ); 
} 

template<class Real>
const Vector2< Real >& Vector2<Real>::operator*= ( const Real& factor ) 
{ 

	this->mX  *= factor;
	this->mY  *= factor;

	return ( *this ); 
}

template<class Real>
const Vector2< Real >& Vector2<Real>::operator/= ( const Real& factor ) 
{ 
	Real lFactor = (Real)1 / factor;

	this->mX *= lFactor;
	this->mY *= lFactor; 

	return ( *this ); 
}


template<class Real>
inline Vector2<Real> operator* ( const Vector2<Real>& u, const Real& factor ) 	
{

	return (  Vector2<Real>( u.mX * factor, u.mY * factor ) );

};

template<class Real>
inline Vector2<Real> operator*	( const Real& factor, const Vector2<Real>& u ) 
{
	return ( Vector2<Real>( u.mX * factor, u.mY * factor )
	);

};

template<class Real>
inline Vector2<Real> operator/ ( const Vector2<Real>& u, const Real& factor ) 	
{

	return (  Vector2<Real>( u.mX / factor, u.mY / factor ) );

};

template<class Real>
inline Vector2<Real> operator+ (const Real& factor, const Vector2<Real>& u )  
{
	return ( Vector2<Real> ( u.mX + factor, u.mY + factor ) );

};

template<class Real>
inline Vector2<Real> operator+ (const Vector2<Real>& u, const Real& factor )  
{
	return ( Vector2<Real> ( u.mX + factor, u.mY + factor )	);

};

template<class Real>
inline Vector2<Real> operator- (const Real& factor, const Vector2<Real>& u )  
{
	return ( Vector2<Real> ( factor - u.mX ,factor - u.mY  ) );

};

template<class Real>
inline Vector2<Real> operator- (const Vector2<Real>& u, const Real& factor )  
{
	return ( Vector2<Real> ( u.mX - factor,	u.mY - factor ) );

};

// With Vector

template<class Real>
inline const Vector2<Real>& Vector2<Real>::operator= ( const Vector2<Real>& u )
{
	this->mX = u.mX;
	this->mY = u.mY;

	return ( *this );
};

template<class Real>
const Vector2< Real >& Vector2<Real>::operator+= (  const Vector2<Real>& u ) 
{ 
	this->mX += u.mX; 
	this->mY += u.mY;

	return ( *this ); 
}

template<class Real>
const Vector2< Real >& Vector2<Real>::operator-= (  const Vector2<Real>& u ) 
{ 
	this->mX -= u.mX; 
	this->mY -= u.mY;

	return ( *this ); 
} 

template<class Real>
const Vector2< Real >& Vector2<Real>::operator/= ( const Vector2<Real>& u ) 
{ 

	this->mX /= u.mX;
	this->mY /= u.mY;

	return ( *this ); 
} 

template<class Real>
inline bool Vector2<Real>::operator== ( const Vector2<Real>& u) const
{
	return ( ( this->mX == u.mX ) and ( this->mY == u.mY ) );
};	

template<class Real>
inline bool Vector2<Real>::operator!= ( const Vector2<Real>& u) const
{
	return  !(*this == u) ;
};	

template<class Real>
inline Vector2<Real>  Vector2<Real>::operator- ( const Vector2<Real>& u) const
{

	return ( Vector2 ( this->mX - u.mX, this->mY - u.mY ) );
};

template<class Real>
inline Vector2<Real>  Vector2<Real>::operator+ ( const Vector2<Real>& u)	const
{

	return ( Vector2 ( this->mX + u.mX, this->mY + u.mY) );

};

template<class Real>
inline Real Vector2<Real>::operator* ( const Vector2<Real>& u) const	
{

	return (  (u.mX * mX ) +  ( u.mY * mY ) );

};


template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Vector2<Real>& u)
{
	s << "Vector2" << " x = " << u.x() << " ,y = " << u.y() << std::endl;

	return s;
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector2<Real>::length ()
{
	return sqrt( (this->mX * this->mX) + (this->mY * this->mY) );
};

template<class Real>
inline void Vector2<Real>::normalize ()
{
	Real factor = sqrt( (mX * mX) + (mY * mY) );

	assert (factor);

	Real lFactor = 1 / factor;

	mX *= lFactor;
	mY *= lFactor;


};

template<class Real>
inline Vector2<Real> Vector2<Real>::norm ()
{
	Real factor = sqrt( (mX * mX) + (mY * mY) );

	assert (factor);

	Real lFactor = 1 / factor;

	return ( Vector2 (mX * lFactor, mY * lFactor) );

};
template <class Real>
Vector2<Real>::~Vector2 (){};


#endif
