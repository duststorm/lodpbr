#ifndef	LAL_MATRIX4X4_INLINE_HPP_
#define LAL_MATRIX4X4_INLINE_HPP_

template <class Real>
Matrix4x4<Real>::Matrix4x4()
{
	this->m[0].x =  static_cast< Real > ( 1 );
	this->m[0].y =  static_cast< Real > ( 0 );
	this->m[0].z =  static_cast< Real > ( 0 );
	this->m[0].w =  static_cast< Real > ( 0 );

	this->m[1].x =  static_cast< Real > ( 0 );
	this->m[1].y =  static_cast< Real > ( 1 ); 
	this->m[1].z =  static_cast< Real > ( 0 );
	this->m[1].w =  static_cast< Real > ( 0 );

	this->m[2].x =  static_cast< Real > ( 0 );
	this->m[2].y =  static_cast< Real > ( 0 );
	this->m[2].z =  static_cast< Real > ( 1 );
	this->m[2].w =  static_cast< Real > ( 0 );

	this->m[3].x =  static_cast< Real > ( 0 ); 
	this->m[3].y =  static_cast< Real > ( 0 );
	this->m[3].z =  static_cast< Real > ( 0 );
	this->m[3].w =  static_cast< Real > ( 1 );
};

template <class Real>
Matrix4x4<Real>::Matrix4x4(const Matrix4x4<Real>& a)
{
	this->m[0].x = a[0].x; this->m[0].y = a[0].y; this->m[0].z = a[0].z; this->m[0].w = a[0].w; 
	this->m[1].x = a[1].x; this->m[1].y = a[1].y; this->m[1].z = a[1].z; this->m[1].w = a[1].w;
	this->m[2].x = a[2].x; this->m[2].y = a[2].y; this->m[2].z = a[2].z; this->m[2].w = a[2].w;
	this->m[3].x = a[3].x; this->m[3].y = a[3].y; this->m[3].z = a[3].z; this->m[3].w = a[3].w;
}

template <class Real>
template <class T>
Matrix4x4<Real>::Matrix4x4(const Matrix4x4<T>& A)
{
	this->m[0].x = A[0].x; this->m[0].y = A[0].y; this->m[0].z = A[0].z; this->m[0].w = A[0].w; 
	this->m[1].x = A[1].x; this->m[1].y = A[1].y; this->m[1].z = A[1].z; this->m[1].w = A[1].w;
	this->m[2].x = A[2].x; this->m[2].y = A[2].y; this->m[2].z = A[2].z; this->m[2].w = A[2].w;
	this->m[3].x = A[3].x; this->m[3].y = A[3].y; this->m[3].z = A[3].z; this->m[3].w = A[3].w;
}


template <class Real>
Matrix4x4<Real>::Matrix4x4( Real a00, Real a01,Real  a02,Real  a03,
		Real a10,Real  a11,Real  a12,Real  a13, 
		Real a20,Real  a21,Real  a22,Real  a23,
		Real a30,Real  a31,Real  a32,Real  a33)
{
	this->m[0].x = a00; this->m[0].y = a01; this->m[0].z = a02; this->m[0].w = a03; 
	this->m[1].x = a10; this->m[1].y = a11; this->m[1].z = a12; this->m[1].w = a13;
	this->m[2].x = a20; this->m[2].y = a21; this->m[2].z = a22; this->m[2].w = a23;
	this->m[3].x = a30; this->m[3].y = a31; this->m[3].z = a32; this->m[3].w = a33;
};

template <class Real>
Matrix4x4<Real>::Matrix4x4(const Vector4<Real>& row1, const Vector4<Real>& row2, const Vector4<Real>& row3, const Vector4<Real>& row4  )
{
	this->m[0].x = row1.x; this->m[0].y = row1.y; this->m[0].z = row1.z; this->m[0].w = row1.w;
	this->m[1].x = row2.x; this->m[1].y = row2.y; this->m[1].z = row2.z; this->m[1].w = row2.w;
	this->m[2].x = row3.x; this->m[2].y = row3.y; this->m[2].z = row3.z; this->m[2].w = row3.w;
	this->m[3].x = row4.x; this->m[3].y = row4.y; this->m[3].z = row4.z; this->m[3].w = row4.w;
};

