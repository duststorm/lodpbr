#include <QApplication>

#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include "slal/Vector3.hpp"
#include <ctime> 

#include "interface/myMainWindow.hpp"

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
  	  if ( i > 1 )
  	  {
  		  std::cerr << "[ERROR] Point2 operator[]"        << std::endl
  		  << "        Out of the Point size. " << std::endl
  		  << "        Accepts, 0 , 1 only." << std::endl;
  		  exit(1);
  	  }

  	  return (xy[i]);
    };
    
    inline  float& operator [] ( unsigned int i)  

    {
  	  if ( i > 1 )
  	  {
  		  std::cerr << "[ERROR] Point2 operator[]"        << std::endl
  		  << "        Out of the Point size. " << std::endl
  		  << "        Accepts, 0 , 1 only." << std::endl;
  		  exit(1);
  	  }


  	  return (xy[i]);
    };
    
private:
	
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


int main(int argc, char *argv[])
{

	ppp p1(1.0,1.0);
	pp  p2(1.0,1.0);
	CGL::Vector3<float> v(1.0,1.0,0.0);
	CGL::Vector3<float> u(1.0,0.0,0.0);
	
	std::cout << std::sqrt(2)*0.5 << "  =  " << u.norm() * v.norm() << std::endl;
			
	
	time_t start,end,startc,endc ;
	time (&start);
	unsigned long int i = 0;
	while(i  < 2000000000)
	{
		p1.x = p1.x + p1.y;
		i++;
	}
	time(&end);

	double dif = difftime (end,start);

	std::cout << dif << " maluco" <<std::endl;


	time (&startc);
	i = 0;
	while(i  < 2000000000)
	{
		p2[0] = p2.x() + p2.y();
		i++;
	}
	time(&endc);

	dif = difftime (endc,startc);

	std::cout << dif<< " minha" <<std::endl;
		
		
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


