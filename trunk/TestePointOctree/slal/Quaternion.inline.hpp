#ifndef LAL_QUATERNION_INLINE_HPP_
#define LAL_QUATERNION_INLINE_HPP_


#include <cmath>
#include "Quaternion.hpp"


template <class Real>
Quaternion<Real>::Quaternion()
{
    mW = static_cast<Real> (1.0);
    mX = static_cast<Real> (0.0);
    mY = static_cast<Real> (0.0);
    mZ = static_cast<Real> (0.0);
};
						
template<class Real>
Quaternion<Real>::Quaternion ( const Quaternion<Real>& pQuaternion)
:
	mW(pQuaternion.mW),
	mX(pQuaternion.mX),
	mY(pQuaternion.mY),
	mZ(pQuaternion.mZ)
{};

template<class Real>
Quaternion<Real>::Quaternion ( const Real& pW, const Real& pX, const Real& pY, const Real& pZ ) 
:
	mW(pW),
	mX(pX),
	mY(pY),
	mZ(pZ)
	
{};

template<class Real>
Quaternion<Real>::Quaternion ( const Real& pAngle ,const Vector3<Real>& pAxis)
{
    const Real lenght = axis.lenght();
    if (lenght < 1E-8)
    {	// Null rotation
    	wxyz[0] = 1.0; wxyz[1] = 0.0;      wxyz[2] = 0.0;      wxyz[3] = 0.0;      
    }
    else
    {
    	const Real sin_half_angle = sin(pAngle * 0.5);
    	
    	wxyz[0] = cos(pAngle * 0.5);
    	wxyz[1] = sin_half_angle*pAxis[0]/lenght;
    	wxyz[2] = sin_half_angle*pAxis[1]/lenght;
    	wxyz[3] = sin_half_angle*pAxis[2]/lenght;
    	
    }
};

//Gets and Sets
template<class Real>
inline Real Quaternion<Real>::x() const
{
	return ( this->mX );
};

template<class Real>
inline Real Quaternion<Real>::y() const
{
	return ( this->mY );
};

template<class Real>
inline Real Quaternion<Real>::z() const
{
	return ( this->mZ );
};

template<class Real>
inline Real Quaternion<Real>::w() const
{
	return ( this->mW );
};

//Operator

template<class Real>
inline Quaternion<Real>::operator Real * ()
{
	return  wxyz;
}

