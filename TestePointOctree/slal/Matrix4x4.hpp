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

	template <class Real>
	Matrix4x4<Real>::Matrix4x4()
	{
		this->m[0][0] =  static_cast< Real > ( 1 );
		this->m[0][1] =  static_cast< Real > ( 0 );
		this->m[0][2] =  static_cast< Real > ( 0 );
		this->m[0][3] =  static_cast< Real > ( 0 );
		
		this->m[1][0] =  static_cast< Real > ( 0 );
		this->m[1][1] =  static_cast< Real > ( 1 ); 
		this->m[1][2] =  static_cast< Real > ( 0 );
		this->m[1][3] =  static_cast< Real > ( 0 );
		
		this->m[2][0] =  static_cast< Real > ( 0 );
		this->m[2][1] =  static_cast< Real > ( 0 );
		this->m[2][2] =  static_cast< Real > ( 1 );
		this->m[2][3] =  static_cast< Real > ( 0 );
		
		this->m[3][0] =  static_cast< Real > ( 0 ); 
		this->m[3][1] =  static_cast< Real > ( 0 );
		this->m[3][2] =  static_cast< Real > ( 0 );
		this->m[3][3] =  static_cast< Real > ( 1 );
	};

	template <class Real>
	Matrix4x4<Real>::Matrix4x4(const Matrix4x4<Real>& A)
	{
		this->m[0][0] = A.m[0][0]; this->m[0][1] = A.m[0][1]; this->m[0][2] = A.m[0][2]; this->m[0][3] = A.m[0][3]; 
		this->m[1][0] = A.m[1][0]; this->m[1][1] = A.m[1][1]; this->m[1][2] = A.m[1][2]; this->m[1][3] = A.m[1][3];
 		this->m[2][0] = A.m[2][0]; this->m[2][1] = A.m[2][1]; this->m[2][2] = A.m[2][2]; this->m[2][3] = A.m[2][3];
		this->m[3][0] = A.m[3][0]; this->m[3][1] = A.m[3][1]; this->m[3][2] = A.m[3][2]; this->m[3][3] = A.m[3][3];
	}
	
	template <class Real>
	Matrix4x4<Real>::Matrix4x4(const Real& fov, const Real aspectRation, const Real& near, const Real& far)
	{
		this = this->MakeProjectionMatrix(fov,aspectRation,near,far);
	};
	
	template <class Real>
	Matrix4x4<Real>::Matrix4x4(const Vector3<Real>& eyes, const Vector3<Real>& position, const Vector3<Real>& up)
	{

		Vector3<Real> zaxis = (eyes - position).norm();
		Vector3<Real> xaxis = (up ^ zaxis).norm();
		Vector3<Real> yaxis =  zaxis ^ xaxis;

		this->m[0][0] = xaxis.mX; this->m[0][1] = xaxis.mY; this->m[0][2] = xaxis.mZ; this->m[0][3] = -(xaxis * eyes);
		this->m[1][0] = yaxis.mX; this->m[1][1] = yaxis.mY; this->m[1][2] = yaxis.mZ; this->m[1][3] = -(yaxis * eyes);
		this->m[2][0] = zaxis.mX; this->m[2][1] = zaxis.mY; this->m[2][2] = zaxis.mZ; this->m[2][3] = -(zaxis * eyes);
		
		this->m[3][0] = static_cast< Real > ( 0 );    
		this->m[3][1] = static_cast< Real > ( 0 );    
		this->m[3][2] = static_cast< Real > ( 0 );
		this->m[3][3] = static_cast< Real > ( 1 );

		

		
			
	};
	
	template <class Real>
	Matrix4x4<Real>::Matrix4x4(const Real& a00, const Real& a01, const Real& a02, const Real& a03,
							   const Real& a10, const Real& a11, const Real& a12, const Real& a13, 
							   const Real& a20, const Real& a21, const Real& a22, const Real& a23,
							   const Real& a30, const Real& a31, const Real& a32, const Real& a33)
	{
		this->m[0][0] = a00; this->m[0][1] = a01; this->m[0][2] = a02; this->m[0][3] = a03; 
		this->m[1][0] = a10; this->m[1][1] = a11; this->m[1][2] = a12; this->m[1][3] = a13;
 		this->m[2][0] = a20; this->m[2][1] = a21; this->m[2][2] = a22; this->m[2][3] = a23;
		this->m[3][0] = a30; this->m[3][1] = a31; this->m[3][2] = a32; this->m[3][3] = a33;
	};

	template <class Real>
	Matrix4x4<Real>::Matrix4x4(const Vector4<Real>& u, const Vector4<Real>& v, const Vector4<Real>& t, const Vector4<Real>& w  )
	{
		this->m[0][0] = u.mX; this->m[0][1] = u.mY; this->m[0][2] = u.mZ; this->m[0][3] = u.mW;
		this->m[1][0] = v.mX; this->m[1][1] = v.mY; this->m[1][2] = v.mZ; this->m[1][3] = v.mW;
		this->m[2][0] = t.mX; this->m[2][1] = t.mY; this->m[2][2] = t.mZ; this->m[2][3] = t.mW;
		this->m[3][0] = w.mX; this->m[3][1] = w.mY; this->m[3][2] = w.mZ; this->m[3][3] = w.mW;
	};
	
