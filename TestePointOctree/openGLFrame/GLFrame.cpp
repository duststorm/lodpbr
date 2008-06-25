#include <QtGui>
#include <QtOpenGL>

#include <limits>

#include "GLFrame.hpp"
#include "surfels/MergeEllipses.hpp"

#define DA_APLICACAO_PASSADA 0

GLFrame::GLFrame(QWidget *parent):QGLWidget(parent)
{
	
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    setMouseTracking(true);
    
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

void GLFrame::SIZE(OctreeNode<float,Surfel<float>* > * pNode, long int& cont,std::map < int , std::vector<float> >& oi)
{
	
	
 	
	if ( pNode->isLeaf() == true )
	{
		cont += sizeof(*pNode); 
	}
	else
	{
		OctreeInternalNode<float,Surfel<float>* > * lInternalNode = dynamic_cast<OctreeInternalNode< float,Surfel<float>* >* >(pNode);

		for(int i = 0; i < 8; ++i)
			SIZE(lInternalNode->son[i],cont,oi);
				
		oi[lInternalNode->level()].push_back(lInternalNode->perpendicularError(camera.eyes()));  
				
		cont += sizeof(*lInternalNode);
	}

	
}

void GLFrame::LODSelection( OctreeNode<float,Surfel<float>* > * pNode, int& cont)
{
	
	if ( pNode->isLeaf() == true )
	{

		std::list< Surfel<float>* > lp = pNode->itemList();

		for(std::list< Surfel<float>* >::iterator surfe = lp.begin(); surfe != lp.end(); ++surfe )
		{
			LAL::Vector3<float> eyeInverse =  camera.eyes();
			LAL::Vector3<float> p ((*surfe)->Center().x,(*surfe)->Center().y,(*surfe)->Center().z);
			LAL::Vector3<float> dir = p - eyeInverse;

			dir.Normalize();

			float cosNDir = (dir*(*surfe)->Normal());

			if ( cosNDir < 0.0)
			{
				//						LAL::Point3<float> point = (*surfe)->Center();
				glPointSize(1.0);
				//(*surfe)->draw();
				if ( pNode->level() == 2 )
					glColor3f(1.0,0.0,0.0);
				else if ( pNode->level() == 3 )
					glColor3f(1.0,0.0,1.0);
				else if ( pNode->level() == 4 )
					glColor3f(1.0,1.0,0.0);
				else if ( pNode->level() == 5 )
					glColor3f(0.0,1.0,0.0);
				else if ( pNode->level() == 6 )
					glColor3f(0.0,1.0,1.0);
				else if ( pNode->level() == 7 )
					glColor3f(0.0,0.0,1.0);
				else 
					glColor3f(1.0,1.0,1.0);
				glVertex3fv((*surfe)->Center().ToRealPtr());
				cont++;
			}

		}	
		
	}else
	{
		
		OctreeInternalNode<float,Surfel<float>* > * lInternalNode = dynamic_cast<OctreeInternalNode< float,Surfel<float>* >* >(pNode);
			
//		for(int i = 0; i < 8; ++i)
//			LODSelection(lInternalNode->son[i],cont);
		if ( lInternalNode->level() < 1)
		{
			for(int i = 0; i < 8; ++i)
				LODSelection(lInternalNode->son[i],cont);
		}
		else
		{
			LAL::Vector3<float> v (camera.eyes());
			LAL::Vector3<float> eyeInverse = camera.eyes();

			LAL::Vector3<float> p (lInternalNode->surfel()->Center().x,lInternalNode->surfel()->Center().y,lInternalNode->surfel()->Center().z);
			LAL::Vector3<float> dir =  p - eyeInverse ;

			dir.Normalize();
			
			float cosNDir = (dir * lInternalNode->surfel()->Normal());

			if ( cosNDir < lInternalNode->normalCone())
			{
					
				if ( (lInternalNode->perpendicularError(v) >= 0) && (lInternalNode->perpendicularError(v) < Threshold))
					{
						glPointSize(1.0);

						if ( lInternalNode->level() == 2 )
							glColor3f(1.0,0.0,0.0);
						else if ( lInternalNode->level() == 3 )
							glColor3f(1.0,0.0,1.0);
						else if ( lInternalNode->level() == 4 )
							glColor3f(1.0,1.0,0.0);
						else if ( lInternalNode->level() == 5 )
							glColor3f(0.0,1.0,0.0);
						else if ( lInternalNode->level() == 6 )
							glColor3f(0.0,1.0,1.0);
						else if ( lInternalNode->level() == 7 )
							glColor3f(0.0,0.0,1.0);
						else 
							glColor3f(1.0,1.0,1.0);

						//lInternalNode->surfel()->draw();
						LAL::Point3<float> p = lInternalNode->surfel()->Center();
						glVertex3fv( p.ToRealPtr() );
						cont++;

					}
				
				else
				{
					for(int i = 0; i < 8; ++i)
						LODSelection(lInternalNode->son[i],cont);
				}
				
			}else
			{
				for(int i = 0; i < 8; ++i)
					LODSelection(lInternalNode->son[i],cont);
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
    
    std::map < int , std::vector<float> > oi;
    
    SIZE(octree.root,cont,oi);
        
	for(std::map<int , std::vector<float> >::iterator it = oi.begin(); it != oi.end(); ++it)
	{
    	std::cout << "level min " << it->first << ":>" << *(std::min_element(it->second.begin(),it->second.end()) ) << std::endl;
    	std::cout << "level max " << it->first << ":>" << *(std::max_element(it->second.begin(),it->second.end()) ) << std::endl;
    	std::cout << "----" << std::endl;
	}
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
    camera.setWindowSize(width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    camera.setProjectionMatrix(90.0,x,0.1,1000);
    
    if (width <= height)
      camera.setProjectionMatrix(-1.0f, 1.0f, -1.0f, 1.0f/*(GLfloat(height)/width)*/,-10.0f,10.0f);
    else                              
      camera.setProjectionMatrix(-1.0f, 1.0f/*(GLfloat(width)/height)*/, -1.0f, 1.0f,-10.0f,10.0f);
    
    glLoadMatrixf((~camera.pespectiveProjectionMatrix()).ToRealPtr());//((~camera.orthographicProjectionMatrix()).ToRealPtr());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mCenterX =  static_cast<float> (width*0.5);
    mCenterY =  static_cast<float> (height*0.5);
       
}

void GLFrame::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf((~camera.viewMatrix()).ToRealPtr());
    
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
    
//    float heading = 0.0f;
//    float pitch = 0.0f;
//    float roll = 0.0f;
//
//    pitch = (static_cast<float>(event->x()) - mCenterX) * 0.2;
//    heading = -(static_cast<float>(event->y()) - mCenterY) * 0.2;
//
//    camera.rotate(heading, pitch, 0.0f);
//
//    //mouse.moveToWindowCenter();
//    QCursor::setPos(mapToGlobal(QPoint(static_cast<int>(width()*0.5),static_cast<int>(height()*0.5))));
 	updateGL();
    lastPos = event->pos();
}


