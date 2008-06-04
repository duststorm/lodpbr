#ifndef LAL_VECTOR2_HPP_
#define LAL_VECTOR2_HPP_


#include <iostream>

#include <cassert>
#include <cmath>


namespace LAL { 

/*!
*@class Vector2.
*@brief Class that represent a Vector in 2D.
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 25-Feb-2008.
*@todo OpenGL interface and a C style array.
*/  

	template <class Real>	class Vector2
	{

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
    
	public:

		// VETOR COLUNA OU VETOR LINHA ??
  	  /*! @name  Defining a Point2 */
  	  //@{
  	  /*! Default constructor. Value is set to (0,0,0). */
		Vector2 ();

		template < class T >
		Vector2 (const T* v);

		Vector2 ( const Vector2<Real>& v);

		Vector2 ( const Real& x, const Real& y );
		virtual ~Vector2 ();
		//@}
		//Operator

		/*! @name Accessing the value */
		//@{

		/*! Conversion operator returning the memory address of the Point.

  	  	Useful to pass as a parameter to OpenGL functions:	
  	  	\code
  	  	LAL:Point2<float> pos, normal;
  	  	glNormal2fv(normal);
  	  	glVertex2fv(pos);
  	  	\endcode */
		
		Real 				operator[]( unsigned int index) const;
		Real& 				operator[]( unsigned int index);
		//@}
		
		// Assignment Opertators
		//With Scalar
  	  	/*! @name Algebraic computations */
  	  	// @{
  	  	Vector2<Real>   	operator+() const;
  	  	Vector2<Real>   	operator-() const;
  	  	
		Vector2< Real >& 	operator+=( const Real& factor );
		Vector2< Real >& 	operator-=( const Real& factor ); 
		Vector2< Real >& 	operator*=( const Real& factor ); 
		Vector2< Real >& 	operator/=( const Real& factor );

		template <class T>
		friend Vector2<T>	operator*( const Vector2<T>& v, const T& factor ); 	
		template <class T>
		friend Vector2<T>	operator*( const T& factor, const Vector2<T>& v ); 
		template <class T>
		friend Vector2<T> 	operator/( const Vector2<T>& v, const T& factor ); 	
		template <class T>
		friend Vector2<T> 	operator+( const T& factor, const Vector2<T>& v );  
		template <class T>
		friend Vector2<T> 	operator+( const Vector2<T>& v, const T& factor );
		template <class T>
		friend Vector2<T> 	operator-( const T& factor, const Vector2<T>& v );  
		template <class T>
		friend Vector2<T> 	operator-( const Vector2<T>& v, const T& factor ); 
		
		
		
		// With Vector
		Vector2<Real>& 		operator= ( const Vector2<Real>& v );
		Vector2<Real>&		operator+=( const Vector2<Real>& v );
		Vector2<Real>&		operator-=( const Vector2<Real>& v ); 
		Vector2<Real>&		operator/=( const Vector2<Real>& v ); 
		
		bool 				operator==( const Vector2<Real>& v) const;
		bool 				operator!=( const Vector2<Real>& v) const;
		
		Vector2<Real>  		operator-( const Vector2<Real>& v) const;
		Vector2<Real>  		operator+( const Vector2<Real>& v) const;
		
		Real 				operator*( const Vector2<Real>& v ) const;
		//@}
		
  	  //@}
  	  /*! @name Output stream */
  	  //@{
  	  /*! Output stream operator. Enables debugging code like:
  	  \code
  	  LAL::Vector2<> p(...);
  	  std::cout << "Vector2" << " x = " << v.x << " ,y = " << v.y << std::endl;
  	  \endcode */
  	  template <class T>
  	  friend std::ostream& 	operator<<( std::ostream & s, const Vector2<T>& v );
  	  //@}
		
  	  	/*! @name Functions */
  	  	//@{
  	   	/*!  */
		Real 				Length( void );
		void 				Normalize( void );
		Vector2<Real> 		Norm( void );
		const Real* 	    ToRealPtr( void ) const;
		Real* 				ToRealPtr( void );
		
		//@}
	


	};

#include "Vector2.inline.hpp"

} /* LAL :: NAMESPACE */


#endif /*VECTOR2_HPP_*/

// CASOS DE TESTE


/* Teste operator+ e operator-
LAL::Vector2<double> v1(1.0,1.0,1.0);
LAL::Vector2<double> v2(-1.0,-1.0,-1.0);
LAL::Vector2<double> v3(0.0,0.0,0.0);

v3 = v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#v1+v2#"<<std::endl;
v3 = v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#v1-v2#"<<std::endl;
v3 = -v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#-v1-v2#"<<std::endl;
v3 = -v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#-v1+v2#"<<std::endl;
v3 = + v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#+v1-v2#"<<std::endl;
v3 = + v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#+v1+v2#"<<std::endl;
*/

/*Teste operator*
	LAL::Vector2<double> v1(1.0,1.0,1.0);
	LAL::Vector2<double> v3(0.0,0.0,0.0);
	
	v3 = 3.0 * v1;
	std::cout << v3.x << v3.y << v3.z << "#3*v1#"<<std::endl;
	v3 = 3.0 * (-v1);
	std::cout << v3.x << v3.y << v3.z << "#3*(-v1)#"<<std::endl;
	v3 = 3.0 * (+v1);
	std::cout << v3.x << v3.y << v3.z << "#3*(+v1)#"<<std::endl;
	v3 = (-v1) * 3.0;
	std::cout << v3.x << v3.y << v3.z << "#(-v1)*3#"<<std::endl;
	v3 = (+v1) * 3.0;
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*3#"<<std::endl;
	v3 = (+v1) * 0.0;
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*0.0#"<<std::endl;
	v3 = (+v1) * v2[1];
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*0.0#"<<std::endl;
*/

/* Teste operator* (puduto interno ou  produto escalar) 
LAL::Vector2<double> v1(6.0,-1.0,0.0);
LAL::Vector2<double> v2(0.5,-4.0,0.0);
double t = 0.0 ;
t = v1 * v2
std::cout << t << "#(v1)*(v2)#"<<std::endl;
v1[1] = v1*(-v2)
*/



/*
 * solucão para não ter warnning no retorno de uma referencia
Vector2<T>&  operator- ( const Vector2<T>& u) const
{
	Vector2<T> w;
	 	
	w.x = this->x - u.x;
	w.y = this->y - u.y;
	w.z = this->z - u.z;
		
	Vector2<T>& h = w;
	
	return ( h );
};
*/


