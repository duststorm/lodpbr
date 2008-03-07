#ifndef POLYNOMIAL_HPP_
#define POLYNOMIAL_HPP_

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
 // 2x3   - 4x2   - 22x + 24 = 0  3 raizes diferentes
 // 3x3   - 10x2   + 14x + 27 = 0 1 raiz real
 // x3   + 6x2   + 12x + 8 = 0 3 raizes reais e iguais


	template <class Real> class CubicEquation
	{
	private:
		
	    	    
	public:
		
		Real 			mEigenvalue[3];
		Vector3<Real> 	mEigenvector[3];			
		Matrix3x3<Real> mCovariance; 
		
		static const int	None							= 0;
		static const int 	HasThreeRealRoots 			= 1;
		static const int	HasAllRealRootsAndEqual 	= 2;
		static const int	HasOnlyOneRealRoot 			= 3;
	
		
		CubicEquation()
		{
			
		}
		
		CubicEquation(const Matrix3x3<Real>& rkA)
		{
			
		}
		
		CubicEquation(std::list<Point3<Real>* >& pPoint3List, const Point3<Real>& pMean)
		{
			covarianceMatrix (pPoint3List,pMean);
           // Eigensolver (mCovariance, mEigenvalue, mEigenvector);
           	//eigen_decomposition();
           	
		}
		
		
		
		void QR (Matrix3x3<Real> A)
		{
			
			Vector3<Real> v1 (A.col(0));
			Vector3<Real> v2 (A.col(1));
			Vector3<Real> v3 (A.col(2));
			
			v2 = v2 - ((v1*v2) / (v1*v1))*v1;
			
			v3 = v3 - ((v3*v1) / (v1*v1))*v1  - ((v3*v2) / (v2*v2))*v2 ;
			
			std::cout << "v1 " << v1;
			std::cout << "v2 " << v2;
			std::cout << "v3 " << v3;
			
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

		    if (fabs(fDet) < 1e-06f)
		    {
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
			/* Eigen decomposition code for symmetric 3x3 matrices, copied from the public
		   domain Java Matrix library JAMA. */


		Real hypot2(Real x, Real y) 
		{
		  return sqrt(x*x+y*y);
		}

		// Symmetric Householder reduction to tridiagonal form.

		void eigen_decomposition() 
		{

			 Real e[3];
			 Real d[3];
			
			//  This is derived from the Algol procedures tred2 by
			//  Bowdler, Martin, Reinsch, and Wilkinson, Handbook for
			//  Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
			//  Fortran subroutine in EISPACK.

			d[0] = mCovariance[2][0];
			d[1] = mCovariance[2][1];
			d[2] = mCovariance[2][2];

			// Householder reduction to tridiagonal form.

			for (int i = 3-1; i > 0; i--) 
			{

				// Scale to avoid under/overflow.

				Real scale = 0.0;
				Real h 	   = 0.0;
				
				for (int k = 0; k < i; k++) 
				{
					scale = scale + fabs(d[k]);
				}
				
				if (scale == 0.0) 
				{

					e[i] = d[i-1];

					for (int j = 0; j < i; j++) 
					{
						d[j] = mCovariance[i-1][j];
						mCovariance[i][j] = 0.0;
						mCovariance[j][i] = 0.0;
					}

				}
				else
				{

					// Generate Householder vector.

					for (int k = 0; k < i; k++) 
					{
						d[k] /= scale;
						h += d[k] * d[k];
					}

					Real f = d[i-1];
					Real g = sqrt(h);

					if (f > 0) 
					{
						g = -g;
					}

					e[i] 	= scale * g;
					h 		= h - f * g;
					d[i-1] 	= f - g;

					for (int j = 0; j < i; j++) 
					{
						e[j] = 0.0;
					}

					// Apply similarity transformation to remaining columns.

					for (int j = 0; j < i; j++) 
					{

						f 		= d[j];
						mCovariance[j][i] = f;
						g 		= e[j] + mCovariance[j][j] * f;

						for (int k = j+1; k <= i-1; k++) 
						{
							g 	 += mCovariance[k][j] * d[k];
							e[k] += mCovariance[k][j] * f;
						}

						e[j] = g;
					}

					f = 0.0;
					for (int j = 0; j < i; j++) 
					{
						e[j] /= h;
						f 	 += e[j] * d[j];
					}
					Real hh = f / (h + h);
					for (int j = 0; j < i; j++) 
					{
						e[j] -= hh * d[j];
					}
					for (int j = 0; j < i; j++) 
					{
						f = d[j];
						g = e[j];
						for (int k = j; k <= i-1; k++) 
						{
							mCovariance[k][j] -= (f * e[k] + g * d[k]);
						}
						d[j] 	= mCovariance[i-1][j];
						mCovariance[i][j] = 0.0;
					}
				}

				d[i] = h;
			}

			// Accumulate transformations.

			for (int i = 0; i < 3-1; i++) 
			{
				mCovariance[3-1][i] = mCovariance[i][i];
				mCovariance[i][i] = 1.0;
				Real h = d[i+1];
				if (h != 0.0) {
					for (int k = 0; k <= i; k++) {
						d[k] = mCovariance[k][i+1] / h;
					}
					for (int j = 0; j <= i; j++) {
						Real g = 0.0;
						for (int k = 0; k <= i; k++) {
							g += mCovariance[k][i+1] * mCovariance[k][j];
						}
						for (int k = 0; k <= i; k++) {
							mCovariance[k][j] -= g * d[k];
						}
					}
				}
				for (int k = 0; k <= i; k++) {
					mCovariance[k][i+1] = 0.0;
				}
			}
			
			for (int j = 0; j < 3; j++) 
			{
				d[j] = mCovariance[3-1][j];
				mCovariance[3-1][j] = 0.0;
			}
			
			mCovariance[3-1][3-1] = 1.0;
			e[0] = 0.0;
		 

		// Symmetric tridiagonal QL algorithm.
		// Start QL algorithm	
		//static void tql2(Real V[3][3], Real d[3], Real e[3]) 
		
		//  This is derived from the Algol procedures tql2, by
		//  Bowdler, Martin, Reinsch, and Wilkinson, Handbook for
		//  Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
		//  Fortran subroutine in EISPACK.

			for (int i = 1; i < 3; i++) 
			{
				e[i-1] = e[i];
			}
			e[3-1] = 0.0;

			Real f = 0.0;
			Real tst1 = 0.0;
			Real eps = 0.00000001;
			for (int l = 0; l < 3; l++) {

				// Find small subdiagonal element

				tst1 = std::max( tst1, fabs( d[l]) + fabs(e[l] ) );
				int m = l;
				while (m < 3) 
				{
					if (fabs(e[m]) <= eps*tst1) 
					{
						break;
					}
					m++;
				}

				// If m == l, d[l] is an eigenvalue,
				// otherwise, iterate.

				if (m > l) {
					int iter = 0;
					do 
					{
						iter = iter + 1;  // (Could check iteration count here.)

						// Compute implicit shift

						Real g = d[l];
						Real p = (d[l+1] - g) / (2.0 * e[l]);
						Real r = hypot2(p,1.0);
						if (p < 0) {
							r = -r;
						}
						d[l] = e[l] / (p + r);
						d[l+1] = e[l] * (p + r);
						Real dl1 = d[l+1];
						Real h = g - d[l];
						for (int i = l+2; i < 3; i++) {
							d[i] -= h;
						}
						f = f + h;

						// Implicit QL transformation.

						p = d[m];
						Real c 	 = 1.0;
						Real c2  = c;
						Real c3  = c;
						Real el1 = e[l+1];
						Real s 	 = 0.0;
						Real s2  = 0.0;

						for (int i = m-1; i >= l; i--) 
						{
							c3 = c2;
							c2 = c;
							s2 = s;
							g = c * e[i];
							h = c * p;
							r = hypot2(p,e[i]);
							e[i+1] = s * r;
							s = e[i] / r;
							c = p / r;
							p = c * d[i] - s * g;
							d[i+1] = h + s * (c * g + s * d[i]);

							// Accumulate transformation.

							for (int k = 0; k < 3; k++) 
							{
								h = mCovariance[k][i+1];
								mCovariance[k][i+1] = s * mCovariance[k][i] + c * h;
								mCovariance[k][i] = c * mCovariance[k][i] - s * h;
							}
						}
						p = -s * s2 * c3 * el1 * e[l] / dl1;
						e[l] = s * p;
						d[l] = c * p;

						// Check for convergence.

					} while (fabs(e[l]) > eps*tst1);
				}
				d[l] = d[l] + f;
				e[l] = 0.0;
			}

			// Sort eigenvalues and corresponding vectors.

			for (int i = 0; i < 3-1; i++) 
			{
				int k = i;
				Real p = d[i];
				for (int j = i+1; j < 3; j++) 
				{
					if (d[j] < p) 
					{
						k = j;
						p = d[j];
					}
				}
				if (k != i) 
				{
					d[k] = d[i];
					d[i] = p;
					for (int j = 0; j < 3; j++) 
					{
						p = mCovariance[j][i];
						mCovariance[j][i] = mCovariance[j][k];
						mCovariance[j][k] = p;
					}
				}
			}
			mEigenvalue[0] = d[0];
			mEigenvalue[1] = d[1];
			mEigenvalue[2] = d[2];
			
			mEigenvector[0] = mCovariance.col(0);
			mEigenvector[1] = mCovariance.col(1);
			mEigenvector[2] = mCovariance.col(2);
		}
	
		void Eigensolver (Matrix3x3<Real> A, Real * evalue, Vector3<Real> * evector)
		{
		    Real root[3];
		    ComputeRoots(A,root);
	    
		    evalue[0] = root[0];
		    evalue[1] = root[1];
		    evalue[2] = root[2];
		    
		    Matrix3x3<Real> M0 = A - evalue[0]*M0.identity(); // I is the identity matrix
		    int rank0 = ComputeRank(M0);
		    if (rank0 == 0)
		    {
		        // evalue[0] = evalue[1] = evalue[2]
		        evector[0] = Vector3<Real>(1,0,0);
		        evector[1] = Vector3<Real>(0,1,0);
		        evector[2] = Vector3<Real>(0,0,1);
		        return;
		    }
		    if (rank0 == 1)
		    {
		        // evalue[0] = evalue[1] < evalue[2]
		        GetComplement2(M0.row(0),evector[0],evector[1]);
		        evector[2] = (evector[0] ^  evector[1]);
		        return;
		    }
		    // rank0 == 2
		    GetComplement1(M0.row(0),M0.row(1),evector[0]);
		    Matrix3x3<Real> M1 = A - evalue[1]*M1.identity();
		    int rank1 = ComputeRank(M1); // zero rank detected earlier, rank1 must be positive
		    if (rank1 == 1)
		    {
		        // evalue[0] < evalue[1] = evalue[2]
		        GetComplement2(evector[0],evector[1],evector[2]);
		        return;
		    }
		    // rank1 == 2
		    GetComplement1(M1.row(0),M1.row(1),evector[1]);
		    // rank2 == 2 (eigenvalues must be distinct at this point, rank2 must be 2)
		    evector[2] = (evector[0] ^ evector[1]);
		}

		
		void GetComplement1 (Vector3<Real> U, Vector3<Real> V, Vector3<Real>& W)
		{
		    W = (U ^ V);
		    W.normalize();
		}

		void GetComplement2 (Vector3<Real> U, Vector3<Real>& V, Vector3<Real>& W)
		{
		    U.normalize();
		    if (fabs(U[0]) >= fabs(U[1]))
		    {
		         Real invLength = 1/sqrt(U[0]*U[0] + U[2]*U[2]);
		         V[0] = -U[2]*invLength;
		         V[1] = 0;
		         V[2] = U[0]*invLength;
		         W[0] = U[1]*V[2];
		         W[1] = U[2]*V[0] - U[0]*V[2];
		         W[2] = -U[1]*V[0];
		    }
		    else
		    {
		         Real invLength = 1/sqrt(U[1]*U[1] + U[2]*U[2]);
		         V[0] = 0;
		         V[1] = U[2]*invLength;
		         V[2] = -U[1]*invLength;
		         W[0] = U[1]*V[2] - U[2]*V[1];
		         W[1] = -U[0]*V[2];
		         W[2] = U[0]*V[1];
		    }
		}

		void ComputeRoots (const Matrix3x3<Real>& rkA, Real adRoot[3])
		{
		    // Convert the unique matrix entries to double precision.
		    Real dA00 = static_cast<Real> (rkA[0][0]);
		    Real dA01 = static_cast<Real> (rkA[0][1]);
		    Real dA02 = static_cast<Real> (rkA[0][2]);
		    Real dA11 = static_cast<Real> (rkA[1][1]);
		    Real dA12 = static_cast<Real> (rkA[1][2]);
		    Real dA22 = static_cast<Real> (rkA[2][2]);

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

	
		int ComputeRank (Matrix3x3<Real>& M)
			{
				// Compute the maximum magnitude matrix entry.
				Real abs, save; 
				Real max = -1;
				int row, col, maxRow = -1, maxCol = -1;
				for (row = 0; row < 3; row++)
				{
					for (col = row; col < 3; col++)
					{
						
						abs = fabs (M[row][col]);
						if (abs > max)
						{
							max = abs;
							maxRow = row;
							maxCol = col;
						}
					}
				}
				if (max == 0)
				{
					// The rank is 0.  The eigenvalue has multiplicity 3.
					return 0;
				}
				// The rank is at least 1. Swap the row containing the maximum-magnitude
				// entry with row 0.
				if (maxRow != 0)
				{
					for (col = 0; col < 3; col++)
					{
						save = M[0][col];
						M[0][col] = M[maxRow][col];
						M[maxRow][col] = save;
					}
				}
				// Row-reduce the matrix...
				// Scale the row containing the maximum to generate a 1-valued pivot.
				Real invMax = 1/M[maxRow][maxCol];
				M[0][0] *= invMax;
				M[0][1] *= invMax;
				M[0][2] *= invMax;
				// Eliminate the maxCol column entries in rows 1 and 2.
				if (maxCol == 0)
				{
					M[1][1] -= M[1][0]*M[0][1];
					M[1][2] -= M[1][0]*M[0][2];
					M[2][1] -= M[2][0]*M[0][1];
					M[2][2] -= M[2][0]*M[0][2];
					M[1][0] = 0;
					M[2][0] = 0;
				}
				else if (maxCol == 1)
				{
					M[1][0] -= M[1][1]*M[0][0];
					M[1][2] -= M[1][1]*M[0][2];
					M[2][0] -= M[2][1]*M[0][0];
					M[2][2] -= M[2][1]*M[0][2];
					M[1][1] = 0;
					
					M[2][1] = 0;
				}
				else
				{
					M[1][0] -= M[1][2]*M[0][0];
					M[1][1] -= M[1][2]*M[0][1];
					M[2][0] -= M[2][2]*M[0][0];
					M[2][1] -= M[2][2]*M[0][1];
					M[1][2] = 0;
					M[2][2] = 0;
				}
				// Compute the maximum-magnitude entry of the last two rows of the
				// row-reduced matrix.
				max = -1;
				maxRow = -1;
				maxCol = -1;
				for (row = 1; row < 3; row++)
				{
					for (col = 0; col < 3; col++)
					{
						abs = fabs (M[row][col]);
						if (abs > max)
						{
							max = abs;
							maxRow = row;
							maxCol = col;
						}
					}
				}
				if (max == 0)
				{
					// The rank is 1. The eigenvalue has multiplicity 2.
					return 1;
				}
				// If row 2 has the maximum-magnitude entry, swap it with row 1.
				if (maxRow == 2)
				{
					for (col = 0; col < 3; col++)
					{
						save = M[1][col];
						M[1][col] = M[2][col];
						M[2][col] = save;
					}
				}
				// Scale the row containing the maximum to generate a 1-valued pivot.
				invMax = 1/M[maxRow][maxCol];
				M[1][0] *= invMax;
				M[1][1] *= invMax;
				M[1][2] *= invMax;
				
				// The rank is 2. The eigenvalue has multiplicity 1.
				return 2;
			}
		
	};
	
	
	
	


}/* CGL :: NAMESPACE */

#endif /*POLYNOMIAL_HPP_*/

