#ifndef POLYNOMIAL_HPP_
#define POLYNOMIAL_HPP_

#include <cassert>

#include <cmath>

#include "Matrix3x3.hpp"
#include "Vector3.hpp"

#define PI 			3.14159265358979323846264338
#define ms_dInv3 	0.333333333
#define ms_dRoot3 	1.732050808


namespace CGL
{
 // 2x3   - 4x2   - 22x + 24 = 0  3 raizes diferentes
 // 3x3   - 10x2   + 14x + 27 = 0 1 raiz real
 // x3   + 6x2   + 12x + 8 = 0 3 raizes reais e iguais


	template <class Real> class CubicEquation
	{
	private:
		
	    	    
	public:
		
		Real 			mEigenvalue[3];
		Vector3<Real> 	mEigenvector[3];			
			
		static const int	None							= 0;
		static const int 	HasThreeRealRoots 			= 1;
		static const int	HasAllRealRootsAndEqual 	= 2;
		static const int	HasOnlyOneRealRoot 			= 3;
		
	
		CubicEquation(const Matrix3x3<Real>& rkA)
		{
			Matrix3x3<Real> kM = rkA;
			
		    double adRoot[3];
		    ComputeRoots(kM,adRoot);
		    
		    double b[3] = {0.0,0.0,1.0};
		    
		    mEigenvalue[0] = adRoot[0];
		    mEigenvalue[1] = adRoot[1];
		    mEigenvalue[2] = adRoot[2];
			
			std::cout << mEigenvalue[0] << std::endl;
			std::cout << mEigenvalue[1] << std::endl;
			std::cout << mEigenvalue[2] << std::endl;
		    
		    
		    for (int i = 0; i < 3 ; ++i)
		    {
		    	double result[3];
		    	
		    	Matrix3x3<Real> kM = rkA;
		    	        	
		    	kM(0,0) -= mEigenvalue[i];
		    	kM(1,1) -= mEigenvalue[i];
		    	kM(2,2) -= mEigenvalue[i];
		    	
		    	std::cout << kM << std::endl;
		    	
		    	if ( Solve3(kM,b,result) ){
		    		std::cout << "resolveu  " <<result[0]<< std::endl;
		    		mEigenvector[i] = Vector3<Real> (result[0],result[1],result[2]);
		    	}
		    	    	
		    	
		    }
	        

#if 0
			// Scale the matrix so its entries are in [-1,1].  The scaling is applied
			    // only when at least one matrix entry has magnitude larger than 1.
				Matrix3x3<Real> kAScaled = rkA;
			    Real* afAScaledEntry = kAScaled.getArray();
			    Real fMax = fabs(afAScaledEntry[0]);
			    Real fAbs = fabs(afAScaledEntry[1]);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			    }
			    fAbs = fabs(afAScaledEntry[2]);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			    }
			    fAbs = fabs(afAScaledEntry[4]);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			    }
			    fAbs = fabs(afAScaledEntry[5]);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			    }
			    fAbs = fabs(afAScaledEntry[8]);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			    }

			    int i;
			    if (fMax > (Real)1)
			    {
			        Real fInvMax = ((Real)1)/fMax;
			        for (i = 0; i < 9; i++)
			        {
			            afAScaledEntry[i] *= fInvMax;
			        }
			    }

			    // Compute the eigenvalues using double-precision arithmetic.
			    double adRoot[3];
			    ComputeRoots(kAScaled,adRoot);
			    mEigenvalue[0] = adRoot[0];
			    mEigenvalue[1] = adRoot[1];
			    mEigenvalue[2] = adRoot[2];

			    Real afMax[3];
			    Vector3<Real> akMaxRow[3];
			    for (i = 0; i < 3; i++)
			    {
			        Matrix3x3<Real> kM = kAScaled;
			        kM(0,0) -= mEigenvalue[i];
			        kM(1,1) -= mEigenvalue[i];
			        kM(2,2) -= mEigenvalue[i];
			        if (!PositiveRank(kM,afMax[i],akMaxRow[i]))
			        {
			            // Rescale back to the original size.
			            if (fMax > 1.0)
			            {
			                for (int j = 0; j < 3; j++)
			                {
			                    mEigenvalue[j] *= fMax;
			                }
			            }

			            mEigenvector[0] = Vector3<Real>(1,0,0);
			            mEigenvector[1] = Vector3<Real>(0,1,0);
			            mEigenvector[2] = Vector3<Real>(0,0,1);
			            return;
			        }
			    }

			    Real fTotalMax = afMax[0];
			    i = 0;
			    if (afMax[1] > fTotalMax)
			    {
			        fTotalMax = afMax[1];
			        i = 1;
			    }
			    if (afMax[2] > fTotalMax)
			    {
			        i = 2;
			    }

			    if (i == 0)
			    {
			        akMaxRow[0].normalize();
			        ComputeVectors(kAScaled,akMaxRow[0],1,2,0);
			    }
			    else if (i == 1)
			    {
			        akMaxRow[1].normalize();
			        ComputeVectors(kAScaled,akMaxRow[1],2,0,1);
			    }
			    else
			    {
			        akMaxRow[2].normalize();
			        ComputeVectors(kAScaled,akMaxRow[2],0,1,2);
			    }

			    // Rescale back to the original size.
			    if (fMax > (Real)1)
			    {
			        for (i = 0; i < 3; i++)
			        {
			            mEigenvalue[i] *= fMax;
			        }
			    }
