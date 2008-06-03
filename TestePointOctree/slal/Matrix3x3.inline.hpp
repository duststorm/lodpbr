#ifndef LAL_MATRIX3X3_INLINE_HPP_
#define LAL_MATRIX3X3_INLINE_HPP_


template <class Real>
Matrix3x3<Real>::Matrix3x3()
{
	this->m[0].x = (Real)1; this->m[0].y = (Real)0; this->m[0].z = (Real)0; 
	this->m[1].x = (Real)0; this->m[1].y = (Real)1; this->m[1].z = (Real)0;
	this->m[2].x = (Real)0; this->m[2].y = (Real)0; this->m[2].z = (Real)1;
};

template <class Real>
Matrix3x3<Real>::Matrix3x3(Real a11, Real a12, Real a13,Real a21, Real a22, Real a23,Real a31, Real a32, Real a33)
{
	this->m[0].x = a11; this->m[0].y = a12; this->m[0].z = a13; 
	this->m[1].x = a21; this->m[1].y = a22; this->m[1].z = a23;
	this->m[2].x = a31; this->m[2].y = a32; this->m[2].z = a33;
};

template <class Real>
Matrix3x3<Real>::Matrix3x3(const Vector3<Real>& row1, const Vector3<Real>& row2, const Vector3<Real>& row3 )
{
	this->m[0].x = row1.x; this->m[0].y = row1.y; this->m[0].z = row1.z; 
	this->m[1].x = row2.x; this->m[1].y = row2.y; this->m[1].z = row2.z;
	this->m[2].x = row3.x; this->m[2].y = row3.y; this->m[2].z = row3.z;
};

template <class Real>
Matrix3x3<Real>::Matrix3x3(const Point3<Real>& row1, const Point3<Real>& row2, const Point3<Real>& row3 )
{
	this->m[0].x = row1.x; this->m[0].y = row1.y; this->m[0].z = row1.z; 
	this->m[1].x = row2.x; this->m[1].y = row2.y; this->m[1].z = row2.z;
	this->m[2].x = row3.x; this->m[2].y = row3.y; this->m[2].z = row3.z;
};

// transpose
template <class Real>
inline Matrix3x3<Real> Matrix3x3<Real>::operator~ () const
{
	return ( Matrix3x3<Real>( m[0].x,m[1].x,m[2].x,
			m[0].y,m[1].y,m[2].y,
			m[0].z,m[1].z,m[2].z )
	);

};

//----------------------------------------------------------------------------

template <class Real>
inline const Vector3<Real>& Matrix3x3<Real>::operator[] (int rowIndex) const
{
	return m[rowIndex];
}
//----------------------------------------------------------------------------

template <class Real>
inline Vector3<Real>& Matrix3x3<Real>::operator[] (int rowIndex)
{
	return m[rowIndex];
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

	return ( m[i][j] );

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

	return ( m[i][j] );

}


// Return Colum
template <class Real>
Vector3<Real> Matrix3x3<Real>::Column ( int i )  const
{

	if( i<0 || i>=3 ){
		std::cerr << "[ERROR] Matrix operator()" << std::endl
		<< " out of the matrix size."
		<< std::endl;
		exit(1);
	}

	return ( Vector3<Real>( m[0][i] , m[1][i] , m[2][i] ) );

}

template <class Real>
Vector3<Real> Matrix3x3<Real>::Row ( int i ) const  
{

	if( i<0 || i>=3 ){
		std::cerr << "[ERROR] Matrix operator()" << std::endl
		<< " out of the matrix size."
		<< std::endl;
		exit(1);
	}

	return ( Vector3<Real>( m[i].x , m[i].y , m[i].z ) );

}

template <class Real>
inline Matrix3x3<Real>& Matrix3x3<Real>::operator= ( const Matrix3x3<Real>& A)
{

	this->m[0].x = A(0,0); this->m[0].y = A(0,1); this->m[0].z = A(0,2); 
	this->m[1].x = A(1,0); this->m[1].y = A(1,1); this->m[1].z = A(1,2);
	this->m[2].x = A(2,0); this->m[2].y = A(2,1); this->m[2].z = A(2,2);

	return ( *this );
};

// FRIEND FUNCRealIONS

template <class Real>
inline Matrix3x3<Real>  Matrix3x3<Real>::operator- ( ) const
{

	return ( Matrix3x3<Real>( -m[0].x,-m[0].y,-m[0].z,
			-m[1].x,-m[1].y,-m[1].z,
			-m[2].x,-m[2].y,-m[2].z )
	);

};

template <class Real>
inline Matrix3x3<Real>  Matrix3x3<Real>::operator+ ( ) const
{
	return ( Matrix3x3<Real>( this->m[0].x,this->m[0].y,this->m[0].z,
			this->m[1].x,this->m[1].y,this->m[1].z,
			this->m[2].x,this->m[2].y,this->m[2].z )
	);
};

