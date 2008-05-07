#ifndef VECTOR4_HPP_
#define VECTOR4_HPP_

#include <iostream>

#include <cassert>
#include <cmath>

#include "Vector3.hpp"

namespace CGL { 

	template <class Real>	class Vector4
	{

	private:

		union
		{

			struct
			{
				Real mX;
				Real mY;
				Real mZ;
				Real mW;
			};

			Real xyzw[4];

		};

	public:
		
		friend class Vector3<Real>;
		// VETOR  LINHA 

		Vector4 ();

		template < typename U >
		Vector4 (const U* u);

		Vector4 ( const Vector4<Real>& u);
		
		Vector4 ( const Vector3<Real>& u );
		
		Vector4 ( const Vector3<Real>& u, const Real& w);
		

		Vector4 ( const Real& pX, const Real& pY, const Real& pZ, const Real& pW );

		//Gets and Sets

		inline Real x() const;

		inline Real y() const;

		inline Real z() const;
		
		inline Real w() const;

		//Operator

		inline operator Real * ();

		inline Real  operator [] ( int i) const;

		inline Real& operator [] ( int i);

		// Assignment Opertators with Scalar
		
  	  	inline Vector4<Real>   		  operator+ ( ) const;
  	  	inline Vector4<Real>   		  operator- ( ) const;
  	  	
		inline const Vector4< Real >& operator+= ( const Real& factor );
		inline const Vector4< Real >& operator-= ( const Real& factor ); 
		inline const Vector4< Real >& operator*= ( const Real& factor ); 
		inline const Vector4< Real >& operator/= ( const Real& factor );

		template <class T>
		friend inline Vector4<T> operator* (const Vector4<T>& u, const T& factor); 	
		template <class T>
		friend inline Vector4<T> operator* (const T& factor, const Vector4<T>& u); 
		template <class T>
		friend inline Vector4<T> operator/ (const Vector4<T>& u, const T& factor); 	
		template <class T>
		inline friend Vector4<T> operator+ (const T& factor, const Vector4<T>& u);  
		template <class T>
		inline friend Vector4<T> operator+ (const Vector4<T>& u, const T& factor);
		template <class T>
		inline friend Vector4<T> operator- (const T& factor, const Vector4<T>& u);  
		template <class T>
		inline friend Vector4<T> operator- (const Vector4<T>& u, const T& factor); 
		
		
		
		// Assignment with Vector
		inline const Vector4<Real>& operator=  ( const Vector4<Real>& u );
		inline const Vector4<Real>& operator+= ( const Vector4<Real>& u );
		inline const Vector4<Real>& operator-= ( const Vector4<Real>& u ); 
		inline const Vector4<Real>& operator/= ( const Vector4<Real>& u ); 
		
		inline bool operator== ( const Vector4<Real>& u) const;
		inline bool operator!= ( const Vector4<Real>& u) const;
		
		inline Vector4<Real>  operator- ( const Vector4<Real>& u) const;
		inline Vector4<Real>  operator+ ( const Vector4<Real>& u) const;
		
		inline Real operator* ( const Vector4<Real>& u) const;

		template <class T>
		friend inline std::ostream& operator<< (std::ostream & s, const Vector4<T>& u);
		
		// AUXILIAR FUNCTIONS
		inline Real length ();
		inline void normalize ();
		inline Vector4<Real> norm ();
	

		~Vector4 ();


	};
#include "Vector4.inline.hpp"

} // END NAMESPACE


#endif

// CASOS DE TESTE


