#ifndef MATRIX4X4_HPP_
#define MATRIX4X4_HPP_

// [Header files]
#include <iostream>
// [Project Includes]
#include "Math.hpp"
#include "Vector4.hpp" 
#include "Vector3.hpp"

  

namespace LAL {

/*! \brief The Matrix4x4 class .

*@class Matrix4x4.
*@brief Class that represent a dense 4x4 Matrix and Homogeneous Coordinate ..
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@todo OpenGL interface and a C style array, Why MakeView ans MakeProjection dont need The Transpose?
*@todo Não deu certo integrar por que minha nova 3x3 e 4x4 matrix estavam colum major , por isso dava dando bugs ...

  \nosubgrouping */

	template<class Real> class Matrix4x4
	{
	public:
		
		friend class Vector3<Real>;
		friend class Vector4<Real>;
	
		/*! @name Defining a Matrix4x4 */
		//@{
		/*! Default constructor. All value is set to 0. */
		Matrix4x4();
		 /*! Copy constructor. */ 
		Matrix4x4(const Matrix4x4<Real>& A );
		inline Matrix4x4<Real>& operator= ( const Matrix4x4<Real>& A);
		
		/*! Copy constructor for a Matrix with another type */
		template <class T>
		Matrix4x4(const Matrix4x4<T>& A );

		/*! Constructor. Four Vector4 representing the rows*/
		Matrix4x4(const Vector4<Real>& row1, const Vector4<Real>& row2, const Vector4<Real>& row3, const Vector4<Real>& row4 );
		/*! Constructor. Three Vector3 representing the three  first rows*/
		Matrix4x4(const Vector3<Real>& row1, const Vector3<Real>& row1, const Vector3<Real>& row3);
		
		 /*! Constructor. Taking 16 arguments. */
		Matrix4x4(Real a11, Real a12, Real a13, Real a14, 
				  Real a21, Real a22, Real a23, Real a24,
				  Real a31, Real a32, Real a31, Real a34, 
				  Real a41, Real a42, Real a43, Real a44 );
		virtual ~Matrix4x4();
		
		//@}
		
		/*! @name Accessing the value */
		//@{
		
		
		inline const Vector4<Real>& operator[] (int rowIndex) const;
		inline Vector4<Real>& operator[] (int rowIndex);
		
		Real  operator()  ( int i, int j )  	const;
		Real& operator() ( int i, int j );
		// Return Colum
		Vector4<Real> Column ( int i ) const;
		Vector4<Real> Row ( int i ) const;

		
		//@}
		
		/*! @name Algebraic computations */
		//@{
		inline Matrix4x4<Real> operator~ () const;
		inline Matrix4x4<Real>  operator- ( ) const;
		inline Matrix4x4<Real>  operator+ ( ) const;
		template <class T>
		friend inline Matrix4x4<T> operator* ( const T& factor, const Matrix4x4<T>& A);
		template <class T>
		friend inline Matrix4x4<T> operator* ( const Matrix4x4<T>& A, const T& factor);
		template <class T>
		friend inline Matrix4x4<T> operator/ ( const Matrix4x4<T>& A, const T& factor);
		
		inline Matrix4x4<Real>& operator/=( const Real& factor);
		inline Matrix4x4<Real>& operator*=( const Real& factor);
		inline Matrix4x4<Real>& operator+=( const Real& factor);
		inline Matrix4x4<Real>& operator-=( const Real& factor);

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
		
		//@}
		
		
		/*! @name Translate and Scalar */
		//@{
		Matrix4x4<Real> MakeTranslate (const Vector3<Real>& v) const;
		Matrix4x4<Real> MakeTranslate (const Vector4<Real>& v) const;
		Matrix4x4<Real> MakeTranslate (const Real& v0,const Real& v1,const Real& v2) const;
		
		Matrix4x4<Real> MakeScalar (const Vector3<Real>& v) const;

		//@}
		
		/*! @name Projection */
		static Matrix4x4<Real> MakeProjectionMatrix (const Real& fovy, const Real aspectRation, const Real& near, const Real& far) ;
		static Matrix4x4<Real> MakeViewMatrix       (const Vector3<Real>& eyes, const Vector3<Real>& position, const Vector3<Real>& up) ;
		//@}
		/*! @name Rotation  */
		//@{ 
		void FromHeadPitchRoll(Real headDegrees, Real pitchDegrees, Real rollDegrees);
		void Rotate(const Vector3<Real>& axis, Real& degrees);
		void ToHeadPitchRoll(Real &headDegrees, Real &pitchDegrees, Real &rollDegrees) const;
		//@}
		
		/*! @name Matrix Function  */
		//@{ 
				
		Matrix4x4<Real> Identity ();
		
		Real Determinant () const;
		
		Matrix4x4<Real> Inverse () const;
		//Inquiry
		bool IsSymetric ();
		
//		const Real* ToRealPtr( void ) const 
		
		Real* ToRealPtr( void );
		
		template <class T>
		friend  inline std::ostream& operator<< (std::ostream & s, const Matrix4x4<T>& A);
		//@}
		
	private:
		
	Vector4<Real> m[4];
	
	};

#include "Matrix4x4.inline.hpp"

}/* LAL :: NAMESPACE */

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


//LAL::Matrix4x4<float> m2 (5.0,1.0,6.0,0.0,
//						   9.0,7.0,8.0,0.0,
//						   4,5.0,6.0,0.0,
//						   0.0,0.0,0.0,0.0);
//LAL::Matrix4x4<float> m3;
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