template <class Real>
Matrix4x4<Real>::Matrix4x4(const Vector3<Real>& row1, const Vector3<Real>& row2, const Vector3<Real>& row3)
{
	this->m[0].x = row1.x; this->m[0].y = row1.y; this->m[0].z = row1.z; this->m[0].w = static_cast< Real > ( 0 );
	this->m[1].x = row2.x; this->m[1].y = row2.y; this->m[1].z = row2.z; this->m[1].w = static_cast< Real > ( 0 );
	this->m[2].x = row3.x; this->m[2].y = row3.y; this->m[2].z = row3.z; this->m[2].w = static_cast< Real > ( 0 ) ;
	this->m[3].x = static_cast< Real > ( 0 ); this->m[3].y = static_cast< Real > ( 0 ); this->m[3].z =	static_cast< Real > ( 0 ) ; this->m[3].w = static_cast< Real > ( 1 );
};



// transpose
template <class Real>
inline Matrix4x4<Real> Matrix4x4<Real>::operator~ () const
{
	return ( Matrix4x4<Real>( m[0].x,m[1].x,m[2].x,m[3].x,
			m[0].y,m[1].y,m[2].y,m[3].y,
			m[0].z,m[1].z,m[2].z,m[3].z,
			m[0].w,m[1].w,m[2].w,m[3].w)
	);

};


//----------------------------------------------------------------------------

template <class Real>
inline const Vector4<Real>& Matrix4x4<Real>::operator[] (int rowIndex) const
{
 	return m[rowIndex];
}
//----------------------------------------------------------------------------

