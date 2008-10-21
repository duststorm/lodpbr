#include <QApplication>
#include <iostream>
#include <list>
#include <algorithm>
#include <ctime>

#include "interface/myMainWindow.hpp"

#include "math/Vector3.hpp"
#include "math/Math.hpp"

class ppp{
public:
    ppp(float w,float u)
    {
    	x = w;
    	y = u;
    };

	float x;
	float y;

};

class pp{
public:
    pp(float w,float u)
    {
    	mx = w;
    	my = u;
    };

    inline const float& x() const
    {
  	  return ( this->mx );
    };

    inline const float& y() const
    {
  	  return ( this->my );
    };



    inline  float operator [] ( unsigned int i)  const
    {
//  	  if ( i > 1 )
//  	  {
//  		  std::cerr << "[ERROR] Point2 operator[]"        << std::endl
//  		  << "        Out of the Point size. " << std::endl
//  		  << "        Accepts, 0 , 1 only." << std::endl;
//  		  exit(1);
//  	  }

  	  return (xy[i]);
    };

    inline  float& operator [] ( unsigned int i)

    {
//  	  if ( i > 1 )
//  	  {
//  		  std::cerr << "[ERROR] Point2 operator[]"        << std::endl
//  		  << "        Out of the Point size. " << std::endl
//  		  << "        Accepts, 0 , 1 only." << std::endl;
//  		  exit(1);
//  	  }


  	  return (xy[i]);
    };



	union
	{
		struct
		{
			float mx;
			float my;
		};
		float xy[2];
	};


};



float hypot2(float x, float y) 
{
	return std::sqrt(x*x+y*y);
}


