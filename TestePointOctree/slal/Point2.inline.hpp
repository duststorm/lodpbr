#ifndef LAL_POINT2_INLINE_HPP_
#define LAL_POINT2_INLINE_HPP_



//============================= LIFECYCLE ====================================

template<class Real>
Point2<Real>::Point2()
{
	this->mX 		= static_cast< Real > (0);
	this->mY 		= static_cast< Real > (0);
};

/*!@brief Constructor with X, Y and Z initialization.
 * @details Initialize all abscissas.
 * @param[in] x Real number.
 * @param[in] y Real number.
 * @param[in] z Real number.
 */
template<class Real>
Point2<Real>::Point2 ( const Real& x, const Real& y )
: mX(x), mY(y) {};

/*!@brief Constructor with X, Y and Z initialization with vector paramenter.
 * @param[in] u Vector of Real.
 */  

template<class Real>
Point2<Real>::Point2 ( const Vector2<Real>& vector)
: mX(vector.mX), mY(vector.mY) {};

/*!@brief Copy Constructor.
 *  @param[in] p Point Real.
 */
template<class Real>
Point2<Real>::Point2 ( const Point2<Real>& point)
: mX(point.mX), mY(point.mY) {};

/*!@brief Constructor with X, Y and Z initialization of any type.
 *  @details Initialize all abscissas of any. Try cast to the Real type of the class
 *  @param[in] array of any type.
 */                                              
template<class Real>    
template < typename P >
Point2<Real>::Point2 (const P* point)
{
	assert(point);

	this->mX = static_cast< Real > ( point[0] );
	this->mY = static_cast< Real > ( point[1] );

};

//============================= ACESS ======================================

/*!@brief Get X abscissa.
 *  @return Real.
 */              
template<class Real>
inline const Real& Point2<Real>::x() const
{
	return ( this->mX );
};
/*!@brief Get Y abscissa.
 *  @return Real.
 */
template<class Real>
inline const Real& Point2<Real>::y() const
{
	return ( this->mY );
};

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
	return ( Point2<Real> (this->mX, this->mY)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point2.
 */
template<class Real>
inline Point2<Real>  Point2<Real>::operator- ( ) const
{

	return ( Point2<Real> (-this->mX, -this->mY) );

};

/*!@brief operator+=
 * @details Add the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
template<class Real>
const Point2< Real >& Point2<Real>::operator+= ( const Real&  factor )
{
	this->mX += factor;
	this->mY += factor;

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
	this->mX -= factor;
	this->mY -= factor;

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

	this->mX  *= factor;
	this->mY  *= factor;

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

	this->mX *= lFactor;
	this->mY *= lFactor;

	return ( *this );
}

/*!@brief operator+
 * @details Binary operator tha add a poitn with number.
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Real& factor,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.mX + factor, point.mY + factor ) );

};
/*!@brief operator+
 * @see operator+
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Point2<Real>& point, const Real& factor )   
{
	return ( Point2<Real> ( point.mX + factor, point.mY + factor ) );

};

/*!@brief operator-
 * @details Binary operator tha subtratc a poitn and number.
 * @return Point2
 */
template<class Real>
inline  Point2<Real> operator- (const Real& factor,const Point2<Real>& point )  
{
	return ( Point2<Real> ( factor - point.mX , factor - point.mY )
	);

};

/*!@brief operator-
 * @see operator-
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator- (const Point2<Real>& point, const Real& factor )  
{
	return ( Point2<Real> ( point.mX - factor, point.mY - factor ) );

};

/*!@brief operator*
 * @details Binary operator tha multi the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator* (const Real& factor,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.mX * factor, point.mY * factor ) );

};

template<class Real>
inline Point2<Real> operator* (const Point2<Real>& point, const Real& factor )   
{
	return ( Point2<Real> ( point.mX * factor, point.mY * factor ) );

};

/*!@brief operator/
 * @details Binary operator tha divide the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point2
 */
template<class Real>
inline Point2<Real> Point2<Real>::operator/ ( const Real& factor )  const  
{
	return ( Point2<Real> ( mX / factor, mY/ factor ) );

};

/*!@brief operator=
 * @details Assigment operator
 * @return Point2
 */
template<class Real>
inline const Point2<Real>& Point2<Real>::operator= ( const Point2<Real>& point)
{
	this->mX = point.mX;
	this->mY = point.mY;

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
	this->mX += point.mX;
	this->mY += point.mY;

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
	this->mX -= point.mX;
	this->mY -= point.mY;

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

	this->mX /= point.mX;
	this->mY /= point.mY;

	return ( *this );
}

/*!@brief operator==
 * @details Two points are identical whether your correspondents abscissa are equal.
 * @return bool.
 */
template<class Real>
inline bool Point2<Real>::operator== ( const Point2<Real>& p) const
{
	return ( ( this->mX == p.mX ) and ( this->mY == p.mY ) );
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
	return ( Vector2<Real>( 	source.mX - target.mX,  source.mY - target.mY ) );

};

/*!@brief operator-
 * @details Binary operator tha subtract a poitn and a vecctor.
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator- (const Point2<Real>& point, const Vector2<Real>& vector)   
{
	return ( Point2<Real>( point.mX - vector.mX, point.mY - vector.mY)  );
};


/*!@brief operator-
 * @see operator-
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator- (const Vector2<Real>& vector,const Point2<Real>& point )   
{

	return ( Point2<Real>( vector.mX - point.mX, vector.mY - point.mY ) );

};


/*!@brief operator+
 * @details Binary operator tha add a poitn and another point.
 * @return Point2
 */

template<class Real>
inline Point2<Real> Point2<Real>::operator+ (const Point2<Real>& point)  const 
{
	return ( Point2<Real>( mX + point.mX, mY + point.mY ) );

};


/*!@brief operator+
 * @details Binary operator tha add a poitn and a vecctor.
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Point2<Real>& point, const Vector2<Real>& vector)   
{
	return ( Point2<Real> ( point.mX + vector.mX, point.mY + vector.mY, point.mZ + vector.mZ ) );

};
/*!@brief operator+
 * @see operator+
 * @return Point2
 */
template<class Real>
inline Point2<Real> operator+ (const Vector2<Real>& vector,const Point2<Real>& point )   
{
	return ( Point2<Real> ( point.mX + vector.mX, point.mY + vector.mY ) );

};

//============================= OPERATIONS ===================================

/*!@brief operator<<
 * @details For debug
 */
template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Point2<Real>& point)
{
	s << "Point2" << " x = " << point.mX << " ,y = " << std::endl;


	return ( s );
};
/*!@fn squareDistance
 * @details return the distance of two points
 */            
template<class Real>
Real Point2<Real>::SquaredDistance ( const Point2<Real>& point ) 
{
	return (  (point.mX - this->mX ) * ( point.mX - this->mX ) +  ( point.mY - this->mY) * ( point.mY - this->mY) );
}

#endif /*POINT2__INLINE_HPP_*/
