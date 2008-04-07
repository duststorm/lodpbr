#include <QtGui>
#include <QtOpenGL>

#include <limits>

#include "GLFrame.hpp"
#include "surfels/MergeEllipses.hpp"

#define DA_APLICACAO_PASSADA 0

GLFrame::GLFrame(QWidget *parent):QGLWidget(parent)
{
	
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    
    rotationX = -21.0;
    rotationY = -57.0;
    rotationZ = 0.0;
    zoomFactor = 1.0;
    
    setFocusPolicy(Qt::StrongFocus);
   
	renderMode_A = Points;
	show_A 	= true;
	
	midlePoint = CGL::Point3<double>();
	
	surfels = Surfels<double>();
	
	mousePositionX = 0.0;
	mousePositionY = 0.0;
	mousePositionZ = 0.0;
    
}

void GLFrame::initializeGL()
{
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
 	GLfloat luzDifusa[4]={1.0,1.0,0.0,1.0};         //cor
	//GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};   //brilho
	GLfloat especularidade[4]={1.0,0.0,0.0,1.0};	  //brilho do material
		
	GLint especMaterial = 64;

	GLfloat light_position[] = {0.0, 0.5, 10.0, 0.0};
	
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);           //cor fundo
	glShadeModel(GL_SMOOTH);                      	//gouraud
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, luzDifusa);//refletancia do material
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, especularidade);//refletancia do material
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,especMaterial);  //concentracao do brilho
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);        //luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, luzAmbiente);        //luz ambiente
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);  //parametros da luz 0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_position );

	glEnable(GL_COLOR_MATERIAL);  //cor do material a partir da cor corrente
	glEnable(GL_LIGHTING);        //uso de iluminacao
	glEnable(GL_LIGHT0);          //luz  0
	glEnable(GL_DEPTH_TEST);      //depth-buffering

	glEnable(GL_NORMALIZE);
	
	sceneTransformation.identity();

	

}

void GLFrame::model()
{
	
	for (OctreeIterator<double, Surfel<double>* > oi = octree.begin();oi != octree.end();++oi )
	{
		if ( (*oi)->isLeaf())
		{
	   	   glDisable(GL_LIGHTING);		
		   glColor3f(0.0,0.0,1.0);
		   glBegin(GL_LINES);

		   	   
#if 0		   
		   while ( surfe != lp.end() )
		   {

			   CGL::Point3<double> p0 = *(*surfe) + (*oi)->eigenVector(0)*1.25;
			   glColor3f(1.0,0.0,0.0);
			   glVertex3f((*(*surfe))[0],(*(*surfe))[1],(*(*surfe))[2]);
			   glVertex3f(p0.x(),p0.y(),p0.z());

			   CGL::Point3<double> p1 = (*(*surfe)) +  (*oi)->eigenVector(1)*1.25;
			   glColor3f(0.0,1.0,0.0);
			   glVertex3f((*(*surfe))[0],(*(*surfe))[1],(*(*surfe))[2]);
			   glVertex3f(p1.x(),p1.y(),p1.z());
			   
			   CGL::Point3<double> p2 = (*(*surfe)) + (*oi)->eigenVector(2)*1.25;
			   glColor3f(0.0,0.0,1.0);
			   glVertex3f((*(*surfe))[0],(*(*surfe))[1],(*(*surfe))[2]);
			   glVertex3f(p2.x(),p2.y(),p2.z());

	

			   ++surfe;
		   }
#endif		   
		   glEnd();
		   glEnable(GL_LIGHTING);
		   glPointSize(1.0);
		   break;
		}  
					
	}
	
}


