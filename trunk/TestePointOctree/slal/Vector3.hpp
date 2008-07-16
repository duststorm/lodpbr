#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>

#include <cassert>
#include <cmath>


namespace LAL { 

/*!
*@class Vector3.
*@brief Class that represent a Vector in 3D.
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 25-Feb-2008.
*@todo OpenGL interface and a C style array.
*/     

	template <class Real>	class Vector3
	{

    public:
    	/*! @name Members  */
    	//@{
    	Real x; /*!< x abscissa of space. */  
    	Real y; /*!< y abscissa of space. */
    	Real z; /*!< z abscissa of space. */
    	//@}

    	static const Vector3 ZERO;
    	static const Vector3 UNIT_X;
    	static const Vector3 UNIT_Y;
    	static const Vector3 UNIT_Z;
    	static const Vector3 UNIT;

	public:

		// VETOR COLUNA OU VETOR LINHA ??
		
  	  	/*! @name  Defining a Vector3 */
  	  	//@{
  	  	/*! Default constructor. Value is set to (0,0,0). */
		Vector3 ();

		template < class T >
		Vector3 (const T* v);
		//Copy constructor			
		Vector3 ( const Vector3<Real>& v);
		
		template < typename T >
		Vector3 ( const Vector3<T>& v);

		Vector3 ( const Real& x, const Real& y, const Real& z );
		
		Vector3<Real>& 			operator=( const Vector3<Real>& v );
		
		void 					Set( const Real& x, const Real& y, const Real& z );
		//@}
		/*! @name Accessing the value */
		//@{

		/*! Conversion operator returning the memory address of the Point.

  	  	Useful to pass as a parameter to OpenGL functions:
  	  	\code
  	  	LAL:Vector3<float> pos, normal;
  	  	glNormal3fv(normal);
  	  	glVertex3fv(pos);
  	  	\endcode */
		
 		Real 					operator[]( int index) const;
		Real& 					operator[]( int index);
		//@}
		
		// Assignment Opertators
		//With Scalar
 	  	/*! @name Algebraic computations */
  	  	// @{
  	  	Vector3<Real>   		operator+() const;
  	  	Vector3<Real>   		operator-() const;
  	  	
		Vector3< Real >& 		operator+=( const Real& factor );
		Vector3< Real >& 		operator-=( const Real& factor ); 
		Vector3< Real >& 		operator*=( const Real& factor ); 
		Vector3< Real >& 		operator/=( const Real& factor );

		template <class T>
		friend Vector3<T> 		operator*( const Vector3<T>& v, const T& factor ); 	
		template <class T>
		friend Vector3<T> 		operator*( const T& factor, const Vector3<T>& v ); 
		template <class T>
		friend Vector3<T> 		operator/( const Vector3<T>& v, const T& factor ); 	
		template <class T>
		friend Vector3<T> 		operator+( const T& factor, const Vector3<T>& v );  
		template <class T>
		friend Vector3<T> 		operator+( const Vector3<T>& v, const T& factor );
		template <class T>
		friend Vector3<T> 		operator-( const T& factor, const Vector3<T>& v );  
		template <class T>
		friend Vector3<T> 		operator-( const Vector3<T>& v, const T& factor ); 
			
		// With Vector
		
		bool 					operator==( const Vector3<Real>& v ) const;
		bool 					operator!=( const Vector3<Real>& v ) const;
		
		Vector3<Real>& 			operator+=( const Vector3<Real>& v );
		Vector3<Real>& 			operator-=( const Vector3<Real>& v ); 
		Vector3<Real>& 			operator/=( const Vector3<Real>& v ); 
	
		Vector3<Real>  			operator-( const Vector3<Real>& v ) const;
		Vector3<Real>  			operator+( const Vector3<Real>& v ) const;
		
		Real 					operator*( const Vector3<Real>& v ) const;

		// Cross Product	
		inline Vector3<Real>  	operator^( const Vector3<Real>& v ) const;
		//@}
		//@{
		/*! Output stream operator. Enables debugging code like:
    	  \code
    	  LAL::Vector3<> v(...);
    	  std::cout << "Vector3" << " x = " << v.x << " ,y = " << v.y << " ,z = " << v.z << std::endl;
    	  \endcode */
		template <class T>
		friend std::ostream& 	operator<< ( std::ostream & s, const Vector3<T>& v);
  	  	/*!@name Functions */
  	  	//@{
  	  	/*!  */
		// AUXILIAR FUNCTIONS
		Real 					Length( void );
		Real 					LengthSqr( void );
		void 					Normalize( void );
		Vector3<Real> 			Norm( void );
		
		const Real* 			ToRealPtr( void ) const;
		Real* 					ToRealPtr( void );
		//@}

		~Vector3 ();


	};

#include "Vector3.inline.hpp"

} /* LAL :: NAMESPACE */


#endif

// CASOS DE TESTE


/* Teste operator+ e operator-
LAL::Vector3<double> v1(1.0,1.0,1.0);
LAL::Vector3<double> v2(-1.0,-1.0,-1.0);
LAL::Vector3<double> v3(0.0,0.0,0.0);

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
	LAL::Vector3<double> v1(1.0,1.0,1.0);
	LAL::Vector3<double> v3(0.0,0.0,0.0);
	
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
LAL::Vector3<double> v1(6.0,-1.0,0.0);
LAL::Vector3<double> v2(0.5,-4.0,0.0);
double t = 0.0 ;
t = v1 * v2
std::cout << t << "#(v1)*(v2)#"<<std::endl;
v1[1] = v1*(-v2)
*/



/*
 * solucão para não ter warnning no retorno de uma referencia
inline Vector3<T>&  operator- ( const Vector3<T>& vector) const
{
	Vector3<T> w;
	 	
	w.x = this->x - u.x;
	w.y = this->y - u.y;
	w.z = this->z - u.z;
		
	Vector3<T>& h = w;
	
	return ( h );
};
*/