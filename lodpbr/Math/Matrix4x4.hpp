#ifndef MATRIX4X4_HPP_
#define MATRIX4X4_HPP_

// [Header files]
#include <iostream>
// [Project Includes]
#include "Math.hpp"
#include "Vector4.hpp"
#include "Vector3.hpp"
#include "Matrix3x3.hpp"



namespace LAL {

/*! \brief The Matrix4x4 class .

*@class Matrix4x4.
*@brief Class that represent a dense 4x4 Matrix and Homogeneous Coordinate ..
*@details ...
*@author Felipe Moura.
*@email fmc@cos.ufrj.br
*@version 1.0.
*@todo OpenGL interface and a C style array,
*@todo Keep supporting Homogeneous Coordinates ?

  \nosubgrouping */

	template<class Real> class Matrix4x4
	{
	public:

		friend class Vector3<Real>;
		friend class Vector4<Real>;
		friend class Matrix3x3<Real>;

		/*! @name Defining a Matrix4x4 */
		//@{
		/*! Default constructor. All value is set to 0. */
		Matrix4x4();
		 /*! Copy constructor. */
		Matrix4x4( const Matrix4x4<Real>& a );
		inline Matrix4x4<Real>& operator=( const Matrix3x3<Real>& a);
		inline Matrix4x4<Real>& operator=( const Matrix4x4<Real>& a);

		/*! Copy constructor for a Matrix with another type */
		template <class T>
		Matrix4x4( const Matrix4x4<T>& a );

		/*! Constructor. Four Vector4 representing the rows*/
		Matrix4x4( const Vector4<Real>& row1, const Vector4<Real>& row2, const Vector4<Real>& row3, const Vector4<Real>& row4 );
		/*! Constructor. Three Vector3 representing the three  first rows*/
		Matrix4x4( const Vector3<Real>& row1, const Vector3<Real>& row2, const Vector3<Real>& row3);

		 /*! Constructor. Taking 16 arguments. */
		Matrix4x4( Real a11, Real a12, Real a13, Real a14,
				   Real a21, Real a22, Real a23, Real a24,
				   Real a31, Real a32, Real a33, Real a34,
				   Real a41, Real a42, Real a43, Real a44 );

		virtual ~Matrix4x4();

		//@}
		/*! @name Accessing the value */
		//@{

		const Vector4<Real>& 	operator[]( int rowIndex ) const;
		Vector4<Real>& 			operator[]( int rowIndex );

		Real  					operator()( int i, int j ) const;
		Real& 					operator()( int i, int j );
		// Return Colum
		Vector4<Real> 			Column ( int index ) const;
		Vector4<Real> 			Row ( int index ) const;


		//@}

		/*! @name Algebraic computations */
		//@{
		Matrix4x4<Real> 		operator~() const;
		Matrix4x4<Real>  		operator-() const;
		Matrix4x4<Real>  		operator+() const;

		template <class T>
		friend Matrix4x4<T> 	operator*( const T& factor, const Matrix4x4<T>& a );
		template <class T>
		friend Matrix4x4<T> 	operator*( const Matrix4x4<T>& a, const T& factor );
		template <class T>
		friend Matrix4x4<T> 	operator/( const Matrix4x4<T>& a, const T& factor );

		Matrix4x4<Real>& 		operator/=( const Real& factor);
		Matrix4x4<Real>& 		operator*=( const Real& factor);
		Matrix4x4<Real>& 		operator+=( const Real& factor);
		Matrix4x4<Real>& 		operator-=( const Real& factor);

		template <class T>
		friend Matrix4x4<T> 	operator+ (const Matrix4x4<T>& A, const Matrix4x4<T>& B);
		template <class T>
		friend Matrix4x4<T> 	operator- (const Matrix4x4<T>& A, const Matrix4x4<T>& B);
		template <class T>
		friend Matrix4x4<T> 	operator* (const Matrix4x4<T>& A, const Matrix4x4<T>& B);
		template <class T>
		friend Vector3<T> 		operator* ( const Matrix4x4<T>& A, const Vector4<T>& u);
		template <class T>
		friend Vector3<T> 		operator* ( const Matrix4x4<T>& A, const Vector3<T>& u);
		//@}
		/*! @name Translate and Scalar */
		//@{
		Matrix4x4<Real> 		MakeTranslate (const Vector3<Real>& v) const;
		Matrix4x4<Real> 		MakeTranslate (const Vector4<Real>& v) const;
		Matrix4x4<Real> 		MakeTranslate (const Real& v0,const Real& v1,const Real& v2) const;
		Matrix4x4<Real> 		MakeScalar (const Vector3<Real>& v) const;
		//@}
		/*! @name Projection */
		static Matrix4x4<Real> 	MakePespectiveProjectionMatrix (const Real& fovy, const Real& aspectRation, const Real& near, const Real& far) ;
		static Matrix4x4<Real> 	MakeOrthographicProjectionMatrix (const Real& left, const Real& right,const Real& bottom, const Real& top, const Real& near, const Real& far) ;

		static Matrix4x4<Real> 	MakeViewMatrix       (const Vector3<Real>& eyes, const Vector3<Real>& position, const Vector3<Real>& up) ;
		//@}
		/*! @name Rotation  */
		//@{
		void 					FromHeadPitchRoll(Real headDegrees, Real pitchDegrees, Real rollDegrees);
		void 					Rotate(const Vector3<Real>& axis, Real& degrees);
		void 					ToHeadPitchRoll(Real &headDegrees, Real &pitchDegrees, Real &rollDegrees) const;
		//@}

		/*! @name Matrix Function  */
		//@{

		Matrix4x4<Real> 		Identity ();
		Real 					Determinant () const;
		Matrix4x4<Real> 		Inverse () const;
		bool 					IsSymetric ();

		const Real* 			ToRealPtr( void ) const;
		Real* 					ToRealPtr( void );


	    inline operator const Real*() const;

	    inline operator Real*();


		template <class T>
		friend std::ostream&	operator<< (std::ostream & s, const Matrix4x4<T>& A);
		//@}

	private:


		Vector4<Real> m[4];


	}; // End Interface


