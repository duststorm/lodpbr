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
    	  Point2 ( const Vector2<Real>& u);
    	  /*! Constructor by a array of any type. */
    	  /*!@warning If the type is not a number, the construtor will store trash.*/
    	  template < typename P >
    	  Point2 (const P* p);
    	  virtual ~Point2(){};
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

    	  
    	  inline operator Real * ();
    	  inline operator const Real * ();

    	  inline  Real operator [] ( unsigned int i)  const;

    	  Real& operator [] ( unsigned int i);  
    	  //@}

    	  /*! @name Algebraic computations */
    	  // @{
    	  /*! Unary plus operator. */
    	  inline Point2<Real>  	  operator+ ( ) const;
    	  /*! Unary minus operator. */
    	  inline Point2<Real>  	  operator- ( ) const;

    	  /*! Adds the point by a scalar \p factor. */
    	  inline const Point2<Real>& operator+= ( const Real& factor );
    	  /*! Subtracts the point by a scalar \p factor. */
    	  inline const Point2<Real>& operator-= ( const Real& factor );
    	  /*! Multiply the vector by a scalar \p k. */
    	  inline const Point2<Real>& operator*= ( const Real& factor );

    	  /*! Divides the vector by a scalar \p k.

    	   @wanning A test is performed to avoide division by zero. */

    	  inline const Point2<Real>& operator/= ( const Real& factor );
    	  /*!@see operator+ */
    	  template <class T>
    	  inline friend Point2<T> operator+ (const T& factor,const Point2<T>& p  ) ;
    	  /*!@see operator+ */
    	  template <class T>
    	  inline friend Point2<T> operator+ (const Point2<T>& p, const T& factor ) ;
    	  /*!@see operator- */
    	  template <class T>
    	  inline friend Point2<T> operator- (const T& factor, const Point2<T>& p ) ;
    	  /*!@see operator- */
    	  template <class T>
    	  inline friend Point2<T> operator- (const Point2<T>& p, const T& factor ) ;  
    	  /*!@see operator* */
    	  template <class T>
    	  inline friend Point2<T> operator* (const T& factor, const Point2<T>& p ) ;
    	  /*!@see operator* */
    	  template <class T>
    	  inline friend Point2<T> operator* (const Point2<T>& p, const T& factor ) ;  
    	  /*!@see operator/ */
    	  inline Point2<Real> operator/ ( const Real& factor ) const;
    	  
    	  /*! Assigment operator. */
    	  inline const Point2<Real>& operator=  ( const Point2<Real>& p);
    	  /*! Adds \p a to the point. */
    	  inline const Point2<Real>& operator+= ( const Point2<Real>& u );
    	  /*! Subtract \p a to the vector. */
    	  inline const Point2<Real>& operator-= ( const Point2<Real>& u );
    	  /*! Divide \p a to the point by atribute to atribute. */
    	  /*\code
        	  p1.x() / p2.x();
        	  p1.x() / p2.y();
        	  \endcode */
    	  inline const Point2<Real>& operator/= ( const Point2<Real>& u );
    	  /*!@see operator+= */
    	  inline Point2<Real> operator+ (const Point2<Real>& p) const;
    	  /*! This operation return a vector that has direction ...*/
    	  template <class T>
    	  friend inline Vector2<T>  operator- (const Point2<T>& p,const Point2<T>& q ) ;

    	  inline bool operator== ( const Point2<Real>& p) const;
    	  inline bool operator!= ( const Point2<Real>& p) const;
    	  
    	  template <class T>
    	  inline friend Point2<T> operator+ (const Point2<T>& p, const Vector2<T>& u) ;  
    	  template <class T>
    	  inline friend Point2<T> operator+ (const Vector2<T>& u, const Point2<T>& p ) ;

    	  template <class T>
    	  inline friend Point2<T> operator- (const Point2<T>& p, const Vector2<T>& u ) ;  
    	  template <class T>
    	  inline friend Point2<T> operator- (const Vector2<T>& u, const Point2<T>& p ) ;  
    	  //@}
    	  /*! @name Output stream */
    	  //@{
    	  /*! Output stream operator. Enables debugging code like:
    	  \code
    	  LAL::Point2<> p(...);
    	  std::cout << "Point2" << " x = " << p.x() << " ,y = " << p.y() << std::endl;
    	  \endcode */
    	  template <class T>
    	  inline friend std::ostream& operator<< (std::ostream & s, const Point2<T>& p);
    	  //@}
    	  
    	  /*! @name Functions */
    	  //@{
    	  /*!  */
    	  Real squaredDistance ( const Point2<Real>& p ) ;
		  //@}
    	  
      public:
    	  /*! @name Members  */
    	  //@{
    	  /*! An union. */
    	  /*!
    	   * Shareed memory with abscissas atributes and the XY Array.
    	   * The Struct has the same size of the \code xy[] \endcode.
    	   */
    	  union
    	  {
    		  struct
    		  {
    			  Real x; /*!< X abscissa of space. */  
    			  Real y; /*!< Y abscissa of space. */
    		  };
    		  Real xy[2];/*!< Array of abscissas for fast operator return @see operator[].*/
    	  };
    	  //@}
      };
      
#include "Point2.inline.hpp"
     
} /* LAL :: NAMESPACE */

#endif /*POINT2_HPP_*/
