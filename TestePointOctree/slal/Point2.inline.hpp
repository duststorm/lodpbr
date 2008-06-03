#ifndef LAL_POINT2_INLINE_HPP_
#define LAL_POINT2_INLINE_HPP_



//============================= LIFECYCLE ====================================

template<class Real>
Point2<Real>::Point2()
{
	this->x 		= static_cast< Real > (0);
	this->y 		= static_cast< Real > (0);
};


template<class Real>
Point2<Real>::Point2( const Real& x, const Real& y )
: x(x), y(y) {};


template<class Real>
Point2<Real>::Point2( const Vector2<Real>& v )
: x(v.x), y(v.y) {};

template<class Real>
Point2<Real>::Point2( const Point2<Real>& p )
: x(p.x), y(p.y) {};

                                              
template< class Real>    
template <class T >
Point2<Real>::Point2 (const T* point)
{
	assert(point);

	this->x = static_cast< Real > ( point[0] );
	this->y = static_cast< Real > ( point[1] );

};

template<class Real>
inline void Point3<Real>::Set( const Real& x, const Real& y ) 
{
	this->x = x;
	this->y = y;
};


//============================= ACESS ======================================


template<class Real>
inline  Real Point2<Real>::operator[]( unsigned int index )  const
{
	if ( index > 1 )
	{
		std::cerr << "[ERROR] Point2 operator[]"        << std::endl
		<< "        Out of the Point size. " << std::endl
		<< "        Accepts, 0 , 1 only." << std::endl;
		exit(1);
	}

	return ( ( &x )[ index ] );
};

template<class Real>
inline  Real& Point2<Real>::operator[]( unsigned int index )  

{
	if ( index > 1 )
	{
		std::cerr << "[ERROR] Point2 operator[]"        << std::endl
		<< "        Out of the Point size. " << std::endl
		<< "        Accepts, 0 , 1 only." << std::endl;
		exit(1);
	}


	return ( ( &x )[ index ] );
};

//============================= OPERATORS ====================================


template<class Real>
inline Point2<Real> Point2<Real>::operator+()  const  
{
	return ( Point2<Real> (this->x, this->y)  );
};


template<class Real>
inline Point2<Real>  Point2<Real>::operator-() const
{

	return ( Point2<Real> (-this->x, -this->y) );

};


template<class Real>
inline Point2< Real >& Point2<Real>::operator+=( const Real&  factor )
{
	this->x += factor;
	this->y += factor;

	return ( *this );
}
         
template<class Real>
inline Point2< Real >& Point2<Real>::operator-=( const Real&  factor )
{
	this->x -= factor;
	this->y -= factor;

	return ( *this );
}

template<class Real>
inline Point2< Real >& Point2<Real>::operator*=( const Real& factor )
{

	this->x  *= factor;
	this->y  *= factor;

	return ( *this );
}

template<class Real>
inline Point2< Real >& Point2<Real>::operator/=( const Real& factor )
{
	Real lFactor = (Real)1 / factor;

	this->x *= lFactor;
	this->y *= lFactor;

	return ( *this );
}


template<class Real>
inline Point2<Real> operator+( const Real& factor,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.x + factor, point.y + factor ) );

};

template<class Real>
inline Point2<Real> operator+( const Point2<Real>& point, const Real& factor )   
{
	return ( Point2<Real> ( point.x + factor, point.y + factor ) );

};


template<class Real>
inline  Point2<Real> operator-( const Real& factor,const Point2<Real>& p )  
{
	return ( Point2<Real> ( factor - p.x , factor - p.y )
	);

};


template<class Real>
inline Point2<Real> operator-( const Point2<Real>& p, const Real& factor )  
{
	return ( Point2<Real> ( p.x - factor, p.y - factor ) );

};


template<class Real>
inline Point2<Real> operator*( const Real& factor,const Point2<Real>& p )   
{
	return ( Point2<Real> ( p.x * factor, p.y * factor ) );

};

template<class Real>
inline Point2<Real> operator*( const Point2<Real>& p, const Real& factor )   
{
	return ( Point2<Real> ( p.x * factor, p.y * factor ) );

};


template<class Real>
inline Point2<Real> Point2<Real>::operator/( const Real& factor )  const  
{
	return ( Point2<Real> ( x / factor, y/ factor ) );

};


template<class Real>
inline Point2<Real>& Point2<Real>::operator=( const Point2<Real>& p )
{
	this->x = p.x;
	this->y = p.y;

	return ( *this );
};



template<class Real>
inline Point2< Real >& Point2<Real>::operator+=( const Point2<Real>& p )
{
	this->x += p.x;
	this->y += p.y;

	return ( *this );
}

template<class Real>
inline Point2<Real>& Point2<Real>::operator-=( const Point2<Real>& p )
{
	this->x -= p.x;
	this->y -= p.y;

	return ( *this );
}


template<class Real>
inline Point2<Real>& Point2<Real>::operator/=( const Point2<Real>& p )
{

	this->x /= p.x;
	this->y /= p.y;

	return ( *this );
}

template<class Real>
inline bool Point2<Real>::operator==( const Point2<Real>& p ) const
{
	return ( ( this->x == p.x ) and ( this->y == p.y ) );
};      

template<class Real>
inline bool Point2<Real>::operator!=( const Point2<Real>& p ) const
{
	return  !(*this == p) ;
};      

     

template<class Real>
inline Vector2<Real> operator-( const Point2<Real>& source, const Point2<Real>& target )   
{
	return ( Vector2<Real>( source.x - target.x,  source.y - target.y ) );

};


template<class Real>
inline Point2<Real> operator-( const Point2<Real>& p, const Vector2<Real>& v )   
{
	return ( Point2<Real>( p.x - v.x, p.y - v.y)  );
};


template<class Real>
inline Point2<Real> operator-( const Vector2<Real>& v,const Point2<Real>& p )   
{

	return ( Point2<Real>( v.x - p.x, v.y - p.y ) );

};

template<class Real>
inline Point2<Real> Point2<Real>::operator+( const Point2<Real>& p )  const 
{
	return ( Point2<Real>( x + p.x, y + p.y ) );

};


template<class Real>
inline Point2<Real> operator+( const Point2<Real>& p, const Vector2<Real>& v )   
{
	return ( Point2<Real> ( p.x + v.x, p.y + v.y ) );

};

template<class Real>
inline Point2<Real> operator+( const Vector2<Real>& v,const Point2<Real>& p )   
{
	return ( Point2<Real> ( p.x + v.x, p.y + v.y ) );

};

//============================= OPERATIONS ===================================


template<class Real>
inline std::ostream& operator<<( std::ostream & s, const Point2<Real>& point )
{
	s << "Point2" << " x = " << point.x << " ,y = " << std::endl;


	return ( s );
};
           
template<class Real>
Real Point2<Real>::SquaredDistance( const Point2<Real>& p ) 
{
	return (  (p.x - this->x ) * ( p.x - this->x ) +  ( p.y - this->y) * ( p.y - this->y) );
}

template<class Real>
inline const Real* Point2<Real>::ToRealPtr( void ) const 
{
	return &x;
}

template<class Real>
inline Real* Point2<Real>::ToRealPtr( void )
{
	return &x;
}

#endif /*POINT2__INLINE_HPP_*/
