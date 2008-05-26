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
		union
		{
			Real a[3][3];
			Real mA[9];
		};

	public:

		friend class Vector3<Real>;
		friend class Point3<Real>;
		/*! @name Defining a Matrix4x4 */
		//@{
		Matrix3x3();
		Matrix3x3(Real a11, Real a12, Real a13,Real a21, Real a22, Real a23,Real a31, Real a32, Real a33);
		Matrix3x3(const Vector3<Real>& row1, const Vector3<Real>& row2, const Vector3<Real>& row3 );
		Matrix3x3(const Point3<Real>& row1, const Point3<Real>& row2, const Point3<Real>& row3 );
		inline Matrix3x3<Real>& operator= ( const Matrix3x3<Real>& A);
		virtual ~Matrix3x3();
		//@}
		// transpose
		inline Matrix3x3<Real> operator~ () const;
		
		/*! @name Accessing the value */
		//@{
			
		inline operator const Real* () const;
		
		inline operator Real* ();
		
		inline const Real* operator[] (int rowIndex) const;
		
		inline Real* operator[] (int rowIndex);
		Real operator()  ( int i, int j )  	const;
		Real& operator() ( int i, int j );
		// Return Colum
		Vector3<Real> column ( int i ) const;
		Vector3<Real> row ( int i ) const;
		//@}	
		// 
		/*! @name Algebraic computations */
		//@{
		inline Matrix3x3<Real>  operator- ( ) const;
		inline Matrix3x3<Real>  operator+ ( ) const;

		template <class T>
		friend inline Matrix3x3<T> operator* ( const T& factor, const Matrix3x3<T>& A);
		template <class T>
		friend inline Matrix3x3<T> operator* ( const Matrix3x3<T>& A, const T& factor);
		template <class T>
		friend inline Matrix3x3<T> operator/ ( const Matrix3x3<T>& A, const T& factor);

		template <class T>
		friend inline Matrix3x3<T> operator+ (const Matrix3x3<T>& A, const Matrix3x3<T>& B);
		template <class T>
		friend inline Matrix3x3<T> operator- (const Matrix3x3<T>& A, const Matrix3x3<T>& B);
		template <class T>
		friend inline Matrix3x3<T> operator* (const Matrix3x3<T>& A, const Matrix3x3<T>& B);
		
		template <class T>
		friend inline Vector3<T> operator* ( const Matrix3x3<T>& A, const Vector3<T>& u);
		template <class T>
		friend inline Point3<T>  operator* ( const Matrix3x3<T>& A, const Point3<T>& p );
		template <class T>
		//@}
	
		
		/*! @name Matrix Function  */
		//@{ 
		friend  inline std::ostream& operator<< (std::ostream & s, const Matrix3x3<T>& A);
	
		bool isSymetric ();
		Matrix3x3<Real> identity ();
		
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