template<class Real>
inline Real Quaternion<Real>::operator [] ( int i) const
{
	if ( i > 3)
	{
		std::cerr << "[ERROR] Quaternion operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}

	return (wxyz[i]);

};

template<class Real>
inline Real& Quaternion<Real>::operator [] ( int i) 
{
	if ( i > 3)
	{
		std::cerr << "[ERROR] Quaternion operator[]"        << std::endl
		<< "        Out of the vector size. " << std::endl
		<< "        Accepts, 0 , 1 , 2 only." << std::endl;
		exit(1);
	}


	return (wxyz[i]);

};
template<class Real>
inline void Quaternion<Real>::setAngle (const Real& pAngle)
{
	mW = pAngle;
}

template<class Real>
inline void Quaternion<Real>::setAxis  (const Vector3<Real>& pAxis)
{
	mX = pAxis.mX;
	mY = pAxis.mY;
	mZ = pAxis.mZ;
};

template<class Real>
inline void Quaternion<Real>::setAxis  (const Real& pX, const Real& pY, const Real& pZ)
{
	
	mX = pX;
	mY = pY;
	mZ = pZ;

};
	
template<class Real>
inline Vector3<Real> Quaternion<Real>::axis () const
{
	return ( Vector3<Real> (mX,mY,mZ) );
};

template<class Real>
inline Real Quaternion<Real>::angle() const
{
	return ( mW ); 
}


template <class Real>
inline Quaternion<Real>& Quaternion<Real>::operator= (const Quaternion<Real>& pQuaternion)
{
	mW = pQuaternion.mW;
    mX = pQuaternion.mX;
    mY = pQuaternion.mY;
    mZ = pQuaternion.mZ;
    return *this;
}

template <class Real>
inline Quaternion<Real>& Quaternion<Real>::operator *= (const Real& pFactor)
{
	mW *= pFactor;
	mX *= pFactor;
	mY *= pFactor; 
	mZ *= pFactor;
	
	return *this;
}

//------------------------------------------------------------------------------
//
template<class Real>
inline Quaternion<Real>& Quaternion<Real>::operator /= (const Real& pFactor)
{
	mW /= pFactor;
	mX /= pFactor; 
	mY /= pFactor; 
	mZ /= pFactor; 
		
	return *this;
}

template <class Real>
inline Quaternion<Real> operator* (const Quaternion<Real>& a, const Quaternion<Real>& b)
{
  return Quaternion<Real>( a.mW*b.mW - a.mX*b.mX - a.mY*b.mY - a.mZ*b.mZ,
						   a.mW*b.mX + a.mX*b.mW + a.mY*b.mZ - a.mZ*b.mY,
						   a.mW*b.mY - a.mX*b.mZ + a.mY*b.mW + a.mZ*b.mX,
				           a.mW*b.mZ + a.mX*b.mY - a.mY*b.mX + a.mZ*b.mW  );
  		  
//  res.w = w*r.w - x*r.x - y*r.y - z*r.z;
//   res.x = w*r.x + x*r.w + y*r.z - z*r.y;
//   res.y = w*r.y - x*r.z + y*r.w + z*r.x;
//   res.z = w*r.z + x*r.y - y*r.x + z*r.w;
	
}

template <class Real>
inline Vector3<Real> Quaternion<Real>::rotate(const Vector3<Real>& v) const
{
    Quaternion<Real> lQuaternio(1.0,v.x, v.y, v.z);
    
    lQuaternio = *this*lQuaternio*(~(*this));
    
    return Vector3<Real> (lQuaternio.mX, lQuaternio.mY, lQuaternio.mZ);
}


template <class Real>
inline void Quaternion<Real>::to3x3Matrix (Matrix3x3<Real>& pRotMatrix) const
{
    Real x  = static_cast<Real> (2.0)*mX;
    Real y  = static_cast<Real> (2.0)*mY;
    Real z  = static_cast<Real> (2.0)*mZ;
    Real wx = x*mW;
    Real wy = y*mW;
    Real wz = z*mW;
    Real xx = x*mX;
    Real xy = y*mX;
    Real xz = z*mX;
    Real yy = y*mY;
    Real yz = z*mY;
    Real zz = z*mZ;

    pRotMatrix(0,0) = static_cast<Real>(1.0) -(yy+zz);
    pRotMatrix(0,1) = xy-wz;
    pRotMatrix(0,2) = xz+wy;
    pRotMatrix(1,0) = xy+wz;
    pRotMatrix(1,1) = static_cast<Real>(1.0) -(xx+zz);
    pRotMatrix(1,2) = yz-wx;
    pRotMatrix(2,0) = xz-wy;
    pRotMatrix(2,1) = yz+wx;
    pRotMatrix(2,2) = static_cast<Real> (1.0) - (xx+yy);
}

template <class Real>
inline void Quaternion<Real>::to4x4Matrix(Matrix4x4<Real> &pRotMatrix) const 
{
    Real x  = static_cast<Real> (2.0)*mX;
    Real y  = static_cast<Real> (2.0)*mY;
    Real z  = static_cast<Real> (2.0)*mZ;
    Real wx = x*mW;
    Real wy = y*mW;
    Real wz = z*mW;
    Real xx = x*mX;
    Real xy = y*mX;
    Real xz = z*mX;
    Real yy = y*mY;
    Real yz = z*mY;
    Real zz = z*mZ;

    pRotMatrix(0,0) = static_cast<Real>(1.0) -(yy+zz);
    pRotMatrix(0,1) = xy-wz;
    pRotMatrix(0,2) = xz+wy;
    pRotMatrix(1,0) = xy+wz;
    pRotMatrix(1,1) = static_cast<Real>(1.0) -(xx+zz);
    pRotMatrix(1,2) = yz-wx;
    pRotMatrix(2,0) = xz-wy;
    pRotMatrix(2,1) = yz+wx;
    pRotMatrix(2,2) = static_cast<Real> (1.0) - (xx+yy);
    pRotMatrix(3,0) = pRotMatrix(3,1) = pRotMatrix(3,2) = pRotMatrix(0,3) = pRotMatrix(1,3) = pRotMatrix(2,3) = static_cast<Real> (0.0);
    pRotMatrix(3,3) = static_cast<Real>(1.0);
  }

template <class Real>
inline Matrix4x4<Real> Quaternion<Real>::to4x4Matrix() const 
{
	
	Matrix4x4<Real> pRotMatrix;
	
    Real x  = static_cast<Real> (2.0)*mX;
    Real y  = static_cast<Real> (2.0)*mY;
    Real z  = static_cast<Real> (2.0)*mZ;
    Real wx = x*mW;
    Real wy = y*mW;
    Real wz = z*mW;
    Real xx = x*mX;
    Real xy = y*mX;
    Real xz = z*mX;
    Real yy = y*mY;
    Real yz = z*mY;
    Real zz = z*mZ;

    pRotMatrix(0,0) = static_cast<Real>(1.0) -(yy+zz);
    pRotMatrix(0,1) = xy-wz;
    pRotMatrix(0,2) = xz+wy;
    pRotMatrix(1,0) = xy+wz;
    pRotMatrix(1,1) = static_cast<Real>(1.0) -(xx+zz);
    pRotMatrix(1,2) = yz-wx;
    pRotMatrix(2,0) = xz-wy;
    pRotMatrix(2,1) = yz+wx;
    pRotMatrix(2,2) = static_cast<Real> (1.0) - (xx+yy);
    pRotMatrix(3,0) = pRotMatrix(3,1) = pRotMatrix(3,2) = pRotMatrix(0,3) = pRotMatrix(1,3) = pRotMatrix(2,3) = static_cast<Real> (0.0);
    pRotMatrix(3,3) = static_cast<Real>(1.0);
    
    return (pRotMatrix);
  }

template <class Real>
inline void Quaternion<Real>::to4x4Matrix( Real * pRotMatrix) const {
	
    Real x  = static_cast<Real> (2.0)*mX;
    Real y  = static_cast<Real> (2.0)*mY;
    Real z  = static_cast<Real> (2.0)*mZ;
    Real wx = x*mW;
    Real wy = y*mW;
    Real wz = z*mW;
    Real xx = x*mX;
    Real xy = y*mX;
    Real xz = z*mX;
    Real yy = y*mY;
    Real yz = z*mY;
    Real zz = z*mZ;
    
    pRotMatrix[0] = static_cast<Real>(1.0) -(yy+zz);;
    pRotMatrix[1] = xy+wz;
    pRotMatrix[2] = xz-wy;
    pRotMatrix[4] = xy-wz;
    pRotMatrix[5] = static_cast<Real>(1.0) -(xx+zz);
    pRotMatrix[6] = yz+wx;
    pRotMatrix[8] = xz+wy;
    pRotMatrix[9] = yz-wx;
    pRotMatrix[10] = static_cast<Real> (1.0) - (xx+yy);
    pRotMatrix[12] = pRotMatrix[13] = pRotMatrix[14] = pRotMatrix[3] = pRotMatrix[7] = pRotMatrix[11] =  static_cast<Real> (0.0);
    pRotMatrix[15] = static_cast<Real> (1.0);
 }




//----------------------------------------------------------------------------
template <class Real>
inline void  Quaternion<Real>::fromRotationMatrix ( const Matrix4x4<Real>& pRotMatrix )
{
	  const Real onePlusTrace = static_cast<Real> (1.0)  + pRotMatrix[0][0] + pRotMatrix[1][1] + pRotMatrix[2][2];

	  if (onePlusTrace > 1E-5)
	    {
	      // Direct computation
	      const Real s = sqrt(onePlusTrace) * static_cast<Real> (2.0) ;
	      mX = (pRotMatrix[2][1] - pRotMatrix[1][2]) / s;
	      mY = (pRotMatrix[0][2] - pRotMatrix[2][0]) / s;
	      mZ = (pRotMatrix[1][0] - pRotMatrix[0][1]) / s;
	      mW = static_cast<Real> (0.25)  * s;
	    }
	  else
	    {
	      // Computation depends on major diagonal term
	      if ((pRotMatrix[0][0] > pRotMatrix[1][1])&(pRotMatrix[0][0] > pRotMatrix[2][2]))
		{ 
		  const Real s = sqrt(1.0 + pRotMatrix[0][0] - pRotMatrix[1][1] - pRotMatrix[2][2]) * static_cast<Real> (2.0) ; 
		  mX = static_cast<Real> (0.25) * s;
		  mY = (pRotMatrix[0][1] + pRotMatrix[1][0]) / s; 
		  mZ = (pRotMatrix[0][2] + pRotMatrix[2][0]) / s; 
		  mW = (pRotMatrix[1][2] - pRotMatrix[2][1]) / s;
		}
	      else
		if (pRotMatrix[1][1] > pRotMatrix[2][2])
		  { 
		    const Real s = sqrt(1.0 + pRotMatrix[1][1] - pRotMatrix[0][0] - pRotMatrix[2][2]) * static_cast<Real> (2.0) ; 
		    mX = (pRotMatrix[0][1] + pRotMatrix[1][0]) / s; 
		    mY = static_cast<Real> (0.25) * s;
		    mZ = (pRotMatrix[1][2] + pRotMatrix[2][1]) / s; 
		    mW = (pRotMatrix[0][2] - pRotMatrix[2][0]) / s;
		  }
		else
		  { 
		    const Real s = sqrt(1.0 + pRotMatrix[2][2] - pRotMatrix[0][0] - pRotMatrix[1][1]) * static_cast<Real> (2.0) ; 
		    mX = (pRotMatrix[0][2] + pRotMatrix[2][0]) / s; 
		    mY = (pRotMatrix[1][2] + pRotMatrix[2][1]) / s; 
		    mZ = static_cast<Real> (0.25) * s;
		    mW = (pRotMatrix[0][1] - pRotMatrix[1][0]) / s;
		  }
	    }
	  
 this->normalize();

}

template <class Real>
inline void  Quaternion<Real>::fromAxisAngle(const Vector3<Real> &axis, const Real& degrees)
{
    Real halfTheta = static_cast<Real> (Math::degreesToRadians(degrees) * 0.5f);
    
    Real s = std::sin(halfTheta);
    
    mW = std::cos(halfTheta);
    mX = axis.x * s;
    mY = axis.y * s;
    mZ = axis.z * s;
}
template <class Real>
inline void  Quaternion<Real>::fromHeadPitchRoll(Real headDegrees, Real pitchDegrees, Real rollDegrees)
{
    Matrix4x4<Real> m;
    m.fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
    fromRotationMatrix(m);
}

template <class Real>
inline void  Quaternion<Real>::toAxisAngle( Vector3<Real>& axis, Real& degrees ) const
{
    // Converts this quaternion to an axis and an angle.

    Real sinHalfThetaSq = static_cast< Real >(1) - mW * mW;

    // Guard against numerical imprecision and identity quaternions.
    if (sinHalfThetaSq <= static_cast< Real >(0))
    {
        axis[0] = static_cast< Real >(1), axis[1] = axis[2] = static_cast< Real >(0);
        degrees = static_cast< Real >(0);
    }
    else
    {
        Real invSinHalfTheta = static_cast< Real >(1) / std::sqrt(sinHalfThetaSq);

        axis[0] = mX * invSinHalfTheta;
        axis[1] = mY * invSinHalfTheta;	
        axis[2] = mZ * invSinHalfTheta;
        degrees = Math::radiansToDegrees(2.0f * std::acos(w));
    }
}


// Reference: Stan Melax, Game Programming Gems
template <class Real>
inline void  Quaternion<Real>::toRotationArc(Vector3<Real> &u, Vector3<Real> &v) 
{

	u.normalize();
	v.normalize();
	Vector3<Real> w = u ^ v;

	Real d = u*v;
	Real s = std::sqrt((1+d)*2);

	mW = s * static_cast<Real> (0.5);  
	mX = w.x / s;
	mY = w.y / s;
	mZ = w.z / s; 

}


template <class Real>
inline  Vector3<Real> operator*(const Quaternion<Real>& pQuaternion, const Vector3<Real>& v)
{
  return pQuaternion.Rotate(v);
}

template < class Real>
inline Quaternion<Real>& Quaternion<Real>::operator*= (const Quaternion<Real>& pQuaternion)
{
  *this = (*this)*pQuaternion;
  return *this;
}

template <class Real>
inline Quaternion<Real> Quaternion<Real>::operator* (const Real& pFactor) const
{
	
	return Quaternion<Real>(mW * pFactor, mX * pFactor, mY * pFactor, mZ * pFactor);
}

//------------------------------------------------------------------------------
//
template <class Real>
inline Quaternion<Real> Quaternion<Real>::operator/ (const Real& pFactor) const
{

	return Quaternion<Real>(mW / pFactor, mX / pFactor, mY / pFactor, mZ / pFactor);

}

template <class Real>
inline Quaternion<Real>  Quaternion<Real>::operator- ( ) const
{
	return Quaternion<Real> ( -mW , -mX, -mY, -mZ );

}
// Conjugate
template <class Real>
inline Quaternion<Real> Quaternion<Real>::operator~ () const
{
	return Quaternion<Real> (mW , -mX, -mY, -mZ );
}

template <class Real>
inline Real Quaternion<Real>::length () const
{
    return std::sqrt(  mX*mX +  mY*mY +  mZ*mZ + mW*mW );
}

template <class Real>
inline Real Quaternion<Real>::norm () const
{
    return   ( mX*mX + mY*mY +  mZ*mZ + mW*mW ) ;
}


template <class Real>
inline void Quaternion<Real>::normalize ()
{
    Real lLength = sqrt(  mX*mX +  mY*mY +  mZ*mZ + mW*mW );

    if (lLength > 1e-06f)
    {
        Real lInvLength =  static_cast<Real> (1.0) / lLength;
        
        mW *= lInvLength;
        mX *= lInvLength;
        mY *= lInvLength;
        mZ *= lInvLength;
    }
    else
    {
        mW = static_cast<Real> (1.0);
        mX = static_cast<Real> (0.0);
        mY = static_cast<Real> (0.0);
        mZ = static_cast<Real> (0.0);
    }

}

template <class Real>
inline void Quaternion<Real>::identity ()
{
	this->mW = static_cast<Real> (1);
	this->mX = static_cast<Real> (0);
	this->mY = static_cast<Real> (0);
	this->mZ = static_cast<Real> (0);

}


template <class Real>
inline Quaternion<Real> Quaternion<Real>::normalized ()
{
    Real lLength = sqrt(  mX*mX +  mY*mY +  mZ*mZ + mW*mW );

    if (lLength > 1e-06f)
    {
        Real lInvLength =  static_cast<Real> (1.0) / lLength;
        
        return Quaternion<Real> (mW * lInvLength, mX * lInvLength, mY * lInvLength, mZ * lInvLength );
            
    }
    else
    {
    	return Quaternion<Real> ( 1.0, 0.0, 0.0, 0.0); 
    }   

}



template <class Real>
inline Quaternion<Real> Quaternion<Real>::inverse () const
{
	Real lNorm =   mX*mX +  mY*mY +  mZ*mZ + mW*mW ;
	
    if (lNorm > static_cast<Real> (0.0))
    {
        Real lInvNorm = static_cast<Real> (1.0) / lNorm;
        
        return Quaternion<Real> (mW * lInvNorm, -mX * lInvNorm, -mY * lInvNorm, -mZ * lInvNorm );        
    }
    else
    {	// Return as a flag error !!
    	return Quaternion<Real> (1.0, 0.0, 0.0, 0.0);    
    }

}

template <class Real>
inline void  Quaternion<Real>::invert () 
{
	Real lNorm =   mX*mX +  mY*mY +  mZ*mZ + mW*mW ;
	
    if (lNorm > static_cast<Real> (0.0))
    {
        Real lInvNorm = static_cast<Real> (1.0) / lNorm;
        
        mW *= lInvNorm;
       -mX *= lInvNorm; 
       -mY *= lInvNorm; 
       -mZ *= lInvNorm;
        
    }
    else
    {
        mW = static_cast<Real> (1.0);
        mX = static_cast<Real> (0.0);
        mY = static_cast<Real> (0.0);
        mZ = static_cast<Real> (0.0);   
    }

}

template <class Real>
inline Real Quaternion<Real>::dot (const Quaternion<Real>& pQuaternion) const
{
    Real lScalar = static_cast<Real> (0.0);
        
    lScalar +=  mW * pQuaternion.mW +
    			mX * pQuaternion.mX +
    			mY * pQuaternion.mY +
    			mZ * pQuaternion.mZ ;
    
    return lScalar;
}
//--

template<class Real>
inline std::ostream& operator<< (std::ostream & s, const Quaternion<Real>& pQuaternion)
{
	s << " Quaternion " << " w = " << pQuaternion.w() << " x = " << pQuaternion.x() << " ,y = " << pQuaternion.y() << " ,z = " << pQuaternion.z() << std::endl;

	return s;
};

template <class Real>
Quaternion<Real>::~Quaternion()
{}
	

#endif /*QUATERNION_INLINE_HPP_*/
