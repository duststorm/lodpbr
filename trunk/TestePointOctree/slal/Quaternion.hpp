#ifndef LAL_QUATERNION_HPP_
#define LAL_QUATERNION_HPP_

#include "Vector3.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"
#include "Math.hpp"

namespace LAL{

/*!
*@class Quaternion.
*@brief Class that represent Quaternion.
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 23 Abril-2008.
*@todo OpenGL interface and a C style array.
*@todo Constructor FromRotMatrix, Get toRotMatrix
*@todo Ver as Classes friends e otimizar   
*/   


	template <class Real> class Quaternion
	{
		

	public:
		
		friend class Vector3<Real>;
		friend class Matrix3x3<Real>;
		friend class Matrix4x4<Real>;
		
	   	 /*! @name  Defining a Quaternion */
	    //@{
		/*! Default constructor. Value is set to (1,0,0,0). */
		Quaternion();
		Quaternion( const Quaternion<Real>& quat );
		Quaternion( const Real& w, const Real& x, const Real& y, const Real& z );
		Quaternion( const Real& pAngle, const Vector3<Real>& pAxis );
		
		Quaternion<Real>& 		operator=(const Quaternion<Real>& quat );
  	  	void 					SetAngle( const Real& angle ); 
  	  	void 					SetAxis( const Vector3<Real>& axis );
  	  	void 					SetAxis( const Real& x, const Real& y, const Real& z );
		
		/*! @name Accessing the value */
		//@{
 
 	  	
  	  	Vector3<Real> 			Axis () const;
  	  	Real 					Angle() const; 

		Real  					operator[]( int index ) const;
		Real& 					operator[]( int index );
		
		//@}
		
	    // arithmetic updates
		
  	  	/*! @name Algebraic computations */
  	  	// @{
		Quaternion<Real>& 		operator*=( const Quaternion<Real>& quat );
	    Quaternion<Real>& 		operator*=( const Real& factor );
	    Quaternion<Real>& 		operator/=( const Real& factor );
	    
		
	    // arithmetic operations
		template < class T>
	    friend Quaternion<T> 	operator*( const Quaternion<T>& a, const Quaternion<T>& b ) ;
		
		template < class T>
	    friend Vector3<T>    	operator*( const Quaternion<T>& quat, const Vector3<T>& vector ) ;
		
	    Quaternion<Real> 		operator*( const Real& factor) const;
	    Quaternion<Real> 		operator/( const Real& factor) const;
		
		//Negates all the coefficients of the Quaternion.
		Quaternion<Real> 		operator-() const;
 	    
	    // functions of a quaternion
	    //Inverses the Quaternion (same rotation angle(), but negated axis()).
	    Quaternion<Real> 		operator~( ) const;
	    //@}
	    
	   	/*!@name Functions */
	    //@{
	    Real 			    	Length( void ) const;  
	    Quaternion<Real> 		Inverse( void ) const;
	    void 					Invert( void );
	    Real					Norm( void ) const;
	    void	 				Normalize( void );
	    Quaternion<Real>		Normalized( void );
	    Vector3<Real>        	Rotate( const Vector3<Real>& v ) const;
		Real				    Dot( const Quaternion<Real>& quat ) const;
	
		void 					Identity();
		void 					To3x3Matrix( Matrix3x3<Real>& rotationMatrix ) const;
		void 					To4x4Matrix( Matrix4x4<Real>& rotationMatrix ) const;
		void 					To4x4Matrix( Real * rotMatrix) const;
		Matrix4x4<Real>  		To4x4Matrix() const; 
		
		void 					FromRotationMatrix( const Matrix4x4<Real>& rotationMatrix );
		void 					FromAxisAngle( const Vector3<Real>& axis, const Real& degrees );
		void 					FromHeadPitchRoll( const Real& headDegrees, const Real& pitchDegrees, const Real& rollDegrees);
		void 					FromMatrix( const Matrix4x4<Real>& m );
		
		void 					ToAxisAngle( Vector3<Real>& axis, Real& degrees ) const;
		void 					ToHeadPitchRoll( const Real& headDegrees, const Real& pitchDegrees, const Real& rollDegrees ) const;
		void 					ToRotationArc( Vector3<Real> &u, Vector3<Real> &v );
		//@}

		/*! @name Output stream */
		//@{
		/*! Output stream operator. Enables debugging code like:
    	  \code

    	  std::cout << " Quaternion " << " w = " << q.w() << " x = " << q.x() << " ,y = " << q.y() << " ,z = " << z() << std::endl;
    	  \endcode */
		template <class T>
		friend std::ostream& 	operator<< ( std::ostream & s, const Quaternion<Real>& quat );
		//@}
		virtual ~Quaternion();
		
	public:
		
		Real w;
		Real x;
		Real y;
		Real z;
		
	};
	
#include "Quaternion.inline.hpp"
	
} /* LAL :: NAMESPACE */

#endif /*QUATERNION_HPP_*/