void GLFrame::drawPoints() {
   
   glDisable(GL_LIGHTING);		
   glPointSize(3.0);
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_POINTS);
   
     
   for (OctreeIterator<double, Surfel<double>* > oi = octree.begin();oi != octree.end();++oi )
   {
	   
	   if( ( (*oi)->isLeaf()   and (oi.level() < 3) ) or ((oi.level() == 3)) )
	   {

//		   std::list< Surfel<double>* > lp = (*oi)->itemList();
//
//		   for(std::list< Surfel<double>* >::iterator surfe = lp.begin(); surfe != lp.end(); ++surfe )
//		   {
//			    CGL::Point3<double> point = (*surfe)->Center();
//			    glPointSize(3.0);
//			    glColor3f(1.0,0.0,0.0);
//				glVertex3f(point[0],point[1],point[2]);
		   if ((*oi)->MeanItem() != NULL)
				(*oi)->MeanItem()->draw();
				
		  
	   }
	   
#if 0 // dois splats no meio
	
		Surfel<double> s = Surfel<double>(CGL::Point3<double>(1.878106, 0.000000, 0.000000),
										  CGL::Vector3<double>(-0.000000, 0.000000, 1.000000),1.0,1.0,0.0);
		
		s.SetMinorAxis(std::make_pair(1.0,CGL::Vector3<double>(1.000000, 0.000000, 0.000000)));
		s.SetMajorAxis(std::make_pair(2.0,CGL::Vector3<double>(0.000000, 1.000000, 0.000000)));

		std::list<Surfel<double> > sl;
		
		sl.push_back(s);

		Surfel<double> s1 = Surfel<double>(CGL::Point3<double>(-1.721011, 0.000000, 0.000000),
						   				   CGL::Vector3<double>(-0.000000, 0.000000, 1.000000),1.0,1.0,0.0);
		
		s1.SetMinorAxis(std::make_pair(1.0,CGL::Vector3<double>(1.000000, 0.000000, 0.000000)));
		s1.SetMajorAxis(std::make_pair(2.0,CGL::Vector3<double>(0.000000, 1.000000, 0.000000)));
		
		sl.push_back(s1);
						
		MergeEllipses<double> me(sl);
		
		Surfel<double> sr = Surfel<double>(CGL::Point3<double>(me.Center()),
				   						  CGL::Vector3<double>(me.Normal()),1.0,1.0,0.0);
		
		sr.SetMinorAxis(me.MinorAxis());
		sr.SetMajorAxis(me.MajorAxis());
		
		std::list< CGL::Point3<double>* > newE = sr.BoundariesSamples(100);
#endif	
		
#if 0 // dois splats no meio
	
		Surfel<double> s = Surfel<double>(CGL::Point3<double>(0.660652, 0.416949, 1.471741),
										  CGL::Vector3<double>(-0.723338, -0.047630, 0.688850),1.0,1.0,0.0);
		
		s.SetMinorAxis(std::make_pair(1.0,CGL::Vector3<double>(0.642318, 0.319691, 0.696581)));
		s.SetMajorAxis(std::make_pair(2.0,CGL::Vector3<double>(-0.253398, 0.946324, -0.200651)));

		std::list< CGL::Point3<double>* > newE1 = s.BoundariesSamples(100);
		
		std::list<Surfel<double> > sl;
		
		sl.push_back(s);

		Surfel<double> s1 = Surfel<double>(CGL::Point3<double>(-0.621054, 0.556120, -0.106632),
						   				   CGL::Vector3<double>(0.516305, -0.156048, 0.842068),1.0,1.0,0.0);
		
		s1.SetMinorAxis(std::make_pair(1.0,CGL::Vector3<double>(0.782782, -0.312861, -0.537932)));
		s1.SetMajorAxis(std::make_pair(2.0,CGL::Vector3<double>(0.347393, 0.936892, -0.039380)));
		std::list< CGL::Point3<double>* > newE2 = s1.BoundariesSamples(100);
		sl.push_back(s1);
						
		MergeEllipses<double> me(sl);
		
		Surfel<double> sr = Surfel<double>(CGL::Point3<double>(me.Center()),
				   						  CGL::Vector3<double>(me.Normal()),1.0,1.0,0.0);
		
		sr.SetMinorAxis(me.MinorAxis());
		sr.SetMajorAxis(me.MajorAxis());
		
		std::list< CGL::Point3<double>* > newE = sr.BoundariesSamples(100);

		for(std::list<CGL::Point3<double>* >::iterator it = me.mProjectedPoint.begin();it != me.mProjectedPoint.end();++it)
		{		
			glColor3f(0.0,1.0,0.0);
			CGL::Point3<double> point = (*(*it));
		 	glVertex3f(point[0],point[1],point[2]);
		}
		for(std::list<CGL::Point3<double>* >::iterator it = newE.begin();it != newE.end();++it)
		{
			glColor3f(0.0,0.0,1.0);
			CGL::Point3<double> point = (*(*it));
		 	glVertex3f(point[0],point[1],point[2]);
		}
		for(std::list<CGL::Point3<double>* >::iterator it = newE1.begin();it != newE1.end();++it)
		{
			glColor3f(0.0,0.0,1.0);
			CGL::Point3<double> point = (*(*it));
		 	glVertex3f(point[0],point[1],point[2]);
		}
		for(std::list<CGL::Point3<double>* >::iterator it = newE2.begin();it != newE2.end();++it)
		{
			glColor3f(0.0,0.0,1.0);
			CGL::Point3<double> point = (*(*it));
		 	glVertex3f(point[0],point[1],point[2]);
		}
		
#endif

   }
   

   
   glEnd();
   glEnable(GL_LIGHTING);
   glPointSize(1.0);
}

