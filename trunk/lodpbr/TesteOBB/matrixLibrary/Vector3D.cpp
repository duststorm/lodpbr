#include "Vector3D.hpp"

template < class T >
Vector3D< T >::Vector3D()
{
	
}

template < class T >
Vector3D< T >::Vector3D( const Vector3D<T>& vector )
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}


template < class T >
Vector3D< T >::~Vector3D()
{
	
}
