#ifndef VECTOR4_HPP_
#define VECTOR4_HPP_

#include <iostream>

#include <cassert>
#include <cmath>

#include "Vector3.hpp"

namespace LAL {

/*!
*@class Vector4.
*@brief Class that represent a Vector in 3D with w.
*@details ...
*@author Felipe Moura.
*@email fmc@cos.ufrj.br
*@version 1.0.
*@date 25-Feb-2008.
*@todo OpenGL interface and a C style array.
*/

	template <class Real>	class Vector4
	{

	public:

    	/*! @name Members  */
    	//@{
    	Real x; /*!< x abscissa of space. */
    	Real y; /*!< y abscissa of space. */
    	Real z; /*!< z abscissa of space. */
    	Real w; /*!< w abscissa of space. */
    	//@}

	public:

		friend class Vector3<Real>;
		// VETOR  LINHA

		// VETOR COLUNA OU VETOR LINHA ??

		/*! @name  Defining a Vector4 */
		//@{
		/*! Default constructor. Value is set to (0,0,0,0). */
		Vector4();
		template < class T >
		Vector4 (const T* v);
		Vector4( const Vector4<Real>& vector);
		Vector4( const Vector3<Real>& vector );
		Vector4( const Vector3<Real>& vector, const Real& w);
		Vector4( const Real& x, const Real& y, const Real& z, const Real& w );
		//@}

		//Operator

		/*! @name Accessing the value */
		//@{

		/*!Conversion operator returning the memory address of the Point.
		 * Useful to pass as a parameter to OpenGL functions:
		 * \code
		 * LAL:Vector3<float> pos, normal;
		 * glNormal3fv(normal);
		 * glVertex3fv(pos);
		 * \endcode */

		Real  					operator[]( int index ) const;

		Real& 					operator[]( int index );
		//@}

		// Assignment Opertators
		//With Scalar
 	  	/*! @name Algebraic computations */
  	  	// @{

  	  	Vector4<Real>   		operator+ ( ) const;
  	  	Vector4<Real>   		operator- ( ) const;

	    Vector4< Real >& 		operator+=( const Real& factor );
		Vector4< Real >& 		operator-=( const Real& factor );
		Vector4< Real >& 		operator*=( const Real& factor );
		Vector4< Real >& 		operator/=( const Real& factor );

		template <class T>
		friend Vector4<T> 		operator*( const Vector4<T>& v, const T& factor );
		template <class T>
		friend Vector4<T> 		operator*( const T& factor, const Vector4<T>& v );
		template <class T>
		friend Vector4<T> 		operator/( const Vector4<T>& v, const T& factor );
		template <class T>
		friend Vector4<T> 		operator+( const T& factor, const Vector4<T>& v );
		template <class T>
		friend Vector4<T> 		operator+( const Vector4<T>& v, const T& factor );
		template <class T>
		friend Vector4<T> 		operator-( const T& factor, const Vector4<T>& v );
		template <class T>
		friend Vector4<T> 		operator-( const Vector4<T>& v, const T& factor );



		// Assignment with Vector
		Vector4<Real>& 			operator= ( const Vector4<Real>& v );
		Vector4<Real>& 			operator+=( const Vector4<Real>& v );
		Vector4<Real>& 			operator-=( const Vector4<Real>& v );
		Vector4<Real>& 			operator/=( const Vector4<Real>& v );

		bool 					operator==( const Vector4<Real>& v) const;
		bool 					operator!=( const Vector4<Real>& v) const;

		Vector4<Real>  			operator-( const Vector4<Real>& v) const;
		Vector4<Real>  			operator+( const Vector4<Real>& v) const;

		Real 					operator*( const Vector4<Real>& v) const;

		//@}
		//@{
		/*! Output stream operator. Enables debugging code like:
    	  \code
    	  LAL::Vector3<> v(...);
    	  std::cout << "Vector4" << " x = " << v.x << " ,y = " << v.y << " ,z = " << v.z << " ,w = " << v.w << std::endl;
    	  \endcode */
		template <class T>
		friend std::ostream& 	operator<<(std::ostream & s, const Vector4<T>& v);

  	  	/*!@name Functions */
  	  	//@{
  	  	/*!  */
		// AUXILIAR FUNCTIONS

		Real 					Length( void );
		Real					LengthSqr( void );
		void 					Normalize( void );
		Vector4<Real> 			Norm( void );

		const Real* 			ToRealPtr( void ) const ;
		Real*	 				ToRealPtr( void ) ;
		//@}
		~Vector4 ();


	};// End Interface

