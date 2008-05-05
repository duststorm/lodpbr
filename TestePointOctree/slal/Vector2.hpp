#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_


#include <iostream>

#include <cassert>
#include <cmath>


namespace CGL { 

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

	template<class Real>
	Vector2<Real>::Vector2 ()
	{
		this->mX = static_cast< Real > ( 0 );
		this->mY = static_cast< Real > ( 0 );
	};

	template<class Real>
	template < typename U >
	Vector2<Real>::Vector2 (const U* u)
	{
		assert(u);

		this->mX = static_cast< Real > ( u[0] );
		this->mY = static_cast< Real > ( u[1] );
		
	};

	template<class Real>
	Vector2<Real>::Vector2 ( const Vector2<Real>& u)
	{
		this->mX = u.mX;
		this->mY = u.mY;
	};

	template<class Real>
	Vector2<Real>::Vector2 ( const Real& pX, const Real& pY)
	{
		this->mX = pX;
		this->mY = pY;
	};
	
	//Gets and Sets
	template<class Real>
	inline Real Vector2<Real>::x() const
	{
		return ( this->mX );
	};
	
	template<class Real>
	inline Real Vector2<Real>::y() const
	{
		return ( this->mY );
	};

	//Operator

	template<class Real>
	inline Vector2<Real>::operator Real * ()
	{
		return xy;
	}
	
	template<class Real>
	inline Vector2<Real>::operator const Real * ()
	{
		return xy;
	}

