#ifndef VECTOR4_HPP_
#define VECTOR4_HPP_

#include <iostream>

#include <cassert>
#include <cmath>

#include "Vector3.hpp"

namespace LAL { 

	template <class Real>	class Vector4
	{

	public:

		Real x;
		Real y;
		Real z;
		Real w;


	public:
		
		friend class Vector3<Real>;
		// VETOR  LINHA 

		Vector4();
		template < class T >
		Vector4 (const T* v);
		Vector4( const Vector4<Real>& vector);
		Vector4( const Vector3<Real>& vector );
		Vector4( const Vector3<Real>& vector, const Real& w);
		Vector4( const Real& x, const Real& y, const Real& z, const Real& w );


		//Operator

		Real  					operator[]( int index ) const;

		Real& 					operator[]( int index );

		// Assignment Opertators with Scalar
		
  	  	Vector4<Real>   		operator+ ( ) const;
  	  	Vector4<Real>   		operator- ( ) const;
  	  	
	    Vector4< Real >& 		operator+=( const Real& factor );
		Vector4< Real >& 		operator-=( const Real& factor ); 
		Vector4< Real >& 		operator*=( const Real& factor ); 
		Vector4< Real >& 		operator/=( const Real& factor );

		template <class T>
		friend Vector4<T> 		operator*( const Vector4<T>& v, const T& factor ); 	
		template <class T>
		friend Vector4<T> 		operator*( const T& factor, const Vector4<T>& v ); 
		template <class T>
		friend Vector4<T> 		operator/( const Vector4<T>& v, const T& factor ); 	
		template <class T>
		friend Vector4<T> 		operator+( const T& factor, const Vector4<T>& v );  
		template <class T>
		friend Vector4<T> 		operator+( const Vector4<T>& v, const T& factor );
		template <class T>
		friend Vector4<T> 		operator-( const T& factor, const Vector4<T>& v );  
		template <class T>
		friend Vector4<T> 		operator-( const Vector4<T>& v, const T& factor ); 
		
		
		
		// Assignment with Vector
		Vector4<Real>& 			operator= ( const Vector4<Real>& v );
		Vector4<Real>& 			operator+=( const Vector4<Real>& v );
		Vector4<Real>& 			operator-=( const Vector4<Real>& v ); 
		Vector4<Real>& 			operator/=( const Vector4<Real>& v ); 
		
		bool 					operator==( const Vector4<Real>& v) const;
		bool 					operator!=( const Vector4<Real>& v) const;
		
		Vector4<Real>  			operator-( const Vector4<Real>& v) const;
		Vector4<Real>  			operator+( const Vector4<Real>& v) const;
		
		Real 					operator*( const Vector4<Real>& v) const;

		template <class T>
		friend std::ostream& 	operator<<(std::ostream & s, const Vector4<T>& v);
		
		// AUXILIAR FUNCTIONS
		Real 					Length( void );
		Real					LengthSqr( void );
		void 					Normalize( void );
		Vector4<Real> 			Norm( void );
		
		const Real* 			ToRealPtr( void ) const ;
		Real*	 				ToRealPtr( void ) ;

		~Vector4 ();


	};
#include "Vector4.inline.hpp"

} /* LAL :: NAMESPACE */


#endif

// CASOS DE TESTE


//// Teste operator+ e operator- with vectors
//LAL::Vector4<double> v1(1.0,1.0,1.0,0.0);
//LAL::Vector4<double> v2(-1.0,-1.0,-1.0,0.0);
//LAL::Vector4<double> v3(0.0,0.0,0.0,0.0);
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
//v1 = LAL::Vector4<double>(1.0,1.0,1.0,0.0);
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
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
//LAL::Vector4<double> v4(1.0,1.0,1.0,1.0);
//LAL::Vector4<double> v5(-1.0,-1.0,-1.0,-1.0);
//LAL::Vector4<double> v6(2.0,2.0,2.0,4.0);
//double r = 1.0;
//
//v3 += v4;
//std::cout << "#v3+=v4# = 1,1,1 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 += -3.0*v4;
//std::cout << "#v3+=-3*v4# = -3,-3,-3 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 += -v5+v4;
//std::cout << "#v3+=-v5+v4# = 2,2,2 "<<v3 << std::endl;
//
//v3 -= v4;
//std::cout << "#v3-=v4# = -1,-1,-1 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
//v3 -= -3.0*v4;
//std::cout << "#v3-=-3*v4# = 3,3,3 "<<v3 << std::endl;
//v3 = LAL::Vector4<double>(0.0,0.0,0.0,0.0);
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
//v6 = LAL::Vector4<double>(2.0,2.0,2.0,4.0);
//v6 /= -3.0*v4;
//std::cout << "#v6/=-3*v4# = -0.666,-0.666,-0.666 "<<v6 << std::endl;
//v6 = LAL::Vector4<double>(2.0,2.0,2.0,4.0);
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