	template <class Real>
	Matrix4x4<Real>::Matrix4x4()
	{
		m[ 0 ].x =  static_cast< Real > ( 1 );
		m[ 0 ].y =  static_cast< Real > ( 0 );
		m[ 0 ].z =  static_cast< Real > ( 0 );
		m[ 0 ].w =  static_cast< Real > ( 0 );

		m[ 1 ].x =  static_cast< Real > ( 0 );
		m[ 1 ].y =  static_cast< Real > ( 1 );
		m[ 1 ].z =  static_cast< Real > ( 0 );
		m[ 1 ].w =  static_cast< Real > ( 0 );

		m[ 2 ].x =  static_cast< Real > ( 0 );
		m[ 2 ].y =  static_cast< Real > ( 0 );
		m[ 2 ].z =  static_cast< Real > ( 1 );
		m[ 2 ].w =  static_cast< Real > ( 0 );

		m[ 3 ].x =  static_cast< Real > ( 0 );
		m[ 3 ].y =  static_cast< Real > ( 0 );
		m[ 3 ].z =  static_cast< Real > ( 0 );
		m[ 3 ].w =  static_cast< Real > ( 1 );
	};

	template <class Real>
	Matrix4x4<Real>::Matrix4x4( const Matrix4x4<Real>& a )
	{
		m[ 0 ].x = a[ 0 ].x; m[ 0 ].y = a[ 0 ].y; m[ 0 ].z = a[ 0 ].z; m[ 0 ].w = a[ 0 ].w;
		m[ 1 ].x = a[ 1 ].x; m[ 1 ].y = a[ 1 ].y; m[ 1 ].z = a[ 1 ].z; m[ 1 ].w = a[ 1 ].w;
		m[ 2 ].x = a[ 2 ].x; m[ 2 ].y = a[ 2 ].y; m[ 2 ].z = a[ 2 ].z; m[ 2 ].w = a[ 2 ].w;
		m[ 3 ].x = a[ 3 ].x; m[ 3 ].y = a[ 3 ].y; m[ 3 ].z = a[ 3 ].z; m[ 3 ].w = a[ 3 ].w;

	}

	template <class Real>
	template <class T>
	Matrix4x4<Real>::Matrix4x4( const Matrix4x4<T>& a )
	{
		m[ 0 ].x = a[ 0 ].x; m[ 0 ].y = a[ 0 ].y; m[ 0 ].z = a[ 0 ].z; m[ 0 ].w = a[ 0 ].w;
		m[ 1 ].x = a[ 1 ].x; m[ 1 ].y = a[ 1 ].y; m[ 1 ].z = a[ 1 ].z; m[ 1 ].w = a[ 1 ].w;
		m[ 2 ].x = a[ 2 ].x; m[ 2 ].y = a[ 2 ].y; m[ 2 ].z = a[ 2 ].z; m[ 2 ].w = a[ 2 ].w;
		m[ 3 ].x = a[ 3 ].x; m[ 3 ].y = a[ 3 ].y; m[ 3 ].z = a[ 3 ].z; m[ 3 ].w = a[ 3 ].w;
	}


	template <class Real>
	Matrix4x4<Real>::Matrix4x4( Real a00, Real a01,Real  a02,Real  a03,
								Real a10,Real  a11,Real  a12,Real  a13,
								Real a20,Real  a21,Real  a22,Real  a23,
								Real a30,Real  a31,Real  a32,Real  a33 )
	{
		m[ 0 ].x = a00; m[ 0 ].y = a01; m[ 0 ].z = a02; m[ 0 ].w = a03;
		m[ 1 ].x = a10; m[ 1 ].y = a11; m[ 1 ].z = a12; m[ 1 ].w = a13;
		m[ 2 ].x = a20; m[ 2 ].y = a21; m[ 2 ].z = a22; m[ 2 ].w = a23;
		m[ 3 ].x = a30; m[ 3 ].y = a31; m[ 3 ].z = a32; m[ 3 ].w = a33;
	};

	template <class Real>
	Matrix4x4<Real>::Matrix4x4( const Vector4<Real>& row1, const Vector4<Real>& row2, const Vector4<Real>& row3, const Vector4<Real>& row4 )
	{
		m[ 0 ].x = row1.x; m[ 0 ].y = row1.y; m[ 0 ].z = row1.z; m[ 0 ].w = row1.w;
		m[ 1 ].x = row2.x; m[ 1 ].y = row2.y; m[ 1 ].z = row2.z; m[ 1 ].w = row2.w;
		m[ 2 ].x = row3.x; m[ 2 ].y = row3.y; m[ 2 ].z = row3.z; m[ 2 ].w = row3.w;
		m[ 3 ].x = row4.x; m[ 3 ].y = row4.y; m[ 3 ].z = row4.z; m[ 3 ].w = row4.w;
	};

	template <class Real>
	Matrix4x4<Real>::Matrix4x4( const Vector3<Real>& row1, const Vector3<Real>& row2, const Vector3<Real>& row3 )
	{
		m[ 0 ].x = row1.x; m[ 0 ].y = row1.y; m[ 0 ].z = row1.z; m[ 0 ].w = static_cast< Real > ( 0 );
		m[ 1 ].x = row2.x; m[ 1 ].y = row2.y; m[ 1 ].z = row2.z; m[ 1 ].w = static_cast< Real > ( 0 );
		m[ 2 ].x = row3.x; m[ 2 ].y = row3.y; m[ 2 ].z = row3.z; m[ 2 ].w = static_cast< Real > ( 0 ) ;
		m[ 3 ].x = static_cast< Real > ( 0 ); m[ 3 ].y = static_cast< Real > ( 0 ); m[ 3 ].z =	static_cast< Real > ( 0 ) ; m[ 3 ].w = static_cast< Real > ( 1 );
	};

	// transpose
	template <class Real>
	inline Matrix4x4<Real> Matrix4x4<Real>::operator~() const
	{
		return ( Matrix4x4<Real>
		( m[ 0 ].x,m[ 1 ].x,m[ 2 ].x,m[ 3 ].x,
		  m[ 0 ].y,m[ 1 ].y,m[ 2 ].y,m[ 3 ].y,
		  m[ 0 ].z,m[ 1 ].z,m[ 2 ].z,m[ 3 ].z,
		  m[ 0 ].w,m[ 1 ].w,m[ 2 ].w,m[ 3 ].w )
		);

	};


	//----------------------------------------------------------------------------

	template <class Real>
	inline const Vector4<Real>& Matrix4x4<Real>::operator[]( int rowIndex ) const
	{
	 	return m[ rowIndex ];
	}
	//----------------------------------------------------------------------------

	template <class Real>
	inline Vector4<Real>& Matrix4x4<Real>::operator[]( int rowIndex )
	{
	 	return m[ rowIndex ];
	}

