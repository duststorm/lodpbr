
#ifndef POINT3_HPP_
#define POINT3_HPP_

#include <iostream>
// [C++ Header files]
#include <cmath>
// [C++ Header STL]
#include <map>


#include "Vector3.hpp"


namespace CGL
{


/*!
*@class Point3.
*@brief Class that represent a Point in 3D.
*@details coming soon , but ... coming soon  ... wait ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 25-Feb-2008.
*@todo OpenGL interface and a C style array. 
*/	


	template <class Real>	class Point3
	{
				
	private:
	    /*! An union. */
	    /*! 
	     * Share memory with abscissas atributes and the XYZ Array.
	     * The Struct has the same size of the A. 
	     */
		union
		{
			struct
			{
				
				Real mX; /*!< X abscissa of space. */  
				
				Real mY; /*!< Y abscissa of space. */
				
				Real mZ; /*!< Z abscissa of space. */
			};
			 
			Real xyz[3];/*!< Array of abscissas for fast operator return @see operator[].*/
			
		};
		/*! An union. */
		/*! 
		 * Share memory with color atributes and the RGB vector. 
		 * The Struct has the same size of the A. 
		 */
		union
		{
			struct
			{	
				Real mRed;   /*!< Red color atribute.   */  
				Real mGreen; /*!< Green color atribute. */
				Real mBlue;  /*!< Blue color atribute.  */
			};
			
			Real rgb[3];/*!< Array of color.*/
		};
		
		
	public:
		
		friend class Vector3<Real>;
		
		/*! @brief Default Constructor. 
		 * 	@details Initialize all atribute with Zero.
		 */
		Point3()
		{
			this->mX = static_cast< Real > (0);
			this->mY = static_cast< Real > (0);
			this->mZ = static_cast< Real > (0);
			
			this->mRed   = static_cast< Real > (0);
			this->mGreen = static_cast< Real > (0);
			this->mBlue  = static_cast< Real > (0);
		};
	
	    /*!@brief Constructor with X, Y and Z initialization.
	     * @details Initialize all abscissas.
	     * @param[in] x Real number. 
	     * @param[in] y Real number. 
	     * @param[in] z Real number. 
	     */ 
		Point3 ( const Real& x, const Real& y, const Real& z )
			: mX(x), mY(y), mZ(z) {};
			
	   /*!@brief Constructor with X, Y and Z initialization of any type.
	   * @details Initialize all abscissas of any. Try cast to the Real type of the class
	   * @param[in] array of any type. 
       */ 							
		template < typename P >
		Point3 (const P* p)
		{
			assert(p);
			
	    	this->mX = static_cast< Real > ( p[0] );
	    	this->mY = static_cast< Real > ( p[1] );
	    	this->mZ = static_cast< Real > ( p[2] );
	    	
		};
		/*!@brief Constructor with X, Y and Z initialization with vector paramenter.
		* @param[in] u Vector of Real.
	    */ 	
		
		Point3 ( const Vector3<Real>& u)
			: mX(u.mX), mY(u.mY), mZ(u.mZ) {};
			
		/*!@brief Copy Constructor.
		*  @param[in] p Point Real.
		*/
		Point3 ( const Point3<Real>& p)
			: mX(p.mX), mY(p.mY), mZ(p.mZ) {};
			
		/*!@brief Initialize RGB color.
		*  @param[in] c array of any type.
		*  @note Prefer a number type. 
		*/				
		template < typename C >
		inline void setRGB ( const C* pC)
		{
	    	this->mRed   = static_cast< Real > ( pC[0] );
	    	this->mGreen = static_cast< Real > ( pC[1] );
	    	this->mBlue  = static_cast< Real > ( pC[2] );
		};	
		/*!@brief Initialize RGB color.
		*  @param[in] r Real.
		*  @param[in] g Real.
		*  @param[in] b Real. 
		*/		
		inline void setRGB ( const Real& pRed, const Real& pGreen, const Real& pBlue) 
		{
	    	this->mRed   = pRed;
	    	this->mGreen = pGreen;
	    	this->mBlue  = pBlue;
		};
			
		/*!@brief Initialize Red color.
		*  @param[in] r Real.
		*/				
		inline void setR ( const Real& pRed) 
		{
	    	this->mRed   = pRed;
		};

		/*!@brief Initialize Green color.
		*  @param[in] g Real.
		*/
		inline void setG ( const Real& pGreen)
		{
	    	this->mGreen = pGreen;
		};

		/*!@brief Initialize Blue color.
		*  @param[in] b Real.
		*/		
		inline void setB ( const Real& pBlue)
		{
	    	this->mBlue  = pBlue;
		};
			
		/*!@brief Get X abscissa.
		*  @return Real.
		*/		
		inline const Real& x() const
		{
			return ( this->mX );
		};
		/*!@brief Get Y abscissa.
		*  @return Real.
		*/		
		inline const Real& y() const
		{
			return ( this->mY );
		};
		/*!@brief Get Z abscissa.
		*  @return Real.
		*/
		inline const Real& z() const
		{
			return ( this->mZ );
		};
		/*!@brief Get Red color.
		*  @return Real.
		*/
		inline const Real& r() const
		{
			return ( this->mRed );
		};
		/*!@brief Get Green color.
		*  @return Real.
		*/		
		inline const Real& g() const
		{
			return ( this->mGreen );
		};
		/*!@brief Get Blue color.
		*  @return Real.
		*/
		inline const Real& b() const
		{
			return ( this->mBlue );
		};
		/*!@brief operator[]
		 * @details array based index. "0" for x, "1" for y, "2" for z.
		 * @ This is ready-only
		 * @return Real.
		 */
		inline  Real operator [] ( int i)  const
		{
			if ( (i > 2) or ( i < 0))
			{
				std::cerr << "[ERROR] Point3 operator[]"        << std::endl
					      << "        Out of the Point size. " << std::endl
					      << "        Accepts, 0 , 1 , 2 only." << std::endl;
				exit(1);
			}
			
		    return (xyz[i]);
		};
		/*!@brief operator[]
		 * @see operator[]
		 * @note Acept assigement
		 * @return Real.
		 */
		inline  Real operator [] ( int i)  
	
		{
			if ( (i > 2) or ( i < 0))
			{
				std::cerr << "[ERROR] Point3 operator[]"        << std::endl
					      << "        Out of the Point size. " << std::endl
					      << "        Accepts, 0 , 1 , 2 only." << std::endl;
				exit(1);
			}
			  
		    return (xyz[i]);
		};
		/*!@brief operator=
		 * @details Assigment operator
		 * @return Point3
		 */
		inline Point3<Real>& operator= ( const Point3<Real>& p)
		{
			this->mX = p.x();
			this->mY = p.y();
			this->mZ = p.z();
				
			return ( *this );
		};
		/*!@brief operator+=
		 * @details Add the value of the second operand to the value of the all abscissa of the point.
		 * @param[in] factor Real 
		 * @return Point3
		 */
		const Point3< Real >& operator+= ( const Real&  factor ) 
		{ 
		    this->mX += factor; 
		    this->mY += factor; 
		    this->mZ += factor;
		    
		    return ( *this ); 
		} 
		/*!@brief operator-=
		 * @details Subtract the value of the second operand to the value of the all abscissa of the point.
		 * @param[in] factor Real 
		 * @return Point3
		 */		
		const Point3< Real >& operator-= ( const Real&  factor ) 
		{ 
		    this->mX -= factor; 
		    this->mY -= factor; 
		    this->mZ -= factor;
		    
		    return ( *this ); 
		} 
		/*!@brief operator*=
		 * @details Multiply the value of the second operand to the value of the all abscissa of the point.
		 * @param[in] factor Real 
		 * @return Point3
		 */
		const Point3< Real >& operator*= ( const Real& factor ) 
		{ 
		 	 	
		 	this->mX  *= factor;
		 	this->mY  *= factor;
		 	this->mZ  *= factor;
							
		    return ( *this ); 
		}
		/*!@brief operator/=
		 * @details Divide the value of the second operand to the value of the all abscissa of the point.
		 * @param[in] factor Real 
		 * @return Point3
		 */
		const Point3< Real >& operator/= ( Real factor ) 
		{ 
		    factor = (Real)1 / factor;
		    
		    this->mX *= factor;
		    this->mY *= factor; 
		    this->mZ *= factor;
		    
		    return ( *this ); 
		}
		/*!@brief operator+=
		 * @see operator+=
		 * @note Add the correspondents abscissa of the left point to the right.
		 * @return Point3
		 */
		const Point3< Real >& operator+= (  const Point3<Real>& u ) 
		{ 
		    this->mX += u.x(); 
		    this->mY += u.y(); 
		    this->mZ += u.z();
		    
		    return ( *this ); 
		}
		/*!@brief operator-=
		 * @see operator-= 
		 * @note Subtract the correspondents abscissa of the left point to the right. 
		 * @return Point3
		 */		
		const Point3< Real >& operator-= (  const Point3<Real>& u ) 
		{ 
		    this->mX -= u.x(); 
		    this->mY -= u.y(); 
		    this->mZ -= u.z();
		    
		    return ( *this ); 
		} 
	
		/*!@brief operator/=
		 * @see operator/=
		 * @note Subtract the correspondents abscissa of the left point to the right.  
		 * @return Point3 
		 */
		const Point3<Real>& operator/=( const Point3<Real>& u ) 
		{ 
		    	    
		    this->mX /= u.x();
		    this->mY /= u.y(); 
		    this->mZ /= u.z();
		    
		    return ( *this ); 
		}
		
		/*!@brief operator==
		 * @details Two points are identical whether your correspondents abscissa are equal.
		 * @return bool.
		 */
		inline bool operator== ( const Point3<Real>& p) const
		{
			return ( ( this->mX == p.x() ) and ( this->mY == p.y() ) and ( this->mZ == p.z() ) );
		};	
		/*!@brief operator!=
		 * @details Opposite to the operator==
		 * @see operator==
		 * @return bool.
		 */
		inline bool operator!= ( const Point3<Real>& p) const
		{
			return  !(*this == p) ;
		};	
		/*!@brief operator-
		 * @details Unary operator tha return the negative of the point.
		 * @return Point3.
		 */
		inline Point3<Real>  operator- ( ) const
		{
			
			return ( Point3<Real> (-this->mX, -this->mY, -this->mZ) );
				
		};
		
		inline bool operator> ( const Point3<Real>& p) const
		{
			return ( ( this->mX > p.x() ) and 
					 ( this->mY > p.y() ) and
					 ( this->mZ > p.z() ) );
		};
		
		/*!@brief operator/
		 * @details Binary operator tha divide the value of the second operand to the value of the all abscissa of the point.
		 * @param[in] factor Real 
		 * @return Point3
		 */
		inline  Point3<Real> operator/ ( const Real& factor ) const  
		{
				return ( Point3<Real> ( this->mX /= factor, 
										this->mY /= factor,
										this->mZ /= factor )
					    );
			    
		};
		/*!@brief operator-
		 * @details Binary operator tha subtract two point and return a vector.
		 * @note First parameter is the origin and the second a target.
		 * @return Vector3
		 */			
		
		inline friend const Vector3<Real> operator- (const Point3<Real>& p, const Point3<Real>& q)  
		{
			return ( Vector3<Real>( p.mX - q.mX,
									p.mY - q.mY,
									p.mZ - q.mZ)
				    );
			
		};
		
		/*!@brief operator-
		 * @details Binary operator tha subtract a poitn and a vecctor.
		 * @return Point3
		 */
		
		inline friend const Point3<Real> operator- (const Point3<Real>& p, const Vector3<Real> u)  
		{
			return ( Point3<Real>( p.mX - u.mX,
							  	p.mY - u.mY,
					  	  	    p.mZ - u.mZ )
				   );
		};

		/*!@brief operator-
		 * @see operator-
		 * @return Point3
		 */
		
		inline friend const Point3<Real> operator- (const Vector3<Real> u,const Point3<Real> p )  
		{
			
			return ( Point3<Real>( u.mX - p.mX,
								   u.mY - p.mY,
								   u.mZ - p.mZ )
				    );
			    
		};
		
		
		/*!@brief operator+
		 * @details Unary operator tha return itself. 
		 * @note To be clearer the arithmetic operations. 
		 * @return Point3.
		 */
		
		inline Point3<Real>  operator+ ( ) const
		{
			return ( *this );
		};
		/*!@brief operator+
		 * @details Binary operator tha add a poitn and a vecctor.
		 * @return Point3
		 */
		inline friend const Point3<Real> operator+ (const Point3<Real> p, const Vector3<Real> u)  
		{
			return ( Point3<Real> ( p.mX + u.mX,
					     	  		p.mY + u.mY,
					     	  		p.mZ + u.mZ )
				    );
			
		};
		/*!@brief operator+
		 * @see operator+
		 * @return Point3
		 */
		inline friend  const Point3<Real> operator+ (const Vector3<Real> u,const Point3<Real> p )  
		{
			return ( Point3<Real> ( p.mX + u.mX,
						      		p.mY + u.mY,
						      		p.mZ + u.mZ )
				    );
		    
		};
		
		
		/*!@brief operator<<
		 * @details For debug
		 */
		friend inline std::ostream& operator<< (std::ostream & s, const Point3<Real>& p)
		{
			s << "Point3" << " x = " << p.x() << " ,y = " << p.y() << " ,z = " << p.z() << std::endl;
			
			
			return ( s );
		};
		/*!@fn squareDistance
		 * @details return the distance of two points
		 */		
		double squaredDistance ( const Point3<Real> p ) const 
		{
		    return ( pow ( p.x() - this->mX, 2) + 
		    		 pow ( p.y() - this->mY, 2) + 
		    		 pow ( p.z() - this->mZ, 2) );
		}
			
		virtual ~Point3(){};
		
	};

} /* CGL :: NAMESPACE */

#endif /*POINT3_HPP_*/