void GLFrame::calLimits()
{
	
	Box_3<double> world = Box_3<double>( CGL::Point3<double>(surfels.box().xmin(),surfels.box().ymin(),surfels.box().zmin()),
				   						 CGL::Point3<double>(surfels.box().xmax(),surfels.box().ymax(),surfels.box().zmax()));
	 
	octree = Octree<double,Surfel<double>* >(world) ;
	
	for (std::vector<Surfel<double> >::iterator surf =  surfels.surfels.begin();surf != surfels.surfels.end(); ++ surf ) 
	{
		
		octree.insert (new Surfel<double>(*surf));
	    midlePoint += surf->Center();
	    
	}
	midlePoint /= surfels.surfels.size();  
		
    std::cout << octree.root->itemPtrCount() <<  " AAA" << std::endl;
    
    octree.split();
    octree.Merge();
    
}

template <class T>
void GLFrame::drawBox(CGL::BoundingBox3<T> BBox){
  glColor3f (1.0, 1.0, 1.0);//white

  glBegin(GL_LINE_LOOP);
    glVertex3f(BBox.xmin(), BBox.ymin(), BBox.zmin());
    glVertex3f(BBox.xmax(), BBox.ymin(), BBox.zmin());
    glVertex3f(BBox.xmax(), BBox.ymax(), BBox.zmin());
    glVertex3f(BBox.xmin(), BBox.ymax(), BBox.zmin());
  glEnd();

  glBegin(GL_LINE_LOOP);
    glVertex3f(BBox.xmin(), BBox.ymin(), BBox.zmax());
    glVertex3f(BBox.xmax(), BBox.ymin(), BBox.zmax());
    glVertex3f(BBox.xmax(), BBox.ymax(), BBox.zmax());
    glVertex3f(BBox.xmin(), BBox.ymax(), BBox.zmax());
  glEnd();

  glBegin(GL_LINES);
    glVertex3f(BBox.xmin(), BBox.ymin(), BBox.zmax());
    glVertex3f(BBox.xmin(), BBox.ymin(), BBox.zmin());
    glVertex3f(BBox.xmax(), BBox.ymin(), BBox.zmax());
    glVertex3f(BBox.xmax(), BBox.ymin(), BBox.zmin());

    glVertex3f(BBox.xmax(), BBox.ymax(), BBox.zmax());
    glVertex3f(BBox.xmax(), BBox.ymax(), BBox.zmin());

    glVertex3f(BBox.xmin(), BBox.ymax(), BBox.zmax());
    glVertex3f(BBox.xmin(), BBox.ymax(), BBox.zmin());
  glEnd();
}

void GLFrame::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    //glOrtho(-1,1,-1,1,-2,2);
    gluPerspective(45.0,x,1.0,200);
    //glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    arcball.setBounds(width, height);
    
}

