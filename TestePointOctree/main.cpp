#include <QApplication>
#include <iostream>
#include <cmath>

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
	
	int  b[3] = {1,1,1};
	double result[3];
		
	CGL::Vector3<double> v(b);
	
	v = v.norm();
		
	
	CGL::Matrix3x3<double> A (1.0,-5.0,-4.0,
								3.0,4.0,-3.0,
								0.0,2.0,0.0);
	
	CGL::Matrix3x3<double> B (1.0,1.0,2.0,
								2.0,4.0,-3.0,
								3.0,6.0,-5.0);
	double BBB[3] = {9.0,1.0,0.0};
	
	CGL::Matrix3x3<double> C (4.0,1.0,4.0,
							  1.0,7.0,1.0,
							  4.0,1.0,4.0);
	
	CGL::CubicEquation<double> resolve = CGL::CubicEquation<double>(C);
	
	resolve.Solve3 (B,BBB,result);
	
	//resolve.mEigenvector[0].normalize();
	//resolve.mEigenvector[1].normalize();
	//resolve.mEigenvector[2].normalize();
	
	std::cout << C * resolve.mEigenvector[0];
	std::cout << C * resolve.mEigenvector[1];
	std::cout << C * resolve.mEigenvector[2];

	std::cout << "Eita " <<  resolve.mEigenvector[0];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "Eita " << resolve.mEigenvector[1]; // * resolve.mEigenvalue[1] << std::endl;
	std::cout << "Eita " << resolve.mEigenvector[2];//  * resolve.mEigenvalue[2] << std::endl;
	
	CGL::Vector3<double> g(3.0,4.0,-5.0);
	
	 g =  A * g;
	
	double a = 0.0;
	double * array;
	
	g = CGL::Vector3<double>(-209.9019,1737.5126,0.0);
	
	array = C.getArray();
		
	std::cout << B.row(2) << B(2,1) ;
	
	g = g.norm();
	std::cout << g;
	std::cout <<  " Result "<< array[0] << " - " << array[1]<<" - "<< array[2] << std::endl <<
					  " - " << array[3] << " - " << array[4]<<" - "<< array[5] << std::endl <<
					  " - " << array[6] << " - " << array[7]<<" - "<< array[8] << std::endl;
		
	a = p[1] - q[0];
	p[1] = 3.8898;
	//std::cout << C;
	std::cout << p ;
	std::cout << p.r() << p.g() << p.b() <<std::endl;
	
    QApplication app(argc, argv);
    if (!QGLFormat::hasOpenGL()) {
        cerr << "This system has no OpenGL support" << endl;
        return 1;
    }
	
	MyMainWindow * form = new MyMainWindow;
	form->show();


    return app.exec();
}


