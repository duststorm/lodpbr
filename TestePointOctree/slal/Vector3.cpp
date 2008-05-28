#include "Vector3.hpp"

namespace LAL
{
	template<>  const Vector3<float> Vector3<float>::ZERO( 0, 0, 0 );

	template<>  const Vector3<float> Vector3<float>::UNIT_X( 1, 0, 0 );
    template<>  const Vector3<float> Vector3<float>::UNIT_Y( 0, 1, 0 );
    template<>  const Vector3<float> Vector3<float>::UNIT_Z( 0, 0, 1 );
    
    template<>  const Vector3<float> Vector3<float>::UNIT(1, 1, 1);
}
