#ifndef MATRIX4X4_HPP_
#define MATRIX4X4_HPP_

#include <iostream>

#include "Math.hpp"

#include "Vector4.hpp" 
#include "Vector3.hpp"

/*!
*@class Matrix4x4.
*@brief Class that represent a dense 4x4 Matrix and Homogeneous Coordinate ..
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@todo OpenGL interface and a C style array, Why MakeView ans MakeProjection dont need The Transpose?
*@todo Não deu certo integrar por que minha nova 3x3 e 4x4 matrix estavam colum major , por isso dava dando bugs ...
*@  
*/      

namespace CGL {

	template<class Real> class Matrix4x4
	{
	private:
		
		union
		{
			Real m[4][4];
			Real mA[16];
		};

	public:

		friend class Vector3<Real>;
		friend class Vector4<Real>;

		Matrix4x4();
		Matrix4x4(const Matrix4x4<Real>& A );

		Matrix4x4(const Real& a11, const Real& a12, const Real& a13, const Real& a14, 
				  const Real& a21, const Real& a22, const Real& a23, const Real& a24,
				  const Real& a31, const Real& a32, const Real& a31, const Real& a34, 
				  const Real& a41, const Real& a42, const Real& a43, const Real& a44 );
		
		Matrix4x4(const Vector4<Real>& u, const Vector4<Real>& v, const Vector4<Real>& t, const Vector4<Real>& w );
		
//		Matrix4x4(const Vector3<Real>& u, const Vector3<Real>& v, const Vector3<Real>& t);
				
		// Construct a Perspective Matrix
		Matrix4x4(const Real& fovy, const Real aspectRation, const Real& near, const Real& far);
		// Construct a View Matrix
		Matrix4x4(const Vector3<Real>& eyes, const Vector3<Real>& position, const Vector3<Real>& up);
		// transpose
		inline Matrix4x4<Real> operator~ () const;
		
		inline operator const Real* () const;
		
		inline operator Real* ();
		
		inline const Real* operator[] (int rowIndex) const;
		
		inline Real* operator[] (int rowIndex);
		Real  operator()  ( int i, int j )  	const;
		Real& operator() ( int i, int j );
		// Return Colum
		Vector4<Real> col ( int i ) const;
		Vector4<Real> row ( int i ) const;
		
		inline Matrix4x4<Real>& operator= ( const Matrix4x4<Real>& A);
		// 
		inline Matrix4x4<Real>  operator- ( ) const;
		inline Matrix4x4<Real>  operator+ ( ) const;

		template <class T>
		friend inline Matrix4x4<T> operator* ( const T& factor, const Matrix4x4<T>& A);
		template <class T>
		friend inline Matrix4x4<T> operator* ( const Matrix4x4<T>& A, const T& factor);
		template <class T>
		friend inline Matrix4x4<T> operator/ ( const Matrix4x4<T>& A, const T& factor);
		
		inline Matrix4x4<Real>& operator/= ( const Real& factor);

		template <class T>
		friend inline Matrix4x4<T> operator+ (const Matrix4x4<T>& A, const Matrix4x4<T>& B);
		template <class T>
		friend inline Matrix4x4<T> operator- (const Matrix4x4<T>& A, const Matrix4x4<T>& B);
		template <class T>
		friend inline Matrix4x4<T> operator* (const Matrix4x4<T>& A, const Matrix4x4<T>& B);
		
		template <class T>
		friend inline Vector3<T> operator* ( const Matrix4x4<T>& A, const Vector4<T>& u);
		
		template <class T>
		friend inline Vector3<T> operator* ( const Matrix4x4<T>& A, const Vector3<T>& u);
		
		template <class T>
		friend  inline std::ostream& operator<< (std::ostream & s, const Matrix4x4<T>& A);
	
		bool isSymetric ();
		Matrix4x4<Real> identity ();
		
		Real Determinant () const;
		
		Matrix4x4<Real> Inverse () const;
		
		Matrix4x4<Real> MakeTranslate (const Vector3<Real>& v) const;
		Matrix4x4<Real> MakeTranslate (const Vector4<Real>& v) const;
		Matrix4x4<Real> MakeTranslate (const Real& v0,const Real& v1,const Real& v2) const;
		
		Matrix4x4<Real> MakeScalar (const Vector3<Real>& v) const;
		Matrix4x4<Real> MakeScalar (const Vector4<Real>& v) const;
		
		Matrix4x4<Real> MakeProjectionMatrix (const Real& fovy, const Real aspectRation, const Real& near, const Real& far) const;
		Matrix4x4<Real> MakeViewMatrix       (const Vector3<Real>& eyes, const Vector3<Real>& position, const Vector3<Real>& up) const;
		
		void FromHeadPitchRoll(Real headDegrees, Real pitchDegrees, Real rollDegrees);
		void Rotate(const Vector3<Real>& axis, Real& degrees);
		void ToHeadPitchRoll(Real &headDegrees, Real &pitchDegrees, Real &rollDegrees) const;
		virtual ~Matrix4x4();

	};

#include "Matrix4x4.inline.hpp"

}// END NAMESPACE

#endif /*MATRIX4X4_HPP_*/

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


//CGL::Matrix4x4<float> m2 (5.0,1.0,6.0,0.0,
//						   9.0,7.0,8.0,0.0,
//						   4,5.0,6.0,0.0,
//						   0.0,0.0,0.0,0.0);
//CGL::Matrix4x4<float> m3;
//
//
//std::cout << m3;
//
//m3 = m1 * m2;
//
//std::cout << "#m3 = m1*m2 = # "
//"\n  m[1][1] = 184 ,m[1][2] = 88 ,m[1][3] = 214 "
//"\n  m[2][1] = 105 ,m[2][2] = 92 ,m[2][3] = 112 "
//"\n  m[3][1] = 111 ,m[3][2] = 87 ,m[3][3] = 126 \n"  << m3 << std::endl;
//
//m3 = -m1 + m2; 
//std::cout << "#m3 = -m1+m2 = # "
//"\n  m[1][1] = 28 ,m[1][2] = 6 ,m[1][3] = 12 "
//"\n  m[2][1] = 10 ,m[2][2] = 15 ,m[2][3] = 15 "
//"\n  m[3][1] = 9 ,m[3][2] = 11,m[3][3] = 14 \n"  << m3 << std::endl;
//
//m3 = (-m2) / (-2.0f); 
//std::cout << "#m3 = 2.0* (-m2) = # "
//"\n m[1][1] = -10 ,m[1][2] = -2 ,m[1][3] = -12 "
//"\n m[2][1] =  -18 , m[2][2] = -14 ,m[2][3]  = -16 "
//"\n m[3][1] =  -8  ,m[3][2] = -10 ,m[3][3] =  -12 \n"  << m3 << std::endl;
//
//
//std::cout << m3;