template <class Real>
inline Vector4<Real>& Matrix4x4<Real>::operator[] (int rowIndex)
{
 	return m[rowIndex];
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
Vector4<Real> Matrix4x4<Real>::Column ( int i )  const
{

	if( i<0 || i>=4 ){
		std::cerr << "[ERROR] Matrix operator()" << std::endl
		<< " out of the matrix size."
		<< std::endl;
		exit(1);
	}

	return ( Vector4<Real>( m[0][i] , m[1][i] , m[2][i] , m[3][i] ) );

}

template <class Real>
Vector4<Real> Matrix4x4<Real>::Row ( int i ) const  
{

	if( i<0 || i>=4 ){
		std::cerr << "[ERROR] Matrix operator()" << std::endl
		<< " out of the matrix size."
		<< std::endl;
		exit(1);
	}

	return ( Vector4<Real>( m[i].x , m[i].y , m[i].z , m[i].w ) );

}


template <class Real>
inline Matrix4x4<Real>& Matrix4x4<Real>::operator= ( const Matrix4x4<Real>& a)
{

	this->m[0].x = a[0].x; this->m[0].y = a[0].y; this->m[0].z = a[0].z; this->m[0].w = a[0].w; 
	this->m[1].x = a[1].x; this->m[1].y = a[1].y; this->m[1].z = a[1].z; this->m[1].w = a[1].w;
	this->m[2].x = a[2].x; this->m[2].y = a[2].y; this->m[2].z = a[2].z; this->m[2].w = a[2].w;
	this->m[3].x = a[3].x; this->m[3].y = a[3].y; this->m[3].z = a[3].z; this->m[3].w = a[3].w;

	return ( *this );
};

// FRIEND FUNCRealIONS

template <class Real>
inline Matrix4x4<Real>  Matrix4x4<Real>::operator- ( ) const
{

	return ( Matrix4x4<Real>( -this->m[0].x,-this->m[0].y,-this->m[0].z,-this->m[0].w,
			-this->m[1].x,-this->m[1].y,-this->m[1].z,-this->m[1].w,
			-this->m[2].x,-this->m[2].y,-this->m[2].z,-this->m[2].w,
			-this->m[3].x,-this->m[3].y,-this->m[3].z,-this->m[3].w)
	);

};

template <class Real>
inline Matrix4x4<Real>  Matrix4x4<Real>::operator+ ( ) const
{
	return ( Matrix4x4<Real>( this->m[0].x,this->m[0].y,this->m[0].z,this->m[0].w,
			this->m[1].x,this->m[1].y,this->m[1].z,this->m[1].w,
			this->m[2].x,this->m[2].y,this->m[2].z,this->m[2].w,
			this->m[3].x,this->m[3].y,this->m[3].z,this->m[3].w)
	);
};

template <class Real>
inline Matrix4x4<Real> operator+ (const Matrix4x4<Real>& a, const Matrix4x4<Real>& b)
{

	return ( Matrix4x4<Real>( a[0].x + b[0].x, a[0].y + b[0].y, a[0].z + b[0].z, a[0].w + b[0].w,
			a[1].x + b[1].x, a[1].y + b[1].y, a[1].z + b[1].z, a[1].w + b[1].w, 
			a[2].x + b[2].x, a[2].y + b[2].y, a[2].z + b[2].z, a[2].w + b[2].w,
			a[3].x + b[3].x, a[3].y + b[3].y, a[3].z + b[3].z, a[3].w + b[3].w)
	);	
};

template <class Real>
inline Matrix4x4<Real> operator- (const Matrix4x4<Real>& a, const Matrix4x4<Real>& b)
{

	return ( Matrix4x4<Real>( a[0].x - b[0].x, a[0].y - b[0].y, a[0].z - b[0].z, a[0].w - b[0].w,
			a[1].x - b[1].x, a[1].y - b[1].y, a[1].z - b[1].z, a[1].w - b[1].w,
			a[2].x - b[2].x, a[2].y - b[2].y, a[2].z - b[2].z, a[2].w - b[2].w,
			a[3].x - b[3].x, a[3].y - b[3].y, a[3].z - b[3].z, a[3].w - b[3].w)
	);	
};

template <class Real>
inline Matrix4x4<Real> operator* ( const Real& factor, const Matrix4x4<Real>& a)
{

	return ( Matrix4x4<Real>( 	a[0].x * factor, a[0].y * factor, a[0].z * factor, a[0].w * factor,
			a[1].x * factor, a[1].y * factor, a[1].z * factor, a[1].w * factor,
			a[2].x * factor, a[2].y * factor, a[2].z * factor, a[2].w * factor, 
			a[3].x * factor, a[3].y * factor, a[3].z * factor, a[3].w * factor)
	);	

};

template <class Real>
inline Matrix4x4<Real> operator* ( const Matrix4x4<Real>& a, const Real& factor)
{

	return ( Matrix4x4<Real>( 	a[0].x * factor, a[0].y * factor, a[0].z * factor, a[0].w * factor,
			a[1].x * factor, a[1].y * factor, a[1].z * factor, a[1].w * factor,
			a[2].x * factor, a[2].y * factor, a[2].z * factor, a[2].w * factor, 
			a[3].x * factor, a[3].y * factor, a[3].z * factor, a[3].w * factor)
	);	
};

template <class Real>
inline Matrix4x4<Real>& Matrix4x4<Real>::operator+= ( const Real& factor)
{

	m[0].x += factor; m[0].y += factor; m[0].z += factor; m[0].w += factor;
	m[1].x += factor; m[1].y += factor; m[1].z += factor; m[1].w += factor;
	m[2].x += factor; m[2].y += factor; m[2].z += factor; m[2].w += factor; 
	m[3].x += factor; m[3].y += factor; m[3].z += factor; m[3].w += factor;

	return (*this);
};

template <class Real>
inline Matrix4x4<Real>& Matrix4x4<Real>::operator-= ( const Real& factor)
{

	m[0].x -= factor; m[0].y -= factor; m[0].z -= factor; m[0].w -= factor;
	m[1].x -= factor; m[1].y -= factor; m[1].z -= factor; m[1].w -= factor;
	m[2].x -= factor; m[2].y -= factor; m[2].z -= factor; m[2].w -= factor; 
	m[3].x -= factor; m[3].y -= factor; m[3].z -= factor; m[3].w -= factor;

	return (*this);
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

	m[0].x *= lFactor; m[0].y *= lFactor; m[0].z *= lFactor; m[0].w *= lFactor;
	m[1].x *= lFactor; m[1].y *= lFactor; m[1].z *= lFactor; m[1].w *= lFactor;
	m[2].x *= lFactor; m[2].y *= lFactor; m[2].z *= lFactor; m[2].w *= lFactor; 
	m[3].x *= lFactor; m[3].y *= lFactor; m[3].z *= lFactor; m[3].w *= lFactor;

	return (*this);
};

template <class Real>
inline Matrix4x4<Real>& Matrix4x4<Real>::operator*= ( const Real& factor)
{

	m[0].x *= factor; m[0].y *= factor; m[0].z *= factor; m[0].w *= factor;
	m[1].x *= factor; m[1].y *= factor; m[1].z *= factor; m[1].w *= factor;
	m[2].x *= factor; m[2].y *= factor; m[2].z *= factor; m[2].w *= factor; 
	m[3].x *= factor; m[3].y *= factor; m[3].z *= factor; m[3].w *= factor;

	return (*this);
};

template <class Real>
inline Matrix4x4<Real> operator/ ( const Matrix4x4<Real>& a, const Real& factor)
{

	if( factor == 0 ){
		std::cerr << "[ERROR]" << std::endl
		<< " division by zero."
		<< std::endl;
		exit(1);
	}

	Real lFactor = 1 / factor;

	return ( Matrix4x4<Real>( 	a[0].x * lFactor, a[0].y * lFactor, a[0].z * lFactor, a[0].w * lFactor,
			a[1].x * lFactor, a[1].y * lFactor, a[1].z * lFactor, a[1].w * lFactor,
			a[2].x * lFactor, a[2].y * lFactor, a[2].z * lFactor, a[2].w * lFactor, 
			a[3].x * lFactor, a[3].y * lFactor, a[3].z * lFactor, a[3].w * lFactor)
	);	
};


template <class Real>
inline Matrix4x4<Real> operator* ( const Matrix4x4<Real>& a, const Matrix4x4<Real>& b)
{
	return ( Matrix4x4<Real>( a[0].x * b[0].x + a[0].y * b[1].x + a[0].z * b[2].x + a[0].w * b[3].x,
			a[0].x * b[0].y + a[0].y * b[1].y + a[0].z * b[2].y + a[0].w * b[3].y, 
			a[0].x * b[0].z + a[0].y * b[1].z + a[0].z * b[2].z + a[0].w * b[3].z,
			a[0].x * b[0].w + a[0].y * b[1].w + a[0].z * b[2].w + a[0].w * b[3].w,

			a[1].x * b[0].x + a[1].y * b[1].x + a[1].z * b[2].x + a[1].w * b[3].x,
			a[1].x * b[0].y + a[1].y * b[1].y + a[1].z * b[2].y + a[1].w * b[3].y,
			a[1].x * b[0].z + a[1].y * b[1].z + a[1].z * b[2].z + a[1].w * b[3].z, 
			a[1].x * b[0].w + a[1].y * b[1].w + a[1].z * b[2].w + a[1].w * b[3].w,

			a[2].x * b[0].x + a[2].y * b[1].x + a[2].z * b[2].x + a[2].w * b[3].x,
			a[2].x * b[0].y + a[2].y * b[1].y + a[2].z * b[2].y + a[2].w * b[3].y,
			a[2].x * b[0].z + a[2].y * b[1].z + a[2].z * b[2].z + a[2].w * b[3].z,
			a[2].x * b[0].w + a[2].y * b[1].w + a[2].z * b[2].w + a[2].w * b[3].w,

			a[3].x * b[0].x + a[3].y * b[1].x + a[3].z * b[2].x + a[3].w * b[3].x,
			a[3].x * b[0].y + a[3].y * b[1].y + a[3].z * b[2].y + a[3].w * b[3].y,
			a[3].x * b[0].z + a[3].y * b[1].z + a[3].z * b[2].z + a[3].w * b[3].z,
			a[3].x * b[0].w + a[3].y * b[1].w + a[3].z * b[2].w + a[3].w * b[3].w)

	); 

};

template <class Real>
inline Vector3<Real> operator* ( const Matrix4x4<Real>& a, const Vector4<Real>& u)
{
	return ( Vector4<Real>( a[0].x * u.x + a[0].y * u.y + a[0].z * u.z + a[0].w * u.w,

			a[1].x * u.x + a[1].y * u.y + a[1].z * u.z + a[1].w * u.w,

			a[2].x * u.x + a[2].y * u.y + a[2].z * u.z + a[2].w * u.w,

			a[3].x * u.x + a[3].y * u.y + a[3].z * u.z + a[3].w * u.w)

	); 

};

template <class Real>
inline Vector3<Real> operator* ( const Matrix4x4<Real>& a, const Vector3<Real>& u)
{
	return ( Vector3<Real>( a[0].x * u.x + a[0].y * u.y + a[0].z * u.z, 

			a[1].x * u.x + a[1].y * u.y + a[1].z * u.z, 

			a[2].x * u.x + a[2].y * u.y + a[2].z * u.z) );





};


template <class Real>
inline std::ostream& operator<< (std::ostream & s, const Matrix4x4<Real>& a)
{
			s << "Matrix 4x4" << std::endl 
			<< " m[1].y = " << a[0].x << " ,m[1].z = " << a[0].y << " ,m[1].w = " << a[0].z << " ,a41 = " <<a[0].w << std::endl
			<< " m[2].y = " << a[1].x << " ,m[2].z = " << a[1].y << " ,m[2].w = " << a[1].z << " ,a42 = " <<a[1].w << std::endl
			<< " m[3].y = " << a[2].x << " ,m[3].z = " << a[2].y << " ,m[3].w = " << a[2].z << " ,a43 = " <<a[2].w << std::endl
			<< " a41 = " << a[3].x << " ,a42 = " << a[3].y << " ,a43 = " << a[3].z << " ,a44 = " << a[3].w << std::endl;

	return ( s );
};

template <class Real>
bool Matrix4x4<Real>::IsSymetric ()
{
	if ( (m[0].y == m[1].x) and  
			(m[0].z == m[2].x) and
			(m[0].w == m[3].x) and
			(m[2].y == m[1].z) and
			(m[3].y == m[1].w) and
			(m[3].z == m[2].w))
	{
		return true;
	}

	return false;
}

template <class Real>
Matrix4x4<Real>	Matrix4x4<Real>::Inverse() const
{
	Real A00 = m[1].z*m[2].w*m[3].y - m[1].w*m[2].z*m[3].y + m[1].w*m[2].y*m[3].z - m[1].y*m[2].w*m[3].z - m[1].z*m[2].y*m[3].w + m[1].y*m[2].z*m[3].w;
	Real A01 = m[0].w*m[2].z*m[3].y - m[0].z*m[2].w*m[3].y - m[0].w*m[2].y*m[3].z + m[0].y*m[2].w*m[3].z + m[0].z*m[2].y*m[3].w - m[0].y*m[2].z*m[3].w;
	Real A02 = m[0].z*m[1].w*m[3].y - m[0].w*m[1].z*m[3].y + m[0].w*m[1].y*m[3].z - m[0].y*m[1].w*m[3].z - m[0].z*m[1].y*m[3].w + m[0].y*m[1].z*m[3].w;
	Real A03 = m[0].w*m[1].z*m[2].y - m[0].z*m[1].w*m[2].y - m[0].w*m[1].y*m[2].z + m[0].y*m[1].w*m[2].z + m[0].z*m[1].y*m[2].w - m[0].y*m[1].z*m[2].w;
	Real A10 = m[1].w*m[2].z*m[3].x - m[1].z*m[2].w*m[3].x - m[1].w*m[2].x*m[3].z + m[1].x*m[2].w*m[3].z + m[1].z*m[2].x*m[3].w - m[1].x*m[2].z*m[3].w;
	Real A11 = m[0].z*m[2].w*m[3].x - m[0].w*m[2].z*m[3].x + m[0].w*m[2].x*m[3].z - m[0].x*m[2].w*m[3].z - m[0].z*m[2].x*m[3].w + m[0].x*m[2].z*m[3].w;
	Real A12 = m[0].w*m[1].z*m[3].x - m[0].z*m[1].w*m[3].x - m[0].w*m[1].x*m[3].z + m[0].x*m[1].w*m[3].z + m[0].z*m[1].x*m[3].w - m[0].x*m[1].z*m[3].w;
	Real A13 = m[0].z*m[1].w*m[2].x - m[0].w*m[1].z*m[2].x + m[0].w*m[1].x*m[2].z - m[0].x*m[1].w*m[2].z - m[0].z*m[1].x*m[2].w + m[0].x*m[1].z*m[2].w;
	Real A20 = m[1].y*m[2].w*m[3].x - m[1].w*m[2].y*m[3].x + m[1].w*m[2].x*m[3].y - m[1].x*m[2].w*m[3].y - m[1].y*m[2].x*m[3].w + m[1].x*m[2].y*m[3].w;
	Real A21 = m[0].w*m[2].y*m[3].x - m[0].y*m[2].w*m[3].x - m[0].w*m[2].x*m[3].y + m[0].x*m[2].w*m[3].y + m[0].y*m[2].x*m[3].w - m[0].x*m[2].y*m[3].w;
	Real A22 = m[0].y*m[1].w*m[3].x - m[0].w*m[1].y*m[3].x + m[0].w*m[1].x*m[3].y - m[0].x*m[1].w*m[3].y - m[0].y*m[1].x*m[3].w + m[0].x*m[1].y*m[3].w;
	Real A23 = m[0].w*m[1].y*m[2].x - m[0].y*m[1].w*m[2].x - m[0].w*m[1].x*m[2].y + m[0].x*m[1].w*m[2].y + m[0].y*m[1].x*m[2].w - m[0].x*m[1].y*m[2].w;
	Real A30 = m[1].z*m[2].y*m[3].x - m[1].y*m[2].z*m[3].x - m[1].z*m[2].x*m[3].y + m[1].x*m[2].z*m[3].y + m[1].y*m[2].x*m[3].z - m[1].x*m[2].y*m[3].z;
	Real A31 = m[0].y*m[2].z*m[3].x - m[0].z*m[2].y*m[3].x + m[0].z*m[2].x*m[3].y - m[0].x*m[2].z*m[3].y - m[0].y*m[2].x*m[3].z + m[0].x*m[2].y*m[3].z;
	Real A32 = m[0].z*m[1].y*m[3].x - m[0].y*m[1].z*m[3].x - m[0].z*m[1].x*m[3].y + m[0].x*m[1].z*m[3].y + m[0].y*m[1].x*m[3].z - m[0].x*m[1].y*m[3].z;
	Real A33 = m[0].y*m[1].z*m[2].x - m[0].z*m[1].y*m[2].x + m[0].z*m[1].x*m[2].y - m[0].x*m[1].z*m[2].y - m[0].y*m[1].x*m[2].z + m[0].x*m[1].y*m[2].z;

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
		m[0].w * m[1].z * m[2].y * m[3].x-m[0].z * m[1].w * m[2].y * m[3].x-m[0].w * m[1].y * m[2].z * m[3].x+m[0].y * m[1].w    * m[2].z * m[3].x+
		m[0].z * m[1].y * m[2].w * m[3].x-m[0].y * m[1].z * m[2].w * m[3].x-m[0].w * m[1].z * m[2].x * m[3].y+m[0].z * m[1].w    * m[2].x * m[3].y+
		m[0].w * m[1].x * m[2].z * m[3].y-m[0].x * m[1].w * m[2].z * m[3].y-m[0].z * m[1].x * m[2].w * m[3].y+m[0].x * m[1].z    * m[2].w * m[3].y+
		m[0].w * m[1].y * m[2].x * m[3].z-m[0].y * m[1].w * m[2].x * m[3].z-m[0].w * m[1].x * m[2].y * m[3].z+m[0].x * m[1].w    * m[2].y * m[3].z+
		m[0].y * m[1].x * m[2].w * m[3].z-m[0].x * m[1].y * m[2].w * m[3].z-m[0].z * m[1].y * m[2].x * m[3].w+m[0].y * m[1].z    * m[2].x * m[3].w+
		m[0].z * m[1].x * m[2].y * m[3].w-m[0].x * m[1].z * m[2].y * m[3].w-m[0].y * m[1].x * m[2].z * m[3].w+m[0].x * m[1].y    * m[2].z * m[3].w;
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
			0.0, 0.0, v.z, 0.0,
			0.0, 0.0, 0.0 , 0.0, 1.0) );
}


