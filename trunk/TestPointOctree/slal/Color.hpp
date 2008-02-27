#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <iostream>

#include "Point3.hpp"
#include "Vector3.hpp"

namespace CGL
{

/*!
*@class Color.
*@brief Class that represent a RGB model of Color.
*@details coming soon , but ... coming soon ... coming soon yet ... wait man !!! ¬¬.
*@author Felipe Moura.
*@version 1.0.
*@date 27-Feb-2008.
*@todo OpenGL interface and a C style array.
*@todo Anather model of color representation like HLS  
*/	

	template <class Real> class Color
	{
		
		public:
			
			friend class Point3<Real>;
			friend class Vector3<Real>;
			
			Color()
			{
				this->mRed   = static_cast< Real > (0);
				this->mGreen = static_cast< Real > (0);
				this->mBlue  = static_cast< Real > (0);
				this->mAlfa  = static_cast< Real > (1);
			};
			
			Color(const Real&pRed,const Real&pGreen, const Real&pBlue)
				: mRed(pRed), mGreen(pGreen), mBlue(pBlue), mAlfa(0) {};
				
			Color(const Real&pRed, const Real&pGreen, const Real& pBlue, const Real& pAlfa)
				: mRed(pRed), mGreen(pGreen), mBlue(pBlue), mAlfa(pAlfa) {};
				
			Color (const Point3<Real>& pPoint )
				: mRed(pPoint.mX), mGreen(pPoint.mY), mBlue(pPoint.mZ), mAlfa(0) {};
				
			Color (const Vector3<Real>& pVector )
				: mRed(pVector.mX), mGreen(pVector.mY), mBlue(pVector.mZ), mAlfa(0) {};
			
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
			inline void setRed ( const Real& pRed) 
			{
		    	this->mRed   = pRed;
			};

			/*!@brief Initialize Green color.
			*  @param[in] g Real.
			*/
			inline void setGreen ( const Real& pGreen)
			{
		    	this->mGreen = pGreen;
			};

			/*!@brief Initialize Blue color.
			*  @param[in] b Real.
			*/		
			inline void setBlue ( const Real& pBlue)
			{
		    	this->mBlue  = pBlue;
			};
			
			/*!@brief Initialize Alfa atribute.
			*  @param[in] b Real.
			*/		
			inline void setAlfa ( const Real& pAlfa)
			{
		    	this->mAlfa  = pAlfa;
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
						      << "        Out of ranger. " 			<< std::endl
						      << "        Accepts, 0 , 1 , 2 only." << std::endl;
					exit(1);
				}
				
			    return (mRGB[i]);
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
						      << "        Out of ranger. " 			<< std::endl
						      << "        Accepts, 0 , 1 , 2 only." << std::endl;
					exit(1);
				}
				  
			    return (mRGB[i]);
			};
				
			/*!@brief operator=
			 * @details Assigment operator
			 * @return Point3
			 */
			inline Color<Real>& operator= ( const Color<Real>& pColor)
			{
				this->mRed   = pColor.mRed;
				this->mGreen = pColor.mGreen;
				this->mBlue  = pColor.mBlue;
				this->mAlfa  = pColor.mAlfa;
					
				return ( *this );
			};
			
			
			/*!@brief operator==
			 * @details Two points are identical whether your correspondents abscissa are equal.
			 * @return bool.
			 */
			inline bool operator== ( const Color<Real>& pColor) const
			{
				return ( ( this->mRed   == pColor.mRed   ) and 
						 ( this->mGreen == pColor.mGreen ) and 
						 ( this->mBlue  == pColor.mBlue  ) );
			};	
			/*!@brief operator!=
			 * @details Opposite to the operator==
			 * @see operator==
			 * @return bool.
			 */
			inline bool operator!= ( const Color<Real>& pColor) const
			{
				return  !(*this == pColor) ;
			};	

			
			/*!@brief operator<<
			 * @details For debug
			 */
			friend inline std::ostream& operator<< (std::ostream & s, const Color<Real>& pColor)
			{
				s << "Color" << " Red = "    << pColor.mRed 
							 << " ,Green = " << pColor.mGreen 
							 << " ,Blue = "  << pColor.mBlue << std::endl;
				
				
				return ( s );
			};
			
			virtual ~Color(){};
		
		private:
			
			union
			{
				struct
				{	
					Real mRed;   /*!< Red color atribute.   */  
					Real mGreen; /*!< Green color atribute. */
					Real mBlue;  /*!< Blue color atribute.  */
					Real mAlfa ; /*!< Alfa color atribute.  */
				};
				
				Real mRGB[4];/*!< Array of color atributes.*/
			};
			
	};

}/* CGL::NAMESPACE */

#endif /*COLOR_HPP_*/
