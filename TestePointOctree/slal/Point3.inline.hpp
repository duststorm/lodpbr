#ifndef LAL_POINT3_INLINE_HPP_
#define LAL_POINT3_INLINE_HPP_


//============================= LIFECYCLE ====================================

template<class Real>
Point3<Real>::Point3()
{
	this->mX 		= static_cast< Real > (0);
	this->mY 		= static_cast< Real > (0);
	this->mZ 		= static_cast< Real > (0);

};

/*!@brief Constructor with X, Y and Z initialization.
 * @details Initialize all abscissas.
 * @param[in] x Real number.
 * @param[in] y Real number.
 * @param[in] z Real number.
 */
template<class Real>
Point3<Real>::Point3 ( const Real& x, const Real& y, const Real& z )
: mX(x), mY(y), mZ(z) {};

/*!@brief Constructor with X, Y and Z initialization with vector paramenter.
 * @param[in] u Vector of Real.
 */  

template<class Real>
Point3<Real>::Point3 ( const Vector3<Real>& vector)
: mX(vector.mX), mY(vector.mY), mZ(vector.mZ) {};

/*!@brief Copy Constructor.
 *  @param[in] p Point Real.
 */
template<class Real>
Point3<Real>::Point3 ( const Point3<Real>& point)
: mX(point.mX), mY(point.mY), mZ(point.mZ) {};

/*!@brief Constructor with X, Y and Z initialization of any type.
 *  @details Initialize all abscissas of any. Try cast to the Real type of the class
 *  @param[in] array of any type.
 */                                              
template<class Real>    
template < typename P >
Point3<Real>::Point3 (const P* p)
{
	assert(p);

	this->mX = static_cast< Real > ( p[0] );
	this->mY = static_cast< Real > ( p[1] );
	this->mZ = static_cast< Real > ( p[2] );

};

//============================= ACESS ======================================

/*!@brief Get X abscissa.
 *  @return Real.
 */              
template<class Real>
inline const Real& Point3<Real>::x() const
{
	return ( this->mX );
};
/*!@brief Get Y abscissa.
 *  @return Real.
 */
template<class Real>
inline const Real& Point3<Real>::y() const
{
	return ( this->mY );
};
/*!@brief Get Z abscissa.
 *  @return Real.
 */
template<class Real>
inline const Real& Point3<Real>::z() const
{
	return ( this->mZ );
};

template<class Real>
inline void Point3<Real>::Set(const Real& x, const Real& y, const Real& z) 
{
	this->mX = x;
	this->mY = y;
	this->mZ = z;
};

//Operator

template<class Real>
inline Point3<Real>::operator Real * ()
{
	return xyz;
}

template<class Real>
inline Point3<Real>::operator const Real * ()
{
	return xyz;
}


