#include <QApplication>
#include <iostream>
#include <cmath>
#include <list>

#include <suitesparse/cs.h>

#include "interface/myMainWindow.hpp"

#include "slal/Vector3.hpp"
#include "slal/Point3.hpp"
#include "slal/Matrix3x3.hpp"
#include "slal/Color.hpp"
#include "slal/Polynomial.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	
	CGL::Point3<double> p(10.0,22.65,26.89);
	CGL::Point3<double> q;
	CGL::Color  c(p);
	
	double  b[3] = {1,1,0};
	double result[3];
		
	
	//v = v.norm();
		
	
	CGL::Matrix3x3<double> A (1.0,-5.0,-4.0,
								3.0,4.0,-3.0,
								0.0,2.0,0.0);
	
	CGL::Matrix3x3<double> B (1.0,1.0,2.0,
								2.0,4.0,-3.0,
								3.0,6.0,-5.0);
		

	std::list<CGL::Point3<double>* >  pt;
	
	CGL::Point3<double> pm = CGL::Point3<double>( 1,-1,2 );
	
	pt.push_back( new CGL::Point3<double>(-1,-2,1) );
	pt.push_back( new CGL::Point3<double>(1,0,2)   );
	pt.push_back( new CGL::Point3<double>(2,-1,3)  );
	pt.push_back( new CGL::Point3<double>(2,-1,2)  );
	
	CGL::CubicEquation<double> resolve = CGL::CubicEquation<double>(pt,pm);
	
	CGL::Matrix3x3<double> C  (	1.5,0.5,0.75,
								0.5,0.5,0.25,
								0.75,0.25,0.5);
	
	CGL::Vector3<double> Eigenvector[3];
	
	resolve.Eigensolver(C,result,Eigenvector);
	
	std::cout << "Rank " << resolve.ComputeRank(C) << std::endl;

	std::cout << "Eita " <<  Eigenvector[0] ;
	std::cout << "Eita " <<  Eigenvector[1] ;
	std::cout << "Eita " <<  Eigenvector[2] ;
	
	//if (resolve.Solve3(C,b,result))
//	{
		std::cout << "Eitaxx " << result[0] << std::endl;
		std::cout << "Eitaxx " << result[1] << std::endl;
		std::cout << "Eitaxx " << result[2] << std::endl;
//	}
	
	CGL::Vector3<double> v(result);
	
	std::cout << v.norm() ;
	
	std::cout << resolve.mCovariance;
		
	std::cout << "Eita " << resolve.mEigenvalue[0] << " | "<< resolve.mEigenvector[0] << " | "<< resolve.mEigenvector[0].length();// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "Eita " << resolve.mEigenvalue[1] << " | "<< resolve.mEigenvector[1] << " | "<< resolve.mEigenvector[1].length();// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "Eita " << resolve.mEigenvalue[2] << " | "<< resolve.mEigenvector[2] << " | "<< resolve.mEigenvector[2].length();// *  resolve.mEigenvalue[0] << std::endl;
	
	

    QApplication app(argc, argv);
    if (!QGLFormat::hasOpenGL()) {
        cerr << "This system has no OpenGL support" << endl;
        return 1;
    }
	
	MyMainWindow * form = new MyMainWindow;
	form->show();


    return app.exec();
}



/*CGL::Vector3<double> g(3.0,4.0,-5.0);

	
	
	a = p[1] - q[0];
	p[1] = 3.8898;
	//std::cout << C;
	std::cout << p ;
	std::cout << p.r() << p.g() << p.b() <<std::endl;
	

g =  A * g;

double a = 0.0;
double * array;

g = CGL::Vector3<double>(-209.9019,1737.5126,0.0);

array = C.getArray();
	
std::cout << B[1][1] << B(2,1) ;
B[1][1] = 54545.32443;

g = g.norm();
std::cout << g;
std::cout <<  " Result "<< array[0] << " - " << array[1]<<" - "<< array[2] << std::endl <<
				  " - " << array[3] << " - " << array[4]<<" - "<< array[5] << std::endl <<
				  " - " << array[6] << " - " << array[7]<<" - "<< array[8] << std::endl;*/