void GLFrame::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0,0.0,-3.0);
    glMultMatrixf(&sceneTransformation);
    
    if ( surfels.surfels.size() != 0 )
    {
    	if (renderMode_A == Points)
    		drawPoints();
    	
    	/*if (renderMode_A == Model)
    	{
    	   model();
    	   drawPoints();
    	}*/
    	
		for (OctreeIterator<double, Surfel<double>* > oi = octree.begin();oi != octree.end();++oi )
		{
		   			  
	      // drawBox(octree.box(oi));
		   glDisable(GL_LIGHTING);		
		   glPointSize(5.0);
		   glColor3f(0.0,0.0,1.0);
		   glBegin(GL_POINTS);
		   			   		   		        
		   //glVertex3f(oi.mean()[0],oi.mean()[1],oi.mean()[2]);
		   		   
		   glEnd();
		   glEnable(GL_LIGHTING);
		   glPointSize(1.0);
						
		}
		
    }

#if DA_APLICACAO_PASSADA    
    /*
	if( A  and  isVisible_A()  )
	{
		
		   for (OctreeIterator<double, CGL::Point3<double>*> oi = octree.begin();oi != octree.end();++oi )
		   {
			   if ((*oi)->isLeaf())
				   drawBox(octree.box(oi));
		   }
		
		if (renderMode_A == PolygonWireFrame)
			A->drawPolygonWireframe(true);
		else if (renderMode_A == WireFrame)
			A->drawWireframe(true);
		else 
			A->drawPoints();
	}*/
#endif
}

void GLFrame::keyPressEvent ( QKeyEvent * event)
{
	if (event->key() == Qt::Key_R)
	{ 
		zoomFactor = 1.0;
	}            
	updateGL();	     
	  
}


void GLFrame::mousePressEvent(QMouseEvent *event)
{
	 
    if (event->button() == Qt::MidButton) 
    {
    	arcball.click(event->x(),height() - event->y());
    	updateGL(); 
    }
    else if (event->button() == Qt::RightButton) 
    {
    	screenToWorld(event->x(),height() - event->y(), mousePositionX, mousePositionY, mousePositionZ);
    	
    }
    
    sceneInitialTransformation = sceneTransformation;
    lastPos = event->pos();
}

void GLFrame::wheelEvent(QWheelEvent *e) 
{
   
   if (e->delta()>0)
	   zoomIn();
   else              
      zoomOut();
      
   updateGL();
}


void GLFrame::mouseMoveEvent(QMouseEvent *event)
{

     if (event->buttons() & Qt::LeftButton) {

        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        //Translation
    	double xWorld, yWorld, zWorld;
    	screenToWorld(event->x(), height() - event->y(), xWorld, yWorld, zWorld);
    	AMatrix<float> matrixTransformation;
    	matrixTransformation.identity();
    	matrixTransformation.translation(xWorld - mousePositionX, yWorld - mousePositionY, zWorld - mousePositionZ);
    	sceneTransformation = matrixTransformation * sceneInitialTransformation;
    	updateGL();
       
    }else if (event->buttons() & Qt::MidButton)  {
    	//Rotation
	    AMatrix<float> matrixTransformation;
	    arcball.drag(event->x(), height() - event->y(), &matrixTransformation);
	    sceneTransformation = matrixTransformation * sceneInitialTransformation;
    	updateGL();
     }
    lastPos = event->pos();
}

void GLFrame::screenToWorld(int x, int y, double &xw, double &yw, double &zw) {
   
   GLdouble mMtx[16], pMtx[16];  /// modelview/projection matrix
   GLint viewport[4];         /// the viewport
    
   glGetIntegerv(GL_VIEWPORT, viewport);
   
   glMatrixMode(GL_MODELVIEW);
   glGetDoublev(GL_MODELVIEW_MATRIX, mMtx);
   glGetDoublev (GL_PROJECTION_MATRIX, pMtx);
     
   gluUnProject(x, y, 1.0, mMtx, pMtx, viewport, &xw, &yw, &zw);
}

void GLFrame::zoomIn() {
   
   AMatrix<float> matrixTransformation;
   matrixTransformation.identity();
   matrixTransformation.scaling(1.2);
   sceneTransformation  = matrixTransformation*sceneTransformation;
}

/// Implements the "zoomout" operation. Enlarges the view of the scene.
void GLFrame::zoomOut() {
	   
   AMatrix<float> matrixTransformation;
   matrixTransformation.identity();
   matrixTransformation.scaling(1.0/1.2);
   sceneTransformation  = matrixTransformation*sceneTransformation;
   
}
