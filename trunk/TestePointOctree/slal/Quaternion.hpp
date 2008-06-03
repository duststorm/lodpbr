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
		Quaternion(const Quaternion<Real>& pQuaternion);
		Quaternion(const Real& pW, const Real& pX, const Real& pY, const Real& pZ);
		Quaternion(const Real& pAngle, const Vector3<Real>& pAxis );
		inline Quaternion<Real>& operator=  (const Quaternion<Real>& pQuaternion);
  	  	inline void setAngle (const Real& pAngle); 
  	  	inline void setAxis  (const Vector3<Real>& pAxis);
  	  	inline void setAxis  (const Real& pX, const Real& pY, const Real& pZ);
		
		/*! @name Accessing the value */
		//@{
		  			
  	  	inline Real x() const;
  	  	inline Real y() const;
  	  	inline Real z() const;
  	  	inline Real w() const; 
 	  	
  	  	inline Vector3<Real> 	axis () const;
  	  	inline Real 			angle() const; 

		inline Real  operator [] ( int i) const;

		inline Real& operator [] ( int i);
		
		inline operator const Real* () const;
		
		inline operator Real* ();
		
		//@}
		
	    // arithmetic updates
		
  	  	/*! @name Algebraic computations */
  	  	// @{
		inline Quaternion<Real>& 			operator*= (const Quaternion<Real>& pQuaternion);
	    inline Quaternion<Real>& 			operator*= (const Real& pFactor);
	    inline Quaternion<Real>& 			operator/= (const Real& pFactor);
	    
		
	    // arithmetic operations
		template < class T>
	    inline friend Quaternion<T> operator*  (const Quaternion<T>& a, const Quaternion<T>& b ) ;
		
		template < class T>
	    inline friend Vector3<T>    operator*  (const Quaternion<T>& pQuaternion, const Vector3<T>& pVector ) ;
		
	    inline Quaternion<Real> operator* (const Real& pFactor) const;
	    inline Quaternion<Real> operator/ (const Real& pFactor) const;
		
		//Negates all the coefficients of the Quaternion.
		inline Quaternion<Real> 	operator-  () const;
 	    
	    // functions of a quaternion
	    //Inverses the Quaternion (same rotation angle(), but negated axis()).
	    inline Quaternion<Real> 	operator~  ( ) const;
	    //@}
	    
	   	/*!@name Functions */
	    //@{
	    inline Real 			    Length() const;  
	    inline Quaternion<Real> 	Inverse () const;
	    inline void 				Invert  ();
	    inline Real					Norm() const;
	    inline void	 				Normalize   ();
	    inline Quaternion<Real>		Normalized  ();
	    inline Vector3<Real>        Rotate   ( const Vector3<Real>& v) const;
		inline Real				    Dot      ( const Quaternion<Real>& pQuaternion) const;
	
		inline void Identity ();
		inline void To3x3Matrix (Matrix3x3<Real>& pRotMatrix) const;
		inline void To4x4Matrix (Matrix4x4<Real>& pRotMatrix) const;
		inline void To4x4Matrix( Real * pRotMatrix) const;
		inline Matrix4x4<Real>  To4x4Matrix() const; 
		
		inline void FromRotationMatrix 	(const Matrix4x4<Real>& pRotMatrix );
		inline void FromAxisAngle		(const Vector3<Real>& axis, const Real& degrees);
		inline void FromHeadPitchRoll	( Real headDegrees, Real pitchDegrees, Real rollDegrees);
		inline void FromMatrix			(const Matrix4x4<Real>& m);
		
		inline void ToAxisAngle			(Vector3<Real>& axis, Real& degrees) const;
		inline void ToHeadPitchRoll		(const Real& headDegrees, const Real& pitchDegrees, const Real& rollDegrees) const;
		inline void ToRotationArc		(Vector3<Real> &u, Vector3<Real> &v);
		//@}

		/*! @name Output stream */
		//@{
		/*! Output stream operator. Enables debugging code like:
    	  \code

    	  std::cout << " Quaternion " << " w = " << q.w() << " x = " << q.x() << " ,y = " << q.y() << " ,z = " << z() << std::endl;
    	  \endcode */
		template <class T>
		friend inline std::ostream& operator<< (std::ostream & s, const Quaternion<Real>& pQuaternion);
		//@}
		virtual ~Quaternion();
		
	private:
		
		union
		{
			struct
			{
				Real mW;
				Real mX;
				Real mY;
				Real mZ;
			};

			Real wxyz[4];
		};
		
	};
	
#include "Quaternion.inline.hpp"
	
} /* LAL :: NAMESPACE */

#endif /*QUATERNION_HPP_*/
