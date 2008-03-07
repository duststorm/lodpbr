#ifndef EIGEN_HPP_
#define EIGEN_HPP_

#include <cassert>

#include <list>
#include <algorithm>
#include <cmath>

#include "Matrix3x3.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"


#define ms_dInv3 0.333333333
#define ms_dRoot3 1.732050808

namespace CGL
{
//----------------------------------------------------------------------------
template <class Real> class Eigen{

public:
	  Real m_afEigenvalue[3];
	  Vector3<Real> m_akEigenvector[3];

	  Matrix3x3<Real> mCovariance;
	  
	  Eigen()
	  		{
	  		
	           	         	
	  		}
	  
		Eigen(std::list<Point3<Real>* >& pPoint3List, const Point3<Real>& pMean)
		{
			covarianceMatrix (pPoint3List,pMean);
			//ComputeEigenSystem (mCovariance);
         	         	
		}
	  
	  void covarianceMatrix (std::list<Point3<Real>* >& pPoint3List, const Point3<Real>& pMean)
	  {

		  Real correlationXY = static_cast<Real> (0);
		  Real correlationXZ = static_cast<Real> (0); 
		  Real correlationYZ = static_cast<Real> (0);

		  Real correlationXX = static_cast<Real> (0);
		  Real correlationYY = static_cast<Real> (0);
		  Real correlationZZ = static_cast<Real> (0);

		  // Como é 1 e nao 1.0  o resultado é Zero
		  //Real N  = static_cast<Real> (1/  pPoint3List.size() );

		  Real N  = static_cast<Real> (1.0 / pPoint3List.size());


		  typedef typename std::list<Point3<Real>* >::iterator ListIterator;

		  for (ListIterator it = pPoint3List.begin(); it != pPoint3List.end() ; ++it)
		  {
			  correlationXX += ( ((*it)->x() - pMean.x()) * ((*it)->x() - pMean.x()) ); 
			  correlationYY += ( ((*it)->y() - pMean.y()) * ((*it)->y() - pMean.y()) );
			  correlationZZ += ( ((*it)->z() - pMean.z()) * ((*it)->z() - pMean.z()) );

			  correlationXY += ( ((*it)->x() - pMean.x()) * ((*it)->y() - pMean.y()) );
			  correlationXZ += ( ((*it)->x() - pMean.x()) * ((*it)->z() - pMean.z()) );
			  correlationYZ += ( ((*it)->y() - pMean.y()) * ((*it)->z() - pMean.z()) );

		  }


		  mCovariance = Matrix3x3<Real>(  (N*correlationXX), (N*correlationXY) , (N*correlationXZ),
				  (N*correlationXY), (N*correlationYY) , (N*correlationYZ),
				  (N*correlationXZ), (N*correlationYZ) , (N*correlationZZ) );	
	  }

	  
	void  ComputeEigenSystem (const Matrix3x3<Real>& rkA)
	{
		// Scale the matrix so its entries are in [-1,1].  The scaling is applied
		// only when at least one matrix entry has magnitude larger than 1.
		Matrix3x3<Real> kAScaled = rkA;
		Real* afAScaledEntry = (Real*)kAScaled;
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
		m_afEigenvalue[0] = (Real)adRoot[0];
		m_afEigenvalue[1] = (Real)adRoot[1];
		m_afEigenvalue[2] = (Real)adRoot[2];

		Real afMax[3];
		Vector3<Real> akMaxRow[3];
		for (i = 0; i < 3; i++)
		{
			Matrix3x3<Real> kM = kAScaled;
			kM[0][0] -= m_afEigenvalue[i];
			kM[1][1] -= m_afEigenvalue[i];
			kM[2][2] -= m_afEigenvalue[i];
			if (!PositiveRank(kM,afMax[i],akMaxRow[i]))
			{
				// Rescale back to the original size.
				if (fMax > (Real)1)
				{
					for (int j = 0; j < 3; j++)
					{
						m_afEigenvalue[j] *= fMax;
					}
				}

				m_akEigenvector[0] = Vector3<Real>(1.0,0.0,0.0);
				m_akEigenvector[1] = Vector3<Real>(0.0,1.0,0.0);
				m_akEigenvector[2] = Vector3<Real>(0.0,0.0,1.0);
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
				m_afEigenvalue[i] *= fMax;
			}
		}
	}
	//----------------------------------------------------------------------------

	~Eigen ()
	{
	};
	//----------------------------------------------------------------------------

	const Real GetEigenvalue (int i) const
	{
		assert(0 <= i && i < 3);
		return m_afEigenvalue[i];
	}
	//----------------------------------------------------------------------------

	const Real* GetEigenvalues () const
	{
		return m_afEigenvalue;
	}
	//----------------------------------------------------------------------------

	const Vector3<Real>& GetEigenvector (int i) const
	{
		assert(0 <= i && i < 3);
		return m_akEigenvector[i];
	}
	//----------------------------------------------------------------------------

	const Vector3<Real>* GetEigenvectors () const
	{
		return m_akEigenvector;
	}
	//----------------------------------------------------------------------------

	void ComputeRoots (const Matrix3x3<Real>& rkA,
			Real adRoot[3])
	{
		// Convert the unique matrix entries to Real precision.
		Real dA00 = (Real)rkA[0][0];
		Real dA01 = (Real)rkA[0][1];
		Real dA02 = (Real)rkA[0][2];
		Real dA11 = (Real)rkA[1][1];
		Real dA12 = (Real)rkA[1][2];
		Real dA22 = (Real)rkA[2][2];

		// The characteristic equation is x^3 - c2*x^2 + c1*x - c0 = 0.  The
		// eigenvalues are the roots to this equation, all guaranteed to be
		// real-valued, because the matrix is symmetric.
		Real dC0 = dA00*dA11*dA22 + 2.0*dA01*dA02*dA12 - dA00*dA12*dA12 -
		dA11*dA02*dA02 - dA22*dA01*dA01;

		Real dC1 = dA00*dA11 - dA01*dA01 + dA00*dA22 - dA02*dA02 +
		dA11*dA22 - dA12*dA12;

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

	bool PositiveRank (Matrix3x3<Real>& rkM,
			Real& rfMax, Vector3<Real>& rkMaxRow) const
			{
		// Locate the maximum-magnitude entry of the matrix.
		rfMax = (Real)-1;
		int iRow, iCol, iMaxRow = -1;
		for (iRow = 0; iRow < 3; iRow++)
		{
			for (iCol = iRow; iCol < 3; iCol++)
			{
				Real fAbs = fabs(rkM[iRow][iCol]);
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

		return rfMax >=1e-06f;
			}
	//----------------------------------------------------------------------------

	void ComputeVectors (const Matrix3x3<Real>& rkA,
			Vector3<Real>& rkU2, int i0, int i1, int i2)
	{
		Vector3<Real> kU0, kU1;
		GenerateComplementBasis (kU0,kU1,rkU2);

		// V[i2] = c0*U0 + c1*U1,  c0^2 + c1^2=1
		// e2*V[i2] = c0*A*U0 + c1*A*U1
		// e2*c0 = c0*U0.Dot(A*U0) + c1*U0.Dot(A*U1) = d00*c0 + d01*c1
		// e2*c1 = c0*U1.Dot(A*U0) + c1*U1.Dot(A*U1) = d01*c0 + d11*c1
		Vector3<Real> kTmp = rkA*kU0;
		Real fP00 = m_afEigenvalue[i2] - (kU0 * (kTmp));
		Real fP01 = kU1 *(kTmp);
		Real fP11 = m_afEigenvalue[i2] - (kU1 * (rkA*kU1));
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
				m_akEigenvector[i2] = fP01*kU0 + fP00*kU1;
			}
			else
			{
				fInvLength = 1/sqrt(fP11*fP11 + fP01*fP01);
				fP11 *= fInvLength;
				fP01 *= fInvLength;
				m_akEigenvector[i2] = fP11*kU0 + fP01*kU1;
			}
		}
		else
		{
			if (iRow == 0)
			{
				m_akEigenvector[i2] = kU1;
			}
			else
			{
				m_akEigenvector[i2] = kU0;
			}
		}

		// V[i0] = c0*U2 + c1*Cross(U2,V[i2]) = c0*R + c1*S
		// e0*V[i0] = c0*A*R + c1*A*S
		// e0*c0 = c0*R.Dot(A*R) + c1*R.Dot(A*S) = d00*c0 + d01*c1
		// e0*c1 = c0*S.Dot(A*R) + c1*S.Dot(A*S) = d01*c0 + d11*c1
		Vector3<Real> kS = rkU2 ^ (m_akEigenvector[i2]);
		kTmp = rkA*rkU2;
		fP00 = m_afEigenvalue[i0] - rkU2 * (kTmp);
		fP01 = kS * (kTmp);
		fP11 = m_afEigenvalue[i0] - kS * (rkA*kS);
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

		if (fMax >= 1e-06f)
		{
			if (iRow == 0)
			{
				fInvLength = 1/sqrt(fP00*fP00 + fP01*fP01);
				fP00 *= fInvLength;
				fP01 *= fInvLength;
				m_akEigenvector[i0] = fP01*rkU2 + fP00*kS;
			}
			else
			{
				fInvLength = 1/sqrt(fP11*fP11 + fP01*fP01);
				fP11 *= fInvLength;
				fP01 *= fInvLength;
				m_akEigenvector[i0] = fP11*rkU2 + fP01*kS;
			}
		}
		else
		{
			if (iRow == 0)
			{
				m_akEigenvector[i0] = kS;
			}
			else
			{
				m_akEigenvector[i0] = rkU2;
			}
		}

		// V[i1] = Cross(V[i2],V[i0])
		m_akEigenvector[i1] = m_akEigenvector[i2] ^ (m_akEigenvector[i0]);
	}

	void GenerateComplementBasis (Vector3<Real>& rkU, Vector3<Real>& rkV, const Vector3<Real>& rkW)
	{
	    Real fInvLength;

	    if (fabs(rkW[0]) >=
	        fabs(rkW[1]) )
	    {
	        // W.x or W.z is the largest magnitude component, swap them
	        fInvLength = 1/sqrt(rkW[0]*rkW[0] +
	            rkW[2]*rkW[2]);
	        rkU[0] = -rkW[2]*fInvLength;
	        rkU[1] = (Real)0.0;
	        rkU[2] = +rkW[0]*fInvLength;
	        rkV[0] = rkW[1]*rkU[2];
	        rkV[1] = rkW[2]*rkU[0] -
	            rkW[0]*rkU[2];
	        rkV[2] = -rkW[1]*rkU[0];
	    }
	    else
	    {
	        // W.y or W.z is the largest magnitude component, swap them
	        fInvLength = 1/sqrt(rkW[1]*rkW[1] +
	            rkW[2]*rkW[2]);
	        rkU[0] = (Real)0.0;
	        rkU[1] = +rkW[2]*fInvLength;
	        rkU[2] = -rkW[1]*fInvLength;
	        rkV[0] = rkW[1]*rkU[2] -
	            rkW[2]*rkU[1];
	        rkV[1] = -rkW[0]*rkU[2];
	        rkV[2] = rkW[0]*rkU[1];
	    }
	}
	
	
};
}

#endif /*EIGEN_HPP_*/
