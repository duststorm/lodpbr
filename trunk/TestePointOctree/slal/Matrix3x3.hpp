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
		Matrix3x3(const Vector3<Real>& u, const Vector3<Real>& q, const Vector3<Real>& r );
		Matrix3x3(const Point3<Real>& u, const Point3<Real>& q, const Point3<Real>& r );
		
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

	template <class Real>
	Matrix3x3<Real>::Matrix3x3()
	{
		this->a[0][0] = (Real)1; this->a[0][1] = (Real)0; this->a[0][2] = (Real)0; 
		this->a[1][0] = (Real)0; this->a[1][1] = (Real)1; this->a[1][2] = (Real)0;
		this->a[2][0] = (Real)0; this->a[2][1] = (Real)0; this->a[2][2] = (Real)1;
	};

	template <class Real>
	Matrix3x3<Real>::Matrix3x3(Real a11, Real a12, Real a13,Real a21, Real a22, Real a23,Real a31, Real a32, Real a33)
	{
		this->a[0][0] = a11; this->a[0][1] = a12; this->a[0][2] = a13; 
		this->a[1][0] = a21; this->a[1][1] = a22; this->a[1][2] = a23;
		this->a[2][0] = a31; this->a[2][1] = a32; this->a[2][2] = a33;
	};

	template <class Real>
	Matrix3x3<Real>::Matrix3x3(const Vector3<Real>& u, const Vector3<Real>& q, const Vector3<Real>& r )
	{
		this->a[0][0] = u.mX; this->a[0][1] = u.mY; this->a[0][2] = u.mZ; 
		this->a[1][0] = q.mX; this->a[1][1] = q.mY; this->a[1][2] = q.mZ;
		this->a[2][0] = r.mX; this->a[2][1] = r.mY; this->a[2][2] = r.mZ;
	};

	template <class Real>
	Matrix3x3<Real>::Matrix3x3(const Point3<Real>& u, const Point3<Real>& q, const Point3<Real>& r )
	{
		this->a[0][0] = u.mX; this->a[0][1] = u.mY; this->a[0][2] = u.mZ; 
		this->a[1][0] = q.mX; this->a[1][1] = q.mY; this->a[1][2] = q.mZ;
		this->a[2][0] = r.mX; this->a[2][1] = r.mY; this->a[2][2] = r.mZ;
	};

	// transpose
	template <class Real>
	inline Matrix3x3<Real> Matrix3x3<Real>::operator~ () const
	{
		return ( Matrix3x3<Real>( a[0][0],a[1][0],a[2][0],
				a[0][1],a[1][1],a[2][1],
				a[0][2],a[1][2],a[2][2] )
		);

	};

	template <class Real>
	inline Matrix3x3<Real>::operator const Real* () const
	{
		return mA;
	}
	//----------------------------------------------------------------------------
	
	template <class Real>
	inline Matrix3x3<Real>::operator Real* ()
	{
		return mA;
	}
	//----------------------------------------------------------------------------

	template <class Real>
	inline const Real* Matrix3x3<Real>::operator[] (int rowIndex) const
	{
		return &mA[3*rowIndex];
	}
	//----------------------------------------------------------------------------

	template <class Real>
	inline Real* Matrix3x3<Real>::operator[] (int rowIndex)
	{
		return &mA[3*rowIndex];
	}

	template <class Real>
	Real Matrix3x3<Real>::operator() ( int i, int j )  	const
	{

		if( i<0 || j<0 || i>=3 || j>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( a[i][j] );

	}

	template <class Real>
	Real& Matrix3x3<Real>::operator() ( int i, int j )  
	{

		if( i<0 || j<0 || i>=3 || j>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( a[i][j] );

	}


	// Return Colum
	template <class Real>
	Vector3<Real> Matrix3x3<Real>::col ( int i )  const
	{

		if( i<0 || i>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( Vector3<Real>( a[0][i] , a[1][i] , a[2][i] ) );

	}

	template <class Real>
	Vector3<Real> Matrix3x3<Real>::row ( int i ) const  
	{

		if( i<0 || i>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
			<< " out of the matrix size."
			<< std::endl;
			exit(1);
		}

		return ( Vector3<Real>( a[i][0] , a[i][1] , a[i][2] ) );

	}

	template <class Real>
	Real * Matrix3x3<Real>::getArray ()
	{
		return mA;
	}



	template <class Real>
	inline Matrix3x3<Real>& Matrix3x3<Real>::operator= ( const Matrix3x3<Real>& A)
	{

		this->a[0][0] = A(0,0); this->a[0][1] = A(0,1); this->a[0][2] = A(0,2); 
		this->a[1][0] = A(1,0); this->a[1][1] = A(1,1); this->a[1][2] = A(1,2);
		this->a[2][0] = A(2,0); this->a[2][1] = A(2,1); this->a[2][2] = A(2,2);

		return ( *this );
	};

	// FRIEND FUNCRealIONS

	template <class Real>
	inline Matrix3x3<Real>  Matrix3x3<Real>::operator- ( ) const
	{

		return ( Matrix3x3<Real>( -this->a[0][0],-this->a[0][1],-this->a[0][2],
				-this->a[1][0],-this->a[1][1],-this->a[1][2],
				-this->a[2][0],-this->a[2][1],-this->a[2][2] )
		);

	};

	template <class Real>
	inline Matrix3x3<Real>  Matrix3x3<Real>::operator+ ( ) const
	{
		return ( Matrix3x3<Real>( this->a[0][0],this->a[0][1],this->a[0][2],
				this->a[1][0],this->a[1][1],this->a[1][2],
				this->a[2][0],this->a[2][1],this->a[2][2] )
		);
	};

	template <class Real>
	inline Matrix3x3<Real> operator+ (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
	{

		return ( Matrix3x3<Real>( A.a[0][0] + B.a[0][0], A.a[0][1] + B.a[0][1], A.a[0][2] + B.a[0][2],
				A.a[1][0] + B.a[1][0], A.a[1][1] + B.a[1][1], A.a[1][2] + B.a[1][2],
				A.a[2][0] + B.a[2][0], A.a[2][1] + B.a[2][1], A.a[2][2] + B.a[2][2] )
		);	
	};

	template <class Real>
	inline Matrix3x3<Real> operator- (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
	{

		return ( Matrix3x3<Real>( A.a[0][0] - B.a[0][0], A.a[0][1] - B.a[0][1], A.a[0][2] - B.a[0][2],
				A.a[1][0] - B.a[1][0], A.a[1][1] - B.a[1][1], A.a[1][2] - B.a[1][2],
				A.a[2][0] - B.a[2][0], A.a[2][1] - B.a[2][1], A.a[2][2] - B.a[2][2] )
		);	
	};

	template <class Real>
	inline Matrix3x3<Real> operator* ( const Real& factor, const Matrix3x3<Real>& A)
	{

		return ( Matrix3x3<Real>( 	A.a[0][0] * factor, A.a[0][1] * factor, A.a[0][2] * factor,
				A.a[1][0] * factor, A.a[1][1] * factor, A.a[1][2] * factor,
				A.a[2][0] * factor, A.a[2][1] * factor, A.a[2][2] * factor )
		);	

	};

	template <class Real>
	inline Matrix3x3<Real> operator* ( const Matrix3x3<Real>& A, const Real& factor)
	{

		return ( Matrix3x3<Real>( A.a[0][0] * factor, A.a[0][1] * factor, A.a[0][2] * factor,
				A.a[1][0] * factor, A.a[1][1] * factor, A.a[1][2] * factor,
				A.a[2][0] * factor, A.a[2][1] * factor, A.a[2][2] * factor )
		);

	};

	template <class Real>
	inline Matrix3x3<Real> operator/ ( const Matrix3x3<Real>& A, const Real& factor)
	{
		Matrix3x3<Real> B;

		if( factor == 0 ){
			std::cerr << "[ERROR]" << std::endl
			<< " division by zero."
			<< std::endl;
			exit(1);
		}

		Real d = 1 / factor;

		return ( Matrix3x3<Real>( A.a[0][0] * d, A.a[0][1] * d, A.a[0][2] * d,
				A.a[1][0] * d, A.a[1][1] * d, A.a[1][2] * d,
				A.a[2][0] * d, A.a[2][1] * d, A.a[2][2] * d )
		);	
	};


	template <class Real>
	inline Matrix3x3<Real> operator* ( const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
	{
		return ( Matrix3x3<Real>( A.a[0][0] * B.a[0][0] + A.a[0][1] * B.a[1][0] + A.a[0][2] * B.a[2][0],
				A.a[0][0] * B.a[0][1] + A.a[0][1] * B.a[1][1] + A.a[0][2] * B.a[2][1],
				A.a[0][0] * B.a[0][2] + A.a[0][1] * B.a[1][2] + A.a[0][2] * B.a[2][2],

				A.a[1][0] * B.a[0][0] + A.a[1][1] * B.a[1][0] + A.a[1][2] * B.a[2][0],
				A.a[1][0] * B.a[0][1] + A.a[1][1] * B.a[1][1] + A.a[1][2] * B.a[2][1],
				A.a[1][0] * B.a[0][2] + A.a[1][1] * B.a[1][2] + A.a[1][2] * B.a[2][2],

				A.a[2][0] * B.a[0][0] + A.a[2][1] * B.a[1][0] + A.a[2][2] * B.a[2][0],
				A.a[2][0] * B.a[0][1] + A.a[2][1] * B.a[1][1] + A.a[2][2] * B.a[2][1],
				A.a[2][0] * B.a[0][2] + A.a[2][1] * B.a[1][2] + A.a[2][2] * B.a[2][2] )

		); 

	};

	template <class Real>
	inline Vector3<Real> operator* ( const Matrix3x3<Real>& A, const Vector3<Real>& u)
	{
		return ( Vector3<Real>( A.a[0][0] * u.mX + A.a[0][1] * u.mY + A.a[0][2] * u.mZ,

				A.a[1][0] * u.mX + A.a[1][1] * u.mY + A.a[1][2] * u.mZ,

				A.a[2][0] * u.mX + A.a[2][1] * u.mY + A.a[2][2] * u.mZ )

		); 

	};

	template <class Real>
	inline Point3<Real> operator* ( const Matrix3x3<Real>& A, const Point3<Real>& p)
	{
		return ( Point3<Real>( A.a[0][0] * p.mX + A.a[0][1] * p.mY + A.a[0][2] * p.mZ,

				A.a[1][0] * p.mX + A.a[1][1] * p.mY + A.a[1][2] * p.mZ,

				A.a[2][0] * p.mX + A.a[2][1] * p.mY + A.a[2][2] * p.mZ )

		); 

	};

	template <class Real>
	inline std::ostream& operator<< (std::ostream & s, const Matrix3x3<Real>& A)
	{
		s << "Matrix 3x3" << std::endl 
		<< " a11 = " << A.a[0][0] << " ,a12 = " << A.a[0][1] << " ,a13 = " << A.a[0][2] << std::endl
		<< " a21 = " << A.a[1][0] << " ,a22 = " << A.a[1][1] << " ,a23 = " << A.a[1][2] << std::endl
		<< " a31 = " << A.a[2][0] << " ,a32 = " << A.a[2][1] << " ,a33 = " << A.a[2][2] << std::endl;

		return ( s );
	};

	template <class Real>
	bool Matrix3x3<Real>::isSymetric ()
	{
		if ( (a[0][1] == a[1][0]) and  
				(a[0][2] == a[2][0]) and	
				(a[2][1] == a[1][2]) )
		{
			return true;
		}

		return false;
	}

	template <class Real>
	Matrix3x3<Real> Matrix3x3<Real>::identity ()
	{
		return Matrix3x3<Real>(1.0,0.0,0.0,
				0.0,1.0,0.0,
				0.0,0.0,1.0);	
	}
	template <class Real>
	Matrix3x3<Real>::~Matrix3x3(){};


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
