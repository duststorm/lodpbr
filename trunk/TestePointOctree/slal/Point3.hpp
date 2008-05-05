#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <iostream>
// [C++ Header files]
#include <cmath>
// [C++ Header STL]

#include "Vector3.hpp"


namespace CGL
{


/*!
*@class Point3.
*@brief Class that represent a Point in 3D.
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 25-Feb-2008.
*@todo OpenGL interface and a C style array.
*/      


      template <class Real>   class Point3
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

                          Real mZ; /*!< Z abscissa of space. */
                  };

                  Real xyz[3];/*!< Array of abscissas for fast operator return @see operator[].*/

          };

      public:

    	  friend class Vector3<Real>;

    	  //constructor
    	  Point3();
    	  Point3 ( const Real& x, const Real& y, const Real& z );
    	  Point3 ( const Point3<Real>& p);
    	  Point3 ( const Vector3<Real>& u);
    	  template < typename P >
    	  Point3 (const P* p);

    	  inline const Real& x() const;
    	  inline const Real& y() const;
    	  inline const Real& z() const;

    	  
    	  inline  Real operator [] ( int i)  const;

    	  Real& operator [] ( int i);  

    	  // Point/Scalar operations
    	  inline Point3<Real>  	  operator+ ( ) const;
    	  inline Point3<Real>  	  operator- ( ) const;

    	  inline const Point3<Real>& operator+= ( const Real& factor );
    	  inline const Point3<Real>& operator-= ( const Real& factor );
    	  inline const Point3<Real>& operator*= ( const Real& factor );
    	  inline const Point3<Real>& operator/= ( const Real& factor );
    	  template <class T>
    	  inline friend Point3<T> operator+ (const T& factor,const Point3<T>& p  ) ;
    	  template <class T>
    	  inline friend Point3<T> operator+ (const Point3<T>& p, const T& factor ) ;
    	  template <class T>
    	  inline friend Point3<T> operator- (const T& factor, const Point3<T>& p ) ;  
    	  template <class T>
    	  inline friend Point3<T> operator- (const Point3<T>& p, const T& factor ) ;  

    	  template <class T>
    	  inline friend Point3<T> operator* (const T& factor, const Point3<T>& p ) ;  
    	  template <class T>
    	  inline friend Point3<T> operator* (const Point3<T>& p, const T& factor ) ;  

    	  inline Point3<Real> operator/ ( const Real& factor ) const;

    	  // Point/Point operations
    	  inline const Point3<Real>& operator=  ( const Point3<Real>& p);
    	  inline const Point3<Real>& operator+= ( const Point3<Real>& u );
    	  inline const Point3<Real>& operator-= ( const Point3<Real>& u );
    	  inline const Point3<Real>& operator/= ( const Point3<Real>& u );

    	  inline Point3<Real> operator+ (const Point3<Real>& p) const;
    	  template <class T>
    	  friend inline Vector3<T>  operator- (const Point3<T>& p,const Point3<T>& q ) ;

    	  inline bool operator== ( const Point3<Real>& p) const;
    	  inline bool operator!= ( const Point3<Real>& p) const;

    	  // Point/Vector
    	  template <class T>
    	  inline friend Point3<T> operator+ (const Point3<T>& p, const Vector3<T>& u) ;  
    	  template <class T>
    	  inline friend Point3<T> operator+ (const Vector3<T>& u, const Point3<T>& p ) ;

    	  template <class T>
    	  inline friend Point3<T> operator- (const Point3<T>& p, const Vector3<T>& u ) ;  
    	  template <class T>
    	  inline friend Point3<T> operator- (const Vector3<T>& u, const Point3<T>& p ) ;  

    	  template <class T>
    	  inline friend std::ostream& operator<< (std::ostream & s, const Point3<T>& p);
    
    	  // Functions
    	  Real SquaredDistance ( const Point3<Real>& p ) ;

    	  virtual ~Point3(){};

      };

