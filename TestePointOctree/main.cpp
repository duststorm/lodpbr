#include <QApplication>

#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>

#include "interface/myMainWindow.hpp"
//#include <cpplapack.h>

#include "slal/Vector3.hpp"
#include "slal/Point3.hpp"
#include "slal/Matrix3x3.hpp"
#include "slal/Color.hpp"
#include "slal/EigenSystem.hpp"
#include "slal/Eigen.hpp"
#include "surfels/MergeEllipses.hpp"

using namespace std;


int main(int argc, char *argv[])
{
	
	CGL::Point3<double> p(10.0,22.65,26.89);
	CGL::Point3<double> q;
	
	CGL::Vector3<double> v(4.0,4.0,4.0);
	CGL::Color  c(p);
	
	double  b[3] = {0,0,0};
	double result[3];
	
	//v = v.norm();
	q = v - p; 


	std::cout << q << std::endl;
	
	CGL::Matrix3x3<double> A (1.0,-5.0,-4.0,
								3.0,4.0,-3.0,
								0.0,2.0,0.0);
	
	CGL::Matrix3x3<double> B (1.0,0.0,0.0,
							  1.0,1.0,0.0,
							  1.0,1.0,1.0);
		
	CGL::Matrix3x3<double> C  (	1.5,0.5,0.75,
								0.5,0.5,0.25,
								0.75,0.25,0.5);
	
	
	
	Surfel<double> s = Surfel<double>(CGL::Point3<double>(0.76880,-1.250622,2.352241),
									  CGL::Vector3<double>(0.0,-0.547623,0.836725),1.0,1.0,0.0);
	
	s.SetMinorAxis(std::make_pair(1.0,CGL::Vector3<double>(1.0,0.0,0.0)));
	s.SetMajorAxis(std::make_pair(1.0,CGL::Vector3<double>(0.0,0.836725,0.547623)));
	
	
	std::list<Surfel<double> > sl;
	
	sl.push_back(s);
	
	std::list<CGL::Point3<double>* > points = s.BoundariesSamples(8);
	
	
	
	MergeEllipses<double> me(sl,CGL::Point3<double>(0.0,0.0,0.0),CGL::Vector3<double>(0.0,0.0,1.0));
	me.ProjectPoints();
		
	CGL::EigenSystem<double> eigen(points,s.Center());
		
	std::cout << " Values  " << eigen.MinorAxis().first << " Vector " << eigen.MinorAxis().second << std::endl;
	std::cout << " Values  " << eigen.MajorAxis().first << " Vector " << eigen.MajorAxis().second << std::endl;
	std::cout << " Values  " << eigen.Normal().first 	<< " Vector " << eigen.Normal().second << std::endl;
	
	
	for(std::list<CGL::Point3<double>* >::iterator it = points.begin();it != points.end();++it)
		std::cout << *(*(it)) << std::endl;

	CGL::Vector3<double> v1(18,6.5,7);
	CGL::Vector3<double> v2(-7,0,18);
	
	CGL::Vector3<double> v3 = v1 ^ v2; 
	
	std::cout <<" UI "<< v1*v2;

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
	
	std::list<CGL::Point3<double>* >  pt;
	
	CGL::Point3<double> pm = CGL::Point3<double>( 1,-1,2 );
	

	pt.push_back( new CGL::Point3<double>(-1,-2,1) );
	pt.push_back( new CGL::Point3<double>(1,0,2)   );
	pt.push_back( new CGL::Point3<double>(2,-1,3)  );
	pt.push_back( new CGL::Point3<double>(2,-1,2)  );
	
	CGL::CubicEquation<double> resolve = CGL::CubicEquation<double>(pt,pm);
	
	CGL::Vector3<double> Eigenvector[3]; 
	
	double Eigenvalue[3];
	
	CGL::Eigen<double> eigen = CGL::Eigen<double>(pt,pm);
	
	std::cout << "ww " << eigen.m_afEigenvalue[0] << " | "<< eigen.m_akEigenvector[0];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "ww " << eigen.m_afEigenvalue[1] << " | "<< eigen.m_akEigenvector[1];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "ww " << eigen.m_afEigenvalue[2] << " | "<< eigen.m_akEigenvector[2];// *  resolve.mEigenvalue[0] << std::endl;
	
	
	resolve.Eigensolver(C,Eigenvalue,Eigenvector);
	
	std::cout << "Eita " << Eigenvalue[0] << " | "<< Eigenvector[0];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "Eita " << Eigenvalue[1] << " | "<< Eigenvector[1];// *  resolve.mEigenvalue[0] << std::endl;
	std::cout << "Eita " << Eigenvalue[2] << " | "<< Eigenvector[2];// *  resolve.mEigenvalue[0] << std::endl;
	
		
	std::cout << "Eita ZERO " << resolve.mEigenvector[0] * resolve.mEigenvector[1] << std::endl;
	
	CGL::Vector3<double> v1 (1.0,2.0,-2.0);
	CGL::Vector3<double> v2 (3.0,0.0,1.0);
	CGL::Vector3<double> v3 (B.col(2));
	

	v3 = v2 ^ v1;
	
	std::cout << "v1 " << v1;
	std::cout << "v2 " << v2;
	std::cout << "v3 " << v3;
 * 
 * */


