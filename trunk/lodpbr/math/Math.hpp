#ifndef LAL_MATH_HPP_
#define LAL_MATH_HPP_


#include <cmath>

//-----------------------------------------------------------------------------
// Common math functions and constants.
//-----------------------------------------------------------------------------



namespace LAL {

/*! \brief The Math class represents some useful math function.
\class Math Math.hpp

<h3>Internal representation</h3>
	All constants are float type
\nosubgrouping */

	class Math
	{
	public:
		/*! @name Constants */
		//@{
		/*!  */
		static const float PI;
		/*! */
	    static const float HALF_PI;
	    /*!
	     * \code
	     *  /f[
		 * \sqrt{ 2 }
		 * /f]
	     * \endcode
	     *  */
	    static const float SQRT_TWO;
	    /*!
	     * \code
	     *  /f[
		 * \sqrt{ 3 }
		 * /f]
	     * \endcode
	     * */
	    static const float SQRT_THREE;
	    /*!
	     *  \code
	     *  /f[
		 * 1 / \sqrt{ 2 }
		 * /f]
	     * \endcode
	     * */
	    static const float INV_SQRT_TWO;
	    /*!
	     * \code
	     *  /f[
		 * 1 / \sqrt{ 3 }
		 * /f]
	     * \endcode
	     *  */
	    static const float INV_SQRT_THREE;
	    /*!
	     * * \code
	     * /f[
		 * 1 / 3
		 * /f]
	     * \endcode
	     * */
	    static const float INV_THREE;
	    /*! Dregrees to radians conversion
	     * Only multiply the number in degrees by it
	     * */
	    static const float	DEG2RAD;
	    /*! Radians to dregrees conversion
	     * * Only multiply the number in radians by it
	     * */
	    static const float	RAD2DEG;
	    /*! */
	    static const float	FLOAT_INFINITY;
	    /*! */
	    static const float 	EPSILON;
	    //@}

		/*! @name functions ... */
		//@{
	    /*! */
	    static bool CloseEnough(float f1, float f2)
	    {
	        // Determines whether the two floating-point values f1 and f2 are
	        // close enough together that they can be considered equal.

	        return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
	    }
	    /*!
	     * \attention maybe move to another package
	     * */

		static float Hypotenuse (float x, float y)
		{
			return std::sqrt( (x * x) + (y * y) );
		}

	    //@}
		virtual ~Math();

	};


}/* LAL :: NAMESPACE */

#endif /*MATH_HPP_*/
