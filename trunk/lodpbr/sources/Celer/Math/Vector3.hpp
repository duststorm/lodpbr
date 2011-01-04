#ifndef CELER_VECTOR3_HPP_
#define CELER_VECTOR3_HPP_

#include <iostream>

#include <cassert>
#include <cmath>


namespace Celer {

/*!
*@class Vector3.
*@brief Class that represent a Vector in 3D.
*@details ...
*@author Felipe Moura.
*@email fmc@cos.ufrj.br
*@version 1.0.
*@date 25-Feb-2008.
*@ TODO OpenGL interface and a C style array.
*@ TODO FriendShip wit Points
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
  	  	Celer:Vector3<float> pos, normal;
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
		Vector3<Real>  	operator^( const Vector3<Real>& v ) const;
		//@}
		//@{
		/*! Output stream operator. Enables debugging code like:
    	  \code
    	  Celer::Vector3<> v(...);
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

	    operator const Real *( void ) const;

	    operator Real * ( void ) ;
		//@}

		~Vector3 ();


	};// End Interface
	//============================= LIFECYCLE ====================================

	template<class Real>
	Vector3<Real>::Vector3()
	{
		this->x = static_cast< Real > ( 0 );
		this->y = static_cast< Real > ( 0 );
		this->z = static_cast< Real > ( 0 );
	};

	template< class Real>
	template< class T >
	Vector3<Real>::Vector3( const T* v )
	{
		assert(v);

		this->x = static_cast< Real > ( v[0] );
		this->y = static_cast< Real > ( v[1] );
		this->z = static_cast< Real > ( v[2] );

	};

	template< class Real>
	template< class T >
	Vector3<Real>::Vector3( const Vector3<T>& v )
	{
		this->x = static_cast< Real > (v.x);
		this->y = static_cast< Real > (v.y);
		this->z = static_cast< Real > (v.z);
	};


	template<class Real>
	Vector3<Real>::Vector3( const Vector3<Real>& v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	};

	template<class Real>
	Vector3<Real>::Vector3( const Real& x, const Real& y, const Real& z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	template<class Real>
	inline Vector3<Real>& Vector3<Real>::operator=( const Vector3<Real>& v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;

		return ( *this );
	};

	template<class Real>
	inline void Vector3<Real>::Set( const Real& x, const Real& y, const Real& z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};

	//============================= ACESS ======================================

	//Operator

	template<class Real>
	inline Real Vector3<Real>::operator[]( int index ) const
	{
		assert( ( index >= 0 ) && ( index < 3 ) );

		return ( ( &x )[ index ] );

	};

	template<class Real>
	inline Real& Vector3<Real>::operator[]( int index )
	{
		assert( ( index >= 0 ) && ( index < 3 ) );

		return ( ( &x )[ index ] );

	};

	//============================= OPERATORS ====================================

	// Assignment Opertators
	//With Scalar

	template<class Real>
	inline Vector3<Real> Vector3<Real>::operator+()  const
	{
		return ( Vector3<Real> (this->x, this->y, this->z)  );
	};


	template<class Real>
	inline Vector3<Real>  Vector3<Real>::operator-() const
	{

		return ( Vector3<Real> (-this->x, -this->y, -this->z) );

	};

	template<class Real>
	Vector3< Real >& Vector3<Real>::operator+=( const Real&  factor )
	{
		this->x += factor;
		this->y += factor;
		this->z += factor;

		return ( *this );
	}

	template<class Real>
	Vector3< Real >& Vector3<Real>::operator-=( const Real&  factor )
	{
		this->x -= factor;
		this->y -= factor;
		this->z -= factor;

		return ( *this );
	}

	template<class Real>
	Vector3< Real >& Vector3<Real>::operator*=( const Real& factor )
	{

		this->x  *= factor;
		this->y  *= factor;
		this->z  *= factor;

		return ( *this );
	}

	template<class Real>
	Vector3< Real >& Vector3<Real>::operator/=( const Real& factor )
	{
		Real lFactor = (Real)1 / factor;

		this->x *= lFactor;
		this->y *= lFactor;
		this->z *= lFactor;

		return ( *this );
	}


	template<class Real>
	inline Vector3<Real> operator*( const Vector3<Real>& v, const Real& factor )
	{

		return (  Vector3<Real>( v.x * factor, v.y * factor, v.z * factor )	);

	};

	template<class Real>
	inline Vector3<Real> operator*( const Real& factor, const Vector3<Real>& v )
	{
		return ( Vector3<Real>( v.x * factor, v.y * factor, v.z * factor ) );

	};

	template<class Real>
	inline Vector3<Real> operator/( const Vector3<Real>& v, const Real& factor )
	{

		return (  Vector3<Real>( v.x / factor, 	v.y / factor, v.z / factor ) );

	};

	template<class Real>
	inline Vector3<Real> operator+( const Real& factor, const Vector3<Real>& v )
	{
		return ( Vector3<Real> ( v.x + factor, v.y + factor, v.z + factor ) );

	};

	template<class Real>
	inline Vector3<Real> operator+( const Vector3<Real>& v, const Real& factor )
	{
		return ( Vector3<Real> ( v.x + factor, v.y + factor, v.z + factor ) );

	};

	template<class Real>
	inline Vector3<Real> operator-( const Real& factor, const Vector3<Real>& v )
	{
		return ( Vector3<Real> ( factor - v.x , factor - v.y , factor - v.z  ) );

	};

	template<class Real>
	inline Vector3<Real> operator-( const Vector3<Real>& v, const Real& factor )
	{
		return ( Vector3<Real> ( v.x - factor, 	v.y - factor, v.z - factor ) );

	};

	// With Vector


	template<class Real>
	Vector3< Real >& Vector3<Real>::operator+=(  const Vector3<Real>& v )
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return ( *this );
	}

	template<class Real>
	Vector3< Real >& Vector3<Real>::operator-=( const Vector3<Real>& v )
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;

		return ( *this );
	}

	template<class Real>
	Vector3< Real >& Vector3<Real>::operator/=( const Vector3<Real>& v )
	{

		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;

		return ( *this );
	}

	template<class Real>
	inline bool Vector3<Real>::operator==( const Vector3<Real>& v ) const
	{
		return ( ( this->x == v.x ) and ( this->y == v.y ) and ( this->z == v.z ) );
	};

	template<class Real>
	inline bool Vector3<Real>::operator!=( const Vector3<Real>& v) const
	{
		return  !(*this == v) ;
	};

	template<class Real>
	inline Vector3<Real>  Vector3<Real>::operator-( const Vector3<Real>& v ) const
	{

		return ( Vector3 ( this->x - v.x, this->y - v.y, this->z - v.z) );
	};

	template<class Real>
	inline Vector3<Real>  Vector3<Real>::operator+( const Vector3<Real>& v )	const
	{

		return ( Vector3 ( this->x + v.x, this->y + v.y, this->z + v.z) );

	};

	template<class Real>
	inline Real Vector3<Real>::operator*( const Vector3<Real>& v ) const
	{

		return (  (v.x * x ) +  ( v.y * y ) + ( v.z * z )  );

	};

	// Cross Product
	template<class Real>
	inline Vector3<Real>  Vector3<Real>::operator^( const Vector3<Real>& v ) const
	{
		return ( Vector3<Real> ( y*v.z - z*v.y, 	z*v.x - x*v.z, 	x*v.y - y*v.x ) );

	};

	//============================= OPERATIONS ===================================

	template<class Real>
	inline std::ostream& operator<<( std::ostream & s, const Vector3<Real>& v )
	{
		s << "Vector3"<< " x = " << v.x << " ,y = " << v.y << " ,z = " << v.z << std::endl;

		return s;
	};

	// AUXILIAR FUNCTIONS
	template<class Real>
	inline Real Vector3<Real>::Length()
	{
		return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
	};

	// AUXILIAR FUNCTIONS
	template<class Real>
	inline Real Vector3<Real>::LengthSqr()
	{
		return ( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) );
	};


	template<class Real>
	inline void Vector3<Real>::Normalize()
	{
		Real factor = std::sqrt( (x * x) + (y * y) + (z * z) );

		if (factor <= static_cast<Real>(0))
		{

		}
		else{
			Real d = 1 / factor;

			x *= d;
			y *= d;
			z *= d;


		}

	};

	template<class Real>
	inline Vector3<Real> Vector3<Real>::Norm ()
	{
		Real factor = sqrt( (x * x) + (y * y) + (z * z) );

		if (factor <= static_cast<Real>(0))
			return ( Vector3 (x, y, z) );


		Real d = 1 / factor;

		return ( Vector3<Real> (x * d, y * d, z * d) );

	};

	template<class Real>
	const Real* Vector3<Real>::ToRealPtr( void ) const
	{
		return &x;
	}

	template<class Real>
	Real* Vector3<Real>::ToRealPtr( void )
	{
		return &x;
	}

	template<class Real>
	inline Vector3<Real>::operator const Real *( void ) const { return &x; }

	template<class Real>
    inline Vector3<Real>::operator Real * ( void ) { return &x; }

	template <class Real>
	Vector3<Real>::~Vector3 (){};

} /* Celer :: NAMESPACE */


#endif

// CASOS DE TESTE


/* Teste operator+ e operator-
Celer::Vector3<double> v1(1.0,1.0,1.0);
Celer::Vector3<double> v2(-1.0,-1.0,-1.0);
Celer::Vector3<double> v3(0.0,0.0,0.0);

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
	Celer::Vector3<double> v1(1.0,1.0,1.0);
	Celer::Vector3<double> v3(0.0,0.0,0.0);

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
Celer::Vector3<double> v1(6.0,-1.0,0.0);
Celer::Vector3<double> v2(0.5,-4.0,0.0);
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