	template <class Real>
	Real Matrix4x4<Real>::operator()( int i, int j ) const
	{

		if( i<0 || j<0 || i>=4 || j>=4 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;

		}

		return ( m[ i ][ j ] );

	}

	template <class Real>
	Real& Matrix4x4<Real>::operator()( int i, int j )
	{

		if( i<0 || j<0 || i>=4 || j>=4 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;

		}

		return ( m[ i ][ j ] );

	}


	// Return Colum
	template <class Real>
	Vector4<Real> Matrix4x4<Real>::Column( int i )  const
	{

		if( i<0 || i>=4 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;

		}

		return ( Vector4<Real>( m[ 0 ][ i ] , m[ 1 ][ i ] , m[ 2 ][ i ] , m[ 3 ][ i ] ) );

	}

	template <class Real>
	Vector4<Real> Matrix4x4<Real>::Row( int i ) const
	{

		if( i<0 || i>=4 )
		{
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;

		}

		return ( Vector4<Real>( m[ i ].x , m[ i ].y , m[ i ].z , m[ i ].w ) );

	}

	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator=( const Matrix3x3<Real>& a)
	{

		m[ 0 ].x = a[ 0 ].x; m[ 0 ].y = a[ 0 ].y; m[ 0 ].z = a[ 0 ].z; m[ 0 ].w = static_cast< Real > ( 0 );
		m[ 1 ].x = a[ 1 ].x; m[ 1 ].y = a[ 1 ].y; m[ 1 ].z = a[ 1 ].z; m[ 1 ].w = static_cast< Real > ( 0 );
		m[ 2 ].x = a[ 2 ].x; m[ 2 ].y = a[ 2 ].y; m[ 2 ].z = a[ 2 ].z; m[ 2 ].w = static_cast< Real > ( 0 );

		m[ 3 ].x = static_cast< Real > ( 0 );
		m[ 3 ].y = static_cast< Real > ( 0 );
		m[ 3 ].z = static_cast< Real > ( 0 );
		m[ 3 ].w = static_cast< Real > ( 1 );

		return ( *this );
	};

	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator=( const Matrix4x4<Real>& a)
	{

		m[ 0 ].x = a[ 0 ].x; m[ 0 ].y = a[ 0 ].y; m[ 0 ].z = a[ 0 ].z; m[ 0 ].w = a[ 0 ].w;
		m[ 1 ].x = a[ 1 ].x; m[ 1 ].y = a[ 1 ].y; m[ 1 ].z = a[ 1 ].z; m[ 1 ].w = a[ 1 ].w;
		m[ 2 ].x = a[ 2 ].x; m[ 2 ].y = a[ 2 ].y; m[ 2 ].z = a[ 2 ].z; m[ 2 ].w = a[ 2 ].w;
		m[ 3 ].x = a[ 3 ].x; m[ 3 ].y = a[ 3 ].y; m[ 3 ].z = a[ 3 ].z; m[ 3 ].w = a[ 3 ].w;

		return ( *this );
	};

	// FRIEND FUNCRealIONS

	template <class Real>
	inline Matrix4x4<Real>  Matrix4x4<Real>::operator-() const
	{

		return ( Matrix4x4<Real>
		( -m[ 0 ].x,-m[ 0 ].y,-m[ 0 ].z,-m[ 0 ].w,
		  -m[ 1 ].x,-m[ 1 ].y,-m[ 1 ].z,-m[ 1 ].w,
	      -m[ 2 ].x,-m[ 2 ].y,-m[ 2 ].z,-m[ 2 ].w,
		  -m[ 3 ].x,-m[ 3 ].y,-m[ 3 ].z,-m[ 3 ].w)
		);

	};

	template <class Real>
	inline Matrix4x4<Real>  Matrix4x4<Real>::operator+() const
	{
		return ( Matrix4x4<Real>
		( m[ 0 ].x,m[ 0 ].y,m[ 0 ].z,m[ 0 ].w,
		  m[ 1 ].x,m[ 1 ].y,m[ 1 ].z,m[ 1 ].w,
		  m[ 2 ].x,m[ 2 ].y,m[ 2 ].z,m[ 2 ].w,
		  m[ 3 ].x,m[ 3 ].y,m[ 3 ].z,m[ 3 ].w )
		);
	};

	template <class Real>
	inline Matrix4x4<Real> operator+( const Matrix4x4<Real>& a, const Matrix4x4<Real>& b )
	{

		return ( Matrix4x4<Real>
		( a[ 0 ].x + b[ 0 ].x, a[ 0 ].y + b[ 0 ].y, a[ 0 ].z + b[ 0 ].z, a[ 0 ].w + b[ 0 ].w,
		  a[ 1 ].x + b[ 1 ].x, a[ 1 ].y + b[ 1 ].y, a[ 1 ].z + b[ 1 ].z, a[ 1 ].w + b[ 1 ].w,
		  a[ 2 ].x + b[ 2 ].x, a[ 2 ].y + b[ 2 ].y, a[ 2 ].z + b[ 2 ].z, a[ 2 ].w + b[ 2 ].w,
		  a[ 3 ].x + b[ 3 ].x, a[ 3 ].y + b[ 3 ].y, a[ 3 ].z + b[ 3 ].z, a[ 3 ].w + b[ 3 ].w )
		);
	};

	template <class Real>
	inline Matrix4x4<Real> operator-( const Matrix4x4<Real>& a, const Matrix4x4<Real>& b )
	{

		return ( Matrix4x4<Real>
		( a[ 0 ].x - b[ 0 ].x, a[ 0 ].y - b[ 0 ].y, a[ 0 ].z - b[ 0 ].z, a[ 0 ].w - b[ 0 ].w,
		  a[ 1 ].x - b[ 1 ].x, a[ 1 ].y - b[ 1 ].y, a[ 1 ].z - b[ 1 ].z, a[ 1 ].w - b[ 1 ].w,
		  a[ 2 ].x - b[ 2 ].x, a[ 2 ].y - b[ 2 ].y, a[ 2 ].z - b[ 2 ].z, a[ 2 ].w - b[ 2 ].w,
		  a[ 3 ].x - b[ 3 ].x, a[ 3 ].y - b[ 3 ].y, a[ 3 ].z - b[ 3 ].z, a[ 3 ].w - b[ 3 ].w)
		);
	};

