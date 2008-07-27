#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <iostream>
// [C++ Header files]
#include <cmath>
// [C++ Header STL]

#include "Vector3.hpp"


namespace LAL
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

      public:
     	  /*! @name Members  */
     	  //@{
     	  /*! An union. */
     	  /*!
     	   * Shareed memory with abscissas atributes and the XYZ Array.
     	   * The Struct has the same size of the \code xyz[] \endcode.
     	   */
    	  Real x; /*!< X abscissa of space. */  
    	  Real y; /*!< Y abscissa of space. */
    	  Real z; /*!< Y abscissa of space. */

     	  //@}

      public:

    	  friend class Vector3<Real>;

    	  /*! @name  Defining a Point3 */
    	  //@{
    	  /*! Default constructor. Value is set to (0,0,0). */
    	  Point3();
    	  Point3( const Real& x, const Real& y, const Real& z );
    	  Point3( const Point3<Real>& point );
    	  Point3( const Vector3<Real>& v );
    	  template < class T >
    	  Point3( const T* point );
    	  virtual ~Point3(){};
    	  
    	  void 					Set( const Real& x, const Real& y, const Real& z );
    	  //Operator
    	  //@}
    	  
  		  /*! @name Accessing the value */
  		  //@{
  			
    	  /*! Conversion operator returning the memory address of the Point.

    	  Useful to pass as a parameter to OpenGL functions:
    	  \code
    	  LAL:Point3<float> pos, normal;
    	  glNormal3fv(normal);
    	  glVertex3fv(pos);
    	  \endcode */
    	  
    	  Real 					operator[]( int i ) const;
    	  Real& 				operator[]( int i );  
    	  //@}
    	  
    	  /*! @name Algebraic computations */
    	  // @{
    	  // Point/Scalar operations
    	  Point3<Real>  	  	operator+() const;
    	  Point3<Real>  	  	operator-() const;

    	  Point3<Real>& 		operator+=( const Real& factor );
    	  Point3<Real>& 		operator-=( const Real& factor );
    	  Point3<Real>& 		operator*=( const Real& factor );
    	  Point3<Real>& 		operator/=( const Real& factor );
    	  template <class T>
    	  friend Point3<T> 		operator+( const T& factor,const Point3<T>& p  ) ;
    	  template <class T>
    	  friend Point3<T> 		operator+( const Point3<T>& p, const T& factor ) ;
    	  template <class T>
    	  friend Point3<T> 		operator-( const T& factor, const Point3<T>& p ) ;  
    	  template <class T>
    	  friend Point3<T> 		operator-( const Point3<T>& p, const T& factor ) ;  

    	  template <class T>
    	  friend Point3<T> 		operator*( const T& factor, const Point3<T>& p ) ;  
    	  template <class T>
    	  friend Point3<T> 		operator*( const Point3<T>& p, const T& factor ) ;  

    	   Point3<Real> 		operator/( const Real& factor ) const;

    	  // Point/Point operations
    	  Point3<Real>& 		operator= ( const Point3<Real>& p );
    	  Point3<Real>& 		operator+=( const Point3<Real>& p );
    	  Point3<Real>& 		operator-=( const Point3<Real>& p );
    	  Point3<Real>& 		operator/=( const Point3<Real>& p );

    	  Point3<Real> 			operator+( const Point3<Real>& p ) const;
    	  template <class T>
    	  friend  Vector3<T>  	operator-( const Point3<T>& source,const Point3<T>& target ) ;

    	  bool 					operator==( const Point3<Real>& p ) const;
    	  bool 					operator!=( const Point3<Real>& p ) const;

    	  // Point/Vector
    	  template <class T>
    	  friend Point3<T> 		operator+( const Point3<T>& p, const Vector3<T>& v ) ;  
    	  template <class T>
    	  friend Point3<T> 		operator+( const Vector3<T>& v, const Point3<T>& p ) ;

    	  template <class T>
    	  friend Point3<T> 		operator-( const Point3<T>& p, const Vector3<T>& v ) ;  
    	  template <class T>
    	  friend Point3<T> 		operator-( const Vector3<T>& v, const Point3<T>& p ) ;  
      	  /*! @name Output stream */
      	  //@{
      	  /*! Output stream operator. Enables debugging code like:
      	  \code
      	  LAL::Point3<> p(...);
      	  std::cout << "Point3" << " x = " << p.x << " ,y = " << p.y << " ,z = " << p.z << std::endl;
      	  \endcode */
    	  template <class T>
    	  friend std::ostream& 	operator<< (std::ostream & s, const Point3<T>& p);
    	  
    	  //@}
    	  /*!@name Functions */
    	  //@{
    	  /*!  */
    	  Real 					SquaredDistance ( const Point3<Real>& p ) ;
  		  const Real* 			ToRealPtr( void ) const;
  		  Real* 				ToRealPtr( void );
		  //@}
    	  

      };


#include "Point3.inline.hpp"
     
} /* LAL :: NAMESPACE */

#endif /*POINT3_HPP_*/