//// Teste operator+ e operator- with vectors
//CGL::Vector4<double> v1(1.0,1.0,1.0,0.0);
//CGL::Vector4<double> v2(-1.0,-1.0,-1.0,0.0);
//CGL::Vector4<double> v3(0.0,0.0,0.0,0.0);
//
//v3 = v1 + v2;
//std::cout << "#v1+v2# = 0,0,0 " << v3 << std::endl;
//v3 = v1 - v2;
//std::cout << "#v1+v2# = 2,2,2 " << v3 << std::endl;
//v3 = -v1 - v2;
//std::cout << "#-v1-v2# = 0,0,0 "<< v3 << std::endl;
//v3 = -v1 + v2;
//std::cout << "#-v1+v2# = -2,-2,-2 "<< v3 << std::endl;
//v3 = + v1 - v2;
//std::cout << "#+v1-v2# = 2,2,2 "<< v3 << std::endl;
//v3 = + v1 + v2;
//std::cout << "#+v1+v2 = 0,0,0 # "<< v3 << std::endl;
//
//// Teste operator+ e operator- with scalar
//
//v3 = v1 + 4.0;
//std::cout << "#v1+4# = 4,4,4 " << v3 << std::endl;
//v3 = 9.0 - v2;
//std::cout << "#9-v2# = 10,10,10 " << v3 << std::endl;
//v3 = -v1 / -8.0;
//std::cout << "#-v1-8# = 0.125,0.125,0.125 "<< v3 << std::endl;
//v3 = -v1 * 3.0;
//std::cout << "#-v1+3# = -3,-3,-3 "<< v3 << std::endl;
//
//
////Teste operator* with scalar
//v1 = CGL::Vector4<double>(1.0,1.0,1.0,0.0);
//v3 = CGL::Vector4<double>(0.0,0.0,0.0,0.0);
//
//v3 = 3.0 * v1;
//std::cout << "#3*v1# = 3,3,3 "<<v3 << std::endl;
//v3 = 3.0 * (-v1);
//std::cout << "#3*(-v1)# = -3,-3,-3 " << v3 << std::endl;
//v3 = 3.0 * (+v1);
//std::cout << "#3*(+v1)# = 3,3,3 "<< v3 << std::endl;
//v3 = (-v1) * 3.0;
//std::cout << "#(-v1)*3# = -3,-3,-3 " << v3 << std::endl;
//v3 = (+v1) * 3.0;
//std::cout << "#(+v1)*3# = 3,3,3 "<< v3 << std::endl;
//v3 = (+v1) * 0.0;
//std::cout << "#(+v1)*0.0# = 0,0,0"<< v3 << std::endl;
//v3 = (+v1) * v2[3];
//std::cout << "#(+v1)*0.0# = 0,0,0" << v3 << std::endl;
//
//CGL::Vector4<double> v4(1.0,1.0,1.0,1.0);
//CGL::Vector4<double> v5(-1.0,-1.0,-1.0,-1.0);
//CGL::Vector4<double> v6(2.0,2.0,2.0,4.0);
//double r = 1.0;
//
//v3 += v4;
//std::cout << "#v3+=v4# = 1,1,1 "<<v3 << std::endl;
//v3 = CGL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 += -3.0*v4;
//std::cout << "#v3+=-3*v4# = -3,-3,-3 "<<v3 << std::endl;
//v3 = CGL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 += -v5+v4;
//std::cout << "#v3+=-v5+v4# = 2,2,2 "<<v3 << std::endl;
//
//v3 -= v4;
//std::cout << "#v3-=v4# = -1,-1,-1 "<<v3 << std::endl;
//v3 = CGL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 -= -3.0*v4;
//std::cout << "#v3-=-3*v4# = 3,3,3 "<<v3 << std::endl;
//v3 = CGL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 -= -v5+v4;
//std::cout << "#v3-=-v5+v4# = -2,-2,-2 "<<v3 << std::endl;
//
//r = v4 * v6;
//std::cout << "#v4*v64# = 10 "<< r << std::endl;
//r = v4[1] * v6[3];
//std::cout << "#v4[1]*v6[3]# = 4 "<< r << std::endl;
//			
//v6 /= v4;
//std::cout << "#v6/=v4# = 2,2,2,4 "<<v6 << std::endl;
//v6 = CGL::Vector4<double>(2.0,2.0,2.0,4.0);
//v6 /= -3.0*v4;
//std::cout << "#v6/=-3*v4# = -0.666,-0.666,-0.666 "<<v6 << std::endl;
//v6 = CGL::Vector4<double>(2.0,2.0,2.0,4.0);
//v6 /= -v5+v4;
//std::cout << "#v6/=-v5+v4# = 1,1,1,2 "<<v6 << std::endl;
//	
//std::vector<double> vec(static_cast< double * >(v4),static_cast< double * >(v4)+4);
//std::ostream_iterator<double> output( std::cout, " ");
//std::cout << "vec" << std::endl;
//
//std::copy(vec.begin(),vec.end(),output);
//
//solucão para não ter warnning no retorno de uma referencia
//inline Vector3<T>&  operator- ( const Vector3<T>& u) const
//{
//	Vector3<T> w;
//	 	
//	w.x = this->x - u.x;
//	w.y = this->y - u.y;
//	w.z = this->z - u.z;
//		
//	Vector3<T>& h = w;
//	
//	return ( h );
//};

