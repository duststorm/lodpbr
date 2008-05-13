#ifndef LAL_INLINE_VECTOR2_HPP_
#define LAL_INLINE_VECTOR2_HPP_

template<class Real>
Vector2<Real>::Vector2 ()
{
	this->x = static_cast< Real > ( 0 );
	this->y = static_cast< Real > ( 0 );
};

template<class Real>
template < typename U >
Vector2<Real>::Vector2 (const U* u)
{
	assert(u);

	this->x = static_cast< Real > ( u[0] );
	this->y = static_cast< Real > ( u[1] );

};

template<class Real>
Vector2<Real>::Vector2 ( const Vector2<Real>& u)
{
	this->x = u.x;
	this->y = u.y;
};

template<class Real>
Vector2<Real>::Vector2 ( const Real& pX, const Real& pY)
{
	this->x = pX;
	this->y = pY;
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
	return ( Vector2<Real> (this->x, this->y)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point3.
 */
template<class Real>
inline Vector2<Real>  Vector2<Real>::operator- ( ) const
{

	return ( Vector2<Real> (-this->x, -this->y) );

};

template<class Real>
const Vector2< Real >& Vector2<Real>::operator+= ( const Real&  factor ) 
{ 
	this->x += factor; 
	this->y += factor; 

	return ( *this ); 
} 

template<class Real>
const Vector2< Real >& Vector2<Real>::operator-= ( const Real&  factor ) 
{ 
	this->x -= factor; 
	this->y -= factor; 

	return ( *this ); 
} 

template<class Real>
const Vector2< Real >& Vector2<Real>::operator*= ( const Real& factor ) 
{ 

	this->x  *= factor;
	this->y  *= factor;

	return ( *this ); 
}

template<class Real>
const Vector2< Real >& Vector2<Real>::operator/= ( const Real& factor ) 
{ 
	Real lFactor = (Real)1 / factor;

	this->x *= lFactor;
	this->y *= lFactor; 

	return ( *this ); 
}


template<class Real>
inline Vector2<Real> operator* ( const Vector2<Real>& u, const Real& factor ) 	
{

	return (  Vector2<Real>( u.x * factor, u.y * factor ) );

};

template<class Real>
inline Vector2<Real> operator*	( const Real& factor, const Vector2<Real>& u ) 
{
	return ( Vector2<Real>( u.x * factor, u.y * factor )
	);

};

template<class Real>
inline Vector2<Real> operator/ ( const Vector2<Real>& u, const Real& factor ) 	
{

	return (  Vector2<Real>( u.x / factor, u.y / factor ) );

};

template<class Real>
inline Vector2<Real> operator+ (const Real& factor, const Vector2<Real>& u )  
{
	return ( Vector2<Real> ( u.x + factor, u.y + factor ) );

};

template<class Real>
inline Vector2<Real> operator+ (const Vector2<Real>& u, const Real& factor )  
{
	return ( Vector2<Real> ( u.x + factor, u.y + factor )	);

};

template<class Real>
inline Vector2<Real> operator- (const Real& factor, const Vector2<Real>& u )  
{
	return ( Vector2<Real> ( factor - u.x ,factor - u.y  ) );

};

template<class Real>
inline Vector2<Real> operator- (const Vector2<Real>& u, const Real& factor )  
{
	return ( Vector2<Real> ( u.x - factor,	u.y - factor ) );

};

// With Vector

template<class Real>
inline const Vector2<Real>& Vector2<Real>::operator= ( const Vector2<Real>& u )
{
	this->x = u.x;
	this->y = u.y;

	return ( *this );
};

template<class Real>
const Vector2< Real >& Vector2<Real>::operator+= (  const Vector2<Real>& u ) 
{ 
	this->x += u.x; 
	this->y += u.y;

	return ( *this ); 
}

template<class Real>
const Vector2< Real >& Vector2<Real>::operator-= (  const Vector2<Real>& u ) 
{ 
	this->x -= u.x; 
	this->y -= u.y;

	return ( *this ); 
} 

template<class Real>
const Vector2< Real >& Vector2<Real>::operator/= ( const Vector2<Real>& u ) 
{ 

	this->x /= u.x;
	this->y /= u.y;

	return ( *this ); 
} 

template<class Real>
inline bool Vector2<Real>::operator== ( const Vector2<Real>& u) const
{
	return ( ( this->x == u.x ) and ( this->y == u.y ) );
};	

template<class Real>
inline bool Vector2<Real>::operator!= ( const Vector2<Real>& u) const
{
	return  !(*this == u) ;
};	

template<class Real>
inline Vector2<Real>  Vector2<Real>::operator- ( const Vector2<Real>& u) const
{

	return ( Vector2 ( this->x - u.x, this->y - u.y ) );
};

template<class Real>
inline Vector2<Real>  Vector2<Real>::operator+ ( const Vector2<Real>& u)	const
{

	return ( Vector2 ( this->x + u.x, this->y + u.y) );

};

template<class Real>
inline Real Vector2<Real>::operator* ( const Vector2<Real>& u) const	
{

	return (  (u.x * x ) +  ( u.y * y ) );

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
	return sqrt( (this->x * this->x) + (this->y * this->y) );
};

template<class Real>
inline void Vector2<Real>::normalize ()
{
	Real factor = sqrt( (x * x) + (y * y) );

	assert (factor);

	Real lFactor = 1 / factor;

	x *= lFactor;
	y *= lFactor;


};

template<class Real>
inline Vector2<Real> Vector2<Real>::norm ()
{
	Real factor = sqrt( (x * x) + (y * y) );

	assert (factor);

	Real lFactor = 1 / factor;

	return ( Vector2 (x * lFactor, y * lFactor) );

};
template <class Real>
Vector2<Real>::~Vector2 (){};


#endif
