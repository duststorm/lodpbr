#include <QApplication>
#include <iostream>

#include "interface/myMainWindow.hpp"
#include "matrixLibrary/Vector3.hpp"
#include "matrixLibrary/Matrix3x3.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	SLAL::Vector3<double> v1(-3.0,4.0,0.0);
	SLAL::Vector3<double> v2(-3.0,4.0,0.0);
	
	SLAL::Matrix3x3<double> A (1.0,1.0,1.0,
							   2.0,2.0,2.0,
							   3.0,3.0,3.0);
	
	bool f = false	;
	
	f = v1 != v2;
	
	std::cout << v1 <<std::endl;
	
	std::cout << A;
	
    QApplication app(argc, argv);
    if (!QGLFormat::hasOpenGL()) {
        cerr << "This system has no OpenGL support" << endl;
        return 1;
    }
	
	MyMainWindow * form = new MyMainWindow;
	form->show();
    
    //tetrahedron.setWindowTitle(QObject::tr("Tetrahedron"));
    //tetrahedron.resize(300, 300);

    return app.exec();
}