//  -------->  Implementation

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
      Point3<Real>::Point3 ( const Vector3<Real>& u)
      : mX(u.mX), mY(u.mY), mZ(u.mZ) {};

      /*!@brief Copy Constructor.
       *  @param[in] p Point Real.
       */
      template<class Real>
      Point3<Real>::Point3 ( const Point3<Real>& p)
      : mX(p.mX), mY(p.mY), mZ(p.mZ) {};
      
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
      inline Point3<Real> operator+ (const Real& factor,const Point3<Real>& p )   
      {
    	  return ( Point3<Real> ( p.mX + factor, p.mY + factor, p.mZ + factor ) );

      };
      /*!@brief operator+
       * @see operator+
       * @return Point3
      */
      template<class Real>
      inline Point3<Real> operator+ (const Point3<Real>& p, const Real& factor )   
      {
    	  return ( Point3<Real> ( p.mX + factor, p.mY + factor, p.mZ + factor ) );

      };
      
      /*!@brief operator-
       * @details Binary operator tha subtratc a poitn and number.
       * @return Point3
      */
      template<class Real>
      inline  Point3<Real> operator- (const Real& factor,const Point3<Real>& p )  
      {
    	  return ( Point3<Real> ( factor - p.mX , factor - p.mY , factor - p.mZ  )
    	  );

      };

      /*!@brief operator-
       * @see operator-
       * @return Point3
      */
      template<class Real>
      inline Point3<Real> operator- (const Point3<Real>& p, const Real& factor )  
      {
    	  return ( Point3<Real> ( p.mX - factor, p.mY - factor, p.mZ - factor )	 );

      };
      
      /*!@brief operator*
       * @details Binary operator tha multi the value of the second operand to the value of the all abscissa of the point.
       * @param[in] factor Real
       * @return Point3
       */
      template<class Real>
      inline Point3<Real> operator* (const Real& factor,const Point3<Real>& p )   
      {
    	  return ( Point3<Real> ( p.mX * factor, p.mY * factor, p.mZ * factor ) );

      };

      template<class Real>
      inline Point3<Real> operator* (const Point3<Real>& p, const Real& factor )   
      {
    	  return ( Point3<Real> ( p.mX * factor, p.mY * factor, p.mZ * factor ) );

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
      inline const Point3<Real>& Point3<Real>::operator= ( const Point3<Real>& p)
      {
    	  this->mX = p.mX;
    	  this->mY = p.mY;
    	  this->mZ = p.mZ;

    	  return ( *this );
      };
      
      
      /*!@brief operator+=
       * @see operator+=
       * @note Add the correspondents abscissa of the left point to the right.
       * @return Point3
       */
      template<class Real>
      const Point3< Real >& Point3<Real>::operator+= (  const Point3<Real>& u )
      {
    	  this->mX += u.x();
    	  this->mY += u.y();
    	  this->mZ += u.z();

    	  return ( *this );
      }
      /*!@brief operator-=
       * @see operator-=
       * @note Subtract the correspondents abscissa of the left point to the right.
       * @return Point3
       */    
      template<class Real>
      const Point3<Real>& Point3<Real>::operator-= (  const Point3<Real>& u )
      {
    	  this->mX -= u.x();
    	  this->mY -= u.y();
    	  this->mZ -= u.z();

    	  return ( *this );
      }

      /*!@brief operator/=
       * @see operator/=
       * @note Subtract the correspondents abscissa of the left point to the right.  
       * @return Point3
       */
      template<class Real>
      const Point3<Real>& Point3<Real>::operator/= ( const Point3<Real>& u )
      {

    	  this->mX /= u.x();
    	  this->mY /= u.y();
    	  this->mZ /= u.z();

    	  return ( *this );
      }

      /*!@brief operator==
       * @details Two points are identical whether your correspondents abscissa are equal.
       * @return bool.
       */
      template<class Real>
      inline bool Point3<Real>::operator== ( const Point3<Real>& p) const
      {
    	  return ( ( this->mX == p.x() ) and ( this->mY == p.y() ) and ( this->mZ == p.z() ) );
      };      
      /*!@brief operator!=
       * @details Opposite to the operator==
       * @see operator==
       * @return bool.
       */
      template<class Real>
      inline bool Point3<Real>::operator!= ( const Point3<Real>& p) const
      {
    	  return  !(*this == p) ;
      };      


      /*!@brief operator-
       * @details Binary operator tha subtract two point and return a vector.
       * @note First parameter is the origin and the second a target.
       * @return Vector3
       */                    
      template<class Real>
      inline Vector3<Real> operator- (const Point3<Real>& p, const Point3<Real>& q)   
      {
    	  return ( Vector3<Real>( 	p.mX - q.mX,
    			  p.mY - q.mY,
    			  p.mZ - q.mZ)
    	  );

      };

      /*!@brief operator-
       * @details Binary operator tha subtract a poitn and a vecctor.
       * @return Point3
       */
      template<class Real>
      inline Point3<Real> operator- (const Point3<Real>& p, const Vector3<Real>& u)   
      {
    	  return ( Point3<Real>( p.mX - u.mX, p.mY - u.mY, p.mZ - u.mZ )  );
      };


      /*!@brief operator-
       * @see operator-
       * @return Point3
       */
      template<class Real>
      inline Point3<Real> operator- (const Vector3<Real>& u,const Point3<Real>& p )   
      {

    	  return ( Point3<Real>( u.mX - p.mX, u.mY - p.mY, u.mZ - p.mZ ) );

      };


      /*!@brief operator+
       * @details Binary operator tha add a poitn and another point.
       * @return Point3
      */

      template<class Real>
      inline Point3<Real> Point3<Real>::operator+ (const Point3<Real>& p)  const 
      {
    	  return ( Point3<Real>( mX + p.mX, mY + p.mY, mZ + p.mZ ) );

      };


      /*!@brief operator+
       * @details Binary operator tha add a poitn and a vecctor.
       * @return Point3
       */
      template<class Real>
      inline Point3<Real> operator+ (const Point3<Real>& p, const Vector3<Real>& u)   
      {
    	  return ( Point3<Real> ( p.mX + u.mX, p.mY + u.mY, p.mZ + u.mZ ) );

      };
      /*!@brief operator+
       * @see operator+
       * @return Point3
       */
      template<class Real>
      inline Point3<Real> operator+ (const Vector3<Real>& u,const Point3<Real>& p )   
      {
    	  return ( Point3<Real> ( p.mX + u.mX,p.mY + u.mY, p.mZ + u.mZ ) );

      };


      /*!@brief operator<<
       * @details For debug
       */
      template<class Real>
      inline std::ostream& operator<< (std::ostream & s, const Point3<Real>& p)
      {
    	  s << "Point3" << " x = " << p.mX << " ,y = " << p.mY << " ,z = " << p.mZ << std::endl;


    	  return ( s );
      };
      /*!@fn squareDistance
       * @details return the distance of two points
       */            
      template<class Real>
      Real Point3<Real>::SquaredDistance ( const Point3<Real>& p ) 
      {
    	  return ( pow ( p.x() - this->mX, 2) + pow ( p.y() - this->mY, 2) +   pow ( p.z() - this->mZ, 2) );
      }


     
} /* CGL :: NAMESPACE */

#endif /*POINT3_HPP_*/

