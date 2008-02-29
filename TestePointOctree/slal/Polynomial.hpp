#ifndef POLYNOMIAL_HPP_
#define POLYNOMIAL_HPP_

#include <cassert>

#include <cmath>

#define PI 3.14159265358979323846264338


namespace CGL
{
 // 2x3   - 4x2   - 22x + 24 = 0  3 raizes diferentes
 // 3x3   - 10x2   + 14x + 27 = 0 1 raiz real
 // x3   + 6x2   + 12x + 8 = 0 3 raizes reais e iguais


	template <class Real> class CubicEquation
	{
	
	public:
					
		CubicEquation(); 
		
		static const int	None							= 0;
		static const int 	HasThreeRealRoots 			= 1;
		static const int	HasAllRealRootsAndEqual 	= 2;
		static const int	HasOnlyOneRealRoot 			= 3;
				
		static int findCubicRoots(	const Real& pA, 
				  		   		  	const Real& pB, 
				  		   		  	const Real& pC,
				  		   		  	const Real& pD, Real roots[3])
		{
			
			Real a, b, c;
			assert (pA);			
			// Testar Algo para evitar Zero no parâmentro do pow
						
			Real f = (  (3.0*pC / pA ) - ( pow(pB,2.0) / pow(pA,2.0) ) ) / 3;
			Real g = (  (2*pow(pB,3.0) / pow(pA,3.0) ) - ( (9.0*pB*pC) / ( pow(pA,2.0) ) ) + (27.0*pD / pA) ) / 27.0;
			Real h = ( pow(g,2.0) / 4.0 ) + (pow(f,3.0) / 27.0 );

			a = pB / pA;
			b = pC / pA;
			c = pD / pA;

			Real Q = (a * a - 3 * b) / 9;
			Real R = (2 * a * a * a - 9 * a * b + 27 * c) / 54;
			Real Qcubed = Q * Q * Q;
			Real d = Qcubed - R * R;

		  
			if ( (h == 0) and (f == 0) and (g == 0) )
			{
				roots[0] = roots[1] = roots[2] = -pow((pD/pA),(1.0/3.0));
				return HasAllRealRootsAndEqual;
			}	
			
			/* Three real roots */
			else if (h <= 0) 
			{
				Real theta = acos(R / sqrt(Qcubed));
				Real sqrtQ = sqrt(Q);
		    
				roots[0] = -2 * sqrtQ * cos( theta           / 3) - a / 3;
				roots[1] = -2 * sqrtQ * cos((theta + 2 * PI) / 3) - a / 3;
				roots[2] = -2 * sqrtQ * cos((theta + 4 * PI) / 3) - a / 3;
		    
				return  HasThreeRealRoots;
		    
			}

			/* One real root */
			else if (h > 0)
			{
				Real e = pow(sqrt(-d) + fabs(R), 1. / 3.);
		    
				if (R > 0)
					e = -e;
		    
				roots[0] = (e + Q / e) - a / 3.;
		    
				return HasOnlyOneRealRoot;
		    
			}
		  
			else
			{
				std::cerr << "NEVER !!";
				return None;
			}
			  
			  
		}
		
			
	};

}/* CGL :: NAMESPACE */

#endif /*POLYNOMIAL_HPP_*/


/*int solver(Real * result)
{
	
	Real lF = 0;
	Real lG = 0;
	Real lH = 0;
	
	Real lI = 0;
	Real lJ = 0;
	Real lK = 0;
	Real lL = 0;
	Real lM = 0;
	Real lN = 0;
	Real lP = 0;
	

	else if ( lH <= 0)
	{
		
		lI = sqrt ( ( pow (lG,2.0) * 0.25 ) - lH );
		std::cout << "dentro LI " << lI << std::endl;
		lJ = pow (lI, (1.0/3.0) );
		std::cout << "dentro LJ " << lJ << std::endl;
		lK = acos ( -(lG / (2.0*lI) ) );
		std::cout << "dentro LK " << lK << std::endl;
		lL = -lJ; 
		std::cout << "dentro LL " << lL << std::endl;
		lM = cos( lK/3.0 );
		std::cout << "dentro LM" << lM << std::endl;
		lN = sqrt(3.0) * sin (lK/3.0);
		std::cout << "dentro LN " << lN << std::endl;
		lP = -( mB / (3.0*mA) );
		std::cout << "dentro LP " << lP << std::endl;
		
		result[0] = 2.0*lJ * cos( lK/3.0 ) - (mB/(3.0*mA));
		result[1] = lL * ( lM + lN ) + lP;
		result[2] = lL * ( lM - lN ) + lP;
		
		std::cout << "dentro " << result[0] << " " << result[1] << " " << result[2] << std::endl; 
		
		return Has_Three_Real_Roots;	
	}
		
	else if ( lH > 0)
	{
		lI = (-(lG*0.5)) + sqrt(lH);
		std::cout << "dentro LI " << lI << std::endl;
		lJ = pow (lI, (1.0/3.0));
		std::cout << "dentro LJ " << lJ << std::endl;
		lK = (-(lG*0.5)) - sqrt(lH);
		std::cout << "dentro LK " << lK << std::endl;
		lM = pow (lK, (1.0/3.0));
		std::cout << "dentro LM " << lM << std::endl;
		result[0] = (lJ + lM) - (mB/(3*mA));
		
		return Has_Only_One_Real_Root;
	}
	else
		std::cout << "NEVER" << std::endl;

}*/