	//============================= LIFECYCLE ====================================

	template<class Real>
	Vector4<Real>::Vector4()
	{
		this->x = static_cast< Real > ( 0 );
		this->y = static_cast< Real > ( 0 );
		this->z = static_cast< Real > ( 0 );
		this->w = static_cast< Real > ( 1 );
	};

	template< class Real>
	template< class T >
	Vector4<Real>::Vector4( const T* v )
	{
		assert(v);

		this->x = static_cast< Real > ( v[0] );
		this->y = static_cast< Real > ( v[1] );
		this->z = static_cast< Real > ( v[2] );
		this->w = static_cast< Real > ( v[3] );

	};

	template<class Real>
	Vector4<Real>::Vector4( const Vector4<Real>& v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = v.w;
	};

	template<class Real>
	Vector4<Real>::Vector4( const Vector3<Real>& v, const Real& w )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = w;
	};

	template<class Real>
	Vector4<Real>::Vector4( const Vector3<Real>& v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = static_cast< Real > (1);
	};

	template<class Real>
	Vector4<Real>::Vector4( const Real& x, const Real& y, const Real& z, const Real& w )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	};

	//============================= ACESS ======================================

	//Operator

	template<class Real>
	inline Real Vector4<Real>::operator[]( int index ) const
	{
		assert( ( index >= 0 ) && ( index < 4 ) );

		return ( ( &x )[ index ] );

	};

	template<class Real>
	inline Real& Vector4<Real>::operator[]( int index )
	{
		assert( ( index >= 0 ) && ( index < 4 ) );

		return ( ( &x )[ index ] );

	};

	//============================= OPERATORS ====================================

	// Assignment Opertators
	//With Scalar

	template<class Real>
	inline Vector4<Real> Vector4<Real>::operator+()  const
	{
		return ( Vector4<Real> (this->x, this->y, this->z, this->w)  );
	};

	/*!@brief operator-
	 * @details Unary operator tha return the negative of the point.
	 * @note To be clearer the arithmetic operations.
	 * @return Point3.
	 */
	template<class Real>
	inline Vector4<Real>  Vector4<Real>::operator-() const
	{

		return ( Vector4<Real> (-this->x, -this->y, -this->z, -this->w) );

	};

	template<class Real>
	inline Vector4< Real >& Vector4<Real>::operator+=( const Real&  factor )
	{
		this->x += factor;
		this->y += factor;
		this->z += factor;
		this->w += factor;

		return ( *this );
	}

	template<class Real>
	inline Vector4< Real >& Vector4<Real>::operator-=( const Real&  factor )
	{
		this->x -= factor;
		this->y -= factor;
		this->z -= factor;
		this->w -= factor;

		return ( *this );
	}

	template<class Real>
	inline Vector4< Real >& Vector4<Real>::operator*=( const Real& factor )
	{

		this->x  *= factor;
		this->y  *= factor;
		this->z  *= factor;
		this->w  *= factor;

		return ( *this );
	}

	template<class Real>
	inline Vector4< Real >& Vector4<Real>::operator/=( const Real& factor )
	{
		Real f = static_cast<Real>(1) / factor;

		this->x *= f;
		this->y *= f;
		this->z *= f;
		this->w *= f;

		return ( *this );
	}


	template<class Real>
	inline Vector4<Real> operator*( const Vector4<Real>& v, const Real& factor )
	{

		return ( Vector4<Real>( v.x * factor, v.y * factor, v.z * factor, v.w * factor ) );

	};

	template<class Real>
	inline Vector4<Real> operator*( const Real& factor, const Vector4<Real>& v )
	{
		return ( Vector4<Real>( v.x * factor, v.y * factor, v.z * factor, v.w * factor)	);

	};

	template<class Real>
	inline Vector4<Real> operator/( const Vector4<Real>& v, const Real& factor )
	{

		return (  Vector4<Real>( v.x / factor, v.y / factor, v.z / factor, v.w / factor) );

	};

	template<class Real>
	inline Vector4<Real> operator+( const Real& factor, const Vector4<Real>& v )
	{
		return ( Vector4<Real> ( v.x + factor, v.y + factor, v.z + factor, v.w + factor) );

	};

	template<class Real>
	inline Vector4<Real> operator+( const Vector4<Real>& v, const Real& factor )
	{
		return ( Vector4<Real> ( v.x + factor, v.y + factor, v.z + factor, v.w + factor) );

	};

	template<class Real>
	inline Vector4<Real> operator-( const Real& factor, const Vector4<Real>& v )
	{
		return ( Vector4<Real> ( factor - v.x , factor - v.y, factor - v.z, factor - v.w) );

	};

	template<class Real>
	inline Vector4<Real> operator-( const Vector4<Real>& v, const Real& factor )
	{
		return ( Vector4<Real> ( v.x - factor, v.y - factor, v.z - factor, v.w - factor) );

	};

	// With Vector

	template<class Real>
	inline Vector4<Real>& Vector4<Real>::operator=( const Vector4<Real>& v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		this->w = v.w;

		return ( *this );
	};

	template<class Real>
	inline Vector4< Real >& Vector4<Real>::operator+=(  const Vector4<Real>& v )
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		this->w += v.w;

		return ( *this );
	}

	template<class Real>
	inline Vector4< Real >& Vector4<Real>::operator-=(  const Vector4<Real>& v )
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		this->w -= v.w;

		return ( *this );
	}

	template<class Real>
	inline Vector4< Real >& Vector4<Real>::operator/=( const Vector4<Real>& v )
	{

		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
		this->w /= v.w;

		return ( *this );
	}

	template<class Real>
	inline bool Vector4<Real>::operator==( const Vector4<Real>& v) const
	{
		return ( ( this->x == v.x ) and ( this->y == v.y ) and ( this->z == v.z ) and (this->w == v.w) );
	};

	template<class Real>
	inline bool Vector4<Real>::operator!=( const Vector4<Real>& v) const
	{
		return  !(*this == v) ;
	};

	template<class Real>
	inline Vector4<Real>  Vector4<Real>::operator-( const Vector4<Real>& v) const
	{

		return ( Vector4 ( this->x - v.x, this->y - v.y, this->z - v.z,	this->w - v.w) );
	};

	template<class Real>
	inline Vector4<Real>  Vector4<Real>::operator+( const Vector4<Real>& v)	const
	{

		return ( Vector4 ( this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w) );

	};

	// Dot produt
	template<class Real>
	inline Real Vector4<Real>::operator*( const Vector4<Real>& v) const
	{

		return (  (v.x * x ) +  ( v.y * y ) + ( v.z * z ) + (v.w * w) );

	};


	template<class Real>
	inline std::ostream& operator<<( std::ostream & s, const Vector4<Real>& v )
	{
		s << "Vector4" << "  x = " << v.x
					   << " ,y = " << v.y
					   << " ,z = " << v.z
					   << " ,w = " << v.w << std::endl;

		return s;
	};

	//============================= OPERATIONS ===================================

	// AUXILIAR FUNCTIONS
	template<class Real>
	inline Real Vector4<Real>::Length( void )
	{
		return sqrt( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w) );
	};

	template<class Real>
	inline Real Vector4<Real>::LengthSqr( void )
	{
		return ( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w) );
	};

	template<class Real>
	inline void Vector4<Real>::Normalize( void )
	{
		Real factor = sqrt( (x * x) + (y * y) + (z * z) + (w * w) );

		assert (factor);

		Real lFactor = 1 / factor;

		x *= lFactor;
		y *= lFactor;
		z *= lFactor;
		w *= lFactor;

	};

	template<class Real>
	inline Vector4<Real> Vector4<Real>::Norm( void )
	{
		Real factor = sqrt( (x * x) + (y * y) + (z * z) + (w * w) );

		assert (factor);

		Real lFactor = 1 / factor;

		return ( Vector4 (x * lFactor, y * lFactor, z * lFactor, w * lFactor) );

	};

	template<class Real>
	const Real* Vector4<Real>::ToRealPtr( void ) const
	{
		return &x;
	}

	template<class Real>
	Real* Vector4<Real>::ToRealPtr( void )
	{
		return &x;
	}

	template <class Real>
	Vector4<Real>::~Vector4 (){};


} /* LAL :: NAMESPACE */


