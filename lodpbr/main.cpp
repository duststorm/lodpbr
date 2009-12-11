#include <QApplication>
#include <iostream>

#include "Qt/myMainWindow.hpp"

#include "Surfels/Surfel.hpp"
#include "Surfels/IOSurfels.hpp"
#include "Math/Vector3.hpp"
#include "Math/BoundingBox3.hpp"

int main(int argc, char *argv[])
{

	std::cout <<" size of "<<sizeof(Celer::Surfel<float>::Vector3) << std::endl;
    QApplication app(argc, argv);
//    if (!QGLFormat::hasOpenGL()) {
//        std::cerr << "This system has no OpenGL support" << std::endl;
//        return 1;
//    }

//    Celer::Surfel<float>::LoadPlySurfel s;
//
//	s.cx = 1.0;
//	s.cy = 2.0;
//	s.cz = 3.0;
//	s.nx = 4.0;
//	s.ny = 5.0;
//	s.nz = 6.0;
//	s.major_axisx = 1.0;
//	s.major_axisy = 1.0;
//	s.major_axisz = 1.0;
//	s.major_axis_size = 10;
//	s.minor_axisx = 2.0;
//	s.minor_axisy = 2.0;
//	s.minor_axisz = 2.0;
//	s.minor_axis_size = 20;
//	s.r = 1.0;
//	s.g = 1.0;
//	s.b = 1.0;
//	s.max_error = 7.0;
//	s.min_error = 8.0;
//
//    Celer::Surfel<float> sc(s);
//
//    std::cout << sc << std::endl;
//
//    sc.SetCenter(Celer::Vector3<float>(6.58,9.84,12.58));
//
//    s = sc;
//
//
//		std:: cout << "cx " << s.cx << std::endl;
//		std:: cout << "cy " << s.cy << std::endl;
//		std:: cout << "cz " << s.cz << std::endl;
//		std:: cout << "nx " << s.nx << std::endl;
//		std:: cout << "ny " << s.ny << std::endl;
//		std:: cout << "nz " << s.nz << std::endl;
//		std:: cout << "major_axisx " << s.major_axisx << std::endl;
//		std:: cout << "major_axisy " << s.major_axisy << std::endl;
//		std:: cout << "major_axisz " << s.major_axisz << std::endl;
//		std:: cout << "major_axis_size " << s.major_axis_size << std::endl;
//
//    std::vector<Celer::Surfel<float> > s;
//
//	QString fileName = 		 "../TesteMarked/surfel.ply";
//
//	std::string filename = QFile::encodeName(fileName).constData ();
//
//	vcg::tri::io::PlyInfo pi;

	MyMainWindow * form = new MyMainWindow;
//	QString fileNameLsplat = QFileDialog::getOpenFileName (
//						form,
//	                      ("Choose a mesh file"),
//	                      ".",
//	                      ("Ply file (*.ply)"));
//
//
//	std::string filenameLsplat = QFile::encodeName(fileNameLsplat).constData ();
//
//	std:: cout << "filenameLsplat" << filenameLsplat << " " << filenameLsplat << std::endl;
//
//	//int i = Celer::IOSurfels<>::LoadSurfels(filenameLsplat.c_str(),s);
//
//	Celer::BoundingBox3<float> bb;
//	int i = Celer::IOSurfels<float>::LoadMesh(filenameLsplat.c_str(),s,bb);
//
//
//
//	std:: cout << "s size " << s.size() << " " << filenameLsplat << std::endl;


	form->show();


    return app.exec();
}