	template <class Real>
	inline Matrix4x4<Real> operator*( const Real& factor, const Matrix4x4<Real>& a )
	{

		return ( Matrix4x4<Real>
		( a[ 0 ].x * factor, a[ 0 ].y * factor, a[ 0 ].z * factor, a[ 0 ].w * factor,
		  a[ 1 ].x * factor, a[ 1 ].y * factor, a[ 1 ].z * factor, a[ 1 ].w * factor,
		  a[ 2 ].x * factor, a[ 2 ].y * factor, a[ 2 ].z * factor, a[ 2 ].w * factor,
		  a[ 3 ].x * factor, a[ 3 ].y * factor, a[ 3 ].z * factor, a[ 3 ].w * factor )
		);

	};

	template <class Real>
	inline Matrix4x4<Real> operator*( const Matrix4x4<Real>& a, const Real& factor )
	{

		return ( Matrix4x4<Real>
		( a[ 0 ].x * factor, a[ 0 ].y * factor, a[ 0 ].z * factor, a[ 0 ].w * factor,
		  a[ 1 ].x * factor, a[ 1 ].y * factor, a[ 1 ].z * factor, a[ 1 ].w * factor,
		  a[ 2 ].x * factor, a[ 2 ].y * factor, a[ 2 ].z * factor, a[ 2 ].w * factor,
		  a[ 3 ].x * factor, a[ 3 ].y * factor, a[ 3 ].z * factor, a[ 3 ].w * factor)
		);
	};

	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator+=( const Real& factor )
	{

		m[ 0 ].x += factor; m[ 0 ].y += factor; m[ 0 ].z += factor; m[ 0 ].w += factor;
		m[ 1 ].x += factor; m[ 1 ].y += factor; m[ 1 ].z += factor; m[ 1 ].w += factor;
		m[ 2 ].x += factor; m[ 2 ].y += factor; m[ 2 ].z += factor; m[ 2 ].w += factor;
		m[ 3 ].x += factor; m[ 3 ].y += factor; m[ 3 ].z += factor; m[ 3 ].w += factor;

		return (*this);
	};

	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator-=( const Real& factor )
	{

		m[ 0 ].x -= factor; m[ 0 ].y -= factor; m[ 0 ].z -= factor; m[ 0 ].w -= factor;
		m[ 1 ].x -= factor; m[ 1 ].y -= factor; m[ 1 ].z -= factor; m[ 1 ].w -= factor;
		m[ 2 ].x -= factor; m[ 2 ].y -= factor; m[ 2 ].z -= factor; m[ 2 ].w -= factor;
		m[ 3 ].x -= factor; m[ 3 ].y -= factor; m[ 3 ].z -= factor; m[ 3 ].w -= factor;

		return (*this);
	};


	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator/=( const Real& factor )
	{

		if( factor == 0 ){
			std::cerr << "[ERROR]" << std::endl
			<< " division by zero."
			<< std::endl;

		}

		Real f = 1 / factor;

		m[ 0 ].x *= f; m[ 0 ].y *= f; m[ 0 ].z *= f; m[ 0 ].w *= f;
		m[ 1 ].x *= f; m[ 1 ].y *= f; m[ 1 ].z *= f; m[ 1 ].w *= f;
		m[ 2 ].x *= f; m[ 2 ].y *= f; m[ 2 ].z *= f; m[ 2 ].w *= f;
		m[ 3 ].x *= f; m[ 3 ].y *= f; m[ 3 ].z *= f; m[ 3 ].w *= f;

		return (*this);
	};

	template <class Real>
	inline Matrix4x4<Real>& Matrix4x4<Real>::operator*= ( const Real& factor)
	{

		m[ 0 ].x *= factor; m[ 0 ].y *= factor; m[ 0 ].z *= factor; m[ 0 ].w *= factor;
		m[ 1 ].x *= factor; m[ 1 ].y *= factor; m[ 1 ].z *= factor; m[ 1 ].w *= factor;
		m[ 2 ].x *= factor; m[ 2 ].y *= factor; m[ 2 ].z *= factor; m[ 2 ].w *= factor;
		m[ 3 ].x *= factor; m[ 3 ].y *= factor; m[ 3 ].z *= factor; m[ 3 ].w *= factor;

		return (*this);
	};

	template <class Real>
	inline Matrix4x4<Real> operator/ ( const Matrix4x4<Real>& a, const Real& factor)
	{

		if( factor == 0 ){
			std::cerr << "[ERROR]" << std::endl
			<< " division by zero."
			<< std::endl;

		}

		Real f = 1 / factor;

		return ( Matrix4x4<Real>
		(	a[ 0 ].x * f, a[ 0 ].y * f, a[ 0 ].z * f, a[ 0 ].w * f,
			a[ 1 ].x * f, a[ 1 ].y * f, a[ 1 ].z * f, a[ 1 ].w * f,
			a[ 2 ].x * f, a[ 2 ].y * f, a[ 2 ].z * f, a[ 2 ].w * f,
			a[ 3 ].x * f, a[ 3 ].y * f, a[ 3 ].z * f, a[ 3 ].w * f )
		);
	};


