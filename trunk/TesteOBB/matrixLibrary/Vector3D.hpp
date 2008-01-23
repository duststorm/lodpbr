#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

template <class T>
class Vector3D
{
public:
	
	Vector3D ();
	
	Vector3D ( const Vector3D<T>& );
	
	Vector3D ( const T& x, const T& y, const T& z );
	
	virtual ~Vector3D ();
};

#endif /*VECTOR3D_HPP_*/
