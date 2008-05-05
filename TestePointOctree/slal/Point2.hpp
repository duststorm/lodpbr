#ifndef POINT2_HPP_
#define POINT2_HPP_

#include <iostream>
// [C++ Header files]
#include <cmath>



#include "Vector2.hpp"


namespace CGL
{


/*!
*@class Point2.
*@brief Class that represent a Point in 3D.
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 25-Feb-2008.
*@todo OpenGL interface and a C style array. Auxiliar Functions
*/      


      template <class Real>   class Point2
      {

      private:
          /*! An union. */
          /*!
           * Share memory with abscissas atributes and the XYZ Array.
           * The Struct has the same size of the A.
           */
          union
          {
                  struct
                  {
                          Real mX; /*!< X abscissa of space. */  

                          Real mY; /*!< Y abscissa of space. */

                  };

                  Real xy[2];/*!< Array of abscissas for fast operator return @see operator[].*/

          };

      public:

    	  friend class Vector2<Real>;

    	  //constructor
    	  Point2();
    	  Point2 ( const Real& x, const Real& y );
    	  Point2 ( const Point2<Real>& p);
    	  Point2 ( const Vector2<Real>& u);
    	  template < typename P >
    	  Point2 (const P* p);
    	  
    	  inline const Real& x() const;
    	  inline const Real& y() const;

    	  inline  Real operator [] ( unsigned int i)  const;

    	  Real& operator [] ( unsigned int i);  

    	  // Point/Scalar operations
    	  inline Point2<Real>  	  operator+ ( ) const;
    	  inline Point2<Real>  	  operator- ( ) const;

    	  inline const Point2<Real>& operator+= ( const Real& factor );
    	  inline const Point2<Real>& operator-= ( const Real& factor );
    	  inline const Point2<Real>& operator*= ( const Real& factor );
    	  inline const Point2<Real>& operator/= ( const Real& factor );
    	  template <class T>
    	  inline friend Point2<T> operator+ (const T& factor,const Point2<T>& p  ) ;
    	  template <class T>
    	  inline friend Point2<T> operator+ (const Point2<T>& p, const T& factor ) ;
    	  template <class T>
    	  inline friend Point2<T> operator- (const T& factor, const Point2<T>& p ) ;  
    	  template <class T>
    	  inline friend Point2<T> operator- (const Point2<T>& p, const T& factor ) ;  

    	  template <class T>
    	  inline friend Point2<T> operator* (const T& factor, const Point2<T>& p ) ;  
    	  template <class T>
    	  inline friend Point2<T> operator* (const Point2<T>& p, const T& factor ) ;  

    	  inline Point2<Real> operator/ ( const Real& factor ) const;

    	  // Point/Point operations
    	  inline const Point2<Real>& operator=  ( const Point2<Real>& p);
    	  inline const Point2<Real>& operator+= ( const Point2<Real>& u );
    	  inline const Point2<Real>& operator-= ( const Point2<Real>& u );
    	  inline const Point2<Real>& operator/= ( const Point2<Real>& u );

    	  inline Point2<Real> operator+ (const Point2<Real>& p) const;
    	  template <class T>
    	  friend inline Vector2<T>  operator- (const Point2<T>& p,const Point2<T>& q ) ;

    	  inline bool operator== ( const Point2<Real>& p) const;
    	  inline bool operator!= ( const Point2<Real>& p) const;

    	  // Point/Vector
    	  template <class T>
    	  inline friend Point2<T> operator+ (const Point2<T>& p, const Vector2<T>& u) ;  
    	  template <class T>
    	  inline friend Point2<T> operator+ (const Vector2<T>& u, const Point2<T>& p ) ;

    	  template <class T>
    	  inline friend Point2<T> operator- (const Point2<T>& p, const Vector2<T>& u ) ;  
    	  template <class T>
    	  inline friend Point2<T> operator- (const Vector2<T>& u, const Point2<T>& p ) ;  

    	  template <class T>
    	  inline friend std::ostream& operator<< (std::ostream & s, const Point2<T>& p);
    
    	  // Functions
    	  Real SquaredDistance ( const Point2<Real>& p ) ;

    	  virtual ~Point2(){};

      };

//  -------->  Implementation

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
      Point2<Real>::Point2 ( const Vector2<Real>& u)
      : mX(u.mX), mY(u.mY) {};

      /*!@brief Copy Constructor.
       *  @param[in] p Point Real.
       */
      template<class Real>
      Point2<Real>::Point2 ( const Point2<Real>& p)
      : mX(p.mX), mY(p.mY) {};
      
      /*!@brief Constructor with X, Y and Z initialization of any type.
       *  @details Initialize all abscissas of any. Try cast to the Real type of the class
       *  @param[in] array of any type.
       */                                              
      template<class Real>    
      template < typename P >
      Point2<Real>::Point2 (const P* p)
      {
    	  assert(p);

    	  this->mX = static_cast< Real > ( p[0] );
    	  this->mY = static_cast< Real > ( p[1] );
    	  
      };

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
      inline Point2<Real> operator+ (const Real& factor,const Point2<Real>& p )   
      {
    	  return ( Point2<Real> ( p.mX + factor, p.mY + factor ) );

      };
      /*!@brief operator+
       * @see operator+
       * @return Point2
      */
      template<class Real>
      inline Point2<Real> operator+ (const Point2<Real>& p, const Real& factor )   
      {
    	  return ( Point2<Real> ( p.mX + factor, p.mY + factor ) );

      };
      