	template <class Real>
	inline Matrix4x4<Real> operator*( const Matrix4x4<Real>& a, const Matrix4x4<Real>& b )
	{
		return ( Matrix4x4<Real>
		(
		  // Row 1
		  a[ 0 ].x * b[ 0 ].x + a[ 0 ].y * b[ 1 ].x + a[ 0 ].z * b[ 2 ].x + a[ 0 ].w * b[ 3 ].x,
		  a[ 0 ].x * b[ 0 ].y + a[ 0 ].y * b[ 1 ].y + a[ 0 ].z * b[ 2 ].y + a[ 0 ].w * b[ 3 ].y,
		  a[ 0 ].x * b[ 0 ].z + a[ 0 ].y * b[ 1 ].z + a[ 0 ].z * b[ 2 ].z + a[ 0 ].w * b[ 3 ].z,
		  a[ 0 ].x * b[ 0 ].w + a[ 0 ].y * b[ 1 ].w + a[ 0 ].z * b[ 2 ].w + a[ 0 ].w * b[ 3 ].w,
		  // Row 2
		  a[ 1 ].x * b[ 0 ].x + a[ 1 ].y * b[ 1 ].x + a[ 1 ].z * b[ 2 ].x + a[ 1 ].w * b[ 3 ].x,
		  a[ 1 ].x * b[ 0 ].y + a[ 1 ].y * b[ 1 ].y + a[ 1 ].z * b[ 2 ].y + a[ 1 ].w * b[ 3 ].y,
		  a[ 1 ].x * b[ 0 ].z + a[ 1 ].y * b[ 1 ].z + a[ 1 ].z * b[ 2 ].z + a[ 1 ].w * b[ 3 ].z,
		  a[ 1 ].x * b[ 0 ].w + a[ 1 ].y * b[ 1 ].w + a[ 1 ].z * b[ 2 ].w + a[ 1 ].w * b[ 3 ].w,
		  // Row 3
		  a[ 2 ].x * b[ 0 ].x + a[ 2 ].y * b[ 1 ].x + a[ 2 ].z * b[ 2 ].x + a[ 2 ].w * b[ 3 ].x,
		  a[ 2 ].x * b[ 0 ].y + a[ 2 ].y * b[ 1 ].y + a[ 2 ].z * b[ 2 ].y + a[ 2 ].w * b[ 3 ].y,
		  a[ 2 ].x * b[ 0 ].z + a[ 2 ].y * b[ 1 ].z + a[ 2 ].z * b[ 2 ].z + a[ 2 ].w * b[ 3 ].z,
		  a[ 2 ].x * b[ 0 ].w + a[ 2 ].y * b[ 1 ].w + a[ 2 ].z * b[ 2 ].w + a[ 2 ].w * b[ 3 ].w,
		  // Row 4
		  a[ 3 ].x * b[ 0 ].x + a[ 3 ].y * b[ 1 ].x + a[ 3 ].z * b[ 2 ].x + a[ 3 ].w * b[ 3 ].x,
		  a[ 3 ].x * b[ 0 ].y + a[ 3 ].y * b[ 1 ].y + a[ 3 ].z * b[ 2 ].y + a[ 3 ].w * b[ 3 ].y,
		  a[ 3 ].x * b[ 0 ].z + a[ 3 ].y * b[ 1 ].z + a[ 3 ].z * b[ 2 ].z + a[ 3 ].w * b[ 3 ].z,
		  a[ 3 ].x * b[ 0 ].w + a[ 3 ].y * b[ 1 ].w + a[ 3 ].z * b[ 2 ].w + a[ 3 ].w * b[ 3 ].w)

		);

	};

	template <class Real>
	inline Vector3<Real> operator*( const Matrix4x4<Real>& a, const Vector4<Real>& v )
	{
		return ( Vector4<Real>
		( a[ 0 ].x * v.x + a[ 0 ].y * v.y + a[ 0 ].z * v.z + a[ 0 ].w * v.w,
	      a[ 1 ].x * v.x + a[ 1 ].y * v.y + a[ 1 ].z * v.z + a[ 1 ].w * v.w,
	   	  a[ 2 ].x * v.x + a[ 2 ].y * v.y + a[ 2 ].z * v.z + a[ 2 ].w * v.w,
	      a[ 3 ].x * v.x + a[ 3 ].y * v.y + a[ 3 ].z * v.z + a[ 3 ].w * v.w)
		);

	};

	template <class Real>
	inline Vector3<Real> operator*( const Matrix4x4<Real>& a, const Vector3<Real>& v )
	{
		return ( Vector3<Real>
		( a[ 0 ].x * v.x + a[ 0 ].y * v.y + a[ 0 ].z * v.z,
	      a[ 1 ].x * v.x + a[ 1 ].y * v.y + a[ 1 ].z * v.z,
	      a[ 2 ].x * v.x + a[ 2 ].y * v.y + a[ 2 ].z * v.z)
	    );
	};


	template <class Real>
	inline std::ostream& operator<< (std::ostream & s, const Matrix4x4<Real>& a)
	{
				s << "Matrix 4x4" << std::endl
				<< " m[ 1 ].x = " << a[ 0 ].x << " ,m[ 1 ].y = " << a[ 0 ].y << " ,m[ 1 ].z = " << a[ 0 ].z << " ,m[ 4 ].w = " << a[ 0 ].w << std::endl
				<< " m[ 2 ].x = " << a[ 1 ].x << " ,m[ 2 ].y = " << a[ 1 ].y << " ,m[ 2 ].z = " << a[ 1 ].z << " ,m[ 4 ].w = " << a[ 1 ].w << std::endl
				<< " m[ 3 ].x = " << a[ 2 ].x << " ,m[ 3 ].y = " << a[ 2 ].y << " ,m[ 3 ].z = " << a[ 2 ].z << " ,m[ 4 ].w = " << a[ 2 ].w << std::endl
				<< " m[ 4 ].x = " << a[ 3 ].x << " ,m[ 4 ].y = " << a[ 3 ].y << " ,m[ 4 ].z = " << a[ 3 ].z << " ,m[ 4 ].w = " << a[ 3 ].w << std::endl;

		return ( s );
	};

	template <class Real>
	bool Matrix4x4<Real>::IsSymetric ()
	{
		if ( 	(m[ 0 ].y == m[ 1 ].x) and
				(m[ 0 ].z == m[ 2 ].x) and
				(m[ 0 ].w == m[ 3 ].x) and
				(m[ 2 ].y == m[ 1 ].z) and
				(m[ 3 ].y == m[ 1 ].w) and
				(m[ 3 ].z == m[ 2 ].w)
			)
		{
			return true;
		}

		return false;
	}