#endif
		}
		
		
		bool Solve3 (const Matrix3x3<Real>& aafA, const Real afB[3],Real afX[3])
		{
		    Real aafAInv[3][3];
		    
		    aafAInv[0][0] = aafA(1,1)*aafA(2,2)-aafA(1,2)*aafA(2,1);
		    aafAInv[0][1] = aafA(0,2)*aafA(2,1)-aafA(0,1)*aafA(2,2);
		    aafAInv[0][2] = aafA(0,1)*aafA(1,2)-aafA(0,2)*aafA(1,1);
		    aafAInv[1][0] = aafA(1,2)*aafA(2,0)-aafA(1,0)*aafA(2,2);
		    aafAInv[1][1] = aafA(0,0)*aafA(2,2)-aafA(0,2)*aafA(2,0);
		    aafAInv[1][2] = aafA(0,2)*aafA(1,0)-aafA(0,0)*aafA(1,2);
		    aafAInv[2][0] = aafA(1,0)*aafA(2,1)-aafA(1,1)*aafA(2,0);
		    aafAInv[2][1] = aafA(0,1)*aafA(2,0)-aafA(0,0)*aafA(2,1);
		    aafAInv[2][2] = aafA(0,0)*aafA(1,1)-aafA(0,1)*aafA(1,0);
		    Real fDet = aafA(0,0)*aafAInv[0][0] + aafA(0,1)*aafAInv[1][0] +
		        aafA(0,2)*aafAInv[2][0];

		    if ( fabs(fDet) < 0.00001)
		    {
		    	std::cout << "Mas Por que " << fabs(fDet) << std::endl;
		        return false;
		    }

		    Real fInvDet = ((Real)1.0)/fDet;
		    for (int iRow = 0; iRow < 3; iRow++)
		    {
		        for (int iCol = 0; iCol < 3; iCol++)
		        {
		            aafAInv[iRow][iCol] *= fInvDet;
		        }
		    }

		    afX[0] = aafAInv[0][0]*afB[0]+aafAInv[0][1]*afB[1]+aafAInv[0][2]*afB[2];
		    afX[1] = aafAInv[1][0]*afB[0]+aafAInv[1][1]*afB[1]+aafAInv[1][2]*afB[2];
		    afX[2] = aafAInv[2][0]*afB[0]+aafAInv[2][1]*afB[1]+aafAInv[2][2]*afB[2];
		    return true;
		}
		
		//----------------------------------------------------------------------------

		static void ComputeRoots (const Matrix3x3<Real>& rkA,double adRoot[3])
		{
		    // Convert the unique matrix entries to double precision.
		    Real dA00 = rkA(0,0);
		    Real dA01 = rkA(0,1);
		    Real dA02 = rkA(0,2);
		    Real dA11 = rkA(1,1);
		    Real dA12 = rkA(1,2);
		    Real dA22 = rkA(2,2);

		    // The characteristic equation is x^3 - c2*x^2 + c1*x - c0 = 0.  The
		    // eigenvalues are the roots to this equation, all guaranteed to be
		    // real-valued, because the matrix is symmetric.
		    Real dC0 = dA00 * dA11 * dA22 + 
		                2.0 * dA01 * dA02 * dA12 - 
		               dA00 * dA12 * dA12 -
		        	   dA11 * dA02 * dA02 - 
		        	   dA22 * dA01 * dA01;

		    Real dC1 =  dA00 * dA11 - 
		    			dA01 * dA01 + 
		    			dA00 * dA22 - 
		    			dA02 * dA02 +
		    			dA11 * dA22 - 
		    			dA12 * dA12;

		    Real dC2 = dA00 + dA11 + dA22;

		    // Construct the parameters used in classifying the roots of the equation
		    // and in solving the equation for the roots in closed form.
		    Real dC2Div3 = dC2*ms_dInv3;
		    Real dADiv3 = (dC1 - dC2*dC2Div3)*ms_dInv3;
		    
		    if (dADiv3 > 0.0)
		    {
		        dADiv3 = 0.0;
		    }

		    Real dMBDiv2 = 0.5*(dC0 + dC2Div3*(2.0*dC2Div3*dC2Div3 - dC1));

		    Real dQ = dMBDiv2*dMBDiv2 + dADiv3*dADiv3*dADiv3;
		    if (dQ > 0.0)
		    {
		        dQ = 0.0;
		    }

		    // Compute the eigenvalues by solving for the roots of the polynomial.
		    Real dMagnitude = sqrt(-dADiv3);
		    Real dAngle = atan2(sqrt(-dQ),dMBDiv2)*ms_dInv3;
		    Real dCos = cos(dAngle);
		    Real dSin = sin(dAngle);
		    Real dRoot0 = dC2Div3 + 2.0*dMagnitude*dCos;
		    Real dRoot1 = dC2Div3 - dMagnitude*(dCos + ms_dRoot3*dSin);
		    Real dRoot2 = dC2Div3 - dMagnitude*(dCos - ms_dRoot3*dSin);

		    // Sort in increasing order.
		    if (dRoot1 >= dRoot0)
		    {
		        adRoot[0] = dRoot0;
		        adRoot[1] = dRoot1;
		    }
		    else
		    {
		        adRoot[0] = dRoot1;
		        adRoot[1] = dRoot0;
		    }

		    if (dRoot2 >= adRoot[1])
		    {
		        adRoot[2] = dRoot2;
		    }
		    else
		    {
		        adRoot[2] = adRoot[1];
		        if (dRoot2 >= adRoot[0])
		        {
		            adRoot[1] = dRoot2;
		        }
		        else
		        {
		            adRoot[1] = adRoot[0];
		            adRoot[0] = dRoot2;
		        }
		    }
		}
		//----------------------------------------------------------------------------
		bool PositiveRank (Matrix3x3<Real>& rkM,Real& rfMax, Vector3<Real>& rkMaxRow) const
		{
		    // Locate the maximum-magnitude entry of the matrix.
		    rfMax = -1.0;
		    int iRow, iCol, iMaxRow = -1;
		    for (iRow = 0; iRow < 3; iRow++)
		    {
		        for (iCol = iRow; iCol < 3; iCol++)
		        {
		            Real fAbs = fabs(rkM(iRow,iCol));
		            if (fAbs > rfMax)
		            {
		                rfMax = fAbs;
		                iMaxRow = iRow;
		            }
		        }
		    }

		    // Return the row containing the maximum, to be used for eigenvector
		    // construction.
		    rkMaxRow = rkM.row(iMaxRow);

		    return rfMax >= 1e-06f;
		}
		
		
		void ComputeVectors (const Matrix3x3<Real>& rkA, Vector3<Real>& rkU2, int i0, int i1, int i2)
		{
			 Vector3<Real> kU0, kU1;
			 GenerateComplementBasis (kU0,kU1,rkU2);

			    // V[i2] = c0*U0 + c1*U1,  c0^2 + c1^2=1
			    // e2*V[i2] = c0*A*U0 + c1*A*U1
			    // e2*c0 = c0*U0.Dot(A*U0) + c1*U0.Dot(A*U1) = d00*c0 + d01*c1
			    // e2*c1 = c0*U1.Dot(A*U0) + c1*U1.Dot(A*U1) = d01*c0 + d11*c1
			    Vector3<Real> kTmp = rkA*kU0;
			    Real fP00 = mEigenvalue[i2] - (kU0 * (kTmp));
			    Real fP01 = kU1 * kTmp;
			    Real fP11 = mEigenvalue[i2] - (kU1*(rkA*kU1));
			    Real fInvLength;
			    Real fMax = fabs(fP00);
			    int iRow = 0;
			    Real fAbs = fabs(fP01);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			    }
			    fAbs = fabs(fP11);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			        iRow = 1;
			    }

			    if (fMax >= 1e-06f)
			    {
			        if (iRow == 0)
			        {
			            fInvLength = 1/sqrt(fP00*fP00 + fP01*fP01);
			            fP00 *= fInvLength;
			            fP01 *= fInvLength;
			            mEigenvector[i2] = fP01*kU0 + fP00*kU1;
			        }
			        else
			        {
			            fInvLength = 1/sqrt(fP11*fP11 + fP01*fP01);
			            fP11 *= fInvLength;
			            fP01 *= fInvLength;
			            mEigenvector[i2] = fP11*kU0 + fP01*kU1;
			        }
			    }
			    else
			    {
			        if (iRow == 0)
			        {
			            mEigenvector[i2] = kU1;
			        }
			        else
			        {
			            mEigenvector[i2] = kU0;
			        }
			    }

			    // V[i0] = c0*U2 + c1*Cross(U2,V[i2]) = c0*R + c1*S
			    // e0*V[i0] = c0*A*R + c1*A*S
			    // e0*c0 = c0*R.Dot(A*R) + c1*R.Dot(A*S) = d00*c0 + d01*c1
			    // e0*c1 = c0*S.Dot(A*R) + c1*S.Dot(A*S) = d01*c0 + d11*c1
			    Vector3<Real> kS = rkU2 ^ mEigenvector[i2];
			    kTmp = rkA*rkU2;
			    fP00 = mEigenvalue[i0] - (rkU2*(kTmp));
			    fP01 = kS * kTmp;
			    fP11 = mEigenvalue[i0] - (kS * (rkA*kS));
			    fMax = fabs(fP00);
			    iRow = 0;
			    fAbs = fabs(fP01);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			    }
			    fAbs = fabs(fP11);
			    if (fAbs > fMax)
			    {
			        fMax = fAbs;
			        iRow = 1;
			    }

			    if (fMax >=1e-06f)
			    {
			        if (iRow == 0)
			        {
			            fInvLength = 1/sqrt(fP00*fP00 + fP01*fP01);
			            fP00 *= fInvLength;
			            fP01 *= fInvLength;
			            mEigenvector[i0] = fP01*rkU2 + fP00*kS;
			        }
			        else
			        {
			            fInvLength = 1/sqrt(fP11*fP11 + fP01*fP01);
			            fP11 *= fInvLength;
			            fP01 *= fInvLength;
			            mEigenvector[i0] = fP11*rkU2 + fP01*kS;
			        }
			    }
			    else
			    {
			        if (iRow == 0)
			        {
			            mEigenvector[i0] = kS;
			        }
			        else
			        {
			            mEigenvector[i0] = rkU2;
			        }
			    }

			    // V[i1] = Cross(V[i2],V[i0])
			    mEigenvector[i1] = mEigenvector[i2] ^ mEigenvector[i0];
		    
		}//Computer Vectors
		
		void GenerateComplementBasis (Vector3<Real>& rkU, Vector3<Real>& rkV,const Vector3<Real>& rkW)
		{
		    Real fInvLength;

		    if ( (fabs(rkW[0])) >= ( fabs(rkW[1]) ) )
		    {
		        // W.x or W.z is the largest magnitude component, swap them
		        fInvLength = 1/sqrt(rkW[0]*rkW[0] + rkW[2]*rkW[2]);
		        rkU[0] = -rkW[2]*fInvLength;
		        rkU[1] = (Real)0.0;
		        rkU[2] = rkW[0]*fInvLength;
		        rkV[0] = rkW[1]*rkU[2];
		        rkV[1] = rkW[2]*rkU[0] - rkW[0]*rkU[2];
		        rkV[2] = -rkW[1]*rkU[0];
		    }
		    else
		    {
		        // W.y or W.z is the largest magnitude component, swap them
		        fInvLength = 1/sqrt(rkW[1]*rkW[1] + rkW[2]*rkW[2]);
		        rkU[0] = (Real)0.0;
		        rkU[1] =  rkW[2]*fInvLength;
		        rkU[2] = -rkW[1]*fInvLength;
		        rkV[0] =  rkW[1]*rkU[2] - rkW[2]*rkU[1];
		        rkV[1] = -rkW[0]*rkU[2];
		        rkV[2] =  rkW[0]*rkU[1];
		    }
		}// Complement Basis
		

	};

}/* CGL :: NAMESPACE */

#endif /*POLYNOMIAL_HPP_*/



// Calcular as raizes cubic do polinomio dado
/*static int findCubicRoots(	const Real& pA, 
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
	
	/* Three real roots 
	else if (h <= 0) 
	{
		Real theta = acos(R / sqrt(Qcubed));
		Real sqrtQ = sqrt(Q);
    
		roots[0] = -2 * sqrtQ * cos( theta           / 3) - a / 3;
		roots[1] = -2 * sqrtQ * cos((theta + 2 * PI) / 3) - a / 3;
		roots[2] = -2 * sqrtQ * cos((theta + 4 * PI) / 3) - a / 3;
    
		return  HasThreeRealRoots;
    
	}

	/* One real root 
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
	  
	  
}*/




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

