#ifndef LAL_POINT2_INLINE_HPP_
#define LAL_POINT2_INLINE_HPP_



//============================= LIFECYCLE ====================================

template<class Real>
Point2<Real>::Point2()
{
	this->x 		= static_cast< Real > (0);
	this->y 		= static_cast< Real > (0);
};

/*!@brief Constructor with X, Y and Z initialization.
 * @details Initialize all abscissas.
 * @param[in] x Real number.
 * @param[in] y Real number.
 * @param[in] z Real number.
 */
template<class Real>
Point2<Real>::Point2 ( const Real& x, const Real& y )
: x(x), y(y) {};

/*!@brief Constructor with X, Y and Z initialization with vector paramenter.
 * @param[in] u Vector of Real.
 */  

template<class Real>
Point2<Real>::Point2 ( const Vector2<Real>& vector)
: x(vector.x), y(vector.y) {};

/*!@brief Copy Constructor.
 *  @param[in] p Point Real.
 */
template<class Real>
Point2<Real>::Point2 ( const Point2<Real>& point)
: x(point.x), y(point.y) {};

/*!@brief Constructor with X, Y and Z initialization of any type.
 *  @details Initialize all abscissas of any. Try cast to the Real type of the class
 *  @param[in] array of any type.
 */                                              
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


/*!@brief operator[]
 * @details array based index. "0" for x, "1" for y, "2" for z.
 * @ This is ready-only
 * @return Real.
 */
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
/*!@brief operator[]
 * @see operator[]
 * @note Acept assigement
 * @return Real.
 */
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

/*!@brief operator+
 * @details Unary operator tha return itself.
 * @note To be clearer the arithmetic operations.
 * @return Point2.
 */