	template <class Real>
	Matrix4x4<Real>	Matrix4x4<Real>::Inverse() const
	{
		Real a00 = m[ 1 ].z*m[ 2 ].w*m[ 3 ].y - m[ 1 ].w*m[ 2 ].z*m[ 3 ].y + m[ 1 ].w*m[ 2 ].y*m[ 3 ].z - m[ 1 ].y*m[ 2 ].w*m[ 3 ].z - m[ 1 ].z*m[ 2 ].y*m[ 3 ].w + m[ 1 ].y*m[ 2 ].z*m[ 3 ].w;
		Real a01 = m[ 0 ].w*m[ 2 ].z*m[ 3 ].y - m[ 0 ].z*m[ 2 ].w*m[ 3 ].y - m[ 0 ].w*m[ 2 ].y*m[ 3 ].z + m[ 0 ].y*m[ 2 ].w*m[ 3 ].z + m[ 0 ].z*m[ 2 ].y*m[ 3 ].w - m[ 0 ].y*m[ 2 ].z*m[ 3 ].w;
		Real a02 = m[ 0 ].z*m[ 1 ].w*m[ 3 ].y - m[ 0 ].w*m[ 1 ].z*m[ 3 ].y + m[ 0 ].w*m[ 1 ].y*m[ 3 ].z - m[ 0 ].y*m[ 1 ].w*m[ 3 ].z - m[ 0 ].z*m[ 1 ].y*m[ 3 ].w + m[ 0 ].y*m[ 1 ].z*m[ 3 ].w;
		Real a03 = m[ 0 ].w*m[ 1 ].z*m[ 2 ].y - m[ 0 ].z*m[ 1 ].w*m[ 2 ].y - m[ 0 ].w*m[ 1 ].y*m[ 2 ].z + m[ 0 ].y*m[ 1 ].w*m[ 2 ].z + m[ 0 ].z*m[ 1 ].y*m[ 2 ].w - m[ 0 ].y*m[ 1 ].z*m[ 2 ].w;
		Real a10 = m[ 1 ].w*m[ 2 ].z*m[ 3 ].x - m[ 1 ].z*m[ 2 ].w*m[ 3 ].x - m[ 1 ].w*m[ 2 ].x*m[ 3 ].z + m[ 1 ].x*m[ 2 ].w*m[ 3 ].z + m[ 1 ].z*m[ 2 ].x*m[ 3 ].w - m[ 1 ].x*m[ 2 ].z*m[ 3 ].w;
		Real a11 = m[ 0 ].z*m[ 2 ].w*m[ 3 ].x - m[ 0 ].w*m[ 2 ].z*m[ 3 ].x + m[ 0 ].w*m[ 2 ].x*m[ 3 ].z - m[ 0 ].x*m[ 2 ].w*m[ 3 ].z - m[ 0 ].z*m[ 2 ].x*m[ 3 ].w + m[ 0 ].x*m[ 2 ].z*m[ 3 ].w;
		Real a12 = m[ 0 ].w*m[ 1 ].z*m[ 3 ].x - m[ 0 ].z*m[ 1 ].w*m[ 3 ].x - m[ 0 ].w*m[ 1 ].x*m[ 3 ].z + m[ 0 ].x*m[ 1 ].w*m[ 3 ].z + m[ 0 ].z*m[ 1 ].x*m[ 3 ].w - m[ 0 ].x*m[ 1 ].z*m[ 3 ].w;
		Real a13 = m[ 0 ].z*m[ 1 ].w*m[ 2 ].x - m[ 0 ].w*m[ 1 ].z*m[ 2 ].x + m[ 0 ].w*m[ 1 ].x*m[ 2 ].z - m[ 0 ].x*m[ 1 ].w*m[ 2 ].z - m[ 0 ].z*m[ 1 ].x*m[ 2 ].w + m[ 0 ].x*m[ 1 ].z*m[ 2 ].w;
		Real a20 = m[ 1 ].y*m[ 2 ].w*m[ 3 ].x - m[ 1 ].w*m[ 2 ].y*m[ 3 ].x + m[ 1 ].w*m[ 2 ].x*m[ 3 ].y - m[ 1 ].x*m[ 2 ].w*m[ 3 ].y - m[ 1 ].y*m[ 2 ].x*m[ 3 ].w + m[ 1 ].x*m[ 2 ].y*m[ 3 ].w;
		Real a21 = m[ 0 ].w*m[ 2 ].y*m[ 3 ].x - m[ 0 ].y*m[ 2 ].w*m[ 3 ].x - m[ 0 ].w*m[ 2 ].x*m[ 3 ].y + m[ 0 ].x*m[ 2 ].w*m[ 3 ].y + m[ 0 ].y*m[ 2 ].x*m[ 3 ].w - m[ 0 ].x*m[ 2 ].y*m[ 3 ].w;
		Real a22 = m[ 0 ].y*m[ 1 ].w*m[ 3 ].x - m[ 0 ].w*m[ 1 ].y*m[ 3 ].x + m[ 0 ].w*m[ 1 ].x*m[ 3 ].y - m[ 0 ].x*m[ 1 ].w*m[ 3 ].y - m[ 0 ].y*m[ 1 ].x*m[ 3 ].w + m[ 0 ].x*m[ 1 ].y*m[ 3 ].w;
		Real a23 = m[ 0 ].w*m[ 1 ].y*m[ 2 ].x - m[ 0 ].y*m[ 1 ].w*m[ 2 ].x - m[ 0 ].w*m[ 1 ].x*m[ 2 ].y + m[ 0 ].x*m[ 1 ].w*m[ 2 ].y + m[ 0 ].y*m[ 1 ].x*m[ 2 ].w - m[ 0 ].x*m[ 1 ].y*m[ 2 ].w;
		Real a30 = m[ 1 ].z*m[ 2 ].y*m[ 3 ].x - m[ 1 ].y*m[ 2 ].z*m[ 3 ].x - m[ 1 ].z*m[ 2 ].x*m[ 3 ].y + m[ 1 ].x*m[ 2 ].z*m[ 3 ].y + m[ 1 ].y*m[ 2 ].x*m[ 3 ].z - m[ 1 ].x*m[ 2 ].y*m[ 3 ].z;
		Real a31 = m[ 0 ].y*m[ 2 ].z*m[ 3 ].x - m[ 0 ].z*m[ 2 ].y*m[ 3 ].x + m[ 0 ].z*m[ 2 ].x*m[ 3 ].y - m[ 0 ].x*m[ 2 ].z*m[ 3 ].y - m[ 0 ].y*m[ 2 ].x*m[ 3 ].z + m[ 0 ].x*m[ 2 ].y*m[ 3 ].z;
		Real a32 = m[ 0 ].z*m[ 1 ].y*m[ 3 ].x - m[ 0 ].y*m[ 1 ].z*m[ 3 ].x - m[ 0 ].z*m[ 1 ].x*m[ 3 ].y + m[ 0 ].x*m[ 1 ].z*m[ 3 ].y + m[ 0 ].y*m[ 1 ].x*m[ 3 ].z - m[ 0 ].x*m[ 1 ].y*m[ 3 ].z;
		Real a33 = m[ 0 ].y*m[ 1 ].z*m[ 2 ].x - m[ 0 ].z*m[ 1 ].y*m[ 2 ].x + m[ 0 ].z*m[ 1 ].x*m[ 2 ].y - m[ 0 ].x*m[ 1 ].z*m[ 2 ].y - m[ 0 ].y*m[ 1 ].x*m[ 2 ].z + m[ 0 ].x*m[ 1 ].y*m[ 2 ].z;

		Real factor = static_cast<Real>(1.0)/this->Determinant();

		return ( Matrix4x4<Real>
		( a00 * factor, a01 * factor, a02 * factor, a03 * factor,
		  a10 * factor, a11 * factor, a12 * factor, a13 * factor,
		  a20 * factor, a21 * factor, a22 * factor, a23 * factor,
		  a30 * factor, a31 * factor, a32 * factor, a33 * factor)
		);


	}


