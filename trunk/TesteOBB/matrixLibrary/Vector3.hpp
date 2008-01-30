#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <iostream>

namespace SLAL { 

template <class T>	class Vector3
{

private:

	T x_;
	T y_;
	T z_;
	
public:
	

	// VETOR COLUNA OU VETOR LINHA ??
	Vector3 ()
	{
		this->x_ = (T)0;
		this->y_ = (T)0;
		this->z_ = (T)0;
	};
	
	Vector3 ( const Vector3<T>& u)
	{
		this->x_ = u.x();
		this->y_ = u.y();
		this->z_ = u.z();
	};
	
	Vector3 ( const T& x, const T& y, const T& z )
	{
		this->x_ = x;
		this->y_ = y;
		this->z_ = z;
	};
	
	//Gets and Sets
			
	inline T x() const
	{
		return ( this->x_ );
	};
	
	inline T y() const
	{
		return ( this->y_ );
	};
	
	inline T z() const
	{
		return ( this->z_ );
	};
	
	//Operator
	
	inline T& operator [] (const unsigned int i) 
	{
		if ( i > 2)
		{
			std::cerr << "[ERROR] Vector3 operator[]"        << std::endl
				      << "        Out of the vector size. " << std::endl
				      << "        Accepts, 0 , 1 , 2 only." << std::endl;
			exit(1);
		}
			
		
	    if (i == 0)
	    	return (this->x_);
	    if (i == 1)
	    	return (this->y_);
	    return (this->z_);
	};
	
	inline Vector3<T>& operator= ( const Vector3<T>& u)
	{
		this->x_ = u.x();
		this->y_ = u.y();
		this->z_ = u.z();
			
		return ( *this );
	};
	
	friend inline bool operator== ( const Vector3<T>& u,const Vector3<T>& v)
	{
		return ( ( u.x() == v.x() ) and ( u.y() == v.y() ) and ( u.z() == v.z() ) );
	};	
	
	friend inline bool operator!= ( const Vector3<T>& u, const Vector3<T>& v)
	{
		return  !(u == v) ;
	};	
	
	inline Vector3<T>  operator- ( const Vector3<T>& u) const
	{
		Vector3<T> w = Vector3( this->x_ - u.x(),
								this->y_ - u.y(),
							    this->z_ - u.z());
		
		return ( w );
	};
	
	inline Vector3<T>  operator- ( ) const
	{
		Vector3<T> w = Vector3 (-this->x_, -this->y_, -this->z_);
			
		return ( w );
	};
	
	inline Vector3<T>  operator+ ( const Vector3<T>& u)	const
	{
	 	Vector3<T> w = Vector3 ( this->x_ + u.x(),
	 							 this->y_ + u.y(),
	 							 this->z_ + u.z());
	 	
		return ( w );
	};
	
	inline Vector3<T>  operator+ ( ) const
	{
		return ( *this );
	};
	
	friend inline Vector3<T> operator* ( const Vector3<T>& u,const T& factor ) 	
	{
	 	Vector3<T> w = Vector3( u.x() * factor,
	 							u.y() * factor,
	 							u.z() * factor );
		
		return ( w );
	};
	
	friend inline Vector3<T> operator*	( const T& factor ,const Vector3<T>& u) 	
	{
	 	Vector3<T> w = Vector3( u.x() * factor,
	 							u.y() * factor,
	 							u.z() * factor );

		return ( w );
	};
	
	friend inline T operator* ( const Vector3<T>& u ,const Vector3<T>& v) 	
	{
	 	T dotProduct;
	 	
	 	dotProduct = ( u.x() * v.x()) +  (u.y() * v.y()) + (u.z() * v.z() ) ;
		
		return ( dotProduct );
	};

		
	friend inline Vector3<T>  operator^	( const Vector3<T>& u ,const Vector3<T>& v)
	{
		Vector3<T> crossProduct = Vector3( u.y() * v.z() - u.z() * v.y(),
										  -u.x() * v.z() + u.z() * v.x(),
										   u.x() * v.y() - u.y() * v.x() );

		return ( crossProduct );
	};
	
	friend inline std::ostream& operator<< (std::ostream & s, const Vector3<T>& u)
	{
		s << "Vector3"<< " x = " << u.x() << " ,y = " << u.y() << " ,z = " << u.z() << std::endl;
		
		return s;
	};
	
	~Vector3 (){};
		
};


} // END NAMESPACE


#endif

// CASOS DE TESTE

/*
 * Teste operator+ e operator-
SLAL::Vector3<double> v1(1.0,1.0,1.0);
SLAL::Vector3<double> v2(-1.0,-1.0,-1.0);
SLAL::Vector3<double> v3(0.0,0.0,0.0);

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

/*
 * Teste operator*
	SLAL::Vector3<double> v1(1.0,1.0,1.0);
	SLAL::Vector3<double> v3(0.0,0.0,0.0);
	
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
 */

/*
 * Teste operator* (puduto interno ou  produto escalar) 
SLAL::Vector3<double> v1(6.0,-1.0,0.0);
SLAL::Vector3<double> v2(0.5,-4.0,0.0);
double t = 0.0 ;
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
