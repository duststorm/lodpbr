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
    	  Point3 ( const Point3<Real>& point);
    	  Point3 ( const Vector3<Real>& u);
    	  template < typename P >
    	  Point3 (const P* point);

    	  inline const Real& x() const;
    	  inline const Real& y() const;
    	  inline const Real& z() const;

    	  inline void Set(const Real& x, const Real& y, const Real& z);
    	  //Operator

    	  inline operator Real * ();
    	  inline operator const Real * ();
    	  
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
    	  inline friend Point3<T> operator+ (const T& factor,const Point3<T>& point  ) ;
    	  template <class T>
    	  inline friend Point3<T> operator+ (const Point3<T>& point, const T& factor ) ;
    	  template <class T>
    	  inline friend Point3<T> operator- (const T& factor, const Point3<T>& point ) ;  
    	  template <class T>
    	  inline friend Point3<T> operator- (const Point3<T>& point, const T& factor ) ;  

    	  template <class T>
    	  inline friend Point3<T> operator* (const T& factor, const Point3<T>& point ) ;  
    	  template <class T>
    	  inline friend Point3<T> operator* (const Point3<T>& point, const T& factor ) ;  

    	  inline Point3<Real> operator/ ( const Real& factor ) const;

    	  // Point/Point operations
    	  inline const Point3<Real>& operator=  ( const Point3<Real>& point);
    	  inline const Point3<Real>& operator+= ( const Point3<Real>& point );
    	  inline const Point3<Real>& operator-= ( const Point3<Real>& point );
    	  inline const Point3<Real>& operator/= ( const Point3<Real>& point );

    	  inline Point3<Real> operator+ (const Point3<Real>& point) const;
    	  template <class T>
    	  friend inline Vector3<T>  operator- (const Point3<T>& source,const Point3<T>& target ) ;

    	  inline bool operator== ( const Point3<Real>& point) const;
    	  inline bool operator!= ( const Point3<Real>& point) const;

    	  // Point/Vector
    	  template <class T>
    	  inline friend Point3<T> operator+ (const Point3<T>& point, const Vector3<T>& vector) ;  
    	  template <class T>
    	  inline friend Point3<T> operator+ (const Vector3<T>& vector, const Point3<T>& point ) ;

    	  template <class T>
    	  inline friend Point3<T> operator- (const Point3<T>& point, const Vector3<T>& vector ) ;  
    	  template <class T>
    	  inline friend Point3<T> operator- (const Vector3<T>& vector, const Point3<T>& point ) ;  

    	  template <class T>
    	  inline friend std::ostream& operator<< (std::ostream & s, const Point3<T>& point);
    
    	  // Functions
    	  Real SquaredDistance ( const Point3<Real>& point ) ;

    	  virtual ~Point3(){};

      };


#include "Point3.inline.hpp"
     
} /* LAL :: NAMESPACE */

#endif /*POINT3_HPP_*/

