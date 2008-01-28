#ifndef MATRIX3X3_HPP_
#define MATRIX3X3_HPP_

#include <iostream>

namespace SLAL {

template<class T> class Matrix3x3
{
public:
	
	Matrix3x3()
	{
		this->a[0][0] = (T)1; this->a[0][1] = (T)0; this->a[0][2] = (T)0; 
		this->a[1][0] = (T)0; this->a[1][1] = (T)1; this->a[1][2] = (T)0;
		this->a[2][0] = (T)0; this->a[2][1] = (T)0; this->a[2][2] = (T)1;
	};
	
	Matrix3x3(T a11, T a12, T a13,T a21, T a22, T a23,T a31, T a32, T a33)
	{
		this->a[0][0] = a11; this->a[0][1] = a12; this->a[0][2] = a13; 
		this->a[1][0] = a21; this->a[1][1] = a22; this->a[1][2] = a23;
		this->a[2][0] = a31; this->a[2][1] = a32; this->a[2][2] = a33;
	};

	// transpose
	inline Matrix3x3<T> operator~ () 
	{
		Matrix3x3<T> A =  Matrix3x3(a[0][0],a[1][0],a[2][0],
								    a[0][1],a[1][1],a[2][1],
								    a[0][2],a[1][2],a[2][2]);
		return ( A );				
	};
	

	T operator() ( int i, int j )  	const
	{
				
		if( i<0 || j<0 || i>=3 || j>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
		              << " out of the matrix size."
		              << std::endl;
		    exit(1);
		}
		
		return ( a[i][j] );
		
	}
	
	T& operator() ( int i, int j )  
	{
				
		if( i<0 || j<0 || i>=3 || j>=3 ){
			std::cerr << "[ERROR] Matrix operator()" << std::endl
		              << " out of the matrix size."
		              << std::endl;
		    exit(1);
		}
		
		return ( a[i][j] );
		
	}

	inline Matrix3x3<T>& operator= ( const Matrix3x3<T>& A)
	{
		
		this->a[0][0] = A(0,0); this->a[0][1] = A(0,1); this->a[0][2] = A(0,2); 
		this->a[1][0] = A(1,0); this->a[1][1] = A(1,1); this->a[1][2] = A(1,2);
		this->a[2][0] = A(2,0); this->a[2][1] = A(2,1); this->a[2][2] = A(2,2);
	
		return ( *this );
	};
	
	// FRIEND FUNCTIONS
	
	inline Matrix3x3<T>  operator- ( ) const
	{
		Matrix3x3<T> A;
		 	
		A(0,0) = -this->a[0][0]; 
		A(0,1) = -this->a[0][1];
		A(0,2) = -this->a[0][2];
		
		A(1,0) = -this->a[1][0]; 
		A(1,1) = -this->a[1][1];
		A(1,2) = -this->a[1][2];
		
		A(2,0) = -this->a[2][0]; 
		A(2,1) = -this->a[2][1];
		A(2,2) = -this->a[2][2];

			
		return ( A );
	};
	
	inline Matrix3x3<T>  operator+ ( ) const
	{
		Matrix3x3<T> A;
		 	
		A(0,0) = this->a[0][0]; 
		A(0,1) = this->a[0][1];
		A(0,2) = this->a[0][2];
		
		A(1,0) = this->a[1][0]; 
		A(1,1) = this->a[1][1];
		A(1,2) = this->a[1][2];
		
		A(2,0) = this->a[2][0]; 
		A(2,1) = this->a[2][1];
		A(2,2) = this->a[2][2];

			
		return ( A );
	};
	
	friend inline Matrix3x3<T> operator+ (Matrix3x3<T>& A, Matrix3x3<T>& B)
	{
		Matrix3x3<T> C;
		
		C.a[0][0] = A.a[0][0] + B.a[0][0];
		C.a[0][1] = A.a[0][1] + B.a[0][1];
		C.a[0][2] = A.a[0][2] + B.a[0][2];
		
		C.a[1][0] = A.a[1][0] + B.a[1][0];
		C.a[1][1] = A.a[1][1] + B.a[1][1];
		C.a[1][2] = A.a[1][2] + B.a[1][2];
		
		C.a[2][0] = A.a[2][0] + B.a[2][0];
		C.a[2][1] = A.a[2][1] + B.a[2][1];
		C.a[2][2] = A.a[2][2] + B.a[2][2];	
		
		return ( C );
	};
	
	friend inline Matrix3x3<T> operator- (Matrix3x3<T>& A, Matrix3x3<T>& B)
	{
		Matrix3x3<T> C;
		
		C.a[0][0] = A.a[0][0] - B.a[0][0];
		C.a[0][1] = A.a[0][1] - B.a[0][1];
		C.a[0][2] = A.a[0][2] - B.a[0][2];
		
		C.a[1][0] = A.a[1][0] - B.a[1][0];
		C.a[1][1] = A.a[1][1] - B.a[1][1];
		C.a[1][2] = A.a[1][2] - B.a[1][2];
		
		C.a[2][0] = A.a[2][0] - B.a[2][0];
		C.a[2][1] = A.a[2][1] - B.a[2][1];
		C.a[2][2] = A.a[2][2] - B.a[2][2];
		
		return ( C );
	};
	
	friend inline Matrix3x3<T> operator* ( const T& factor, Matrix3x3<T>& A)
	{
		Matrix3x3<T> B;
		
		B.a[0][0] = A.a[0][0] * factor;
		B.a[0][1] = A.a[0][1] * factor;
		B.a[0][2] = A.a[0][2] * factor;
		
		B.a[1][0] = A.a[1][0] * factor;
		B.a[1][1] = A.a[1][1] * factor;
		B.a[1][2] = A.a[1][2] * factor;
		
		B.a[2][0] = A.a[2][0] * factor;
		B.a[2][1] = A.a[2][1] * factor;
		B.a[2][2] = A.a[2][2] * factor;
		
		return ( B );
	};
	
	friend inline Matrix3x3<T> operator* ( Matrix3x3<T>& A, const T& factor)
	{
		Matrix3x3<T> B;
		
		B.a[0][0] = A.a[0][0] * factor;
		B.a[0][1] = A.a[0][1] * factor;
		B.a[0][2] = A.a[0][2] * factor;
		
		B.a[1][0] = A.a[1][0] * factor;
		B.a[1][1] = A.a[1][1] * factor;
		B.a[1][2] = A.a[1][2] * factor;
		
		B.a[2][0] = A.a[2][0] * factor;
		B.a[2][1] = A.a[2][1] * factor;
		B.a[2][2] = A.a[2][2] * factor;
		
		return ( B );
	};
	

	friend inline Matrix3x3<T> operator/ ( Matrix3x3<T>& A, const T& factor)
	{
		Matrix3x3<T> B;
		
		if( factor == 0 ){
			std::cerr << "[ERROR]" << std::endl
		              << " division by zero."
		              << std::endl;
		    exit(1);
		}
		
		B.a[0][0] = A.a[0][0] / factor;
		B.a[0][1] = A.a[0][1] / factor;
		B.a[0][2] = A.a[0][2] / factor;
		
		B.a[1][0] = A.a[1][0] / factor;
		B.a[1][1] = A.a[1][1] / factor;
		B.a[1][2] = A.a[1][2] / factor;
		
		B.a[2][0] = A.a[2][0] / factor;
		B.a[2][1] = A.a[2][1] / factor;
		B.a[2][2] = A.a[2][2] / factor;
		
		return ( B );
	};

	
	friend inline Matrix3x3<T> operator* ( const Matrix3x3<T>& A, const Matrix3x3<T>& B)
	{
		Matrix3x3<T> C = Matrix3x3(A.a[0][0] * B.a[0][0] + A.a[0][1] * B.a[1][0] + A.a[0][2] * B.a[2][0],
								   A.a[0][0] * B.a[0][1] + A.a[0][1] * B.a[1][1] + A.a[0][2] * B.a[2][1],
		   						   A.a[0][0] * B.a[0][2] + A.a[0][1] * B.a[1][2] + A.a[0][2] * B.a[2][2],
								   A.a[1][0] * B.a[0][0] + A.a[1][1] * B.a[1][0] + A.a[1][2] * B.a[2][0],
								   A.a[1][0] * B.a[0][1] + A.a[1][1] * B.a[1][1] + A.a[1][2] * B.a[2][1],
								   A.a[1][0] * B.a[0][2] + A.a[1][1] * B.a[1][2] + A.a[1][2] * B.a[2][2],
								   A.a[2][0] * B.a[0][0] + A.a[2][1] * B.a[1][0] + A.a[2][2] * B.a[2][0],
								   A.a[2][0] * B.a[0][1] + A.a[2][1] * B.a[1][1] + A.a[2][2] * B.a[2][1],
								   A.a[2][0] * B.a[0][2] + A.a[2][1] * B.a[1][2] + A.a[2][2] * B.a[2][2]);
								   
	return ( C );	
		
	}
	
	friend  inline std::ostream& operator<< (std::ostream & s, const Matrix3x3<T>& A)
	{
		s << "Matrix3" << std::endl 
		  << " a11 = " << A(0,0) << " ,a12 = " << A(0,1) << " ,a13 = " << A(0,2) << std::endl
		  << " a21 = " << A(1,0) << " ,a22 = " << A(1,1) << " ,a23 = " << A(1,2) << std::endl
		  << " a31 = " << A(2,0) << " ,a32 = " << A(2,1) << " ,a33 = " << A(2,2) << std::endl;
		
		return ( s );
	};
	
	virtual ~Matrix3x3(){};

	
	
private:
	
	T a[3][3];
	       
};



}// END NAMESPACE

#endif /*MATRIX3X3_HPP_*/