	template <class Real>
	Real	Matrix4x4<Real>::Determinant() const
	{
		Real value;

		value =
			m[ 0 ].w * m[ 1 ].z * m[ 2 ].y * m[ 3 ].x-m[ 0 ].z * m[ 1 ].w * m[ 2 ].y * m[ 3 ].x-m[ 0 ].w * m[ 1 ].y * m[ 2 ].z * m[ 3 ].x+m[ 0 ].y * m[ 1 ].w    * m[ 2 ].z * m[ 3 ].x+
			m[ 0 ].z * m[ 1 ].y * m[ 2 ].w * m[ 3 ].x-m[ 0 ].y * m[ 1 ].z * m[ 2 ].w * m[ 3 ].x-m[ 0 ].w * m[ 1 ].z * m[ 2 ].x * m[ 3 ].y+m[ 0 ].z * m[ 1 ].w    * m[ 2 ].x * m[ 3 ].y+
			m[ 0 ].w * m[ 1 ].x * m[ 2 ].z * m[ 3 ].y-m[ 0 ].x * m[ 1 ].w * m[ 2 ].z * m[ 3 ].y-m[ 0 ].z * m[ 1 ].x * m[ 2 ].w * m[ 3 ].y+m[ 0 ].x * m[ 1 ].z    * m[ 2 ].w * m[ 3 ].y+
			m[ 0 ].w * m[ 1 ].y * m[ 2 ].x * m[ 3 ].z-m[ 0 ].y * m[ 1 ].w * m[ 2 ].x * m[ 3 ].z-m[ 0 ].w * m[ 1 ].x * m[ 2 ].y * m[ 3 ].z+m[ 0 ].x * m[ 1 ].w    * m[ 2 ].y * m[ 3 ].z+
			m[ 0 ].y * m[ 1 ].x * m[ 2 ].w * m[ 3 ].z-m[ 0 ].x * m[ 1 ].y * m[ 2 ].w * m[ 3 ].z-m[ 0 ].z * m[ 1 ].y * m[ 2 ].x * m[ 3 ].w+m[ 0 ].y * m[ 1 ].z    * m[ 2 ].x * m[ 3 ].w+
			m[ 0 ].z * m[ 1 ].x * m[ 2 ].y * m[ 3 ].w-m[ 0 ].x * m[ 1 ].z * m[ 2 ].y * m[ 3 ].w-m[ 0 ].y * m[ 1 ].x * m[ 2 ].z * m[ 3 ].w+m[ 0 ].x * m[ 1 ].y    * m[ 2 ].z * m[ 3 ].w;

		return value;
	}

	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeTranslate (const Vector3<Real>& v) const
	{
		return ( Matrix4x4<Real>
		( 0.0 ,0.0, 0.0, 0.0,
		  0.0, 0.0, 0.0, 0.0,
		  0.0, 0.0, 0.0, 0.0,
		  v.x , v.y , v.z ,1.0)
		);
	}

	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeTranslate (const Vector4<Real>& v) const
	{
		return ( Matrix4x4<Real>
		( 0.0 ,0.0, 0.0, 0.0,
		  0.0, 0.0, 0.0, 0.0,
		  0.0, 0.0, 0.0, 0.0,
		  v.x , v.y , v.z ,1.0)
		);
	}

	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeTranslate (const Real& v0,const Real& v1,const Real& v2) const
	{
		return ( Matrix4x4<Real>
		( 0.0 ,0.0, 0.0, 0.0,
		  0.0, 0.0, 0.0, 0.0,
		  0.0, 0.0, 0.0, 0.0,
		  v0 , v1 , v2 ,1.0)
		);

	}
	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeScalar (const Vector3<Real>& v) const
	{
		return ( Matrix4x4<Real>
		( v.x ,0.0, 0.0, 0.0,
		  0.0, v.y, 0.0, 0.0,
		  0.0, 0.0, v.z, 0.0,
		  0.0, 0.0, 0.0 ,1.0)
		);
	}


	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakePespectiveProjectionMatrix(const Real& fov, const Real& aspectRation, const Real& near, const Real& far)
	{


		Real c 					= static_cast<Real> (1.0 / std::tan(LAL::Math::kDeg2Rad * fov * 0.5) );
		Real aspectRationInv 	= static_cast<Real> (1.0 / aspectRation);
		Real fovy 				= static_cast<Real> (2.0 * std::atan(aspectRationInv / c));
		Real xScale 			= static_cast<Real> (1.0 / std::tan(0.5 * fovy));
		Real yScale 			= static_cast<Real> (xScale / aspectRationInv);

		Matrix4x4<Real> lProjectionMatrix;

		lProjectionMatrix[ 0 ].x = xScale;
		lProjectionMatrix[ 0 ].y = static_cast< Real >(0);
		lProjectionMatrix[ 0 ].z = static_cast< Real >(0);
		lProjectionMatrix[ 0 ].w = static_cast< Real >(0);

		lProjectionMatrix[ 1 ].x = static_cast< Real >(0);
		lProjectionMatrix[ 1 ].y = yScale;
		lProjectionMatrix[ 1 ].z = static_cast< Real >(0);
		lProjectionMatrix[ 1 ].w = static_cast< Real >(0);

		lProjectionMatrix[ 2 ].x = static_cast< Real >(0);
		lProjectionMatrix[ 2 ].y = static_cast< Real >(0);
		lProjectionMatrix[ 2 ].z = static_cast< Real >((far + near) / (near - far));
		lProjectionMatrix[ 2 ].w = static_cast< Real >((2.0 * far * near) / (near - far));

		lProjectionMatrix[ 3 ].x = static_cast< Real >(0);
		lProjectionMatrix[ 3 ].y = static_cast< Real >(0);
		lProjectionMatrix[ 3 ].z = static_cast< Real >(-1);
		lProjectionMatrix[ 3 ].w = static_cast< Real >(0);

		return Matrix4x4<Real>(lProjectionMatrix);

	};

	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeOrthographicProjectionMatrix (const Real& left, const Real& right,const Real& bottom, const Real& top, const Real& near, const Real& far)
	{
		return Matrix4x4<Real>( (2 / (right - left) ), 0.0, 				  0.0, 					 -(right + left)  /( right - left),
								0.0, 				   (2 / ( top - bottom) ),0.0, 					 -( top + bottom )/( top - bottom ),
								0.0,                   0.0,                   (2 / ( far - near) ),  -( far + near )  /( far - near ),
								0.0,                   0.0,                   0.0,                    1.0 );
	}

	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::MakeViewMatrix(const Vector3<Real>& eyes, const Vector3<Real>& position, const Vector3<Real>& up)
	{

		Vector3<Real> zaxis = (eyes - position).Norm();
		Vector3<Real> xaxis = (up ^ zaxis).Norm();
		Vector3<Real> yaxis =  zaxis ^ xaxis;

		return Matrix4x4<Real>( xaxis.x	   , xaxis.y		, xaxis.z, -(xaxis * eyes),
								yaxis.x	   , yaxis.y		, yaxis.z, -(yaxis * eyes),
								zaxis.x	   , zaxis.y		, zaxis.z, -(zaxis * eyes),
								static_cast< Real > ( 0 ),
								static_cast< Real > ( 0 ),
								static_cast< Real > ( 0 ),
								static_cast< Real > ( 1 ) );


	};