template<class Real>
inline  Real Point3<Real>::operator [] ( int i)  const
{
	if ( (i > 2) or ( i < 0))
	{
		std::cerr << "[ERROR] Point3 operator[]"        << std::endl
		<< "        Out of the Point size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}

	return (xyz[i]);
};
/*!@brief operator[]
 * @see operator[]
 * @note Acept assigement
 * @return Real.
 */
template<class Real>
inline  Real& Point3<Real>::operator [] ( int i)  

{
	if ( (i > 2) or ( i < 0))
	{
		std::cerr << "[ERROR] Point3 operator[]"        << std::endl
		<< "        Out of the Point size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}


	return (xyz[i]);
};

//============================= OPERATORS ====================================

/*!@brief operator+
 * @details Unary operator tha return itself.
 * @note To be clearer the arithmetic operations.
 * @return Point3.
 */
template<class Real>
inline Point3<Real> Point3<Real>::operator+ ( )  const  
{
	return ( Point3<Real> (this->mX, this->mY, this->mZ)  );
};

/*!@brief operator-
 * @details Unary operator tha return the negative of the point.
 * @note To be clearer the arithmetic operations.
 * @return Point3.
 */
template<class Real>
inline Point3<Real>  Point3<Real>::operator- ( ) const
{

	return ( Point3<Real> (-this->mX, -this->mY, -this->mZ) );

};

/*!@brief operator+=
 * @details Add the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point3
 */
template<class Real>
const Point3< Real >& Point3<Real>::operator+= ( const Real&  factor )
{
	this->mX += factor;
	this->mY += factor;
	this->mZ += factor;

	return ( *this );
}
/*!@brief operator-=
 * @details Subtract the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point3
 */            
template<class Real>
const Point3< Real >& Point3<Real>::operator-= ( const Real&  factor )
{
	this->mX -= factor;
	this->mY -= factor;
	this->mZ -= factor;

	return ( *this );
}
/*!@brief operator*=
 * @details Multiply the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point3
 */
template<class Real>
const Point3< Real >& Point3<Real>::operator*= ( const Real& factor )
{

	this->mX  *= factor;
	this->mY  *= factor;
	this->mZ  *= factor;

	return ( *this );
}
/*!@brief operator/=
 * @details Divide the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point3
 */
template<class Real>
const Point3< Real >& Point3<Real>::operator/= ( const Real& factor )
{
	Real lFactor = (Real)1 / factor;

	this->mX *= lFactor;
	this->mY *= lFactor;
	this->mZ *= lFactor;

	return ( *this );
}

/*!@brief operator+
 * @details Binary operator tha add a poitn with number.
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator+ (const Real& factor,const Point3<Real>& point )   
{
	return ( Point3<Real> ( point.mX + factor, point.mY + factor, point.mZ + factor ) );

};
/*!@brief operator+
 * @see operator+
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator+ (const Point3<Real>& point, const Real& factor )   
{
	return ( Point3<Real> ( point.mX + factor, point.mY + factor, point.mZ + factor ) );

};

/*!@brief operator-
 * @details Binary operator tha subtratc a poitn and number.
 * @return Point3
 */
template<class Real>
inline  Point3<Real> operator- (const Real& factor,const Point3<Real>& point )  
{
	return ( Point3<Real> ( factor - point.mX , factor - point.mY , factor - point.mZ  )
	);

};

/*!@brief operator-
 * @see operator-
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator- (const Point3<Real>& point, const Real& factor )  
{
	return ( Point3<Real> ( point.mX - factor, point.mY - factor, point.mZ - factor )	 );

};

/*!@brief operator*
 * @details Binary operator tha multi the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator* (const Real& factor,const Point3<Real>& point )   
{
	return ( Point3<Real> ( point.mX * factor, point.mY * factor, point.mZ * factor ) );

};

template<class Real>
inline Point3<Real> operator* (const Point3<Real>& point, const Real& factor )   
{
	return ( Point3<Real> ( point.mX * factor, point.mY * factor, point.mZ * factor ) );

};

/*!@brief operator/
 * @details Binary operator tha divide the value of the second operand to the value of the all abscissa of the point.
 * @param[in] factor Real
 * @return Point3
 */
template<class Real>
inline Point3<Real> Point3<Real>::operator/ ( const Real& factor )  const  
{
	return ( Point3<Real> ( 	mX / factor, mY/ factor, mZ / factor ) );

};

/*!@brief operator=
 * @details Assigment operator
 * @return Point3
 */
template<class Real>
inline const Point3<Real>& Point3<Real>::operator= ( const Point3<Real>& point)
{
	this->mX = point.mX;
	this->mY = point.mY;
	this->mZ = point.mZ;

	return ( *this );
};


/*!@brief operator+=
 * @see operator+=
 * @note Add the correspondents abscissa of the left point to the right.
 * @return Point3
 */
template<class Real>
const Point3< Real >& Point3<Real>::operator+= (  const Point3<Real>& point )
{
	this->mX += point.mX;
	this->mY += point.mY;
	this->mZ += point.mZ;

	return ( *this );
}
/*!@brief operator-=
 * @see operator-=
 * @note Subtract the correspondents abscissa of the left point to the right.
 * @return Point3
 */    
template<class Real>
const Point3<Real>& Point3<Real>::operator-= (  const Point3<Real>& point )
{
	this->mX -= point.mX;
	this->mY -= point.mY;
	this->mZ -= point.mZ;

	return ( *this );
}

/*!@brief operator/=
 * @see operator/=
 * @note Subtract the correspondents abscissa of the left point to the right.  
 * @return Point3
 */
template<class Real>
const Point3<Real>& Point3<Real>::operator/= ( const Point3<Real>& point )
{

	this->mX /= point.mX;
	this->mY /= point.mY;
	this->mZ /= point.mZ;

	return ( *this );
}

/*!@brief operator==
 * @details Two points are identical whether your correspondents abscissa are equal.
 * @return bool.
 */
template<class Real>
inline bool Point3<Real>::operator== ( const Point3<Real>& point) const
{
	return ( ( this->mX == point.x() ) and ( this->mY == point.y() ) and ( this->mZ == point.z() ) );
};      
/*!@brief operator!=
 * @details Opposite to the operator==
 * @see operator==
 * @return bool.
 */
template<class Real>
inline bool Point3<Real>::operator!= ( const Point3<Real>& point) const
{
	return  !(*this == point) ;
};      


/*!@brief operator-
 * @details Binary operator tha subtract two point and return a vector.
 * @note First parameter is the origin and the second a target.
 * @return Vector3
 */                    
template<class Real>
inline Vector3<Real> operator- (const Point3<Real>& source, const Point3<Real>& target)   
{
	return ( Vector3<Real>( 	source.mX - target.mX,
			source.mY - target.mY,
			source.mZ - target.mZ)
	);

};

/*!@brief operator-
 * @details Binary operator tha subtract a poitn and a vecctor.
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator- (const Point3<Real>& point, const Vector3<Real>& vector)   
{
	return ( Point3<Real>( point.mX - vector.mX, point.mY - vector.mY, point.mZ - vector.mZ )  );
};


/*!@brief operator-
 * @see operator-
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator- (const Vector3<Real>& vector,const Point3<Real>& point )   
{

	return ( Point3<Real>( vector.mX - point.mX, vector.mY - point.mY, vector.mZ - point.mZ ) );

};


/*!@brief operator+
 * @details Binary operator tha add a poitn and another point.
 * @return Point3
 */

template<class Real>
inline Point3<Real> Point3<Real>::operator+ (const Point3<Real>& point)  const 
{
	return ( Point3<Real>( mX + point.mX, mY + point.mY, mZ + point.mZ ) );

};


/*!@brief operator+
 * @details Binary operator tha add a poitn and a vecctor.
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator+ (const Point3<Real>& point, const Vector3<Real>& vector)   
{
	return ( Point3<Real> ( point.mX + vector.mX, point.mY + vector.mY, point.mZ + vector.mZ ) );

};
/*!@brief operator+
 * @see operator+
 * @return Point3
 */
template<class Real>
inline Point3<Real> operator+ (const Vector3<Real>& vector,const Point3<Real>& point )   
{
	return ( Point3<Real> ( point.mX + vector.mX,point.mY + vector.mY, point.mZ + vector.mZ ) );

};

//============================= OPERATIONS ===================================

/*!@brief operator<<
 * @details For debug
 */
template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Point3<Real>& point)
{
	s << "Point3" << " x = " << point.mX << " ,y = " << point.mY << " ,z = " << point.mZ << std::endl;


	return ( s );
};
/*!@fn squareDistance
 * @details return the distance of two points
 */            
template<class Real>
Real Point3<Real>::SquaredDistance ( const Point3<Real>& point ) 
{
	return (  (point.mX - this->mX) * (point.mX - this->mX)	+  
			  (point.mY - this->mY) * (point.mY - this->mY) +   
			  (point.mZ - this->mZ) * (point.mZ - this->mZ) );
}


#endif