template <class Real>
inline Matrix3x3<Real> operator+ (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
{

	return ( Matrix3x3<Real>( A.m[0].x + B.m[0].x, A.m[0].y + B.m[0].y, A.m[0].z + B.m[0].z,
			A.m[1].x + B.m[1].x, A.m[1].y + B.m[1].y, A.m[1].z + B.m[1].z,
			A.m[2].x + B.m[2].x, A.m[2].y + B.m[2].y, A.m[2].z + B.m[2].z )
	);	
};

template <class Real>
inline Matrix3x3<Real> operator- (const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
{

	return ( Matrix3x3<Real>( A.m[0].x - B.m[0].x, A.m[0].y - B.m[0].y, A.m[0].z - B.m[0].z,
			A.m[1].x - B.m[1].x, A.m[1].y - B.m[1].y, A.m[1].z - B.m[1].z,
			A.m[2].x - B.m[2].x, A.m[2].y - B.m[2].y, A.m[2].z - B.m[2].z )
	);	
};

template <class Real>
inline Matrix3x3<Real> operator* ( const Real& factor, const Matrix3x3<Real>& A)
{

	return ( Matrix3x3<Real>( 	A.m[0].x * factor, A.m[0].y * factor, A.m[0].z * factor,
			A.m[1].x * factor, A.m[1].y * factor, A.m[1].z * factor,
			A.m[2].x * factor, A.m[2].y * factor, A.m[2].z * factor )
	);	

};

template <class Real>
inline Matrix3x3<Real> operator* ( const Matrix3x3<Real>& A, const Real& factor)
{

	return ( Matrix3x3<Real>( A.m[0].x * factor, A.m[0].y * factor, A.m[0].z * factor,
			A.m[1].x * factor, A.m[1].y * factor, A.m[1].z * factor,
			A.m[2].x * factor, A.m[2].y * factor, A.m[2].z * factor )
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

	return ( Matrix3x3<Real>( A.m[0].x * d, A.m[0].y * d, A.m[0].z * d,
			A.m[1].x * d, A.m[1].y * d, A.m[1].z * d,
			A.m[2].x * d, A.m[2].y * d, A.m[2].z * d )
	);	
};


template <class Real>
inline Matrix3x3<Real> operator* ( const Matrix3x3<Real>& A, const Matrix3x3<Real>& B)
{
	return ( Matrix3x3<Real>( A.m[0].x * B.m[0].x + A.m[0].y * B.m[1].x + A.m[0].z * B.m[2].x,
			A.m[0].x * B.m[0].y + A.m[0].y * B.m[1].y + A.m[0].z * B.m[2].y,
			A.m[0].x * B.m[0].z + A.m[0].y * B.m[1].z + A.m[0].z * B.m[2].z,

			A.m[1].x * B.m[0].x + A.m[1].y * B.m[1].x + A.m[1].z * B.m[2].x,
			A.m[1].x * B.m[0].y + A.m[1].y * B.m[1].y + A.m[1].z * B.m[2].y,
			A.m[1].x * B.m[0].z + A.m[1].y * B.m[1].z + A.m[1].z * B.m[2].z,

			A.m[2].x * B.m[0].x + A.m[2].y * B.m[1].x + A.m[2].z * B.m[2].x,
			A.m[2].x * B.m[0].y + A.m[2].y * B.m[1].y + A.m[2].z * B.m[2].y,
			A.m[2].x * B.m[0].z + A.m[2].y * B.m[1].z + A.m[2].z * B.m[2].z )

	); 

};

template <class Real>
inline Vector3<Real> operator* ( const Matrix3x3<Real>& A, const Vector3<Real>& u)
{
	return ( Vector3<Real>( A.m[0].x * u.x + A.m[0].y * u.y + A.m[0].z * u.z,

			A.m[1].x * u.x + A.m[1].y * u.y + A.m[1].z * u.z,

			A.m[2].x * u.x + A.m[2].y * u.y + A.m[2].z * u.z )

	); 

};

template <class Real>
inline Point3<Real> operator* ( const Matrix3x3<Real>& A, const Point3<Real>& p)
{
	return ( Point3<Real>( A.m[0].x * p.x + A.m[0].y * p.y + A.m[0].z * p.z,

			A.m[1].x * p.x + A.m[1].y * p.y + A.m[1].z * p.z,

			A.m[2].x * p.x + A.m[2].y * p.y + A.m[2].z * p.z )

	); 

};

template <class Real>
inline std::ostream& operator<< (std::ostream & s, const Matrix3x3<Real>& a)
{
	s << "Matrix 3x3" << std::endl 
	<< " a11 = " << a[0].x << " ,a12 = " << a[0].y << " ,a13 = " << a[0].z << std::endl
	<< " a21 = " << a[1].x << " ,a22 = " << a[1].y << " ,a23 = " << a[1].z << std::endl
	<< " a31 = " << a[2].x << " ,a32 = " << a[2].y << " ,a33 = " << a[2].z << std::endl;

	return ( s );
};

//template <class Real>
//const Real* Matrix3x3<Real>::ToRealPtr( void ) const 
//{
//	return m[0].ToFloatPtr();
//}

template <class Real>
Real* Matrix3x3<Real>::ToRealPtr( void ) 
{
	return m[0].ToRealPtr();
}

template <class Real>
bool Matrix3x3<Real>::IsSymetric ()
{
	if ( (m[0].y == m[1].x) and  
			(m[0].z == m[2].x) and	
			(m[2].y == m[1].z) )
	{
		return true;
	}

	return false;
}

template <class Real>
Matrix3x3<Real> Matrix3x3<Real>::Identity ()
{
	return Matrix3x3<Real>(1.0,0.0,0.0,
			0.0,1.0,0.0,
			0.0,0.0,1.0);	
}
template <class Real>
Matrix3x3<Real>::~Matrix3x3(){};

#endif
