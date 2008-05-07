#ifndef MATRIX3X3_HPP_
#define MATRIX3X3_HPP_

#include <iostream>

#include "Vector3.hpp" 
#include "Point3.hpp"


namespace CGL {

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

		Matrix3x3();
		Matrix3x3(Real a11, Real a12, Real a13,Real a21, Real a22, Real a23,Real a31, Real a32, Real a33);
		Matrix3x3(const Vector3<Real>& row1, const Vector3<Real>& row2, const Vector3<Real>& row3 );
		Matrix3x3(const Point3<Real>& row1, const Point3<Real>& row2, const Point3<Real>& row3 );
		
		// transpose
		inline Matrix3x3<Real> operator~ () const;
		
		inline operator const Real* () const;
		
		inline operator Real* ();
		
		inline const Real* operator[] (int rowIndex) const;
		
		inline Real* operator[] (int rowIndex);
		Real operator()  ( int i, int j )  	const;
		Real& operator() ( int i, int j );
		// Return Colum
		Vector3<Real> col ( int i ) const;
		Vector3<Real> row ( int i ) const;
		
		Real * getArray ();

		inline Matrix3x3<Real>& operator= ( const Matrix3x3<Real>& A);
		// 
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
		friend  inline std::ostream& operator<< (std::ostream & s, const Matrix3x3<T>& A);
	
		bool isSymetric ();
		Matrix3x3<Real> identity ();
	
		virtual ~Matrix3x3();

	};

#include "Matrix3x3.inline.hpp"

}// END NAMESPACE

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
