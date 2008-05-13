#include <QtGui>
#include <QtOpenGL>

#include <limits>

#include "GLFrame.hpp"
#include "surfels/MergeEllipses.hpp"

#define DA_APLICACAO_PASSADA 0

GLFrame::GLFrame(QWidget *parent):QGLWidget(parent)
{
	
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    
    setFocusPolicy(Qt::StrongFocus);
   
	renderMode_A = Points;
	show_A 	= true;
	
	midlePoint = LAL::Point3<double>();
	
	surfels = Surfels<double>();
	
	Threshold = 0.01;
	CameraStep = 0.01;
	mode = true;

    
}

void GLFrame::SetThreshold(const double& t)
{
	Threshold = t;
}

void GLFrame::SetCameraStep(const double& t)
{
	CameraStep = t;
}
void GLFrame::SetMode(bool t)
{
	mode = t;
}

void GLFrame::LODSelection( OctreeNode<double,Surfel<double>* > * pNode, int& cont)
{
	if ( pNode->isLeaf() == true )
	{

		std::list< Surfel<double>* > lp = pNode->itemList();

		for(std::list< Surfel<double>* >::iterator surfe = lp.begin(); surfe != lp.end(); ++surfe )
		{
			LAL::Point3<double> point = (*surfe)->Center();
			glPointSize(3.0);
			glColor3f(0.0,1.0,0.0);
			glVertex3f(point[0],point[1],point[2]);

			cont++;
		}	

		
	}else
	{
		
		OctreeInternalNode<double,Surfel<double>* > * lInternalNode = dynamic_cast<OctreeInternalNode< double,Surfel<double>* >* >(pNode);
			
		LAL::Vector3<double> v (camera.Eyes());
		   
		//std::cout << " - " << lInternalNode->PerpendicularError(v) << " - " <<  Threshold << std::endl;
		
		if (lInternalNode->PerpendicularError(v) < Threshold)
		{
			glPointSize(1.0);
			glColor3f(1.0,0.0,0.0);
			lInternalNode->MeanItem()->draw();
//			LAL::Point3<double> p = lInternalNode->MeanItem()->Center();
//			glVertex3f(p[0],p[1],p[2]);
			cont++;
			
		}else
		{
			for(int i = 0; i < 8; ++i)
				LODSelection(lInternalNode->son[i],cont);
		}

			   
	}
}

void GLFrame::DrawGroud()
{
	glDisable(GL_LIGHTING);  
	glColor3f(0.2f, 0.2f, 0.2f);

	// draw the lines
	glBegin(GL_LINES);

	
	for (int x = -250; x < 250; x += 6)
	{
		glVertex3i(x, 0, -250);
		glVertex3i(x, 0, 250);
	}

	for (int z = -250; z < 250; z += 6)
	{
		glVertex3i(-250, 0, z);
		glVertex3i(250, 0, z);
	}
	glEnd();
	glEnable(GL_LIGHTING);  
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
	

}




void GLFrame::drawPoints() {
   
   glDisable(GL_LIGHTING);		
   glPointSize(3.0);
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_POINTS);
   
   int cont = 0;
   
   LODSelection(octree.root,cont);
   
   std::cout << "Total " <<  mode << " = " << cont << std::endl;
     
   glEnd();
   glEnable(GL_LIGHTING);
   glPointSize(1.0);
}

void GLFrame::calLimits()
{
	
	Box_3<double> world = Box_3<double>( LAL::Point3<double>(surfels.box().xmin(),surfels.box().ymin(),surfels.box().zmin()),
				   						 LAL::Point3<double>(surfels.box().xmax(),surfels.box().ymax(),surfels.box().zmax()));
	 
	octree = Octree<double,Surfel<double>* >(world,mode) ;
	
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
void GLFrame::drawBox(LAL::BoundingBox3<T> BBox){
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
    camera.SetProjectionMatrix(90.0,x,0.1,1000);
    glLoadMatrixf(~camera.ProjectionMatrix());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.SetWindowSize(width,height);
}

void GLFrame::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(~camera.ProjectionMatrix());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(~camera.ViewMatrix());
    
    
    if ( surfels.surfels.size() != 0 )
    {
    	if (renderMode_A == Points)
    	{
    		drawPoints();
    	}
    	DrawGroud();
    }


}

void GLFrame::keyPressEvent(QKeyEvent * event)
{
//	QMessageBox::information( 0, "MessageBox", "Key pressed" );
	if (event->key() == Qt::Key_W)
	{
		camera.MoveForward(CameraStep);	
		
	}
	else if (event->key() == Qt::Key_S){
		camera.MoveForward(-CameraStep);
	 	
	}
	else if (event->key() == Qt::Key_A){
		camera.StrafeRight(CameraStep);   	
	
	}
	else if (event->key() == Qt::Key_D){
		camera.StrafeRight(-CameraStep);   	
	
	}
	else if (event->key() == Qt::Key_R){
	
		camera.Reset();
	}
	else {}
	updateGL();

		
}

void GLFrame::mousePressEvent(QMouseEvent *event)
{
	 
    if (event->button() == Qt::MidButton) 
    {
    	camera.OnRotationBegin(event->x(),event->y());
    	updateGL(); 
    }
    else if (event->button() == Qt::RightButton) 
    {
    	    	
    }
    

    lastPos = event->pos();
}

void GLFrame::wheelEvent(QWheelEvent *e) 
{
   camera.Zoom(e->delta()/120.0);
   updateGL();
}


void GLFrame::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) 
    {

    }else if (event->buttons() & Qt::RightButton) {
        
      
    }else if (event->buttons() & Qt::MidButton)  {
 	
    	camera.OnRotationMove(event->x(), event->y());
    }
 	updateGL();
    lastPos = event->pos();
}


