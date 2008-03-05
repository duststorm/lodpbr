#ifndef MATRIX3X3_HPP_
#define MATRIX3X3_HPP_

#include <iostream>

#include "Vector3.hpp" 
/*
 * 
template<class Real> class Matrix3x3
{
private:
	
	Real a[3][3];
	
public:
	
	Matrix3x3();
	
	Matrix3x3(Real a11, Real a12, Real a13,Real a21, Real a22, Real a23,Real a31, Real a32, Real a33);

	// transpose
	inline Matrix3x3<Real> 	operator~ ();
	Real  					operator() ( int i, int j )  	const;
	Real& 					operator() ( int i, int j );  
	Matrix3x3<Real>& 		operator= ( const Matrix3x3<Real>& A);
	Matrix3x3<Real>  		operator- ( ) const;
	Matrix3x3<Real>  		operator+ ( ) const;
	
	friend Matrix3x3<Real> 	operator+ (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B);
	friend Matrix3x3<Real> 	operator- (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B);
	friend Matrix3x3<Real> 	operator* (const Real& factor, const Matrix3x3<Real>& A);
	friend Matrix3x3<Real> 	operator* (const Matrix3x3<Real>& A, const Real& factor);
	friend Matrix3x3<Real>  operator/ (const Matrix3x3<Real>& A, const Real& factor);
	friend Matrix3x3<Real>  operator/ (const Real& factor, const Matrix3x3<Real>& A);
	friend Matrix3x3<Real>  operator* (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B);
	friend std::ostream& 	operator<< (std::ostream & s, const Matrix3x3<Real>& A);
		
    // vector = matrix * vector
    friend Vector3<Real> operator* (const Matrix3x3<Real>& A, const Vector3<Real>& u);	
    friend Vector3<Real> operator* (const Vector3<Real>& u, const Matrix3x3<Real>& A);
		
	virtual ~Matrix3x3(){};
	       
};

*/


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
	
	Matrix3x3()
	{
		this->a[0][0] = (Real)1; this->a[0][1] = (Real)0; this->a[0][2] = (Real)0; 
		this->a[1][0] = (Real)0; this->a[1][1] = (Real)1; this->a[1][2] = (Real)0;
		this->a[2][0] = (Real)0; this->a[2][1] = (Real)0; this->a[2][2] = (Real)1;
	};
	
	Matrix3x3(Real a11, Real a12, Real a13,Real a21, Real a22, Real a23,Real a31, Real a32, Real a33)
	{
		this->a[0][0] = a11; this->a[0][1] = a12; this->a[0][2] = a13; 
		this->a[1][0] = a21; this->a[1][1] = a22; this->a[1][2] = a23;
		this->a[2][0] = a31; this->a[2][1] = a32; this->a[2][2] = a33;
	};

	// transpose
	inline Matrix3x3<Real> operator~ () const
	{
		return ( Matrix3x3<Real>( a[0][0],a[1][0],a[2][0],
				    	       a[0][1],a[1][1],a[2][1],
							   a[0][2],a[1][2],a[2][2] )
			   );
						
	};
	
	inline operator const Real* () const
	{
	    return mA;
	}
	//----------------------------------------------------------------------------

	inline operator Real* ()
	{
	    return mA;
	}
	//----------------------------------------------------------------------------
	
	inline const Real* operator[] (int rowIndex) const
	{
	    return &mA[3*rowIndex];
	}
	//----------------------------------------------------------------------------
	
	inline Real* operator[] (int rowIndex)
	{
	    return &mA[3*rowIndex];
	}
	
	Real operator() ( int i, int j )  	const
	{
				
		if( i<0 || j<0 || i>=3 || j>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
		              << " out of the matrix size."
		              << std::endl;
		    exit(1);
		}
		
		return ( a[i][j] );
		
	}
	
	Real& operator() ( int i, int j )  
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
	Vector3<Real> col ( int i )  const
	{
				
		if( i<0 || i>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
		              << " out of the matrix size."
		              << std::endl;
		    exit(1);
		}
		
		return ( Vector3<Real>( a[0][i] , a[1][i] , a[2][i] ) );
		
	}
	
	Vector3<Real> row ( int i ) const  
	{
				
		if( i<0 || i>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
		              << " out of the matrix size."
		              << std::endl;
		    exit(1);
		}
		
		return ( Vector3<Real>( a[i][0] , a[i][1] , a[i][2] ) );
		
	}
	
	Real * getArray ()
	{
		return mA;
	}
	// Tentar fazer operator [][] , ver geometric Tools Wm4::Math.h
	/*inline operator const Real* () const
	{
	    return a;
	}
	//----------------------------------------------------------------------------
	
	inline operator Real* ()
	{
	    return a;
	}*/
	
	
	inline Matrix3x3<Real>& operator= ( const Matrix3x3<Real>& A)
	{
		
		this->a[0][0] = A(0,0); this->a[0][1] = A(0,1); this->a[0][2] = A(0,2); 
		this->a[1][0] = A(1,0); this->a[1][1] = A(1,1); this->a[1][2] = A(1,2);
		this->a[2][0] = A(2,0); this->a[2][1] = A(2,1); this->a[2][2] = A(2,2);
	
		return ( *this );
	};
	
	// FRIEND FUNCRealIONS
	
	inline Matrix3x3<Real>  operator- ( ) const
	{
		
		return ( Matrix3x3<Real>( -this->a[0][0],-this->a[0][1],-this->a[0][2],
							   -this->a[1][0],-this->a[1][1],-this->a[1][2],
							   -this->a[2][0],-this->a[2][1],-this->a[2][2] )
			   );
			
	};
	
	inline Matrix3x3<Real>  operator+ ( ) const
	{
		return ( Matrix3x3<Real>( this->a[0][0],this->a[0][1],this->a[0][2],
							   this->a[1][0],this->a[1][1],this->a[1][2],
							   this->a[2][0],this->a[2][1],this->a[2][2] )
			   );
	};
	
	friend inline Matrix3x3<Real> operator+ (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
	{
		
		return ( Matrix3x3<Real>( A.a[0][0] + B.a[0][0], A.a[0][1] + B.a[0][1], A.a[0][2] + B.a[0][2],
							   A.a[1][0] + B.a[1][0], A.a[1][1] + B.a[1][1], A.a[1][2] + B.a[1][2],
							   A.a[2][0] + B.a[2][0], A.a[2][1] + B.a[2][1], A.a[2][2] + B.a[2][2] )
			   );	
	};
	
	friend inline Matrix3x3<Real> operator- (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
	{
		
		return ( Matrix3x3<Real>( A.a[0][0] - B.a[0][0], A.a[0][1] - B.a[0][1], A.a[0][2] - B.a[0][2],
							   A.a[1][0] - B.a[1][0], A.a[1][1] - B.a[1][1], A.a[1][2] - B.a[1][2],
							   A.a[2][0] - B.a[2][0], A.a[2][1] - B.a[2][1], A.a[2][2] - B.a[2][2] )
			   );	
	};
	
	friend inline Matrix3x3<Real> operator* ( const Real& factor, const Matrix3x3<Real>& A)
	{
		
		return ( Matrix3x3<Real>( 	A.a[0][0] * factor, A.a[0][1] * factor, A.a[0][2] * factor,
									A.a[1][0] * factor, A.a[1][1] * factor, A.a[1][2] * factor,
									A.a[2][0] * factor, A.a[2][1] * factor, A.a[2][2] * factor )
			   );	
				
	};
	
	friend inline Matrix3x3<Real> operator* ( const Matrix3x3<Real>& A, const Real& factor)
	{
		
		return ( Matrix3x3<Real>( A.a[0][0] * factor, A.a[0][1] * factor, A.a[0][2] * factor,
							   A.a[1][0] * factor, A.a[1][1] * factor, A.a[1][2] * factor,
							   A.a[2][0] * factor, A.a[2][1] * factor, A.a[2][2] * factor )
			   );
		
	};
	

	friend inline Matrix3x3<Real> operator/ ( const Matrix3x3<Real>& A, const Real& factor)
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

	friend inline Matrix3x3<Real> operator/ (const Real& factor ,  const Matrix3x3<Real>& A)
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
	
	friend inline Matrix3x3<Real> operator* ( const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
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
	
	friend inline Vector3<Real> operator* ( const Matrix3x3<Real>& A, const Vector3<Real>& u)
	{
		return ( Vector3<Real>( A.a[0][0] * u.mX + A.a[0][1] * u.mY + A.a[0][2] * u.mZ,
							   							   
							   	A.a[1][0] * u.mX + A.a[1][1] * u.mY + A.a[1][2] * u.mZ,
							   		
							   	A.a[2][0] * u.mX + A.a[2][1] * u.mY + A.a[2][2] * u.mZ )
		
				); 
		
	};
	
	
	friend  inline std::ostream& operator<< (std::ostream & s, const Matrix3x3<Real>& A)
	{
		s << "Matrix 3x3" << std::endl 
		  << " a11 = " << A.a[0][0] << " ,a12 = " << A.a[0][1] << " ,a13 = " << A.a[0][2] << std::endl
		  << " a21 = " << A.a[1][0] << " ,a22 = " << A.a[1][1] << " ,a23 = " << A.a[1][2] << std::endl
		  << " a31 = " << A.a[2][0] << " ,a32 = " << A.a[2][1] << " ,a33 = " << A.a[2][2] << std::endl;
		
		return ( s );
	};

	bool isSymetric ()
	{
		if ( (a[0][1] == a[1][0]) and  
			 (a[0][2] == a[2][0]) and	
			 (a[2][1] == a[1][2]) )
		{
			return true;
		}
					
		return false;
	}
	
	
	
	virtual ~Matrix3x3(){};
	       
};



}// END NAMESPACE

#endif /*MATRIX3X3_HPP_*/
