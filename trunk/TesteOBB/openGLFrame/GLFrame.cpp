#include <QtGui>
#include <QtOpenGL>

#include "GLFrame.hpp"

GLFrame::GLFrame(QWidget *parent):QGLWidget(parent)
{
	
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    
    rotationX = -21.0;
    rotationY = -57.0;
    rotationZ = 0.0;
    zoomFactor = 1.0;
    
    setFocusPolicy(Qt::StrongFocus);
   
	renderMode_A = PolygonWireFrame;
	show_A 	= true;
	
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

void GLFrame::drawPoints() {
   
   glDisable(GL_LIGHTING);		
   glPointSize(5.0);
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_POINTS);
   
   Surfels<double>::iterator surf =  surfels.begin();
   
   while ( surf != surfels.end() ) {
	        
      glVertex3f(surf->position(0),surf->position(1),surf->position(2));
      
      ++surf;
   }
   
   glEnd();
   glEnable(GL_LIGHTING);
   glPointSize(1.0);
}

void GLFrame::calLimits()
{
	/*Box_3<double> world = Box_3<double>( SLAL::Point3<double>(surfels.box().xmin(),surfels.box().ymin(),surfels.box().zmin()),
				   						 SLAL::Point3<double>(surfels.box().xmax(),surfels.box().ymax(),surfels.box().zmax()));
	 
	octree = Octree<double,SLAL::Point3<double>*>(world) ;

	Surfels<double>::iterator surf =  surfels.begin();
	
    while( surf != surfels.end() ) 
    {
    	SLAL::Point3<double> *fh = new SLAL::Point3<double>(surf->position(0),surf->position(1),surf->position(2));
        octree.insert (fh);
        surf++;
    }
	 
    std::cout << octree.root->itemPtrCount() <<  "AAA" << std::endl;*/
    
}

template <class T>
void GLFrame::drawBox(SLAL::BoundingBox3<T> BBox){
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
    glTranslated(0.0,0.0,-5.0);
    glMultMatrixf(&sceneTransformation);
    if ( surfels.size() != 0 )
    {
    	drawPoints();
    }
    	
    /*
	if( A  and  isVisible_A()  )
	{
		
		   for (OctreeIterator<double, SLAL::Point3<double>*> oi = octree.begin();oi != octree.end();++oi )
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
