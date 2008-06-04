#ifndef MATRIX3X3_HPP_
#define MATRIX3X3_HPP_

#include <iostream>

#include "Vector3.hpp" 
#include "Point3.hpp"


namespace LAL {

/*! \brief The Matrix3x3 class .

*@class Matrix3x3.
*@brief Class that represent a dense 3x3 Matrix and Homogeneous Coordinate ..
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@todo OpenGL interface and a C style array, Why MakeView ans MakeProjection dont need The Transpose?

  \nosubgrouping */

	template<class Real> class Matrix3x3
	{
	private:
		
		Vector3<Real> m[ 3 ];		

	public:

		friend class Vector3<Real>;
		friend class Point3<Real>;
		/*! @name Defining a Matrix4x4 */
		//@{
		Matrix3x3();
		Matrix3x3( Real a11, Real a12, Real a13,Real a21, Real a22, Real a23,Real a31, Real a32, Real a33 );
		Matrix3x3( const Vector3<Real>& row1, const Vector3<Real>& row2, const Vector3<Real>& row3 );
		Matrix3x3( const Point3<Real>& row1, const Point3<Real>& row2, const Point3<Real>& row3 );
		virtual ~Matrix3x3();
		Matrix3x3<Real>& 		operator=( const Matrix3x3<Real>& A);
		//@}
		// transpose
		Matrix3x3<Real> 		operator~() const;
		/*! @name Accessing the value */
		//@{
		const Vector3<Real>& 	operator[]( int rowIndex ) const;
		Vector3<Real>& 			operator[]( int rowIndex );
		
		Real 					operator()( int i, int j )  	const;
		Real& 					operator()( int i, int j );
		// Return Colum
		Vector3<Real> 			Column( int index ) const;
		Vector3<Real> 			Row( int index ) const;
		//@}	
		// 
		/*! @name Algebraic computations */
		//@{
		Matrix3x3<Real>  		operator-() const;
		Matrix3x3<Real>  		operator+() const;

		template <class T>
		friend Matrix3x3<T> 	operator*( const T& factor, const Matrix3x3<T>& a );
		template <class T>
		friend Matrix3x3<T> 	operator*( const Matrix3x3<T>& a, const T& factor );
		template <class T>
		friend Matrix3x3<T> 	operator/( const Matrix3x3<T>& a, const T& factor );

		template <class T>
		friend Matrix3x3<T> 	operator+( const Matrix3x3<T>& a, const Matrix3x3<T>& b );
		template <class T>
		friend Matrix3x3<T> 	operator-( const Matrix3x3<T>& a, const Matrix3x3<T>& b );
		template <class T>
		friend Matrix3x3<T> 	operator*( const Matrix3x3<T>& a, const Matrix3x3<T>& b );
		
		template <class T>
		friend Vector3<T> 		operator*( const Matrix3x3<T>& a, const Vector3<T>& v );
		template <class T>
		friend Point3<T>  		operator*( const Matrix3x3<T>& a, const Point3<T>& p );
		//@}
	
		
		/*! @name Matrix Function  */
		//@{
		template <class T>
		friend  std::ostream& 	operator<< ( std::ostream & s, const Matrix3x3<T>& a );
		
		const Real* 			ToRealPtr( void ) const ;
		
		Real* 					ToRealPtr( void );
	
		bool 					IsSymetric();
		Matrix3x3<Real> 		Identity();
		
		//@}

	};

#include "Matrix3x3.inline.hpp"

}/* LAL :: NAMESPACE */

#endif /*MATRIX3X3_HPP_*/

// Tentar fazer operator [][] , ver geometric Tools Wm4::Math.h
//inline operator const Real* () const
//{
//return a;
//}
//----------------------------------------------------------------------------

//inline operator Real* ()
//{
//return a;
//}
