#include <QApplication>
#include <iostream>
#include <list>
#include <algorithm>
#include <ctime>

#include "interface/myMainWindow.hpp"

#include "math/Vector3.hpp"
#include "math/Math.hpp"


int main(int argc, char *argv[])
{

			
    QApplication app(argc, argv);
    if (!QGLFormat::hasOpenGL()) {
        std::cerr << "This system has no OpenGL support" << std::endl;
        return 1;
    }

	MyMainWindow * form = new MyMainWindow;
	form->show();


    return app.exec();
}




