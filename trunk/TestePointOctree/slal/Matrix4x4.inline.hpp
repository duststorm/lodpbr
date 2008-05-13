#ifndef	LAL_MATRIX4X4_INLINE_HPP_
#define LAL_MATRIX4X4_INLINE_HPP_



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

	this->m[0][0] = xaxis.x; this->m[0][1] = xaxis.y; this->m[0][2] = xaxis.z; this->m[0][3] = -(xaxis * eyes);
	this->m[1][0] = yaxis.x; this->m[1][1] = yaxis.y; this->m[1][2] = yaxis.z; this->m[1][3] = -(yaxis * eyes);
	this->m[2][0] = zaxis.x; this->m[2][1] = zaxis.y; this->m[2][2] = zaxis.z; this->m[2][3] = -(zaxis * eyes);

	this->m[3][0] = static_cast< Real > ( 0 );    
	this->m[3][1] = static_cast< Real > ( 0 );    
	this->m[3][2] = static_cast< Real > ( 0 );
	this->m[3][3] = static_cast< Real > ( 1 );

}


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
	this->m[0][0] = u.x; this->m[0][1] = u.y; this->m[0][2] = u.z; this->m[0][3] = u.w;
	this->m[1][0] = v.x; this->m[1][1] = v.y; this->m[1][2] = v.z; this->m[1][3] = v.w;
	this->m[2][0] = t.x; this->m[2][1] = t.y; this->m[2][2] = t.z; this->m[2][3] = t.w;
	this->m[3][0] = w.x; this->m[3][1] = w.y; this->m[3][2] = w.z; this->m[3][3] = w.w;
};

//	template <class Real>
//	Matrix4x4<Real>::Matrix4x4(const Vector3<Real>& u, const Vector3<Real>& v, const Vector3<Real>& t)
//	{
//		this->m[0][0] = u.x; this->m[0][1] = u.y; this->m[0][2] = u.z; this->m[0][3] = static_cast< Real > ( 0 );
//		this->m[1][0] = v.x; this->m[1][1] = v.y; this->m[1][2] = v.z; this->m[1][3] = static_cast< Real > ( 0 );
//		this->m[2][0] = t.x; this->m[2][1] = t.y; this->m[2][2] = t.z; this->m[2][3] = static_cast< Real > ( 0 ) ;
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
	return ( Vector4<Real>( A.m[0][0] * u.x + A.m[0][1] * u.y + A.m[0][2] * u.z + A.m[0][3] * u.w,

			A.m[1][0] * u.x + A.m[1][1] * u.y + A.m[1][2] * u.z + A.m[1][3] * u.w,

			A.m[2][0] * u.x + A.m[2][1] * u.y + A.m[2][2] * u.z + A.m[2][3] * u.w,

			A.m[3][0] * u.x + A.m[3][1] * u.y + A.m[3][2] * u.z + A.m[3][3] * u.w)

	); 

};

template <class Real>
inline Vector3<Real> operator* ( const Matrix4x4<Real>& A, const Vector3<Real>& u)
{
	return ( Vector3<Real>( A.m[0][0] * u.x + A.m[0][1] * u.y + A.m[0][2] * u.z, 

			A.m[1][0] * u.x + A.m[1][1] * u.y + A.m[1][2] * u.z, 

			A.m[2][0] * u.x + A.m[2][1] * u.y + A.m[2][2] * u.z) );





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
			v.x , v.y , v.z ,1.0) );
}

template <class Real>
Matrix4x4<Real> Matrix4x4<Real>::MakeTranslate (const Vector4<Real>& v) const
{
	return ( Matrix4x4<Real>( 0.0 ,0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0,
			v.x , v.y , v.z ,1.0) );
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
	return ( Matrix4x4<Real>( v.x ,0.0, 0.0, 0.0,
			0.0, v.y, 0.0, 0.0,
			0.0, 0.0, v.y, 0.0,
			0.0, 0.0, 0.0 , 0.0, 1.0) );
}

template <class Real>
Matrix4x4<Real> Matrix4x4<Real>::MakeScalar (const Vector4<Real>& v) const
{
	return ( Matrix4x4<Real>( v.x ,0.0, 0.0, 0.0,
			0.0, v.y, 0.0, 0.0,
			0.0, 0.0, v.y, 0.0,
			0.0, 0.0, 0.0 , 0.0, 1.0) );
}

template <class Real>
Matrix4x4<Real> Matrix4x4<Real>::MakeProjectionMatrix(const Real& fov, const Real aspectRation, const Real& near, const Real& far) const
{


	Real c 					= static_cast<Real> (1.0 / std::tan(LAL::Math::degreesToRadians(fov) * 0.5) );
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

	return Matrix4x4<Real>( xaxis.x	   , xaxis.my		, xaxis.mz, -(xaxis * eyes), 
			yaxis.z	   , yaxis.y		, yaxis.mz, -(yaxis * eyes), 
			zaxis.z	   , zaxis.y		, zaxis.z, -(zaxis * eyes), 
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


#endif

