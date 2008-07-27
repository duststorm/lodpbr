#ifndef LAL_POINT2_HPP_
#define LAL_POINT2_HPP_

// [System Include]
#include <iostream>    // standard IO interface
				
// [Project Includes]
#include "Math.hpp"	   // Use sqrt()  
#include "Vector2.hpp" // Friend Class 


namespace LAL
{

/*!
*@class Point2.
*@brief Class that represent a Point in 2D.
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 25-Feb-2008.
*@todo OpenGL interface and a C style array.
*/      
      template <class Real> class Point2
      {

      public:

    	  friend class Vector2<Real>;

    	  /*! @name  Defining a Point2 */
    	  //@{
    	  /*! Default constructor. Value is set to (0,0,0). */
    	  Point2();
    	  /*! Standard constructor  with the x , y  values. */
    	  Point2 ( const Real& x, const Real& y );
    	  /*! Copy constructor. */
    	  Point2 ( const Point2<Real>& p);
    	  /*! Constructor by Vector 2. */
    	  Point2 ( const Vector2<Real>& v);
    	  /*! Constructor by a array of any type. */
    	  /*!@warning If the type is not a number, the construtor will store trash.*/
    	  template < class T >
    	  Point2 (const T* p);
    	  virtual ~Point2(){};
    	  
    	  void 					Set( const Real& x, const Real& y );
    	  //@}

  		  /*! @name Accessing the value */
  		  //@{
  			
    	  /*! Conversion operator returning the memory address of the Point.

    	  Useful to pass as a parameter to OpenGL functions:
    	  \code
    	  LAL:Point2<float> pos, normal;
    	  glNormal2fv(normal);
    	  glVertex2fv(pos);
    	  \endcode */


    	  Real 					operator[]( unsigned int i)  const;

    	  Real& 				operator[]( unsigned int i);  
    	  //@}

    	  /*! @name Algebraic computations */
    	  // @{
    	  /*! Unary plus operator. */
    	  Point2<Real>  	  	operator+() const;
    	  /*! Unary minus operator. */
    	  Point2<Real>  	  	operator-() const;

    	  /*! Adds the point by a scalar \p factor. */
    	  Point2<Real>& 		operator+=( const Real& factor );
    	  /*! Subtracts the point by a scalar \p factor. */
    	  Point2<Real>& 		operator-=( const Real& factor );
    	  /*! Multiply the vector by a scalar \p k. */
    	  Point2<Real>& 		operator*=( const Real& factor );

    	  /*! Divides the vector by a scalar \p k.

    	   @wanning A test is performed to avoide division by zero. */

    	  Point2<Real>& 		operator/=( const Real& factor );
    	  /*!@see operator+ */
    	  template <class T>
    	  friend Point2<T> 		operator+( const T& factor,const Point2<T>& p  ) ;
    	  /*!@see operator+ */
    	  template <class T>
    	  friend Point2<T> 		operator+( const Point2<T>& p, const T& factor ) ;
    	  /*!@see operator- */
    	  template <class T>
    	  friend Point2<T> 		operator-( const T& factor, const Point2<T>& p ) ;
    	  /*!@see operator- */
    	  template <class T>
    	  friend Point2<T>		operator-( const Point2<T>& p, const T& factor ) ;  
    	  /*!@see operator* */
    	  template <class T>
    	  friend Point2<T> 		operator*( const T& factor, const Point2<T>& p ) ;
    	  /*!@see operator* */
    	  template <class T>
    	  friend Point2<T> 		operator*( const Point2<T>& p, const T& factor ) ;  
    	  /*!@see operator/ */
    	  Point2<Real> 			operator/( const Real& factor ) const;
    	  
    	  /*! Assigment operator. */
    	  Point2<Real>& 		operator= ( const Point2<Real>& p );
    	  /*! Adds \p a to the point. */
    	  Point2<Real>& 		operator+=( const Point2<Real>& p );
    	  /*! Subtract \p a to the vector. */
    	  Point2<Real>& 		operator-=( const Point2<Real>& p );
    	  /*! Divide \p a to the point by atribute to atribute. */
    	  /*\code
        	  p1.x() / p2.x();
        	  p1.x() / p2.y();
        	  \endcode */
    	  Point2<Real>& 		operator/=( const Point2<Real>& p );
    	  /*!@see operator+= */
    	  Point2<Real> 			operator+ (const Point2<Real>& p ) const;
    	  /*! This operation return a vector that has direction ...*/
    	  template <class T>
    	  friend Vector2<T>  	operator- (const Point2<T>& p,const Point2<T>& q ) ;

    	  bool 					operator== ( const Point2<Real>& p) const;
    	  bool 					operator!= ( const Point2<Real>& p) const;
    	  
    	  template <class T>
    	  friend Point2<T> 		operator+ (const Point2<T>& p, const Vector2<T>& v) ;  
    	  template <class T>
    	  friend Point2<T> 		operator+ (const Vector2<T>& v, const Point2<T>& p ) ;

    	  template <class T>
    	  friend Point2<T> 		operator-( const Point2<T>& p, const Vector2<T>& v ) ;  
    	  template <class T>
    	  friend Point2<T> 		operator-( const Vector2<T>& v, const Point2<T>& p ) ;  
    	  //@}
    	  /*! @name Output stream */
    	  //@{
    	  /*! Output stream operator. Enables debugging code like:
    	  \code
    	  LAL::Point2<> p(...);
    	  std::cout << "Point2" << " x = " << p.x() << " ,y = " << p.y() << std::endl;
    	  \endcode */
    	  template <class T>
    	  friend std::ostream& 	operator<< (std::ostream & s, const Point2<T>& p);
    	  //@}
    	  
    	  /*! @name Functions */
    	  //@{
    	  /*!  */
    	  Real 							SquaredDistance( const Point2<Real>& p ) ;
  		  const Real* 					ToRealPtr( void ) const;
  		  Real* 						ToRealPtr( void );
		  //@}
    	  
      public:
    	  /*! @name Members  */
    	  //@{
    	  /*! An union. */
    	  /*!
    	   * Shareed memory with abscissas atributes and the XY Array.
    	   * The Struct has the same size of the \code xy[] \endcode.
    	   */
    	  Real x; /*!< X abscissa of space. */  
    	  Real y; /*!< Y abscissa of space. */
    	
    	  //@}
      };
      
#include "Point2.inline.hpp"
     
} /* LAL :: NAMESPACE */

#endif /*POINT2_HPP_*/