template <class Real>
Matrix4x4<Real> Matrix4x4<Real>::MakeProjectionMatrix(const Real& fov, const Real aspectRation, const Real& near, const Real& far) 
{


	Real c 					= static_cast<Real> (1.0 / std::tan(LAL::Math::degreesToRadians(fov) * 0.5) );
	Real aspectRationInv 	= static_cast<Real> (1.0 / aspectRation);
	Real fovy 				= static_cast<Real> (2.0 * std::atan(aspectRationInv / c));
	Real xScale 			= static_cast<Real> (1.0 / tanf(0.5 * fovy));
	Real yScale 			= static_cast<Real> (xScale / aspectRationInv);

	Matrix4x4<Real> lProjectionMatrix;

	lProjectionMatrix[0].x = xScale;
	lProjectionMatrix[0].y = static_cast< Real >(0);
	lProjectionMatrix[0].z = static_cast< Real >(0);
	lProjectionMatrix[0].w = static_cast< Real >(0);

	lProjectionMatrix[1].x = static_cast< Real >(0);
	lProjectionMatrix[1].y = yScale;
	lProjectionMatrix[1].z = static_cast< Real >(0);
	lProjectionMatrix[1].w = static_cast< Real >(0);

	lProjectionMatrix[2].x = static_cast< Real >(0);
	lProjectionMatrix[2].y = static_cast< Real >(0);
	lProjectionMatrix[2].z = static_cast< Real >((far + near) / (near - far));
	lProjectionMatrix[2].w = static_cast< Real >((2.0 * far * near) / (near - far));

	lProjectionMatrix[3].x = static_cast< Real >(0);
	lProjectionMatrix[3].y = static_cast< Real >(0);
	lProjectionMatrix[3].z = static_cast< Real >(-1);
	lProjectionMatrix[3].w = static_cast< Real >(0);


	return Matrix4x4<Real>(lProjectionMatrix);



};

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

	headDegrees = Math::degreesToRadians(headDegrees);
	pitchDegrees = Math::degreesToRadians(pitchDegrees);
	rollDegrees = Math::degreesToRadians(rollDegrees);

	Real cosH = std::cos(headDegrees);
	Real cosP = std::cos(pitchDegrees);
	Real cosR = std::cos(rollDegrees);
	Real sinH = std::sin(headDegrees);
	Real sinP = std::sin(pitchDegrees);
	Real sinR = std::sin(rollDegrees);

	m[0].x = cosR * cosH - sinR * sinP * sinH;
	m[0].y = sinR * cosH + cosR * sinP * sinH;
	m[0].z = -cosP * sinH;
	m[0].w = static_cast< Real >(0);

	m[1].x = -sinR * cosP;
	m[1].y = cosR * cosP;
	m[1].z = sinP;
	m[1].w = static_cast< Real >(0);

	m[2].x = cosR * sinH + sinR * sinP * cosH;
	m[2].y = sinR * sinH - cosR * sinP * cosH;
	m[2].z = cosP * cosH;
	m[2].w = static_cast< Real >(0);

	m[3].x = static_cast< Real >(0);
	m[3].y = static_cast< Real >(0);
	m[3].z = static_cast< Real >(0);
	m[3].w = static_cast< Real >(1);
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

	m[0].x = (x * x) * (1.0 - c) + c;
	m[0].y = (x * y) * (1.0 - c) + (z * s);
	m[0].z = (x * z) * (1.0 - c) - (y * s);
	m[0].w = static_cast< Real >(0);

	m[1].x = (y * x) * (1.0 - c) - (z * s);
	m[1].y = (y * y) * (1.0 - c) + c;
	m[1].z = (y * z) * (1.0 - c) + (x * s);
	m[1].w = 0.0;

	m[2].x = (z * x) * (1.0 - c) + (y * s);
	m[2].y = (z * y) * (1.0 - c) - (x * s);
	m[2].z = (z * z) * (1.0 - c) + c;
	m[2].w = static_cast< Real >(0);

	m[3].x = static_cast< Real >(0);
	m[3].y = static_cast< Real >(0);
	m[3].z = static_cast< Real >(0);
	m[3].w = static_cast< Real >(1);
}

