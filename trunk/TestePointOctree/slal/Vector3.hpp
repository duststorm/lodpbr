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

		Vector3 ( const Real& pX, const Real& pY, const Real& pZ );

		//Gets and Sets

		inline Real x() const;

		inline Real y() const;

		inline Real z() const;

		//Operator

		inline operator Real * ();

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
		inline void normalize ();
		inline Vector3<Real> norm ();
	

		~Vector3 ();


	};

	template<class Real>
	Vector3<Real>::Vector3 ()
	{
		this->mX = static_cast< Real > ( 0 );
		this->mY = static_cast< Real > ( 0 );
		this->mZ = static_cast< Real > ( 0 );
	};

	template<class Real>
	template < typename U >
	Vector3<Real>::Vector3 (const U* u)
	{
		assert(u);

		this->mX = static_cast< Real > ( u[0] );
		this->mY = static_cast< Real > ( u[1] );
		this->mZ = static_cast< Real > ( u[2] );

	};

	template<class Real>
	Vector3<Real>::Vector3 ( const Vector3<Real>& u)
	{
		this->mX = u.x();
		this->mY = u.y();
		this->mZ = u.z();
	};

	template<class Real>
	Vector3<Real>::Vector3 ( const Real& pX, const Real& pY, const Real& pZ )
	{
		this->mX = pX;
		this->mY = pY;
		this->mZ = pZ;
	};

	//Gets and Sets
	template<class Real>
	inline Real Vector3<Real>::x() const
	{
		return ( this->mX );
	};
	
	template<class Real>
	inline Real Vector3<Real>::y() const
	{
		return ( this->mY );
	};

	template<class Real>
	inline Real Vector3<Real>::z() const
	{
		return ( this->mZ );
	};

	//Operator

	template<class Real>
	inline Vector3<Real>::operator Real * ()
	{
		return xyz;
	}

	template<class Real>
	inline Real Vector3<Real>::operator [] ( int i) const
	{
		if ( i > 2)
		{
			std::cerr << "[ERROR] Vector3 operator[]"        << std::endl
			<< "        Out of the vector size. " << std::endl
			<< "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}

		return (xyz[i]);

	};

	template<class Real>
	inline Real& Vector3<Real>::operator [] ( int i) 
	{
		if ( i > 2)
		{
			std::cerr << "[ERROR] Vector3 operator[]"        << std::endl
			<< "        Out of the vector size. " << std::endl
			<< "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}


		return (xyz[i]);

	};

	// Assignment Opertators
	//With Scalar

    template<class Real>
    inline Vector3<Real> Vector3<Real>::operator+ ( )  const  
    {
  	  return ( Vector3<Real> (this->mX, this->mY, this->mZ)  );
    };
    
    /*!@brief operator-
     * @details Unary operator tha return the negative of the point.
     * @note To be clearer the arithmetic operations.
     * @return Point3.
     */
    template<class Real>
    inline Vector3<Real>  Vector3<Real>::operator- ( ) const
    {

  	  return ( Vector3<Real> (-this->mX, -this->mY, -this->mZ) );

    };
	
	template<class Real>
	const Vector3< Real >& Vector3<Real>::operator+= ( const Real&  factor ) 
	{ 
		this->mX += factor; 
		this->mY += factor; 
		this->mZ += factor;

		return ( *this ); 
	} 
	
	template<class Real>
	const Vector3< Real >& Vector3<Real>::operator-= ( const Real&  factor ) 
	{ 
		this->mX -= factor; 
		this->mY -= factor; 
		this->mZ -= factor;

		return ( *this ); 
	} 

	template<class Real>
	const Vector3< Real >& Vector3<Real>::operator*= ( const Real& factor ) 
	{ 

		this->mX  *= factor;
		this->mY  *= factor;
		this->mZ  *= factor;

		return ( *this ); 
	}
	
	template<class Real>
	const Vector3< Real >& Vector3<Real>::operator/= ( const Real& factor ) 
	{ 
		Real lFactor = (Real)1 / factor;

		this->mX *= lFactor;
		this->mY *= lFactor; 
		this->mZ *= lFactor;

		return ( *this ); 
	}
	
	
	template<class Real>
	inline Vector3<Real> operator* ( const Vector3<Real>& u, const Real& factor ) 	
	{

		return (  Vector3<Real>( u.mX * factor,
				u.mY * factor,
				u.mZ * factor ) 
		);

	};

	template<class Real>
	inline Vector3<Real> operator*	( const Real& factor, const Vector3<Real>& u ) 
	{
		return ( Vector3<Real>( u.mX * factor,
				u.mY * factor,
				u.mZ * factor )
		);

	};

	template<class Real>
	inline Vector3<Real> operator/ ( const Vector3<Real>& u, const Real& factor ) 	
	{

		return (  Vector3<Real>( u.mX / factor,
				u.mY / factor,
				u.mZ / factor ) 
		);

	};

	template<class Real>
	inline Vector3<Real> operator+ (const Real& factor, const Vector3<Real>& u )  
	{
		return ( Vector3<Real> ( u.mX + factor,
				u.mY + factor,
				u.mZ + factor )
		);

	};

	template<class Real>
	inline Vector3<Real> operator+ (const Vector3<Real>& u, const Real& factor )  
	{
		return ( Vector3<Real> ( u.mX + factor,
				u.mY + factor,
				u.mZ + factor )
		);

	};

	template<class Real>
	inline Vector3<Real> operator- (const Real& factor, const Vector3<Real>& u )  
	{
		return ( Vector3<Real> ( factor - u.mX ,
				factor - u.mY ,
				factor - u.mZ  )
		);

	};

	template<class Real>
	inline Vector3<Real> operator- (const Vector3<Real>& u, const Real& factor )  
	{
		return ( Vector3<Real> ( u.mX - factor,
				u.mY - factor,
				u.mZ - factor )
		);

	};
	
	// With Vector
	
	template<class Real>
	inline const Vector3<Real>& Vector3<Real>::operator= ( const Vector3<Real>& u )
	{
		this->mX = u.mX;
		this->mY = u.mY;
		this->mZ = u.mZ;

		return ( *this );
	};
	
	template<class Real>
	const Vector3< Real >& Vector3<Real>::operator+= (  const Vector3<Real>& u ) 
	{ 
		this->mX += u.mX; 
		this->mY += u.mY; 
		this->mZ += u.mZ;

		return ( *this ); 
	}
	
	template<class Real>
	const Vector3< Real >& Vector3<Real>::operator-= (  const Vector3<Real>& u ) 
	{ 
		this->mX -= u.mX; 
		this->mY -= u.mY; 
		this->mZ -= u.mZ;

		return ( *this ); 
	} 

	template<class Real>
	const Vector3< Real >& Vector3<Real>::operator/= ( const Vector3<Real>& u ) 
	{ 

		this->mX /= u.mX;
		this->mY /= u.mY; 
		this->mZ /= u.mZ;

		return ( *this ); 
	} 

	template<class Real>
	inline bool Vector3<Real>::operator== ( const Vector3<Real>& u) const
	{
		return ( ( this->mX == u.mX ) and ( this->mY == u.mY ) and ( this->mZ == u.mZ ) );
	};	

	template<class Real>
	inline bool Vector3<Real>::operator!= ( const Vector3<Real>& u) const
	{
		return  !(*this == u) ;
	};	

	template<class Real>
	inline Vector3<Real>  Vector3<Real>::operator- ( const Vector3<Real>& u) const
	{

		return ( Vector3 ( this->mX - u.mX,
				this->mY - u.mY,
				this->mZ - u.mZ) 
		);
	};

	template<class Real>
	inline Vector3<Real>  Vector3<Real>::operator+ ( const Vector3<Real>& u)	const
	{

		return ( Vector3 ( this->mX + u.mX,
				this->mY + u.mY,
				this->mZ + u.mZ)
		);

	};

	template<class Real>
	inline Real Vector3<Real>::operator* ( const Vector3<Real>& u) const	
	{

		return (  (u.mX * mX ) +  ( u.mY * mY ) + ( u.mZ * mZ )  );

	};

	// Cross Product
	template<class Real>
	inline Vector3<Real>  Vector3<Real>::operator^ (const Vector3<Real>& u) const
	{
		return ( Vector3<Real> ( 	mY*u.z() - mZ*u.y(),
				mZ*u.x() - mX*u.z(),
				mX*u.y() - mY*u.x())
		);

	};

	template<class Real>
	inline std::ostream& operator<< (std::ostream & s, const Vector3<Real>& u)
	{
		s << "Vector3"<< " x = " << u.x() << " ,y = " << u.y() << " ,z = " << u.z() << std::endl;

		return s;
	};

	// AUXILIAR FUNCTIONS
	template<class Real>
	inline Real Vector3<Real>::length ()
	{
		return sqrt( (this->mX * this->mX) + (this->mY * this->mY) + (this->mZ * this->mZ) );
	};

	template<class Real>
	inline void Vector3<Real>::normalize ()
	{
		Real factor = sqrt( (mX * mX) + (mY * mY) + (mZ * mZ) );

		assert (factor);

		Real d = 1 / factor;

		mX *= d;
		mY *= d;
		mZ *= d;

	};

	template<class Real>
	inline Vector3<Real> Vector3<Real>::norm ()
	{
		Real factor = sqrt( (mX * mX) + (mY * mY) + (mZ * mZ) );

		assert (factor);

		Real d = 1 / factor;

		return ( Vector3 (mX * d, mY * d, mZ * d) );

	};
	template <class Real>
	Vector3<Real>::~Vector3 (){};


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
