#ifndef LAL_INLINE_VECTOR2_HPP_
#define LAL_INLINE_VECTOR2_HPP_

#include<cassert>

template<class Real>
Vector2<Real>::Vector2 ()
{
	this->x = static_cast< Real > ( 0 );
	this->y = static_cast< Real > ( 0 );
};

template< class Real>
template< class T >
Vector2<Real>::Vector2 (const T* v )
{
	assert(v);

	this->x = static_cast< Real > ( v[0] );
	this->y = static_cast< Real > ( v[1] );

};

template<class Real>
Vector2<Real>::Vector2 ( const Vector2<Real>& v)
{
	this->x = v.x;
	this->y = v.y;
};

template<class Real>
Vector2<Real>::Vector2 ( const Real& x, const Real& y)
{
	this->x = x;
	this->y = y;
};


//Operator

template<class Real>
inline Real Vector2<Real>::operator[]( unsigned int index ) const
{
	assert( ( index >= 0 ) && ( index < 2 ) );

	return ( ( &x )[ index ] );

};

template<class Real>
inline Real& Vector2<Real>::operator []( unsigned int index ) 
{
	assert( ( index >= 0 ) && ( index < 2 ) );

	return ( ( &x )[ index ] );
};

// Assignment Opertators
//With Scalar

template<class Real>
inline Vector2<Real> Vector2<Real>::operator+()  const  
{
	return ( Vector2<Real> (this->x, this->y)  );
};

template<class Real>
inline Vector2<Real>  Vector2<Real>::operator-() const
{

	return ( Vector2<Real> (-this->x, -this->y) );

};

template<class Real>
inline Vector2< Real >& Vector2<Real>::operator+=( const Real&  factor ) 
{ 
	this->x += factor; 
	this->y += factor; 

	return ( *this ); 
} 

template<class Real>
inline Vector2< Real >& Vector2<Real>::operator-=( const Real&  factor ) 
{ 
	this->x -= factor; 
	this->y -= factor; 

	return ( *this ); 
} 

template<class Real>
inline Vector2< Real >& Vector2<Real>::operator*=( const Real& factor ) 
{ 

	this->x  *= factor;
	this->y  *= factor;

	return ( *this ); 
}

template<class Real>
inline Vector2< Real >& Vector2<Real>::operator/=( const Real& factor ) 
{ 
	Real f = (Real)1 / factor;

	this->x *= f;
	this->y *= f; 

	return ( *this ); 
}


template<class Real>
inline Vector2<Real> operator*( const Vector2<Real>& v, const Real& factor ) 	
{

	return ( Vector2<Real>( v.x * factor, v.y * factor ) );

};

template<class Real>
inline Vector2<Real> operator*( const Real& factor, const Vector2<Real>& v ) 
{
	return ( Vector2<Real>( v.x * factor, v.y * factor ) );

};

template<class Real>
inline Vector2<Real> operator/( const Vector2<Real>& v, const Real& factor ) 	
{

	return (  Vector2<Real>( v.x / factor, v.y / factor ) );

};

template<class Real>
inline Vector2<Real> operator+( const Real& factor, const Vector2<Real>& v )  
{
	return ( Vector2<Real> ( v.x + factor, v.y + factor ) );

};

template<class Real>
inline Vector2<Real> operator+( const Vector2<Real>& v, const Real& factor )  
{ 
	return ( Vector2<Real> ( v.x + factor, v.y + factor )	);

};

template<class Real>
inline Vector2<Real> operator-( const Real& factor, const Vector2<Real>& v )  
{
	return ( Vector2<Real> ( factor - v.x ,factor - v.y  ) );

};

template<class Real>
inline Vector2<Real> operator-( const Vector2<Real>& v, const Real& factor )  
{
	return ( Vector2<Real> ( v.x - factor,	v.y - factor ) );

};

// With Vector

template<class Real>
inline Vector2<Real>& Vector2<Real>::operator=( const Vector2<Real>& v )
{
	this->x = v.x;
	this->y = v.y;

	return ( *this );
};

template<class Real>
inline Vector2< Real >& Vector2<Real>::operator+=( const Vector2<Real>& v ) 
{ 
	this->x += v.x; 
	this->y += v.y;

	return ( *this ); 
}

template<class Real>
inline Vector2< Real >& Vector2<Real>::operator-=( const Vector2<Real>& v ) 
{ 
	this->x -= v.x; 
	this->y -= v.y;

	return ( *this ); 
} 

template<class Real>
inline Vector2< Real >& Vector2<Real>::operator/=( const Vector2<Real>& v ) 
{
	
	this->x /= v.x;
	this->y /= v.y;

	return ( *this ); 
} 

template<class Real>
inline bool Vector2<Real>::operator==( const Vector2<Real>& v ) const
{
	return ( ( this->x == v.x ) and ( this->y == v.y ) );
};	

template<class Real>
inline bool Vector2<Real>::operator!=( const Vector2<Real>& v ) const
{
	return  !(*this == v) ;
};	

template<class Real>
inline Vector2<Real>  Vector2<Real>::operator-( const Vector2<Real>& v ) const
{

	return ( Vector2 ( this->x - v.x, this->y - v.y ) );
};

template<class Real>
inline Vector2<Real>  Vector2<Real>::operator+( const Vector2<Real>& v ) const
{

	return ( Vector2 ( this->x + v.x, this->y + v.y) );

};

template<class Real>
inline Real Vector2<Real>::operator*( const Vector2<Real>& v) const	
{

	return (  (v.x * x ) +  ( v.y * y ) );

};


template<class Real>
inline std::ostream& operator<<( std::ostream & s, const Vector2<Real>& v )
{
	s << "Vector2" << " x = " << v.x() << " ,y = " << v.y() << std::endl;

	return s;
};

// AUXILIAR FUNCTIONS
template<class Real>
inline Real Vector2<Real>::Length( void )
{
	return sqrt( (this->x * this->x) + (this->y * this->y) );
};

template<class Real>
inline void Vector2<Real>::Normalize( void )
{
	Real factor = sqrt( (x * x) + (y * y) );

	assert (factor);

	Real lFactor = 1 / factor;

	x *= lFactor;
	y *= lFactor;


};

template<class Real>
inline Vector2<Real> Vector2<Real>::Norm( void )
{ 
	Real factor = sqrt( (x * x) + (y * y) );

	assert (factor);

	Real f = 1 / factor;

	return ( Vector2 (x * f, y * f) );

};

template<class Real>
inline const Real* Vector2<Real>::ToRealPtr( void ) const 
{
	return &x;
}

template<class Real>
inline Real* Vector2<Real>::ToRealPtr( void )
{
	return &x;
}

template <class Real>
Vector2<Real>::~Vector2 (){};


#endif