template <class Real>
void Matrix4x4<Real>::ToHeadPitchRoll(Real &headDegrees, Real &pitchDegrees, Real &rollDegrees) const
{


	Real thetaX = std::asin(m[1].z);
	Real thetaY = static_cast< Real >(0);
	Real thetaZ = static_cast< Real >(0);

	if (thetaX < Math::HALF_PI)
	{
		if (thetaX > -Math::HALF_PI)
		{
			thetaZ = std::atan2(-m[1].x, m[1].y);
			thetaY = std::atan2(-m[0].z, m[2].z);
		}
		else
		{
			// Not a unique solution.
			thetaZ = -std::atan2(m[2].x, m[0].x);
			thetaY = static_cast< Real >(0);
		}
	}
	else
	{
		// Not a unique solution.
		thetaZ = std::atan2(m[2].x, m[0].x);
		thetaY = static_cast< Real >(0);
	}

	headDegrees  = Math::radiansToDegrees(thetaY);
	pitchDegrees = Math::radiansToDegrees(thetaX);
	rollDegrees  = Math::radiansToDegrees(thetaZ);
}


template <class Real>
Matrix4x4<Real> Matrix4x4<Real>::Identity ()
{
	return Matrix4x4<Real>(1.0,0.0,0.0,0.0,
			0.0,1.0,0.0,0.0,
			0.0,0.0,1.0,0.0,
			0.0,0.0,0.0,1.0);	
}

//template <class Real>
//const Real* Matrix4x4<Real>::ToRealPtr( void ) const 
//{
//	return m[0].ToFloatPtr();
//}

template <class Real>
Real* Matrix4x4<Real>::ToRealPtr( void ) 
{
	return m[0].ToRealPtr();
}

template <class Real>
Matrix4x4<Real>::~Matrix4x4(){};


#endif

