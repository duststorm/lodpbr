#include <QApplication>
#include <iostream>

#include "interface/myMainWindow.hpp"

#include "slal/Vector3.hpp"
#include "slal/Point3.hpp"
#include "slal/Matrix3x3.hpp"
#include "slal/Color.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	
	CGL::Point3<double> p(10.0,22.65,26.89);
	CGL::Point3<double> q;
	CGL::Color  c = Color(p);
	int  b[3] = {1,1,1};
	
	CGL::Vector3<double> v(b);
	
	v = v.norm();
	
	
	CGL::Matrix3x3<double> A (2.0,5.0,3.0,
								4.0,8.0,9.0,
								-8.0,9.0,4.0);
	
	CGL::Matrix3x3<double> B (-8.0,9.0,1.0,
								2.0,5.0,0.0,
								6.0,7.0,7.0);
	
	CGL::Matrix3x3<double> C = B * A;
	
	double a = 0.0;
	
	std::cout << v;
	
	std::cout << c;
	
	a = p[1] - q[0];
	std::cout << C;
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