	template<class Real>
	inline Real Vector2<Real>::operator [] ( unsigned int i) const
	{
		if ( i > 1)
		{
			std::cerr << "[ERROR] Vector2 operator[]"        << std::endl
			<< "        Out of the vector size. " << std::endl
			<< "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}

		return (xy[i]);

	};

	template<class Real>
	inline Real& Vector2<Real>::operator [] ( unsigned int i) 
	{
		if ( i > 1)
		{
			std::cerr << "[ERROR] Vector2 operator[]"        << std::endl
			<< "        Out of the vector size. " << std::endl
			<< "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}


		return (xy[i]);

	};

	// Assignment Opertators
	//With Scalar

    template<class Real>
    inline Vector2<Real> Vector2<Real>::operator+ ( )  const  
    {
  	  return ( Vector2<Real> (this->mX, this->mY)  );
    };
    
    /*!@brief operator-
     * @details Unary operator tha return the negative of the point.
     * @note To be clearer the arithmetic operations.
     * @return Point3.
     */
    template<class Real>
    inline Vector2<Real>  Vector2<Real>::operator- ( ) const
    {

  	  return ( Vector2<Real> (-this->mX, -this->mY) );

    };
	
	template<class Real>
	const Vector2< Real >& Vector2<Real>::operator+= ( const Real&  factor ) 
	{ 
		this->mX += factor; 
		this->mY += factor; 
		
		return ( *this ); 
	} 
	
	template<class Real>
	const Vector2< Real >& Vector2<Real>::operator-= ( const Real&  factor ) 
	{ 
		this->mX -= factor; 
		this->mY -= factor; 
		
		return ( *this ); 
	} 

	template<class Real>
	const Vector2< Real >& Vector2<Real>::operator*= ( const Real& factor ) 
	{ 

		this->mX  *= factor;
		this->mY  *= factor;
		
		return ( *this ); 
	}
	
	template<class Real>
	const Vector2< Real >& Vector2<Real>::operator/= ( const Real& factor ) 
	{ 
		Real lFactor = (Real)1 / factor;

		this->mX *= lFactor;
		this->mY *= lFactor; 
		
		return ( *this ); 
	}
	
	
	template<class Real>
	inline Vector2<Real> operator* ( const Vector2<Real>& u, const Real& factor ) 	
	{

		return (  Vector2<Real>( u.mX * factor, u.mY * factor ) );

	};

	template<class Real>
	inline Vector2<Real> operator*	( const Real& factor, const Vector2<Real>& u ) 
	{
		return ( Vector2<Real>( u.mX * factor, u.mY * factor )
		);

	};

	template<class Real>
	inline Vector2<Real> operator/ ( const Vector2<Real>& u, const Real& factor ) 	
	{

		return (  Vector2<Real>( u.mX / factor, u.mY / factor ) );

	};

	template<class Real>
	inline Vector2<Real> operator+ (const Real& factor, const Vector2<Real>& u )  
	{
		return ( Vector2<Real> ( u.mX + factor, u.mY + factor ) );

	};

	template<class Real>
	inline Vector2<Real> operator+ (const Vector2<Real>& u, const Real& factor )  
	{
		return ( Vector2<Real> ( u.mX + factor, u.mY + factor )	);

	};

	template<class Real>
	inline Vector2<Real> operator- (const Real& factor, const Vector2<Real>& u )  
	{
		return ( Vector2<Real> ( factor - u.mX ,factor - u.mY  ) );

	};

	template<class Real>
	inline Vector2<Real> operator- (const Vector2<Real>& u, const Real& factor )  
	{
		return ( Vector2<Real> ( u.mX - factor,	u.mY - factor ) );

	};
	
	// With Vector
	
	template<class Real>
	inline const Vector2<Real>& Vector2<Real>::operator= ( const Vector2<Real>& u )
	{
		this->mX = u.mX;
		this->mY = u.mY;

		return ( *this );
	};
	
	template<class Real>
	const Vector2< Real >& Vector2<Real>::operator+= (  const Vector2<Real>& u ) 
	{ 
		this->mX += u.mX; 
		this->mY += u.mY;
		
		return ( *this ); 
	}
	
	template<class Real>
	const Vector2< Real >& Vector2<Real>::operator-= (  const Vector2<Real>& u ) 
	{ 
		this->mX -= u.mX; 
		this->mY -= u.mY;
		
		return ( *this ); 
	} 

	template<class Real>
	const Vector2< Real >& Vector2<Real>::operator/= ( const Vector2<Real>& u ) 
	{ 

		this->mX /= u.mX;
		this->mY /= u.mY;
		
		return ( *this ); 
	} 

	template<class Real>
	inline bool Vector2<Real>::operator== ( const Vector2<Real>& u) const
	{
		return ( ( this->mX == u.mX ) and ( this->mY == u.mY ) );
	};	

	template<class Real>
	inline bool Vector2<Real>::operator!= ( const Vector2<Real>& u) const
	{
		return  !(*this == u) ;
	};	

	template<class Real>
	inline Vector2<Real>  Vector2<Real>::operator- ( const Vector2<Real>& u) const
	{

		return ( Vector2 ( this->mX - u.mX, this->mY - u.mY ) );
	};

	template<class Real>
	inline Vector2<Real>  Vector2<Real>::operator+ ( const Vector2<Real>& u)	const
	{

		return ( Vector2 ( this->mX + u.mX, this->mY + u.mY) );

	};

	template<class Real>
	inline Real Vector2<Real>::operator* ( const Vector2<Real>& u) const	
	{

		return (  (u.mX * mX ) +  ( u.mY * mY ) );

	};


	template<class Real>
	inline std::ostream& operator<< (std::ostream & s, const Vector2<Real>& u)
	{
		s << "Vector2" << " x = " << u.x() << " ,y = " << u.y() << std::endl;

		return s;
	};

	// AUXILIAR FUNCTIONS
	template<class Real>
	inline Real Vector2<Real>::length ()
	{
		return sqrt( (this->mX * this->mX) + (this->mY * this->mY) );
	};

	template<class Real>
	inline void Vector2<Real>::normalize ()
	{
		Real factor = sqrt( (mX * mX) + (mY * mY) );

		assert (factor);

		Real lFactor = 1 / factor;

		mX *= lFactor;
		mY *= lFactor;


	};

	template<class Real>
	inline Vector2<Real> Vector2<Real>::norm ()
	{
		Real factor = sqrt( (mX * mX) + (mY * mY) );

		assert (factor);

		Real lFactor = 1 / factor;

		return ( Vector2 (mX * lFactor, mY * lFactor) );

	};
	template <class Real>
	Vector2<Real>::~Vector2 (){};


} // END NAMESPACE


#endif /*VECTOR2_HPP_*/

// CASOS DE TESTE


/* Teste operator+ e operator-
CGL::Vector2<double> v1(1.0,1.0,1.0);
CGL::Vector2<double> v2(-1.0,-1.0,-1.0);
CGL::Vector2<double> v3(0.0,0.0,0.0);

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
	CGL::Vector2<double> v1(1.0,1.0,1.0);
	CGL::Vector2<double> v3(0.0,0.0,0.0);
	
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
CGL::Vector2<double> v1(6.0,-1.0,0.0);
CGL::Vector2<double> v2(0.5,-4.0,0.0);
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


