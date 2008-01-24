#ifndef MATRIX3X3_HPP_
#define MATRIX3X3_HPP_

namespace SLAL {

template<class T> class Matrix3x3
{
public:
	
	Matrix3x3()
	{
		this->a11 = (T)1; this->a12 = (T)0; this->a13 = (T)0; 
		this->a21 = (T)0; this->a22 = (T)1; this->a23 = (T)0;
		this->a31 = (T)0; this->a32 = (T)0; this->a33 = (T)1;
	};
	
	Matrix3x3(T a11, T a12, T a13,T a21, T a22, T a23,T a31, T a32, T a33)
	{
		this->a11 = a11; this->a12 = a12; this->a13 = a13; 
		this->a21 = a21; this->a22 = a22; this->a23 = a23;
		this->a31 = a31; this->a32 = a32; this->a33 = a33;
	};
	
	
	
	// transpose
	inline Matrix3x3<T>& operator~ () 
	{
		Matrix3x3<T> A = Matrix3x3(a11,a21,a31,
								   a12,a22,a32,
								   a13,a23,a33);
		return A;				
	};
	
	inline Matrix3x3<T>& operator= ( const Matrix3x3<T>& A)
	{
		this->a11 = A.a11;
		this->a12 = A.a12;
		this->a13 = A.a13;
		
		this->a21 = A.a21;
		this->a22 = A.a22;
		this->a23 = A.a23;
		
		this->a31 = A.a31;
		this->a32 = A.a32;
		this->a33 = A.a33;
			
		return ( *this );
	};

	friend inline Matrix3x3<T>& operator+ (Matrix3x3<T>& A, Matrix3x3<T>& B)
	{
		Matrix3x3<T> C;
		
		C.a11 = A.a11 + B.a11;
		C.a12 = A.a12 + B.a12;
		C.a13 = A.a13 + B.a13;
		
		C.a21 = A.a21 + B.a21;
		C.a22 = A.a22 + B.a22;
		C.a23 = A.a23 + B.a23;
		
		C.a31 = A.a31 + B.a31;
		C.a32 = A.a32 + B.a32;
		C.a33 = A.a33 + B.a33;
		
		return C;
	};
	
	friend inline Matrix3x3<T>& operator- (Matrix3x3<T>& A, Matrix3x3<T>& B)
	{
		Matrix3x3<T> C;
		
		C.a11 = A.a11 - B.a11;
		C.a12 = A.a12 - B.a12;
		C.a13 = A.a13 - B.a13;
		
		C.a21 = A.a21 - B.a21;
		C.a22 = A.a22 - B.a22;
		C.a23 = A.a23 - B.a23;
		
		C.a31 = A.a31 - B.a31;
		C.a32 = A.a32 - B.a32;
		C.a33 = A.a33 - B.a33;
		
		return C;
	};
	
	friend  std::ostream& operator<< (std::ostream & s, const Matrix3x3<T>& A)
	{
		s << " a11 = " << A.a11 << " ,a12 = " << A.a12 << " ,a13 = " << A.a13 << std::endl
		  << " a21 = " << A.a21 << " ,a22 = " << A.a22 << " ,a23 = " << A.a23 << std::endl
		  << " a31 = " << A.a31 << " ,a32 = " << A.a32 << " ,a33 = " << A.a33 << std::endl;
		
		return s;
	};
	
	virtual ~Matrix3x3(){};

	T a11;
	T a12;
	T a13;
	T a21;
	T a22;
	T a23;
	T a31;
	T a32;
	T a33;
	
private:

};



}// END NAMESPACE

#endif /*MATRIX3X3_HPP_*/