void EigenDecomposition( float matrix[3][3], float eig[3] ) 
{
	float e[3];
	float d[3];
	

	//  This is derived from the Algol procedures tred2 by
	//  Bowdler, Martin, Reinsch, and Wilkinson, Handbook for
	//  Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
	//  Fortran subroutine in EISPACK.

	d[0] = matrix[2][0];
	d[1] = matrix[2][1];
	d[2] = matrix[2][2];

	// Householder reduction to tridiagonal form.

	for (int i = 3-1; i > 0; i--) 
	{

		// Scale to avoid under/overflow.

		float scale = 0.0;
		float h 	   = 0.0;

		for (int k = 0; k < i; k++) 
		{
			scale = scale + fabs(d[k]);
		}

		if (scale == 0.0) 
		{

			e[i] = d[i-1];

			for (int j = 0; j < i; j++) 
			{
				d[j] = matrix[i-1][j];
				matrix[i][j] = 0.0;
				matrix[j][i] = 0.0;
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

			float f = d[i-1];
			float g = sqrt(h);

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
				matrix[j][i] = f;
				g 		= e[j] + matrix[j][j] * f;

				for (int k = j+1; k <= i-1; k++) 
				{
					g 	 += matrix[k][j] * d[k];
					e[k] += matrix[k][j] * f;
				}

				e[j] = g;
			}

			f = 0.0;
			for (int j = 0; j < i; j++) 
			{
				e[j] /= h;
				f 	 += e[j] * d[j];
			}
			float hh = f / (h + h);
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
					matrix[k][j] -= (f * e[k] + g * d[k]);
				}
				d[j] 	= matrix[i-1][j];
				matrix[i][j] = 0.0;
			}
		}

		d[i] = h;
	}

	// Accumulate transformations.

	for (int i = 0; i < 3-1; i++) 
	{
		matrix[3-1][i] = matrix[i][i];
		matrix[i][i] = 1.0;
		float h = d[i+1];
		if (h != 0.0) {
			for (int k = 0; k <= i; k++) {
				d[k] = matrix[k][i+1] / h;
			}
			for (int j = 0; j <= i; j++) {
				float g = 0.0;
				for (int k = 0; k <= i; k++) {
					g += matrix[k][i+1] * matrix[k][j];
				}
				for (int k = 0; k <= i; k++) {
					matrix[k][j] -= g * d[k];
				}
			}
		}
		for (int k = 0; k <= i; k++) {
			matrix[k][i+1] = 0.0;
		}
	}

	for (int j = 0; j < 3; j++) 
	{
		d[j] = matrix[3-1][j];
		matrix[3-1][j] = 0.0;
	}

	matrix[3-1][3-1] = 1.0;
	e[0] = 0.0;


	// Symmetric tridiagonal QL algorithm.
	// Start QL algorithm	
	//static void tql2(float V[3][3], float d[3], float e[3]) 

	//  This is derived from the Algol procedures tql2, by
	//  Bowdler, Martin, Reinsch, and Wilkinson, Handbook for
	//  Auto. Comp., Vol.ii-Linear Algebra, and the corresponding
	//  Fortran subroutine in EISPACK.

	for (int i = 1; i < 3; i++) 
	{
		e[i-1] = e[i];
	}
	e[3-1] = 0.0;

	float f = 0.0;
	float tst1 = 0.0;
	float eps = 0.00000001;
	for (int l = 0; l < 3; l++) {

		// Find small subdiagonal element
		float diag = fabs( d[l]) + fabs(e[l] );
		tst1 = std::max( tst1, diag );
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

				float g = d[l];
				float p = (d[l+1] - g) / (2.0 * e[l]);
				float r = hypot2(p,1.0);
				if (p < 0) {
					r = -r;
				}
				d[l] = e[l] / (p + r);
				d[l+1] = e[l] * (p + r);
				float dl1 = d[l+1];
				float h = g - d[l];
				for (int i = l+2; i < 3; i++) {
					d[i] -= h;
				}
				f = f + h;

				// Implicit QL transformation.

				p = d[m];
				float c 	 = 1.0;
				float c2  = c;
				float c3  = c;
				float el1 = e[l+1];
				float s 	 = 0.0;
				float s2  = 0.0;

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
						h = matrix[k][i+1];
						matrix[k][i+1] = s * matrix[k][i] + c * h;
						matrix[k][i] = c * matrix[k][i] - s * h;
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
		float p = d[i];
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
				p = matrix[j][i];
				matrix[j][i] = matrix[j][k];
				matrix[j][k] = p;
			}
		}
	}
	eig[0] = d[0];
	eig[1] = d[1];
	eig[2] = d[2];

				
}


int main(int argc, char *argv[])
{
//
//	ppp p1(1.0,1.0);
//	pp  p2(1.0,1.0);
//	LAL::Vector3<float> v(1.0,1.0,0.0);
//	LAL::Vector3<float> u(1.0,0.0,0.0);
//
//	std::cout << std::sqrt(2)*0.5 << "  =  " << u.norm() * v.norm() << std::endl;
//
//
//	time_t start,end,startc,endc ;
//	time (&start);
//	unsigned long int i = 0;
//	while(i  < 2000000000)
//	{
//
//		p2.my = p2.mx + p2.my;
//		i++;
//	}
//	time(&end);
//
//	double dif = difftime (end,start);
//
//	std::cout << dif << " maluco" <<std::endl;
//
//
//	time (&startc);
//	i = 0;
//	while(i  < 2000000000)
//	{
//		p1.y = p1.x + p1.y;
//		i++;
//	}
//	time(&endc);
//
//	dif = difftime (endc,startc);
//
//	std::cout << dif<< " minha" <<std::endl;
//
	
	float matrix[3][3];
	float e[3];
	
	matrix[0][0] = 12.0f;
	matrix[0][1] = 4.0f; 
	matrix[0][2] = 8.0f;
		
		matrix[1][0] = 4.0f;
		matrix[1][1] = 3.0f;
		matrix[1][2] = 16.0f;		

			matrix[2][0] = 8.0f;
			matrix[2][1] = 16.0f;
			matrix[2][2] =  2.0f;
			
			EigenDecomposition(matrix,e);
			
			std::cout << e[0] << " * " << e[1] << " * " << e[2] << std::endl;
			
    QApplication app(argc, argv);
    if (!QGLFormat::hasOpenGL()) {
        cerr << "This system has no OpenGL support" << endl;
        return 1;
    }

	MyMainWindow * form = new MyMainWindow;
	form->show();


    return app.exec();
}



