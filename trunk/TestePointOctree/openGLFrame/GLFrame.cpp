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
	
	midlePoint = LAL::Point3<float>();
	
	surfels = Surfels<float>();
	
	Threshold = 0.01;
	CameraStep = 0.01;
	mode = true;

    
}

void GLFrame::SetThreshold(const float& t)
{
	Threshold = t;
}

void GLFrame::SetCameraStep(const float& t)
{
	CameraStep = t;
}
void GLFrame::SetMode(bool t)
{
	mode = t;
}

void GLFrame::SIZE(OctreeNode<float,Surfel<float>* > * pNode, long int& cont)
{
	if ( pNode->isLeaf() == true )
	{
		cont += sizeof(*pNode); 
	}
	else
	{
		OctreeInternalNode<float,Surfel<float>* > * lInternalNode = dynamic_cast<OctreeInternalNode< float,Surfel<float>* >* >(pNode);

		for(int i = 0; i < 8; ++i)
			SIZE(lInternalNode->son[i],cont);
		cont += sizeof(*lInternalNode);
	}

}

void GLFrame::LODSelection( OctreeNode<float,Surfel<float>* > * pNode, int& cont)
{
	if ( pNode->isLeaf() == true )
	{

		if (pNode->MeanItem() != NULL)
		{
			LAL::Vector3<float> eyeInverse = camera.eyes();
			LAL::Vector3<float> p (pNode->MeanItem()->Center().x,pNode->MeanItem()->Center().y,pNode->MeanItem()->Center().z);
			LAL::Vector3<float> dir =  p - eyeInverse ;
			dir.normalize();
			float cosNDir = (dir*pNode->MeanItem()->Normal());
			
			if (cosNDir < pNode->NormalCone() )
			{

				std::list< Surfel<float>* > lp = pNode->itemList();



				for(std::list< Surfel<float>* >::iterator surfe = lp.begin(); surfe != lp.end(); ++surfe )
				{
					LAL::Vector3<float> eyeInverse =  camera.eyes();
					LAL::Vector3<float> p ((*surfe)->Center().x,(*surfe)->Center().y,(*surfe)->Center().z);
					LAL::Vector3<float> dir = p - eyeInverse;

					dir.normalize();

					float cosNDir = (dir*(*surfe)->Normal());

					if ( cosNDir < 0.0)
					{
//						LAL::Point3<float> point = (*surfe)->Center();
						glPointSize(1.0);
						//(*surfe)->draw();
						glColor3f(0.0,1.0,0.0);
						glVertex3fv((*surfe)->Center());
						cont++;
					}

				}	
			}
		}
	}else
	{
		
		OctreeInternalNode<float,Surfel<float>* > * lInternalNode = dynamic_cast<OctreeInternalNode< float,Surfel<float>* >* >(pNode);
//			
//		for(int i = 0; i < 8; ++i)
//			LODSelection(lInternalNode->son[i],cont);
		if ( lInternalNode->level() < 3)
		{
			for(int i = 0; i < 8; ++i)
				LODSelection(lInternalNode->son[i],cont);
		}
		else
		{
			LAL::Vector3<float> v (camera.eyes());
			LAL::Vector3<float> eyeInverse = camera.eyes();

			LAL::Vector3<float> p (lInternalNode->MeanItem()->Center().x,lInternalNode->MeanItem()->Center().y,lInternalNode->MeanItem()->Center().z);
			LAL::Vector3<float> dir =  p - eyeInverse ;

			dir.normalize();

			float cosNDir = (dir * lInternalNode->MeanItem()->Normal());

			if ( cosNDir < lInternalNode->NormalCone())
			{
				if (lInternalNode->PerpendicularError(v) < Threshold)
				{
					glPointSize(1.0);
					glColor3f(1.0,0.0,0.0);
					//lInternalNode->MeanItem()->draw();
//					LAL::Point3<float> p = lInternalNode->MeanItem()->Center();
					glVertex3fv( lInternalNode->MeanItem()->Center());
					cont++;

				}else
				{
					for(int i = 0; i < 8; ++i)
						LODSelection(lInternalNode->son[i],cont);
				}
			}
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
	
	Box_3<float> world = Box_3<float>( LAL::Point3<float>(surfels.box().xmin(),surfels.box().ymin(),surfels.box().zmin()),
				   						 LAL::Point3<float>(surfels.box().xmax(),surfels.box().ymax(),surfels.box().zmax()));
	 
	octree = Octree<float,Surfel<float>* >(world,mode) ;
	
	for (std::vector<Surfel<float> >::iterator surf =  surfels.surfels.begin();surf != surfels.surfels.end(); ++ surf ) 
	{
		
		octree.insert (new Surfel<float>(*surf));
	    midlePoint += surf->Center();
	    
	}
	
	midlePoint /= surfels.surfels.size();  
		
    std::cout << octree.root->itemPtrCount() <<  " AAA" << std::endl;
    
    octree.split();
    octree.Merge();
    
    long int cont = 0;
    
                   
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
    camera.setProjectionMatrix(90.0,x,0.1,1000);
    glLoadMatrixf(~camera.projectionMatrix());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.setWindowSize(width,height);
}

void GLFrame::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(~camera.projectionMatrix());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(~camera.viewMatrix());
    
    std::cout << ~camera.viewMatrix(); 
    
    if ( surfels.surfels.size() != 0 )
    {
    	if (renderMode_A == Points)
    	{
    		drawPoints();
//    		for (OctreeIterator<float, Surfel<float>* > oi = octree.begin();oi != octree.end();++oi )
//    			drawBox(octree.box(oi));


    	}
    	DrawGroud();
    }


}

void GLFrame::keyPressEvent(QKeyEvent * event)
{
//	QMessageBox::information( 0, "MessageBox", "Key pressed" );
	if (event->key() == Qt::Key_W)
	{
		camera.moveForward(CameraStep);	
		
	}
	else if (event->key() == Qt::Key_S){
		camera.moveForward(-CameraStep);
	 	
	}
	else if (event->key() == Qt::Key_A){
		camera.strafeRight(CameraStep);   	
	
	}
	else if (event->key() == Qt::Key_D){
		camera.strafeRight(-CameraStep);   	
	
	}
	else if (event->key() == Qt::Key_R){
	
		camera.reset();
	}
	else {}
	updateGL();

		
}

void GLFrame::mousePressEvent(QMouseEvent *event)
{
	 
    if (event->button() == Qt::MidButton) 
    {
    	camera.onRotationBegin(event->x(),event->y());
    	updateGL(); 
    }
    else if (event->button() == Qt::RightButton) 
    {
    	    	
    }
        
    lastPos = event->pos();
}

void GLFrame::wheelEvent(QWheelEvent *e) 
{
   camera.zoom(e->delta()/120.0);
   updateGL();
}


void GLFrame::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) 
    {

    }else if (event->buttons() & Qt::RightButton) {
        
      
    }else if (event->buttons() & Qt::MidButton)  {
 	
    	camera.onRotationMove(event->x(), event->y());
    }
    
    /*!
     *  event->pos() retorna coordenadas x e y relativa a widget que recebeu o evento.  
     *  mapToGlobla mapei as coordenadas da widget para coordenada global da tela.
     *  QCurso::setPos() posiciona o mouse em coordenada global.
     *  tudo o que eu queria para implementar a First Person Camera !  
    */
    
    //QCursor::setPos(mapToGlobal(QPoint(static_cast<int>(width()*0.5),static_cast<int>(height()*0.5))));
 	updateGL();
    lastPos = event->pos();
}