//	template <class Real>
//	Matrix4x4<Real>::Matrix4x4(const Vector3<Real>& u, const Vector3<Real>& v, const Vector3<Real>& t)
//	{
//		this->m[0][0] = u.mX; this->m[0][1] = u.mY; this->m[0][2] = u.mZ; this->m[0][3] = static_cast< Real > ( 0 );
//		this->m[1][0] = v.mX; this->m[1][1] = v.mY; this->m[1][2] = v.mZ; this->m[1][3] = static_cast< Real > ( 0 );
//		this->m[2][0] = t.mX; this->m[2][1] = t.mY; this->m[2][2] = t.mZ; this->m[2][3] = static_cast< Real > ( 0 ) ;
//		this->m[3][0] = static_cast< Real > ( 0 ); this->m[3][1] = static_cast< Real > ( 0 ); this->m[3][2] =	static_cast< Real > ( 0 ) ; this->m[3][3] = static_cast< Real > ( 1 );
//	};
	

	
	// transpose
	template <class Real>
	inline Matrix4x4<Real> Matrix4x4<Real>::operator~ () const
	{
		return ( Matrix4x4<Real>( m[0][0],m[1][0],m[2][0],m[3][0],
		                          m[0][1],m[1][1],m[2][1],m[3][1],
		                          m[0][2],m[1][2],m[2][2],m[3][2],
		                          m[0][3],m[1][3],m[2][3],m[3][3])
		);

	};

	template <class Real>
	inline Matrix4x4<Real>::operator const Real* () const
	{
		return mA;
	}
	//----------------------------------------------------------------------------
	
	template <class Real>
	inline Matrix4x4<Real>::operator Real* ()
	{
		return mA;
	}
	//----------------------------------------------------------------------------

	template <class Real>
	inline const Real* Matrix4x4<Real>::operator[] (int rowIndex) const
	{
		return &mA[4*rowIndex];
	}
	//----------------------------------------------------------------------------

	template <class Real>
	inline Real* Matrix4x4<Real>::operator[] (int rowIndex)
	{
		return &mA[4*rowIndex];
	}

	template <class Real>
	Real Matrix4x4<Real>::operator() ( int i, int j )  	const
	{

		if( i<0 || j<0 || i>=4 || j>=4 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( m[i][j] );

	}

	template <class Real>
	Real& Matrix4x4<Real>::operator() ( int i, int j )  
	{

		if( i<0 || j<0 || i>=4 || j>=4 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( m[i][j] );

	}


	// Return Colum
	template <class Real>
	Vector4<Real> Matrix4x4<Real>::col ( int i )  const
	{

		if( i<0 || i>=4 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( Vector4<Real>( m[0][i] , m[1][i] , mA[2][i] , m[3][i] ) );

	}

	template <class Real>
	Vector4<Real> Matrix4x4<Real>::row ( int i ) const  
	{

		if( i<0 || i>=4 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( Vector4<Real>( m[i][0] , m[i][1] , m[i][2] , m[i][3] ) );

	}


	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator= ( const Matrix4x4<Real>& A)
	{

		this->m[0][0] = A(0,0); this->m[0][1] = A(0,1); this->m[0][2] = A(0,2); this->m[0][3] = A(0,3); 
		this->m[1][0] = A(1,0); this->m[1][1] = A(1,1); this->m[1][2] = A(1,2); this->m[1][3] = A(1,3);
		this->m[2][0] = A(2,0); this->m[2][1] = A(2,1); this->m[2][2] = A(2,2); this->m[2][3] = A(2,3);
		this->m[3][0] = A(3,0); this->m[3][1] = A(3,1); this->m[3][2] = A(3,2); this->m[3][3] = A(3,3);

		return ( *this );
	};

	// FRIEND FUNCRealIONS

	template <class Real>
	inline Matrix4x4<Real>  Matrix4x4<Real>::operator- ( ) const
	{

		return ( Matrix4x4<Real>( -this->m[0][0],-this->m[0][1],-this->m[0][2],-this->m[0][3],
								  -this->m[1][0],-this->m[1][1],-this->m[1][2],-this->m[1][3],
								  -this->m[2][0],-this->m[2][1],-this->m[2][2],-this->m[2][3],
								  -this->m[3][0],-this->m[3][1],-this->m[3][2],-this->m[3][3])
		);

	};

	template <class Real>
	inline Matrix4x4<Real>  Matrix4x4<Real>::operator+ ( ) const
	{
		return ( Matrix4x4<Real>( this->m[0][0],this->m[0][1],this->m[0][2],this->m[0][3],
								  this->m[1][0],this->m[1][1],this->m[1][2],this->m[1][3],
								  this->m[2][0],this->m[2][1],this->m[2][2],this->m[2][3],
								  this->m[3][0],this->m[3][1],this->m[3][2],this->m[3][3])
		);
	};

	template <class Real>
	inline Matrix4x4<Real> operator+ (const Matrix4x4<Real>& A, const Matrix4x4<Real>& B)
	{

		return ( Matrix4x4<Real>( A.m[0][0] + B.m[0][0], A.m[0][1] + B.m[0][1], A.m[0][2] + B.m[0][2], A.m[0][3] + B.m[0][3],
								  A.m[1][0] + B.m[1][0], A.m[1][1] + B.m[1][1], A.m[1][2] + B.m[1][2], A.m[1][3] + B.m[1][3], 
								  A.m[2][0] + B.m[2][0], A.m[2][1] + B.m[2][1], A.m[2][2] + B.m[2][2], A.m[2][3] + B.m[2][3],
								  A.m[3][0] + B.m[3][0], A.m[3][1] + B.m[3][1], A.m[3][2] + B.m[3][2], A.m[3][3] + B.m[3][3])
		);	
	};

	template <class Real>
	inline Matrix4x4<Real> operator- (const Matrix4x4<Real>& A, const Matrix4x4<Real>& B)
	{

		return ( Matrix4x4<Real>( A.m[0][0] - B.m[0][0], A.m[0][1] - B.m[0][1], A.m[0][2] - B.m[0][2], A.m[0][3] - B.m[0][3],
								  A.m[1][0] - B.m[1][0], A.m[1][1] - B.m[1][1], A.m[1][2] - B.m[1][2], A.m[1][3] - B.m[1][3],
								  A.m[2][0] - B.m[2][0], A.m[2][1] - B.m[2][1], A.m[2][2] - B.m[2][2], A.m[2][3] - B.m[2][3],
								  A.m[3][0] - B.m[3][0], A.m[3][1] - B.m[3][1], A.m[3][2] - B.m[3][2], A.m[3][3] - B.m[3][3])
		);	
	};

	template <class Real>
	inline Matrix4x4<Real> operator* ( const Real& factor, const Matrix4x4<Real>& A)
	{

		return ( Matrix4x4<Real>( 	A.m[0][0] * factor, A.m[0][1] * factor, A.m[0][2] * factor, A.m[0][3] * factor,
									A.m[1][0] * factor, A.m[1][1] * factor, A.m[1][2] * factor, A.m[1][3] * factor,
									A.m[2][0] * factor, A.m[2][1] * factor, A.m[2][2] * factor, A.m[2][3] * factor, 
									A.m[3][0] * factor, A.m[3][1] * factor, A.m[3][2] * factor, A.m[3][3] * factor)
		);	

	};

	template <class Real>
	inline Matrix4x4<Real> operator* ( const Matrix4x4<Real>& A, const Real& factor)
	{

		return ( Matrix4x4<Real>( 	A.m[0][0] * factor, A.m[0][1] * factor, A.m[0][2] * factor, A.m[0][3] * factor,
									A.m[1][0] * factor, A.m[1][1] * factor, A.m[1][2] * factor, A.m[1][3] * factor,
									A.m[2][0] * factor, A.m[2][1] * factor, A.m[2][2] * factor, A.m[2][3] * factor, 
									A.m[3][0] * factor, A.m[3][1] * factor, A.m[3][2] * factor, A.m[3][3] * factor)
		);	
	};

	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator/= ( const Real& factor)
	{
		
		if( factor == 0 ){
			std::cerr << "[ERROR]" << std::endl
			<< " division by zero."
			<< std::endl;
			exit(1);
		}

		Real lFactor = 1 / factor;

		 	m[0][0] *= lFactor; m[0][1] *= lFactor; m[0][2] *= lFactor; m[0][3] *= lFactor;
		 	m[1][0] *= lFactor; m[1][1] *= lFactor; m[1][2] *= lFactor; m[1][3] *= lFactor;
		 	m[2][0] *= lFactor; m[2][1] *= lFactor; m[2][2] *= lFactor; m[2][3] *= lFactor; 
		 	m[3][0] *= lFactor; m[3][1] *= lFactor; m[3][2] *= lFactor; m[3][3] *= lFactor;
		 	
		return (*this);
	};
	
	template <class Real>
	inline Matrix4x4<Real> operator/ ( const Matrix4x4<Real>& A, const Real& factor)
	{
		Matrix4x4<Real> B;

		if( factor == 0 ){
			std::cerr << "[ERROR]" << std::endl
			<< " division by zero."
			<< std::endl;
			exit(1);
		}

		Real lFactor = 1 / factor;

		return ( Matrix4x4<Real>( 	A.m[0][0] * lFactor, A.m[0][1] * lFactor, A.m[0][2] * lFactor, A.m[0][3] * lFactor,
									A.m[1][0] * lFactor, A.m[1][1] * lFactor, A.m[1][2] * lFactor, A.m[1][3] * lFactor,
									A.m[2][0] * lFactor, A.m[2][1] * lFactor, A.m[2][2] * lFactor, A.m[2][3] * lFactor, 
									A.m[3][0] * lFactor, A.m[3][1] * lFactor, A.m[3][2] * lFactor, A.m[3][3] * lFactor)
		);	
	};


	template <class Real>
	inline Matrix4x4<Real> operator* ( const Matrix4x4<Real>& A, const Matrix4x4<Real>& B)
	{
		return ( Matrix4x4<Real>( A.m[0][0] * B.m[0][0] + A.m[0][1] * B.m[1][0] + A.m[0][2] * B.m[2][0] + A.m[0][3] * B.m[3][0],
								  A.m[0][0] * B.m[0][1] + A.m[0][1] * B.m[1][1] + A.m[0][2] * B.m[2][1] + A.m[0][3] * B.m[3][1], 
								  A.m[0][0] * B.m[0][2] + A.m[0][1] * B.m[1][2] + A.m[0][2] * B.m[2][2] + A.m[0][3] * B.m[3][2],
								  A.m[0][0] * B.m[0][3] + A.m[0][1] * B.m[1][3] + A.m[0][2] * B.m[2][3] + A.m[0][3] * B.m[3][3],

								  A.m[1][0] * B.m[0][0] + A.m[1][1] * B.m[1][0] + A.m[1][2] * B.m[2][0] + A.m[1][3] * B.m[3][0],
								  A.m[1][0] * B.m[0][1] + A.m[1][1] * B.m[1][1] + A.m[1][2] * B.m[2][1] + A.m[1][3] * B.m[3][1],
								  A.m[1][0] * B.m[0][2] + A.m[1][1] * B.m[1][2] + A.m[1][2] * B.m[2][2] + A.m[1][3] * B.m[3][2], 
								  A.m[1][0] * B.m[0][3] + A.m[1][1] * B.m[1][3] + A.m[1][2] * B.m[2][3] + A.m[1][3] * B.m[3][3],
								  
								  A.m[2][0] * B.m[0][0] + A.m[2][1] * B.m[1][0] + A.m[2][2] * B.m[2][0] + A.m[2][3] * B.m[3][0],
								  A.m[2][0] * B.m[0][1] + A.m[2][1] * B.m[1][1] + A.m[2][2] * B.m[2][1] + A.m[2][3] * B.m[3][1],
								  A.m[2][0] * B.m[0][2] + A.m[2][1] * B.m[1][2] + A.m[2][2] * B.m[2][2] + A.m[2][3] * B.m[3][2],
								  A.m[2][0] * B.m[0][3] + A.m[2][1] * B.m[1][3] + A.m[2][2] * B.m[2][3] + A.m[2][3] * B.m[3][3],
								 								  
								  A.m[3][0] * B.m[0][0] + A.m[3][1] * B.m[1][0] + A.m[3][2] * B.m[2][0] + A.m[3][3] * B.m[3][0],
								  A.m[3][0] * B.m[0][1] + A.m[3][1] * B.m[1][1] + A.m[3][2] * B.m[2][1] + A.m[3][3] * B.m[3][1],
								  A.m[3][0] * B.m[0][2] + A.m[3][1] * B.m[1][2] + A.m[3][2] * B.m[2][2] + A.m[3][3] * B.m[3][2],
								  A.m[3][0] * B.m[0][3] + A.m[3][1] * B.m[1][3] + A.m[3][2] * B.m[2][3] + A.m[3][3] * B.m[3][3])

		); 

	};

	template <class Real>
	inline Vector3<Real> operator* ( const Matrix4x4<Real>& A, const Vector4<Real>& u)
	{
		return ( Vector4<Real>( A.m[0][0] * u.mX + A.m[0][1] * u.mY + A.m[0][2] * u.mZ + A.m[0][3] * u.mW,

								A.m[1][0] * u.mX + A.m[1][1] * u.mY + A.m[1][2] * u.mZ + A.m[1][3] * u.mW,

								A.m[2][0] * u.mX + A.m[2][1] * u.mY + A.m[2][2] * u.mZ + A.m[2][3] * u.mW,
								
								A.m[3][0] * u.mX + A.m[3][1] * u.mY + A.m[3][2] * u.mZ + A.m[3][3] * u.mW)

		); 

	};

	template <class Real>
	inline Vector3<Real> operator* ( const Matrix4x4<Real>& A, const Vector3<Real>& u)
	{
		return ( Vector3<Real>( A.m[0][0] * u.mX + A.m[0][1] * u.mY + A.m[0][2] * u.mZ, 

								A.m[1][0] * u.mX + A.m[1][1] * u.mY + A.m[1][2] * u.mZ, 

								A.m[2][0] * u.mX + A.m[2][1] * u.mY + A.m[2][2] * u.mZ) );
								
								

		

	};
	

	template <class Real>
	inline std::ostream& operator<< (std::ostream & s, const Matrix4x4<Real>& A)
	{
//		s << "Matrix 4x4" << std::endl 
//		<< " m[1][1] = " << A.m[0][0] << " ,m[1][2] = " << A.m[0][1] << " ,m[1][3] = " << A.m[0][2] << " ,a41 = " <<A.m[0][3] << std::endl
//		<< " m[2][1] = " << A.m[1][0] << " ,m[2][2] = " << A.m[1][1] << " ,m[2][3] = " << A.m[1][2] << " ,a42 = " <<A.m[1][3] << std::endl
//		<< " m[3][1] = " << A.m[2][0] << " ,m[3][2] = " << A.m[2][1] << " ,m[3][3] = " << A.m[2][2] << " ,a43 = " <<A.m[2][3] << std::endl
//		<< " a41 = " << A.m[3][0] << " ,a42 = " << A.m[3][1] << " ,a43 = " << A.m[3][2] << " ,a44 = " << A.m[3][3] << std::endl;
		
		s << "Matrix 4x4" << std::endl 
		<< " a1T1 = " << A.mA[0] << " ,m[1][2] = " << A.mA[1] << " ,m[1][3] = " << A.mA[2] << " ,a41 = " << A.mA[3] << std::endl
		<< " m[2][1] = " << A.mA[4] << " ,m[2][2] = " << A.mA[5] << " ,m[2][3] = " << A.mA[6] << " ,a42 = " << A.mA[7] << std::endl
		<< " m[3][1] = " << A.mA[8] << " ,m[3][2] = " << A.mA[9] << " ,m[3][3] = " << A.mA[10] << " ,a34 = " << A.mA[11] << std::endl
		<< " a41 = " << A.mA[12] << " ,a42 = " << A.mA[13] << " ,a43 = " << A.mA[14] << " ,a44 = " << A.mA[15] << std::endl;

		return ( s );
	};

	template <class Real>
	bool Matrix4x4<Real>::isSymetric ()
	{
		if ( (m[0][1] == m[1][0]) and  
			 (m[0][2] == m[2][0]) and
			 (m[0][3] == m[3][0]) and
			 (m[2][1] == m[1][2]) and
			 (m[3][1] == m[1][3]) and
			 (m[3][2] == m[2][3]))
		{
			return true;
		}

		return false;
	}
	
	template <class Real>
	Matrix4x4<Real>	Matrix4x4<Real>::Inverse() const
	{
		Real A00 = m[1][2]*m[2][3]*m[3][1] - m[1][3]*m[2][2]*m[3][1] + m[1][3]*m[2][1]*m[3][2] - m[1][1]*m[2][3]*m[3][2] - m[1][2]*m[2][1]*m[3][3] + m[1][1]*m[2][2]*m[3][3];
		Real A01 = m[0][3]*m[2][2]*m[3][1] - m[0][2]*m[2][3]*m[3][1] - m[0][3]*m[2][1]*m[3][2] + m[0][1]*m[2][3]*m[3][2] + m[0][2]*m[2][1]*m[3][3] - m[0][1]*m[2][2]*m[3][3];
		Real A02 = m[0][2]*m[1][3]*m[3][1] - m[0][3]*m[1][2]*m[3][1] + m[0][3]*m[1][1]*m[3][2] - m[0][1]*m[1][3]*m[3][2] - m[0][2]*m[1][1]*m[3][3] + m[0][1]*m[1][2]*m[3][3];
		Real A03 = m[0][3]*m[1][2]*m[2][1] - m[0][2]*m[1][3]*m[2][1] - m[0][3]*m[1][1]*m[2][2] + m[0][1]*m[1][3]*m[2][2] + m[0][2]*m[1][1]*m[2][3] - m[0][1]*m[1][2]*m[2][3];
		Real A10 = m[1][3]*m[2][2]*m[3][0] - m[1][2]*m[2][3]*m[3][0] - m[1][3]*m[2][0]*m[3][2] + m[1][0]*m[2][3]*m[3][2] + m[1][2]*m[2][0]*m[3][3] - m[1][0]*m[2][2]*m[3][3];
		Real A11 = m[0][2]*m[2][3]*m[3][0] - m[0][3]*m[2][2]*m[3][0] + m[0][3]*m[2][0]*m[3][2] - m[0][0]*m[2][3]*m[3][2] - m[0][2]*m[2][0]*m[3][3] + m[0][0]*m[2][2]*m[3][3];
		Real A12 = m[0][3]*m[1][2]*m[3][0] - m[0][2]*m[1][3]*m[3][0] - m[0][3]*m[1][0]*m[3][2] + m[0][0]*m[1][3]*m[3][2] + m[0][2]*m[1][0]*m[3][3] - m[0][0]*m[1][2]*m[3][3];
		Real A13 = m[0][2]*m[1][3]*m[2][0] - m[0][3]*m[1][2]*m[2][0] + m[0][3]*m[1][0]*m[2][2] - m[0][0]*m[1][3]*m[2][2] - m[0][2]*m[1][0]*m[2][3] + m[0][0]*m[1][2]*m[2][3];
		Real A20 = m[1][1]*m[2][3]*m[3][0] - m[1][3]*m[2][1]*m[3][0] + m[1][3]*m[2][0]*m[3][1] - m[1][0]*m[2][3]*m[3][1] - m[1][1]*m[2][0]*m[3][3] + m[1][0]*m[2][1]*m[3][3];
		Real A21 = m[0][3]*m[2][1]*m[3][0] - m[0][1]*m[2][3]*m[3][0] - m[0][3]*m[2][0]*m[3][1] + m[0][0]*m[2][3]*m[3][1] + m[0][1]*m[2][0]*m[3][3] - m[0][0]*m[2][1]*m[3][3];
		Real A22 = m[0][1]*m[1][3]*m[3][0] - m[0][3]*m[1][1]*m[3][0] + m[0][3]*m[1][0]*m[3][1] - m[0][0]*m[1][3]*m[3][1] - m[0][1]*m[1][0]*m[3][3] + m[0][0]*m[1][1]*m[3][3];
		Real A23 = m[0][3]*m[1][1]*m[2][0] - m[0][1]*m[1][3]*m[2][0] - m[0][3]*m[1][0]*m[2][1] + m[0][0]*m[1][3]*m[2][1] + m[0][1]*m[1][0]*m[2][3] - m[0][0]*m[1][1]*m[2][3];
		Real A30 = m[1][2]*m[2][1]*m[3][0] - m[1][1]*m[2][2]*m[3][0] - m[1][2]*m[2][0]*m[3][1] + m[1][0]*m[2][2]*m[3][1] + m[1][1]*m[2][0]*m[3][2] - m[1][0]*m[2][1]*m[3][2];
		Real A31 = m[0][1]*m[2][2]*m[3][0] - m[0][2]*m[2][1]*m[3][0] + m[0][2]*m[2][0]*m[3][1] - m[0][0]*m[2][2]*m[3][1] - m[0][1]*m[2][0]*m[3][2] + m[0][0]*m[2][1]*m[3][2];
		Real A32 = m[0][2]*m[1][1]*m[3][0] - m[0][1]*m[1][2]*m[3][0] - m[0][2]*m[1][0]*m[3][1] + m[0][0]*m[1][2]*m[3][1] + m[0][1]*m[1][0]*m[3][2] - m[0][0]*m[1][1]*m[3][2];
		Real A33 = m[0][1]*m[1][2]*m[2][0] - m[0][2]*m[1][1]*m[2][0] + m[0][2]*m[1][0]*m[2][1] - m[0][0]*m[1][2]*m[2][1] - m[0][1]*m[1][0]*m[2][2] + m[0][0]*m[1][1]*m[2][2];
		
		Real lFactor = static_cast<Real>(1.0)/this->Determinant();
		
		return ( Matrix4x4<Real>( A00 * lFactor, A01 * lFactor, A02 * lFactor, A03 * lFactor,
								  A10 * lFactor, A11 * lFactor, A12 * lFactor, A13 * lFactor,
								  A20 * lFactor, A21 * lFactor, A22 * lFactor, A23 * lFactor, 
								  A30 * lFactor, A31 * lFactor, A32 * lFactor, A33 * lFactor) );
		
		
	}


	template <class Real>
	Real	Matrix4x4<Real>::Determinant() const
	{
		Real	 value;
		value =
			m[0][3] * m[1][2] * m[2][1] * m[3][0]-m[0][2] * m[1][3] * m[2][1] * m[3][0]-m[0][3] * m[1][1] * m[2][2] * m[3][0]+m[0][1] * m[1][3]    * m[2][2] * m[3][0]+
			m[0][2] * m[1][1] * m[2][3] * m[3][0]-m[0][1] * m[1][2] * m[2][3] * m[3][0]-m[0][3] * m[1][2] * m[2][0] * m[3][1]+m[0][2] * m[1][3]    * m[2][0] * m[3][1]+
			m[0][3] * m[1][0] * m[2][2] * m[3][1]-m[0][0] * m[1][3] * m[2][2] * m[3][1]-m[0][2] * m[1][0] * m[2][3] * m[3][1]+m[0][0] * m[1][2]    * m[2][3] * m[3][1]+
			m[0][3] * m[1][1] * m[2][0] * m[3][2]-m[0][1] * m[1][3] * m[2][0] * m[3][2]-m[0][3] * m[1][0] * m[2][1] * m[3][2]+m[0][0] * m[1][3]    * m[2][1] * m[3][2]+
			m[0][1] * m[1][0] * m[2][3] * m[3][2]-m[0][0] * m[1][1] * m[2][3] * m[3][2]-m[0][2] * m[1][1] * m[2][0] * m[3][3]+m[0][1] * m[1][2]    * m[2][0] * m[3][3]+
			m[0][2] * m[1][0] * m[2][1] * m[3][3]-m[0][0] * m[1][2] * m[2][1] * m[3][3]-m[0][1] * m[1][0] * m[2][2] * m[3][3]+m[0][0] * m[1][1]    * m[2][2] * m[3][3];
		return value;
	}
	
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeTranslate (const Vector3<Real>& v) const
	{
		return ( Matrix4x4<Real>( 0.0 ,0.0, 0.0, 0.0,
								  0.0, 0.0, 0.0, 0.0,
								  0.0, 0.0, 0.0, 0.0,
								  v.mX , v.mY , v.mZ ,1.0) );
	}
	
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeTranslate (const Vector4<Real>& v) const
	{
		return ( Matrix4x4<Real>( 0.0 ,0.0, 0.0, 0.0,
								  0.0, 0.0, 0.0, 0.0,
								  0.0, 0.0, 0.0, 0.0,
								  v.mX , v.mY , v.mZ ,1.0) );
	}
	
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeTranslate (const Real& v0,const Real& v1,const Real& v2) const
	{
		return ( Matrix4x4<Real>( 0.0 ,0.0, 0.0, 0.0,
								  0.0, 0.0, 0.0, 0.0,
								  0.0, 0.0, 0.0, 0.0,
								  v0 , v1 , v2 ,1.0) );
	
	}
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeScalar (const Vector3<Real>& v) const
	{
		return ( Matrix4x4<Real>( v.mX ,0.0, 0.0, 0.0,
								  0.0, v.mY, 0.0, 0.0,
								  0.0, 0.0, v.mY, 0.0,
								  0.0, 0.0, 0.0 , 0.0, 1.0) );
	}
	
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeScalar (const Vector4<Real>& v) const
	{
		return ( Matrix4x4<Real>( v.mX ,0.0, 0.0, 0.0,
								  0.0, v.mY, 0.0, 0.0,
								  0.0, 0.0, v.mY, 0.0,
								  0.0, 0.0, 0.0 , 0.0, 1.0) );
	}
	
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeProjectionMatrix(const Real& fov, const Real aspectRation, const Real& near, const Real& far) const
	{

				
	    Real c 					= static_cast<Real> (1.0 / std::tan(CGL::Math::degreesToRadians(fov) * 0.5) );
	    Real aspectRationInv 	= static_cast<Real> (1.0 / aspectRation);
	    Real fovy 				= static_cast<Real> (2.0 * std::atan(aspectRationInv / c));
	    Real xScale 			= static_cast<Real> (1.0 / tanf(0.5 * fovy));
	    Real yScale 			= static_cast<Real> (xScale / aspectRationInv);

	    Matrix4x4<Real> lProjectionMatrix;
	    
	    lProjectionMatrix[0][0] = xScale;
	    lProjectionMatrix[0][1] = static_cast< Real >(0);
	    lProjectionMatrix[0][2] = static_cast< Real >(0);
	    lProjectionMatrix[0][3] = static_cast< Real >(0);

	    lProjectionMatrix[1][0] = static_cast< Real >(0);
	    lProjectionMatrix[1][1] = yScale;
	    lProjectionMatrix[1][2] = static_cast< Real >(0);
	    lProjectionMatrix[1][3] = static_cast< Real >(0);

	    lProjectionMatrix[2][0] = static_cast< Real >(0);
	    lProjectionMatrix[2][1] = static_cast< Real >(0);
	    lProjectionMatrix[2][2] = static_cast< Real >((far + near) / (near - far));
	    lProjectionMatrix[2][3] = static_cast< Real >((2.0 * far * near) / (near - far));

	    lProjectionMatrix[3][0] = static_cast< Real >(0);
	    lProjectionMatrix[3][1] = static_cast< Real >(0);
	    lProjectionMatrix[3][2] = static_cast< Real >(-1);
	    lProjectionMatrix[3][3] = static_cast< Real >(0);

		
		return Matrix4x4<Real>(lProjectionMatrix);
		
		

	};
	
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeViewMatrix(const Vector3<Real>& eyes, const Vector3<Real>& position, const Vector3<Real>& up) const
	{

		Vector3<Real> zaxis = (eyes - position ).norm();
		Vector3<Real> xaxis = (up ^ zaxis).norm();
		Vector3<Real> yaxis =  zaxis ^ xaxis;
		
		return Matrix4x4<Real>( xaxis.mX	   , xaxis.my		, xaxis.mz, -(xaxis * eyes), 
								yaxis.mZ	   , yaxis.mY		, yaxis.mz, -(yaxis * eyes), 
								zaxis.mZ	   , zaxis.mY		, zaxis.mZ, -(zaxis * eyes), 
								0, 0 , 0, 1 );

			
	};
	
	template <class Real>
	void Matrix4x4<Real>::FromHeadPitchRoll(Real headDegrees, Real pitchDegrees, Real rollDegrees)
	{
	    // Constructs a rotation matrix based on a Euler Transform.
	    // I use the popular NASA standard airplane convention of 
	    // heading-pitch-roll (i.e., RzRxRy).

	    headDegrees = Math::degreesToRadians(headDegrees);
	    pitchDegrees = Math::degreesToRadians(pitchDegrees);
	    rollDegrees = Math::degreesToRadians(rollDegrees);

	    Real cosH = std::cos(headDegrees);
	    Real cosP = std::cos(pitchDegrees);
	    Real cosR = std::cos(rollDegrees);
	    Real sinH = std::sin(headDegrees);
	    Real sinP = std::sin(pitchDegrees);
	    Real sinR = std::sin(rollDegrees);

	    m[0][0] = cosR * cosH - sinR * sinP * sinH;
	    m[0][1] = sinR * cosH + cosR * sinP * sinH;
	    m[0][2] = -cosP * sinH;
	    m[0][3] = static_cast< Real >(0);

	    m[1][0] = -sinR * cosP;
	    m[1][1] = cosR * cosP;
	    m[1][2] = sinP;
	    m[1][3] = static_cast< Real >(0);

	    m[2][0] = cosR * sinH + sinR * sinP * cosH;
	    m[2][1] = sinR * sinH - cosR * sinP * cosH;
	    m[2][2] = cosP * cosH;
	    m[2][3] = static_cast< Real >(0);

	    m[3][0] = static_cast< Real >(0);
	    m[3][1] = static_cast< Real >(0);
	    m[3][2] = static_cast< Real >(0);
	    m[3][3] = static_cast< Real >(1);
	}

	template <class Real>
	void Matrix4x4<Real>::Rotate(const Vector3<Real>& axis, Real& degrees)
	{


	    degrees = Math::degreesToRadians(degrees);

	    Real x = axis.x();
	    Real y = axis.y();
	    Real z = axis.z();
	    Real c = std::cos(degrees);
	    Real s = std::sin(degrees);

	    m[0][0] = (x * x) * (1.0 - c) + c;
	    m[0][1] = (x * y) * (1.0 - c) + (z * s);
	    m[0][2] = (x * z) * (1.0 - c) - (y * s);
	    m[0][3] = static_cast< Real >(0);

	    m[1][0] = (y * x) * (1.0 - c) - (z * s);
	    m[1][1] = (y * y) * (1.0 - c) + c;
	    m[1][2] = (y * z) * (1.0 - c) + (x * s);
	    m[1][3] = 0.0;

	    m[2][0] = (z * x) * (1.0 - c) + (y * s);
	    m[2][1] = (z * y) * (1.0 - c) - (x * s);
	    m[2][2] = (z * z) * (1.0 - c) + c;
	    m[2][3] = static_cast< Real >(0);

	    m[3][0] = static_cast< Real >(0);
	    m[3][1] = static_cast< Real >(0);
	    m[3][2] = static_cast< Real >(0);
	    m[3][3] = static_cast< Real >(1);
	}

	template <class Real>
	void Matrix4x4<Real>::ToHeadPitchRoll(Real &headDegrees, Real &pitchDegrees, Real &rollDegrees) const
	{


	    Real thetaX = std::asin(m[1][2]);
	    Real thetaY = static_cast< Real >(0);
	    Real thetaZ = static_cast< Real >(0);

	    if (thetaX < Math::HALF_PI)
	    {
	        if (thetaX > -Math::HALF_PI)
	        {
	            thetaZ = std::atan2(-m[1][0], m[1][1]);
	            thetaY = std::atan2(-m[0][2], m[2][2]);
	        }
	        else
	        {
	            // Not a unique solution.
	            thetaZ = -std::atan2(m[2][0], m[0][0]);
	            thetaY = static_cast< Real >(0);
	        }
	    }
	    else
	    {
	        // Not a unique solution.
	        thetaZ = std::atan2(m[2][0], m[0][0]);
	        thetaY = static_cast< Real >(0);
	    }

	    headDegrees  = Math::radiansToDegrees(thetaY);
	    pitchDegrees = Math::radiansToDegrees(thetaX);
	    rollDegrees  = Math::radiansToDegrees(thetaZ);
	}

	
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::identity ()
	{
		return Matrix4x4<Real>(1.0,0.0,0.0,0.0,
							   0.0,1.0,0.0,0.0,
							   0.0,0.0,1.0,0.0,
							   0.0,0.0,0.0,1.0);	
	}
	template <class Real>
	Matrix4x4<Real>::~Matrix4x4(){};


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