template<class Real>
inline Point2<Real> Point2<Real>::operator+ ( )  const  
{
	return ( Point2<Real> (this->x, this->y)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point2.
 */
template<class Real>
inline Point2<Real>  Point2<Real>::operator- ( ) const
{

	return ( Point2<Real> (-this->x, -this->y) );

};

/*!@brief operator+=
 * @details Add the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
template<class Real>
const Point2< Real >& Point2<Real>::operator+= ( const Real&  factor )
{
	this->x += factor;
	this->y += factor;

	return ( *this );
}
/*!@brief operator-=
 * @details Subtract the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */            
template<class Real>
const Point2< Real >& Point2<Real>::operator-= ( const Real&  factor )
{
	this->x -= factor;
	this->y -= factor;

	return ( *this );
}
/*!@brief operator*=
 * @details Multiply the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
template<class Real>
const Point2< Real >& Point2<Real>::operator*= ( const Real& factor )
{

	this->x  *= factor;
	this->y  *= factor;

	return ( *this );
}
/*!@brief operator/=
 * @details Divide the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
template<class Real>
const Point2< Real >& Point2<Real>::operator/= ( const Real& factor )
{
	Real lFactor = (Real)1 / factor;

	this->x *= lFactor;
	this->y *= lFactor;

	return ( *this );
}

/*!@brief operator+
 * @details Binary operator tha add a poitn with number.
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Real& factor,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.x + factor, point.y + factor ) );

};
/*!@brief operator+
 * @see operator+
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Point2<Real>& point, const Real& factor )   
{
	return ( Point2<Real> ( point.x + factor, point.y + factor ) );

};

/*!@brief operator-
 * @details Binary operator tha subtratc a poitn and number.
 * @return Point2
 */
template<class Real>
inline  Point2<Real> operator- (const Real& factor,const Point2<Real>& point )  
{
	return ( Point2<Real> ( factor - point.x , factor - point.y )
	);

};

/*!@brief operator-
 * @see operator-
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator- (const Point2<Real>& point, const Real& factor )  
{
	return ( Point2<Real> ( point.x - factor, point.y - factor ) );

};

/*!@brief operator*
 * @details Binary operator tha multi the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
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

/*!@brief operator/
 * @details Binary operator tha divide the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
template<class Real>
inline Point2<Real> Point2<Real>::operator/ ( const Real& factor )  const  
{
	return ( Point2<Real> ( x / factor, y/ factor ) );

};

/*!@brief operator=
 * @details Assigment operator
 * @return Point2
 */
template<class Real>
inline const Point2<Real>& Point2<Real>::operator= ( const Point2<Real>& point)
{
	this->x = point.x;
	this->y = point.y;

	return ( *this );
};


/*!@brief operator+=
 * @see operator+=
 * @note Add the correspondents abscissa of the left point to the right.
 * @return Point2
 */
template<class Real>
const Point2< Real >& Point2<Real>::operator+= (  const Point2<Real>& point )
{
	this->x += point.x;
	this->y += point.y;

	return ( *this );
}
/*!@brief operator-=
 * @see operator-=
 * @note Subtract the correspondents abscissa of the left point to the right.
 * @return Point2
 */    
template<class Real>
const Point2<Real>& Point2<Real>::operator-= (  const Point2<Real>& point )
{
	this->x -= point.x;
	this->y -= point.y;

	return ( *this );
}

/*!@brief operator/=
 * @see operator/=
 * @note Subtract the correspondents abscissa of the left point to the right.  
 * @return Point2
 */
template<class Real>
const Point2<Real>& Point2<Real>::operator/= ( const Point2<Real>& point )
{

	this->x /= point.x;
	this->y /= point.y;

	return ( *this );
}

/*!@brief operator==
 * @details Two points are identical whether your correspondents abscissa are equal.
 * @return bool.
 */
template<class Real>
inline bool Point2<Real>::operator== ( const Point2<Real>& p) const
{
	return ( ( this->x == p.x ) and ( this->y == p.y ) );
};      
/*!@brief operator!=
 * @details Opposite to the operator==
 * @see operator==
 * @return bool.
 */
template<class Real>
inline bool Point2<Real>::operator!= ( const Point2<Real>& point) const
{
	return  !(*this == point) ;
};      


/*!@brief operator-
 * @details Binary operator tha subtract two point and return a vector.
 * @note First parameter is the origin and the second a target.
 * @return Vector2
 */                    
template<class Real>
inline Vector2<Real> operator- (const Point2<Real>& source, const Point2<Real>& target)   
{
	return ( Vector2<Real>( 	source.x - target.x,  source.y - target.y ) );

};

/*!@brief operator-
 * @details Binary operator tha subtract a poitn and a vecctor.
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator- (const Point2<Real>& point, const Vector2<Real>& vector)   
{
	return ( Point2<Real>( point.x - vector.x, point.y - vector.y)  );
};


/*!@brief operator-
 * @see operator-
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator- (const Vector2<Real>& vector,const Point2<Real>& point )   
{

	return ( Point2<Real>( vector.x - point.x, vector.y - point.y ) );

};


/*!@brief operator+
 * @details Binary operator tha add a poitn and another point.
 * @return Point2
 */

template<class Real>
inline Point2<Real> Point2<Real>::operator+ (const Point2<Real>& point)  const 
{
	return ( Point2<Real>( x + point.x, y + point.y ) );

};


/*!@brief operator+
 * @details Binary operator tha add a poitn and a vecctor.
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Point2<Real>& point, const Vector2<Real>& vector)   
{
	return ( Point2<Real> ( point.x + vector.x, point.y + vector.y ) );

};
/*!@brief operator+
 * @see operator+
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Vector2<Real>& vector,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.x + vector.x, point.y + vector.y ) );

};

//============================= OPERATIONS ===================================

/*!@brief operator<<
 * @details For debug
 */
template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Point2<Real>& point)
{
	s << "Point2" << " x = " << point.x << " ,y = " << std::endl;


	return ( s );
};
/*!@fn squareDistance
 * @details return the distance of two points
 */            
template<class Real>
Real Point2<Real>::SquaredDistance ( const Point2<Real>& point ) 
{
	return (  (point.x - this->x ) * ( point.x - this->x ) +  ( point.y - this->y) * ( point.y - this->y) );
}

#endif /*POINT2__INLINE_HPP_*/