/*LAL::Vector3<double> g(3.0,4.0,-5.0);



	a = p[1] - q[0];
	p[1] = 3.8898;
	//std::cout << C;
	std::cout << p ;
	std::cout << p.r() << p.g() << p.b() <<std::endl;


g =  A * g;

double a = 0.0;
double * array;

g = LAL::Vector3<double>(-209.9019,1737.5126,0.0);

array = C.getArray();

std::cout << B[1][1] << B(2,1) ;
B[1][1] = 54545.32443;

g = g.norm();
std::cout << g;
std::cout <<  " Result "<< array[0] << " - " << array[1]<<" - "<< array[2] << std::endl <<
				  " - " << array[3] << " - " << array[4]<<" - "<< array[5] << std::endl <<
				  " - " << array[6] << " - " << array[7]<<" - "<< array[8] << std::endl;*/

/*
 * 	CPPL::dsymatrix C_lapack = CPPL::dsymatrix(3) ;

	std::vector<double> w1;

	C_lapack(0,0) = 1.5;
	C_lapack(0,1) = 0.5;
	C_lapack(0,2) = 0.75;
	C_lapack(1,0) = 0.5;
	C_lapack(1,1) = 0.5;
	C_lapack(1,2) = 0.25;
	C_lapack(2,0) = 0.75;
	C_lapack(2,1) = 0.25;
	C_lapack(2,2) = 0.5;/

	C_lapack.dsyev(w1,1);

	std::cout << w1[0] << w1[1] << w1[2];

	std::cout << C_lapack;

	std::list<LAL::Point3<double>* >  pt;

	LAL::Point3<double> pm = LAL::Point3<double>( 1,-1,2 );


	pt.push_back( new LAL::Point3<double>(-1,-2,1) );
	pt.push_back( new LAL::Point3<double>(1,0,2)   );
	pt.push_back( new LAL::Point3<double>(2,-1,3)  );
	pt.push_back( new LAL::Point3<double>(2,-1,2)  );

	LAL::CubicEquation<double> resolve = LAL::CubicEquation<double>(pt,pm);

	LAL::Vector3<double> Eigenvector[3];

	double Eigenvalue[3];

	LAL::Eigen<double> eigen = LAL::Eigen<double>(pt,pm);

	std::cout << "ww " << eigen.m_afEigenvalue[0] << " | "<< eigen.m_akEigenvector[0];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "ww " << eigen.m_afEigenvalue[1] << " | "<< eigen.m_akEigenvector[1];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "ww " << eigen.m_afEigenvalue[2] << " | "<< eigen.m_akEigenvector[2];// *  resolve.mEigenvalue[0] << std::endl;


	resolve.Eigensolver(C,Eigenvalue,Eigenvector);

	std::cout << "Eita " << Eigenvalue[0] << " | "<< Eigenvector[0];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "Eita " << Eigenvalue[1] << " | "<< Eigenvector[1];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "Eita " << Eigenvalue[2] << " | "<< Eigenvector[2];// *  resolve.mEigenvalue[0] << std::endl;


	std::cout << "Eita ZERO " << resolve.mEigenvector[0] * resolve.mEigenvector[1] << std::endl;

	LAL::Vector3<double> v1 (1.0,2.0,-2.0);
	LAL::Vector3<double> v2 (3.0,0.0,1.0);
	LAL::Vector3<double> v3 (B.col(2));


	v3 = v2 ^ v1;

	std::cout << "v1 " << v1;
	std::cout << "v2 " << v2;
	std::cout << "v3 " << v3;
 *
 * */


