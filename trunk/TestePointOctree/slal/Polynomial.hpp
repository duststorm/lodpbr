#ifndef POLYNOMIAL_HPP_
#define POLYNOMIAL_HPP_

#include <cassert>

#include <cmath>

namespace CGL
{


	template <class Real> class CubicEquation
	{
	
	private:
		//Coeficientes
		Real mA;
		Real mB;
		Real mC;
		Real mD;
		
		Real mH;
		Real mG;
		Real mF;
		
		typedef enum TypeResult
		{
			Has_Three_Real_Roots,
			Has_All_Real_Roots_And_Equal,
			Has_Only_One_Real_Root
		};
		
		TypeResult solver()
		{
			
			mF = (  (3*mC / mA ) - ( pow(mB,2) / pow(mA,2) ) ) / 3;
			mG = (  (2*pow(mB,3) / pow(mA,3) ) - ( (9*mB*mC) / ( pow(mA,2) ) ) + (27*mD / mA) ) / 27;
			
			mH = ( pow(mG,2) / 4 ) + (pow(mF,3) / 27 );
			
			if ( mH <= 0)
				return Has_Three_Real_Roots;
			else if ( (mH == 0) and (mF == 0) and (mG == 0) )
				return Has_All_Real_Roots_And_Equal;
			else  
				return Has_Only_One_Real_Root;
		
		}
		
	public:
					
		CubicEquation(const Real& a, 
					  const Real& b, 
					  const Real& c,
					  const Real& d) : 	mA(a),mB(b),mC(c),mD(d)
		{
			
		};
		
		template <class C>
		CubicEquation(const C* pArray)
		{
			assert(pArray);
			
	    	mA = static_cast< Real > ( pArray[0] );
	    	mB = static_cast< Real > ( pArray[1] );
	    	mC = static_cast< Real > ( pArray[2] );
	    	mD = static_cast< Real > ( pArray[3] );
	    	
		}
		
		void merda ()
		{
			if (solver() == Has_Three_Real_Roots)
				std::cout << mH << std::endl;
		}
		
		virtual ~CubicEquation(){};
	};

}/* CGL :: NAMESPACE */

#endif /*POLYNOMIAL_HPP_*/
