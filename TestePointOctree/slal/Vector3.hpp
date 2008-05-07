#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>

#include <cassert>
#include <cmath>


namespace CGL { 

	template <class Real>	class Vector3
	{

	private:

		union
		{

			struct
			{
				Real mX;
				Real mY;
				Real mZ;
			};

			Real xyz[3];

		};

	public:

		// VETOR COLUNA OU VETOR LINHA ??

		Vector3 ();

		template < typename U >
		Vector3 (const U* u);

		Vector3 ( const Vector3<Real>& u);
		
		template < typename U >
		Vector3 ( const Vector3<U>& u);

		Vector3 ( const Real& pX, const Real& pY, const Real& pZ );

		//Gets and Sets
	
		inline Real x() const;

		inline Real y() const;

		inline Real z() const;

		inline void set(const Real& x, const Real& y, const Real& z);
		//Operator

		inline operator Real * ();
		inline operator const Real * ();

		inline Real operator [] ( int i) const;

		inline Real& operator [] ( int i);

		// Assignment Opertators
		//With Scalar
  	  	inline Vector3<Real>   		  operator+ ( ) const;
  	  	inline Vector3<Real>   		  operator- ( ) const;
  	  	
		inline const Vector3< Real >& operator+= ( const Real&  factor );
		inline const Vector3< Real >& operator-= ( const Real&  factor ); 
		inline const Vector3< Real >& operator*= ( const Real& factor ); 
		inline const Vector3< Real >& operator/= ( const Real& factor );

		template <class T>
		friend inline Vector3<T> operator* (const Vector3<T>& u, const T& factor); 	
		template <class T>
		friend inline Vector3<T> operator* (const T& factor, const Vector3<T>& u); 
		template <class T>
		friend inline Vector3<T> operator/ (const Vector3<T>& u, const T& factor); 	
		template <class T>
		inline friend Vector3<T> operator+ (const T& factor, const Vector3<T>& u);  
		template <class T>
		inline friend Vector3<T> operator+ (const Vector3<T>& u, const T& factor);
		template <class T>
		inline friend Vector3<T> operator- (const T& factor, const Vector3<T>& u);  
		template <class T>
		inline friend Vector3<T> operator- (const Vector3<T>& u, const T& factor); 
		
		
		
		// With Vector
		inline const Vector3<Real>& operator=  ( const Vector3<Real>& u );
		inline const Vector3<Real>& operator+= ( const Vector3<Real>& u );
		inline const Vector3<Real>& operator-= ( const Vector3<Real>& u ); 
		inline const Vector3<Real>& operator/= ( const Vector3<Real>& u ); 
		
		inline bool operator== ( const Vector3<Real>& u) const;
		inline bool operator!= ( const Vector3<Real>& u) const;
		
		inline Vector3<Real>  operator- ( const Vector3<Real>& u) const;
		inline Vector3<Real>  operator+ ( const Vector3<Real>& u) const;
		
		inline Real operator* ( const Vector3<Real>& u) const;

		// Cross Product	
		inline Vector3<Real>  operator^ (const Vector3<Real>& u) const;
		
		template <class T>
		friend inline std::ostream& operator<< (std::ostream & s, const Vector3<T>& u);
		
		// AUXILIAR FUNCTIONS
		inline Real length ();
		inline Real length2();
		inline void normalize ();
		inline Vector3<Real> norm ();
	

		~Vector3 ();


	};

#include "Vector3.inline.hpp"

} // END NAMESPACE


#endif

// CASOS DE TESTE


/* Teste operator+ e operator-
CGL::Vector3<double> v1(1.0,1.0,1.0);
CGL::Vector3<double> v2(-1.0,-1.0,-1.0);
CGL::Vector3<double> v3(0.0,0.0,0.0);

v3 = v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#v1+v2#"<<std::endl;
v3 = v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#v1-v2#"<<std::endl;
v3 = -v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#-v1-v2#"<<std::endl;
v3 = -v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#-v1+v2#"<<std::endl;
v3 = + v1 - v2;
std::cout << v3.x << v3.y << v3.z << "#+v1-v2#"<<std::endl;
v3 = + v1 + v2;
std::cout << v3.x << v3.y << v3.z << "#+v1+v2#"<<std::endl;
*/

/*Teste operator*
	CGL::Vector3<double> v1(1.0,1.0,1.0);
	CGL::Vector3<double> v3(0.0,0.0,0.0);
	
	v3 = 3.0 * v1;
	std::cout << v3.x << v3.y << v3.z << "#3*v1#"<<std::endl;
	v3 = 3.0 * (-v1);
	std::cout << v3.x << v3.y << v3.z << "#3*(-v1)#"<<std::endl;
	v3 = 3.0 * (+v1);
	std::cout << v3.x << v3.y << v3.z << "#3*(+v1)#"<<std::endl;
	v3 = (-v1) * 3.0;
	std::cout << v3.x << v3.y << v3.z << "#(-v1)*3#"<<std::endl;
	v3 = (+v1) * 3.0;
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*3#"<<std::endl;
	v3 = (+v1) * 0.0;
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*0.0#"<<std::endl;
	v3 = (+v1) * v2[1];
	std::cout << v3.x << v3.y << v3.z << "#(+v1)*0.0#"<<std::endl;
*/

/* Teste operator* (puduto interno ou  produto escalar) 
CGL::Vector3<double> v1(6.0,-1.0,0.0);
CGL::Vector3<double> v2(0.5,-4.0,0.0);
double t = 0.0 ;
t = v1 * v2
std::cout << t << "#(v1)*(v2)#"<<std::endl;
v1[1] = v1*(-v2)
*/



/*
 * solucão para não ter warnning no retorno de uma referencia
inline Vector3<T>&  operator- ( const Vector3<T>& u) const
{
	Vector3<T> w;
	 	
	w.x = this->x - u.x;
	w.y = this->y - u.y;
	w.z = this->z - u.z;
		
	Vector3<T>& h = w;
	
	return ( h );
};
*/
