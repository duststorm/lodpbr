#include <QApplication>
#include <iostream>



#include "interface/myMainWindow.hpp"

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




