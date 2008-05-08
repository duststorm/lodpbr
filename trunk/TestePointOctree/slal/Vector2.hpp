#ifndef LAL_VECTOR2_HPP_
#define LAL_VECTOR2_HPP_


#include <iostream>

#include <cassert>
#include <cmath>


namespace LAL { 

	template <class Real>	class Vector2
	{

	private:

		union
		{

			struct
			{
				Real mX;
				Real mY;
			};

			Real xy[3];

		};

	public:

		// VETOR COLUNA OU VETOR LINHA ??

		Vector2 ();

		template < typename U >
		Vector2 (const U* u);

		Vector2 ( const Vector2<Real>& u);

		Vector2 ( const Real& pX, const Real& pY );

		//Gets and Sets
	
		inline Real x() const;

		inline Real y() const;

		//Operator

		inline operator Real * ();
		inline operator const Real * ();

		inline Real operator [] ( unsigned int i) const;

		inline Real& operator [] ( unsigned int i);

		// Assignment Opertators
		//With Scalar
  	  	inline Vector2<Real>   		  operator+ ( ) const;
  	  	inline Vector2<Real>   		  operator- ( ) const;
  	  	
		inline const Vector2< Real >& operator+= ( const Real&  factor );
		inline const Vector2< Real >& operator-= ( const Real&  factor ); 
		inline const Vector2< Real >& operator*= ( const Real& factor ); 
		inline const Vector2< Real >& operator/= ( const Real& factor );

		template <class T>
		friend inline Vector2<T> operator* (const Vector2<T>& u, const T& factor); 	
		template <class T>
		friend inline Vector2<T> operator* (const T& factor, const Vector2<T>& u); 
		template <class T>
		friend inline Vector2<T> operator/ (const Vector2<T>& u, const T& factor); 	
		template <class T>
		inline friend Vector2<T> operator+ (const T& factor, const Vector2<T>& u);  
		template <class T>
		inline friend Vector2<T> operator+ (const Vector2<T>& u, const T& factor);
		template <class T>
		inline friend Vector2<T> operator- (const T& factor, const Vector2<T>& u);  
		template <class T>
		inline friend Vector2<T> operator- (const Vector2<T>& u, const T& factor); 
		
		
		
		// With Vector
		inline const Vector2<Real>& operator=  ( const Vector2<Real>& u );
		inline const Vector2<Real>& operator+= ( const Vector2<Real>& u );
		inline const Vector2<Real>& operator-= ( const Vector2<Real>& u ); 
		inline const Vector2<Real>& operator/= ( const Vector2<Real>& u ); 
		
		inline bool operator== ( const Vector2<Real>& u) const;
		inline bool operator!= ( const Vector2<Real>& u) const;
		
		inline Vector2<Real>  operator- ( const Vector2<Real>& u) const;
		inline Vector2<Real>  operator+ ( const Vector2<Real>& u) const;
		
		inline Real operator* ( const Vector2<Real>& u) const;
		
		template <class T>
		friend inline std::ostream& operator<< (std::ostream & s, const Vector2<T>& u);
		
		// AUXILIAR FUNCTIONS
		inline Real length ();
		inline void normalize ();
		inline Vector2<Real> norm ();
	

		~Vector2 ();


	};

#include "Vector2.inline.hpp"

} /* LAL :: NAMESPACE */


#endif /*VECTOR2_HPP_*/

// CASOS DE TESTE


/* Teste operator+ e operator-
LAL::Vector2<double> v1(1.0,1.0,1.0);
LAL::Vector2<double> v2(-1.0,-1.0,-1.0);
LAL::Vector2<double> v3(0.0,0.0,0.0);

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
	LAL::Vector2<double> v1(1.0,1.0,1.0);
	LAL::Vector2<double> v3(0.0,0.0,0.0);
	
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
LAL::Vector2<double> v1(6.0,-1.0,0.0);
LAL::Vector2<double> v2(0.5,-4.0,0.0);
double t = 0.0 ;
t = v1 * v2
std::cout << t << "#(v1)*(v2)#"<<std::endl;
v1[1] = v1*(-v2)
*/



/*
 * solucão para não ter warnning no retorno de uma referencia
inline Vector2<T>&  operator- ( const Vector2<T>& u) const
{
	Vector2<T> w;
	 	
	w.x = this->x - u.x;
	w.y = this->y - u.y;
	w.z = this->z - u.z;
		
	Vector2<T>& h = w;
	
	return ( h );
};
*/


