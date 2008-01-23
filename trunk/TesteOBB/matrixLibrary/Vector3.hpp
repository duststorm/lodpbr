#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_




namespace SLAL { 

template <class T>	class Vector3
{
public:
	// VETOR COLUNA OU VETOR LINHA ??
	Vector3 ()
	{
		this->x = (T)0;
		this->y = (T)0;
		this->z = (T)0;
	};
	
	Vector3 ( const Vector3<T>& u)
	{
		this->x = u.x;
		this->y = u.y;
		this->z = u.z;;
	};
	
	Vector3 ( const T& x, const T& y, const T& z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};
	
	//Gets and Sets
			
	//Operator
	
	inline Vector3<T>& operator= ( const Vector3<T>& u)
	{
		this->x = u.x;
		this->y = u.y;
		this->z = u.z;
			
		return ( *this );
	};
	
	friend inline bool operator== ( const Vector3<T>& u,const Vector3<T>& v)
	{
		bool isEqual = false;
		
		isEqual = (u.x == v.x) and (u.y == v.y) and (u.z == v.z);
		
		return ( isEqual );
	};	
	
	friend inline bool operator!= ( const Vector3<T>& u, const Vector3<T>& v)
	{
						
		return  !(u == v) ;
	};	
	
	inline Vector3<T>  operator- ( const Vector3<T>& u) const
	{
		Vector3<T> w;
		 	
		w.x = this->x - u.x;
		w.y = this->y - u.y;
		w.z = this->z - u.z;
			
		return ( w );
	};
	inline Vector3<T>  operator- ( ) const
	{
		Vector3<T> w;
		 	
		w.x = -this->x; 
		w.y = -this->y;
		w.z = -this->z;
			
		return ( w );
	};
	inline Vector3<T>  operator+ ( const Vector3<T>& u)	const
	{
	 	Vector3<T> w;
	 	
		w.x = this->x + u.x;
		w.y = this->y + u.y;
		w.z = this->z + u.z;
		
		return ( w );
	};
	inline Vector3<T>  operator+ ( ) const
	{
		return ( *this );
	};
	friend Vector3<T> operator* ( const Vector3<T>& u,const T& factor ) 	
	{
	 	Vector3<T> w;
	 	
		w.x = u.x * factor;
		w.y = u.y * factor;
		w.z = u.z * factor;

		return ( w );
	};
	
	friend Vector3<T> operator*	( const T& factor ,const Vector3<T>& u) 	
	{
	 	Vector3<T> w;
	 	
		w.x = u.x * factor;
		w.y = u.y * factor;
		w.z = u.z * factor;

		return ( w );
	};
	
	friend T operator*	( const Vector3<T>& u ,const Vector3<T>& v) 	
	{
	 	T w;
	 	
		w = (u.x * v.x) + 
			(u.y * v.y) +
			(u.z * v.z) ;
		
		return ( w );
	};

		
	inline Vector3<T>  operator^	( const Vector3<T>& ) 	const;
	
	~Vector3 (){};
	
	T x;
	T y;
	T z;
	
private:
		
};

/*
template < class T >
Vector3< T >::~Vector3()
{
	
};
*/

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