	template <class Real>
	void Matrix4x4<Real>::FromHeadPitchRoll(Real headDegrees, Real pitchDegrees, Real rollDegrees)
	{
		// Constructs a rotation matrix based on a Euler Transform.
		// I use the popular NASA standard airplane convention of
		// heading-pitch-roll (i.e., RzRxRy).

		headDegrees 	= Math::kDeg2Rad * headDegrees;
		pitchDegrees 	= Math::kDeg2Rad * pitchDegrees;
		rollDegrees 	= Math::kDeg2Rad * rollDegrees;

		Real cosH = std::cos(headDegrees);
		Real cosP = std::cos(pitchDegrees);
		Real cosR = std::cos(rollDegrees);
		Real sinH = std::sin(headDegrees);
		Real sinP = std::sin(pitchDegrees);
		Real sinR = std::sin(rollDegrees);

		m[ 0 ].x = cosR * cosH - sinR * sinP * sinH;
		m[ 0 ].y = sinR * cosH + cosR * sinP * sinH;
		m[ 0 ].z = -cosP * sinH;
		m[ 0 ].w = static_cast< Real >(0);

		m[ 1 ].x = -sinR * cosP;
		m[ 1 ].y = cosR * cosP;
		m[ 1 ].z = sinP;
		m[ 1 ].w = static_cast< Real >(0);

		m[ 2 ].x = cosR * sinH + sinR * sinP * cosH;
		m[ 2 ].y = sinR * sinH - cosR * sinP * cosH;
		m[ 2 ].z = cosP * cosH;
		m[ 2 ].w = static_cast< Real >(0);

		m[ 3 ].x = static_cast< Real >(0);
		m[ 3 ].y = static_cast< Real >(0);
		m[ 3 ].z = static_cast< Real >(0);
		m[ 3 ].w = static_cast< Real >(1);
	}

	template <class Real>
	void Matrix4x4<Real>::Rotate(const Vector3<Real>& axis, Real& degrees)
	{


		degrees = Math::kDeg2Rad * degrees;

		Real x = axis.x();
		Real y = axis.y();
		Real z = axis.z();
		Real c = std::cos(degrees);
		Real s = std::sin(degrees);

		m[ 0 ].x = (x * x) * (1.0 - c) + c;
		m[ 0 ].y = (x * y) * (1.0 - c) + (z * s);
		m[ 0 ].z = (x * z) * (1.0 - c) - (y * s);
		m[ 0 ].w = static_cast< Real >(0);

		m[ 1 ].x = (y * x) * (1.0 - c) - (z * s);
		m[ 1 ].y = (y * y) * (1.0 - c) + c;
		m[ 1 ].z = (y * z) * (1.0 - c) + (x * s);
		m[ 1 ].w = 0.0;

		m[ 2 ].x = (z * x) * (1.0 - c) + (y * s);
		m[ 2 ].y = (z * y) * (1.0 - c) - (x * s);
		m[ 2 ].z = (z * z) * (1.0 - c) + c;
		m[ 2 ].w = static_cast< Real >(0);

		m[ 3 ].x = static_cast< Real >(0);
		m[ 3 ].y = static_cast< Real >(0);
		m[ 3 ].z = static_cast< Real >(0);
		m[ 3 ].w = static_cast< Real >(1);
	}

	template <class Real>
	void Matrix4x4<Real>::ToHeadPitchRoll(Real &headDegrees, Real &pitchDegrees, Real &rollDegrees) const
	{


		Real thetaX = std::asin(m[ 1 ].z);
		Real thetaY = static_cast< Real >(0);
		Real thetaZ = static_cast< Real >(0);

		if (thetaX < Math::kHalfPi)
		{
			if (thetaX > -Math::kHalfPi)
			{
				thetaZ = std::atan2(-m[ 1 ].x, m[ 1 ].y);
				thetaY = std::atan2(-m[ 0 ].z, m[ 2 ].z);
			}
			else
			{
				// Not a unique solution.
				thetaZ = -std::atan2(m[ 2 ].x, m[ 0 ].x);
				thetaY = static_cast< Real >(0);
			}
		}
		else
		{
			// Not a unique solution.
			thetaZ = std::atan2(m[ 2 ].x, m[ 0 ].x);
			thetaY = static_cast< Real >(0);
		}

		headDegrees  = Math::kRad2Deg * (thetaY);
		pitchDegrees = Math::kRad2Deg * (thetaX);
		rollDegrees  = Math::kRad2Deg * (thetaZ);
	}


	template <class Real>
	Matrix4x4<Real> Matrix4x4<Real>::Identity ()
	{
		return Matrix4x4<Real>(1.0,0.0,0.0,0.0,
				0.0,1.0,0.0,0.0,
				0.0,0.0,1.0,0.0,
				0.0,0.0,0.0,1.0);
	}

	template <class Real>
	const Real* Matrix4x4<Real>::ToRealPtr( void ) const
	{
		return m[ 0 ].ToFloatPtr();
	}

	template <class Real>
	Real* Matrix4x4<Real>::ToRealPtr( void )
	{
		return m[ 0 ].ToRealPtr();
	}

	template <class Real>
    inline Matrix4x4<Real>::operator const Real*() const
    {
		return m[ 0 ];
	}

	template <class Real>
    inline Matrix4x4<Real>::operator Real*()
	{
		return m[ 0 ];
	}

	template <class Real>
	Matrix4x4<Real>::~Matrix4x4(){};


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