#endif

// CASOS DE TESTE


//// Teste operator+ e operator- with vectors
//LAL::Vector4<double> v1(1.0,1.0,1.0,0.0);
//LAL::Vector4<double> v2(-1.0,-1.0,-1.0,0.0);
//LAL::Vector4<double> v3(0.0,0.0,0.0,0.0);
//
//v3 = v1 + v2;
//std::cout << "#v1+v2# = 0,0,0 " << v3 << std::endl;
//v3 = v1 - v2;
//std::cout << "#v1+v2# = 2,2,2 " << v3 << std::endl;
//v3 = -v1 - v2;
//std::cout << "#-v1-v2# = 0,0,0 "<< v3 << std::endl;
//v3 = -v1 + v2;
//std::cout << "#-v1+v2# = -2,-2,-2 "<< v3 << std::endl;
//v3 = + v1 - v2;
//std::cout << "#+v1-v2# = 2,2,2 "<< v3 << std::endl;
//v3 = + v1 + v2;
//std::cout << "#+v1+v2 = 0,0,0 # "<< v3 << std::endl;
//
//// Teste operator+ e operator- with scalar
//
//v3 = v1 + 4.0;
//std::cout << "#v1+4# = 4,4,4 " << v3 << std::endl;
//v3 = 9.0 - v2;
//std::cout << "#9-v2# = 10,10,10 " << v3 << std::endl;
//v3 = -v1 / -8.0;
//std::cout << "#-v1-8# = 0.125,0.125,0.125 "<< v3 << std::endl;
//v3 = -v1 * 3.0;
//std::cout << "#-v1+3# = -3,-3,-3 "<< v3 << std::endl;
//
//
////Teste operator* with scalar
//v1 = LAL::Vector4<double>(1.0,1.0,1.0,0.0);
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//
//v3 = 3.0 * v1;
//std::cout << "#3*v1# = 3,3,3 "<<v3 << std::endl;
//v3 = 3.0 * (-v1);
//std::cout << "#3*(-v1)# = -3,-3,-3 " << v3 << std::endl;
//v3 = 3.0 * (+v1);
//std::cout << "#3*(+v1)# = 3,3,3 "<< v3 << std::endl;
//v3 = (-v1) * 3.0;
//std::cout << "#(-v1)*3# = -3,-3,-3 " << v3 << std::endl;
//v3 = (+v1) * 3.0;
//std::cout << "#(+v1)*3# = 3,3,3 "<< v3 << std::endl;
//v3 = (+v1) * 0.0;
//std::cout << "#(+v1)*0.0# = 0,0,0"<< v3 << std::endl;
//v3 = (+v1) * v2[3];
//std::cout << "#(+v1)*0.0# = 0,0,0" << v3 << std::endl;
//
//LAL::Vector4<double> v4(1.0,1.0,1.0,1.0);
//LAL::Vector4<double> v5(-1.0,-1.0,-1.0,-1.0);
//LAL::Vector4<double> v6(2.0,2.0,2.0,4.0);
//double r = 1.0;
//
//v3 += v4;
//std::cout << "#v3+=v4# = 1,1,1 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 += -3.0*v4;
//std::cout << "#v3+=-3*v4# = -3,-3,-3 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 += -v5+v4;
//std::cout << "#v3+=-v5+v4# = 2,2,2 "<<v3 << std::endl;
//
//v3 -= v4;
//std::cout << "#v3-=v4# = -1,-1,-1 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 -= -3.0*v4;
//std::cout << "#v3-=-3*v4# = 3,3,3 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 -= -v5+v4;
//std::cout << "#v3-=-v5+v4# = -2,-2,-2 "<<v3 << std::endl;
//
//r = v4 * v6;
//std::cout << "#v4*v64# = 10 "<< r << std::endl;
//r = v4[1] * v6[3];
//std::cout << "#v4[1]*v6[3]# = 4 "<< r << std::endl;
//
//v6 /= v4;
//std::cout << "#v6/=v4# = 2,2,2,4 "<<v6 << std::endl;
//v6 = LAL::Vector4<double>(2.0,2.0,2.0,4.0);
//v6 /= -3.0*v4;
//std::cout << "#v6/=-3*v4# = -0.666,-0.666,-0.666 "<<v6 << std::endl;
//v6 = LAL::Vector4<double>(2.0,2.0,2.0,4.0);
//v6 /= -v5+v4;
//std::cout << "#v6/=-v5+v4# = 1,1,1,2 "<<v6 << std::endl;
//
//std::vector<double> vec(static_cast< double * >(v4),static_cast< double * >(v4)+4);
//std::ostream_iterator<double> output( std::cout, " ");
//std::cout << "vec" << std::endl;
//
//std::copy(vec.begin(),vec.end(),output);
//
//solucão para não ter warnning no retorno de uma referencia
//inline Vector3<T>&  operator- ( const Vector3<T>& u) const
//{
//	Vector3<T> w;
//
//	w.x = this->x - u.x;
//	w.y = this->y - u.y;
//	w.z = this->z - u.z;
//
//	Vector3<T>& h = w;
//
//	return ( h );
//};

