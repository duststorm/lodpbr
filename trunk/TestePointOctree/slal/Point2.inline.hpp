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
Point2<Real>::Point2 ( const Real& x, const Real& y )
: x(x), y(y) {};


template<class Real>
Point2<Real>::Point2 ( const Vector2<Real>& vector)
: x(vector.x), y(vector.y) {};

template<class Real>
Point2<Real>::Point2 ( const Point2<Real>& point)
: x(point.x), y(point.y) {};

                                              
template<class Real>    
template < typename P >
Point2<Real>::Point2 (const P* point)
{
	assert(point);

	this->x = static_cast< Real > ( point[0] );
	this->y = static_cast< Real > ( point[1] );

};

//============================= ACESS ======================================


template<class Real>
inline Point2<Real>::operator Real * ()
{
	return xy;
}

template<class Real>
inline Point2<Real>::operator const Real * ()
{
	return xy;
}



template<class Real>
inline  Real Point2<Real>::operator [] ( unsigned int i)  const
{
	if ( i > 1 )
	{
		std::cerr << "[ERROR] Point2 operator[]"        << std::endl
		<< "        Out of the Point size. " << std::endl
		<< "        Accepts, 0 , 1 only." << std::endl;
		exit(1);
	}

	return (xy[i]);
};

template<class Real>
inline  Real& Point2<Real>::operator [] ( unsigned int i)  

{
	if ( i > 1 )
	{
		std::cerr << "[ERROR] Point2 operator[]"        << std::endl
		<< "        Out of the Point size. " << std::endl
		<< "        Accepts, 0 , 1 only." << std::endl;
		exit(1);
	}


	return (xy[i]);
};

//============================= OPERATORS ====================================


template<class Real>
inline Point2<Real> Point2<Real>::operator+ ( )  const  
{
	return ( Point2<Real> (this->x, this->y)  );
};


template<class Real>
inline Point2<Real>  Point2<Real>::operator- ( ) const
{

	return ( Point2<Real> (-this->x, -this->y) );

};


template<class Real>
const Point2< Real >& Point2<Real>::operator+= ( const Real&  factor )
{
	this->x += factor;
	this->y += factor;

	return ( *this );
}
         
template<class Real>
const Point2< Real >& Point2<Real>::operator-= ( const Real&  factor )
{
	this->x -= factor;
	this->y -= factor;

	return ( *this );
}

template<class Real>
const Point2< Real >& Point2<Real>::operator*= ( const Real& factor )
{

	this->x  *= factor;
	this->y  *= factor;

	return ( *this );
}

template<class Real>
const Point2< Real >& Point2<Real>::operator/= ( const Real& factor )
{
	Real lFactor = (Real)1 / factor;

	this->x *= lFactor;
	this->y *= lFactor;

	return ( *this );
}


template<class Real>
inline Point2<Real> operator+ (const Real& factor,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.x + factor, point.y + factor ) );

};

template<class Real>
inline Point2<Real> operator+ (const Point2<Real>& point, const Real& factor )   
{
	return ( Point2<Real> ( point.x + factor, point.y + factor ) );

};


template<class Real>
inline  Point2<Real> operator- (const Real& factor,const Point2<Real>& point )  
{
	return ( Point2<Real> ( factor - point.x , factor - point.y )
	);

};


template<class Real>
inline Point2<Real> operator- (const Point2<Real>& point, const Real& factor )  
{
	return ( Point2<Real> ( point.x - factor, point.y - factor ) );

};


template<class Real>
inline Point2<Real> operator* (const Real& factor,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.x * factor, point.y * factor ) );

};

template<class Real>
inline Point2<Real> operator* (const Point2<Real>& point, const Real& factor )   
{
	return ( Point2<Real> ( point.x * factor, point.y * factor ) );

};


template<class Real>
inline Point2<Real> Point2<Real>::operator/ ( const Real& factor )  const  
{
	return ( Point2<Real> ( x / factor, y/ factor ) );

};


template<class Real>
inline const Point2<Real>& Point2<Real>::operator= ( const Point2<Real>& point)
{
	this->x = point.x;
	this->y = point.y;

	return ( *this );
};



template<class Real>
const Point2< Real >& Point2<Real>::operator+= (  const Point2<Real>& point )
{
	this->x += point.x;
	this->y += point.y;

	return ( *this );
}

template<class Real>
const Point2<Real>& Point2<Real>::operator-= (  const Point2<Real>& point )
{
	this->x -= point.x;
	this->y -= point.y;

	return ( *this );
}


template<class Real>
const Point2<Real>& Point2<Real>::operator/= ( const Point2<Real>& point )
{

	this->x /= point.x;
	this->y /= point.y;

	return ( *this );
}

template<class Real>
inline bool Point2<Real>::operator== ( const Point2<Real>& p) const
{
	return ( ( this->x == p.x ) and ( this->y == p.y ) );
};      

template<class Real>
inline bool Point2<Real>::operator!= ( const Point2<Real>& point) const
{
	return  !(*this == point) ;
};      

     

template<class Real>
inline Vector2<Real> operator- (const Point2<Real>& source, const Point2<Real>& target)   
{
	return ( Vector2<Real>( 	source.x - target.x,  source.y - target.y ) );

};


template<class Real>
inline Point2<Real> operator- (const Point2<Real>& point, const Vector2<Real>& vector)   
{
	return ( Point2<Real>( point.x - vector.x, point.y - vector.y)  );
};


template<class Real>
inline Point2<Real> operator- (const Vector2<Real>& vector,const Point2<Real>& point )   
{

	return ( Point2<Real>( vector.x - point.x, vector.y - point.y ) );

};




template<class Real>
inline Point2<Real> Point2<Real>::operator+ (const Point2<Real>& point)  const 
{
	return ( Point2<Real>( x + point.x, y + point.y ) );

};



template<class Real>
inline Point2<Real> operator+ (const Point2<Real>& point, const Vector2<Real>& vector)   
{
	return ( Point2<Real> ( point.x + vector.x, point.y + vector.y ) );

};

template<class Real>
inline Point2<Real> operator+ (const Vector2<Real>& vector,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.x + vector.x, point.y + vector.y ) );

};

//============================= OPERATIONS ===================================


template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Point2<Real>& point)
{
	s << "Point2" << " x = " << point.x << " ,y = " << std::endl;


	return ( s );
};
           
template<class Real>
Real Point2<Real>::squaredDistance ( const Point2<Real>& point ) 
{
	return (  (point.x - this->x ) * ( point.x - this->x ) +  ( point.y - this->y) * ( point.y - this->y) );
}

#endif /*POINT2__INLINE_HPP_*/