      /*!@brief operator-
       * @details Binary operator tha subtratc a poitn and number.
       * @return Point2
      */
      template<class Real>
      inline  Point2<Real> operator- (const Real& factor,const Point2<Real>& p )  
      {
    	  return ( Point2<Real> ( factor - p.mX , factor - p.mY )
    	  );

      };

      /*!@brief operator-
       * @see operator-
       * @return Point2
      */
      template<class Real>
      inline Point2<Real> operator- (const Point2<Real>& p, const Real& factor )  
      {
    	  return ( Point2<Real> ( p.mX - factor, p.mY - factor ) );

      };
      
      /*!@brief operator*
       * @details Binary operator tha multi the value of the second operand to the value of the all abscissa of the point.
       * @param[in] factor Real
       * @return Point2
       */
      template<class Real>
      inline Point2<Real> operator* (const Real& factor,const Point2<Real>& p )   
      {
    	  return ( Point2<Real> ( p.mX * factor, p.mY * factor ) );

      };

      template<class Real>
      inline Point2<Real> operator* (const Point2<Real>& p, const Real& factor )   
      {
    	  return ( Point2<Real> ( p.mX * factor, p.mY * factor ) );

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
      inline const Point2<Real>& Point2<Real>::operator= ( const Point2<Real>& p)
      {
    	  this->mX = p.mX;
    	  this->mY = p.mY;

    	  return ( *this );
      };
      
      
      /*!@brief operator+=
       * @see operator+=
       * @note Add the correspondents abscissa of the left point to the right.
       * @return Point2
       */
      template<class Real>
      const Point2< Real >& Point2<Real>::operator+= (  const Point2<Real>& u )
      {
    	  this->mX += u.mX;
    	  this->mY += u.mY;

    	  return ( *this );
      }
      /*!@brief operator-=
       * @see operator-=
       * @note Subtract the correspondents abscissa of the left point to the right.
       * @return Point2
       */    
      template<class Real>
      const Point2<Real>& Point2<Real>::operator-= (  const Point2<Real>& u )
      {
    	  this->mX -= u.mX;
    	  this->mY -= u.mY;

    	  return ( *this );
      }

      /*!@brief operator/=
       * @see operator/=
       * @note Subtract the correspondents abscissa of the left point to the right.  
       * @return Point2
       */
      template<class Real>
      const Point2<Real>& Point2<Real>::operator/= ( const Point2<Real>& u )
      {

    	  this->mX /= u.mX;
    	  this->mY /= u.mY;

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
      inline bool Point2<Real>::operator!= ( const Point2<Real>& p) const
      {
    	  return  !(*this == p) ;
      };      


      /*!@brief operator-
       * @details Binary operator tha subtract two point and return a vector.
       * @note First parameter is the origin and the second a target.
       * @return Vector2
       */                    
      template<class Real>
      inline Vector2<Real> operator- (const Point2<Real>& p, const Point2<Real>& q)   
      {
    	  return ( Vector2<Real>( 	p.mX - q.mX,  p.mY - q.mY ) );

      };

      /*!@brief operator-
       * @details Binary operator tha subtract a poitn and a vecctor.
       * @return Point2
       */
      template<class Real>
      inline Point2<Real> operator- (const Point2<Real>& p, const Vector2<Real>& u)   
      {
    	  return ( Point2<Real>( p.mX - u.mX, p.mY - u.mY)  );
      };


      /*!@brief operator-
       * @see operator-
       * @return Point2
       */
      template<class Real>
      inline Point2<Real> operator- (const Vector2<Real>& u,const Point2<Real>& p )   
      {

    	  return ( Point2<Real>( u.mX - p.mX, u.mY - p.mY ) );

      };


      /*!@brief operator+
       * @details Binary operator tha add a poitn and another point.
       * @return Point2
      */

      template<class Real>
      inline Point2<Real> Point2<Real>::operator+ (const Point2<Real>& p)  const 
      {
    	  return ( Point2<Real>( mX + p.mX, mY + p.mY ) );

      };


      /*!@brief operator+
       * @details Binary operator tha add a poitn and a vecctor.
       * @return Point2
       */
      template<class Real>
      inline Point2<Real> operator+ (const Point2<Real>& p, const Vector2<Real>& u)   
      {
    	  return ( Point2<Real> ( p.mX + u.mX, p.mY + u.mY, p.mZ + u.mZ ) );

      };
      /*!@brief operator+
       * @see operator+
       * @return Point2
       */
      template<class Real>
      inline Point2<Real> operator+ (const Vector2<Real>& u,const Point2<Real>& p )   
      {
    	  return ( Point2<Real> ( p.mX + u.mX, p.mY + u.mY ) );

      };


      /*!@brief operator<<
       * @details For debug
       */
      template<class Real>
      inline std::ostream& operator<< (std::ostream & s, const Point2<Real>& p)
      {
    	  s << "Point2" << " x = " << p.mX << " ,y = " << std::endl;


    	  return ( s );
      };
      /*!@fn squareDistance
       * @details return the distance of two points
       */            
      template<class Real>
      Real Point2<Real>::SquaredDistance ( const Point2<Real>& p ) 
      {
    	  return (  ( p.mX - this->mX ) * ( p.mX - this->mX ) +  ( p.mY - this->mY) * ( p.mY - this->mY) );
      }


     
} /* CGL :: NAMESPACE */

#endif /*POINT2_HPP_*/
