#include <QtGui>
#include <QtOpenGL>

#include <limits>

#include <stdio.h>
#include <stdlib.h>


#include "GLFrame.hpp"


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

	Threshold = 1.0;
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


void GLFrame::LODSelection( OctreeNode<float,Surfel<float>* > * pNode, int& cont)
{


	if ( pNode->isLeaf() == true )
	{

		std::list< Surfel<float>* > lp = pNode->itemList();

		for(std::list< Surfel<float>* >::iterator surfe = lp.begin(); surfe != lp.end(); ++surfe )
		{
			LAL::Vector3<float> eye =  camera.Eyes();
			LAL::Vector3<float> p ((*surfe)->Center().x,(*surfe)->Center().y,(*surfe)->Center().z);
			LAL::Vector3<float> dir = p - eye;

			dir.Normalize();

			float cosNDir = (dir*(*surfe)->Normal());

			if ( cosNDir < 0.0)
			{
				//						LAL::Point3<float> point = (*surfe)->Center();
//				glPointSize(5.0);
//				//(*surfe)->draw();
//				if ( pNode->level() == 2 )
//					glColor4f(1.0,0.0,0.0,0.75);
//				else if ( pNode->level() == 3 )
//					glColor4f(1.0,0.0,1.0,075);
//				else if ( pNode->level() == 4 )
//					glColor4f(1.0,1.0,0.0,0.75);
//				else if ( pNode->level() == 5 )
//					glColor4f(0.0,1.0,0.0,0.75);
//				else if ( pNode->level() == 6 )
//					glColor4f(0.0,1.0,1.0,0.75);
//				else if ( pNode->level() == 7 )
//					glColor4f(0.0,0.0,1.0,0.75);
//				else
					//glColor4f(0.5,0.5,0.5,0.75);
				glVertex3fv((*surfe)->Center().ToRealPtr());
				//(*surfe)->drawTriangleFan(8);
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
			LAL::Vector3<float> eye = camera.Eyes();

			LAL::Vector3<float> p (lInternalNode->surfel()->Center().x,lInternalNode->surfel()->Center().y,lInternalNode->surfel()->Center().z);
			LAL::Vector3<float> dir =  p - eye ;


			float cosNDir = (dir.Norm() * lInternalNode->surfel()->Normal());

			if ( cosNDir < 0.0 )
			{


				if ( (lInternalNode->geometricError(eye) < Threshold) )
					{
//						glPointSize(3.0);
//
//						if ( lInternalNode->level() == 2 )
//							glColor4f(1.0,0.0,0.0,0.75);
//						else if ( lInternalNode->level() == 3 )
//							glColor4f(1.0,0.0,1.0,0.75);
//						else if ( lInternalNode->level() == 4 )
//							glColor4f(1.0,1.0,0.0,0.75);
//						else if ( lInternalNode->level() == 5 )
//							glColor4f(0.0,1.0,0.0,0.75);
//						else if ( lInternalNode->level() == 6 )
//							glColor4f(0.0,1.0,1.0,0.75);
//						else if ( lInternalNode->level() == 7 )
//							glColor4f(0.0,0.0,1.0,0.75);
//						else
							//glColor4f(0.5f,0.5f,0.5f,0.75);

						//lInternalNode->surfel()->draw(20);
						LAL::Point3<float> p = lInternalNode->surfel()->Center();
						glVertex3fv( p.ToRealPtr() );
						//lInternalNode->surfel()->drawTriangleFan(8);
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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);           //cor fundo
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);           //cor fundo
	glShadeModel(GL_SMOOTH);                      	//gouraud
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, luzDifusa);//refletancia do material
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, especularidade);//refletancia do material
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,especMaterial);  //concentracao do brilho

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);        //luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, luzAmbiente);        //luz ambiente
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);  //parametros da luz 0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_position );

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);  //cor do material a partir da cor corrente
	glEnable(GL_LIGHTING);        //uso de iluminacao
	glEnable(GL_LIGHT0);          //luz  0
	glEnable(GL_DEPTH_TEST);      //depth-buffering

	glEnable(GL_NORMALIZE);

}


/// Draw a node's bounding box and it's contained points
/// @param n kd-tree node
/// @return 1 if empty or leaf node, 0 if internal node
bool GLFrame::drawKdNode(const KdTree3DNode* n) {

  if (n == NULL)
    return 1;

  GLfloat cur_color[4];
  glGetFloatv(GL_CURRENT_COLOR, cur_color);

  glPointSize(1.0);
  glBegin(GL_POINTS);
  glColor4f(0.3, 0.3, 0.3, 1.0);
  

  for (int i = 0; i < n->ItemCount(); ++i) {

	LAL::Vector3<float> p( n->Element(i).x,n->Element(i).y,n->Element(i).z );
    glVertex3fv( p.ToRealPtr() );
//	for( std::deque<LAL::Point3<float> >::iterator i = ItemList.begin() ; i != ItemList.end(); ++i) 
//	{
//		LAL::Vector3<float> p( ((*i)).x,((*i)).y,((*i)).z );
//
//		glVertex3fv( p.ToRealPtr() );
//	}

  }
  
  glEnd();

  glColor4fv(cur_color);

  // Only draw leaf node's boxes

   if (!n->IsLeaf())
    return 0;

  drawBox(n->Box());

  return 1;
}

/// Recursively draw all kd-tree nodes
/// @param n kd-tree node
void GLFrame::drawKdNodeRecursively(const KdTree3DNode* n) {
  const KdTree3DNode* leftNode = n->Left();
  const KdTree3DNode* rightNode = n->Right();

  if (!drawKdNode(leftNode))
    drawKdNodeRecursively(leftNode);

  if (!drawKdNode(rightNode))
    drawKdNodeRecursively(rightNode);
}

/// Draw the kd-tree leaf nodes' boxes and all elements stored in all nodes
void GLFrame::drawKdTree(void)
{
  KdTree3DNode* root = kdTree.Begin();

  glColor4f(0.3, 0.3, 1.0, 1.0);
  glLineWidth(1.0);

  drawKdNode(root); //draw root node first

  drawKdNodeRecursively(root); //draw entire tree

}



void GLFrame::drawPoints(int& cont) 
{
	
   LODSelection(octree.root,cont);

}

void GLFrame::calLimits()
{

	Box_3<float> world = Box_3<float>( LAL::Point3<float>(surfels.box().xMin(),surfels.box().yMin(),surfels.box().zMin()),
				   						 LAL::Point3<float>(surfels.box().xMax(),surfels.box().yMax(),surfels.box().zMax()));

	octree = Octree<float,Surfel<float>* >(world,mode) ;
	kdTree = KdTree<float,LAL::Point3<float> >(world);

	for (std::vector<Surfel<float> >::iterator surf =  surfels.surfels.begin();surf != surfels.surfels.end(); ++ surf )
	{

		octree.insert (new Surfel<float>(*surf));
	    kdTree.Insert ( surf->Center() );
	    midlePoint += surf->Center();

	}

	midlePoint /= surfels.surfels.size();

    std::cout << octree.root->itemPtrCount() <<  " AAA" << std::endl;
    std::cout << kdTree.root->ItemCount() <<  " BBB" << std::endl;

    int k_nearest_search_comps = 0;

    ItemList = kdTree.KNearestNeighbors( LAL::Point3<float>( 0.0515251f , -0.084186f, 0.238488f ),40, k_nearest_search_comps);

    std::cout << ItemList.size() <<  " BdBB" << std::endl;
    
   
    octree.split();

    GLuint fbo;
    //frame begin

    //save viewport and set up new one
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT,(int*)viewport);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    	octree.Merge();
    glPopMatrix();
    glPopAttrib();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width()) / height();
    camera.SetProjectionMatrix(90.0,x,0.1,1000);
    glLoadMatrixf((~camera.PespectiveProjectionMatrix()).ToRealPtr());
    glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);

    // frame end


}

template <class T>
void GLFrame::drawBox(LAL::BoundingBox3<T> BBox){
  glColor3f (1.0, 1.0, 1.0);//white

  glBegin(GL_LINE_LOOP);
    glVertex3f(BBox.xMin(), BBox.yMin(), BBox.zMin());
    glVertex3f(BBox.xMax(), BBox.yMin(), BBox.zMin());
    glVertex3f(BBox.xMax(), BBox.yMax(), BBox.zMin());
    glVertex3f(BBox.xMin(), BBox.yMax(), BBox.zMin());
  glEnd();

  glBegin(GL_LINE_LOOP);
    glVertex3f(BBox.xMin(), BBox.yMin(), BBox.zMax());
    glVertex3f(BBox.xMax(), BBox.yMin(), BBox.zMax());
    glVertex3f(BBox.xMax(), BBox.yMax(), BBox.zMax());
    glVertex3f(BBox.xMin(), BBox.yMax(), BBox.zMax());
  glEnd();

  glBegin(GL_LINES);
    glVertex3f(BBox.xMin(), BBox.yMin(), BBox.zMax());
    glVertex3f(BBox.xMin(), BBox.yMin(), BBox.zMin());
    glVertex3f(BBox.xMax(), BBox.yMin(), BBox.zMax());
    glVertex3f(BBox.xMax(), BBox.yMin(), BBox.zMin());

    glVertex3f(BBox.xMax(), BBox.yMax(), BBox.zMax());
    glVertex3f(BBox.xMax(), BBox.yMax(), BBox.zMin());

    glVertex3f(BBox.xMin(), BBox.yMax(), BBox.zMax());
    glVertex3f(BBox.xMin(), BBox.yMax(), BBox.zMin());
  glEnd();
}

void GLFrame::resizeGL(int width, int height)
{

    glViewport(0, 0, width, height);
    camera.SetWindowSize(width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    camera.SetProjectionMatrix(90.0,x,0.1,1000);

//    camera.SetProjectionMatrix(-p,p,-p,p/*(GLfloat(height)/width)*/,-100.0f,100.0f);
//    camera.SetProjectionMatrix(-su1->MajorAxis().first,su1->MajorAxis().first,-su1->MinorAxis().first,su1->MinorAxis().first/*(GLfloat(height)/width)*/,-100.0f,100.0f);

    glLoadMatrixf((~camera.PespectiveProjectionMatrix()).ToRealPtr());
   // glLoadMatrixf((~camera.OrthographicProjectionMatrix()).ToRealPtr());
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

    glMultMatrixf((~camera.ViewMatrix()).ToRealPtr());

    int cont = 0;

    if ( surfels.surfels.size() != 0 )
    {
    	drawKdTree();
    	if (renderMode_A == Points)
    	{
    		//drawPoints(cont);
    		glColor3f(0.5,0.5,0.5);
    		renderText(10,5,QString("___________________________"));
    		renderText(10,25,QString("Number of Points :"));renderText(145,25,QString::number(cont));
    		renderText(10,30,QString("___________________________"));


//    		for (OctreeIterator<float, Surfel<float>* > oi = octree.begin();oi != octree.end();++oi )
//    			drawBox(octree.box(oi));


    	}
    	DrawGroud();
    }

}

void GLFrame::keyPressEvent(QKeyEvent * event)
{

	if (event->key() == Qt::Key_Q)
	{
		camera.MoveUpward(CameraStep);

	}else if (event->key() == Qt::Key_E)
	{
		camera.MoveUpward(-CameraStep);

	}
	else if (event->key() == Qt::Key_W)
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
    	//camera.OnRotationBegin(event->x(),event->y());
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

    	//camera.OnRotationMove(event->x(), event->y());
    }

    /*!
     *  event->pos() retorna coordenadas x e y relativa a widget que recebeu o evento.
     *  mapToGlobla mapei as coordenadas da widget para coordenada global da tela.
     *  QCurso::setPos() posiciona o mouse em coordenada global.
     *  tudo o que eu queria para implementar a First Person Camera !
    */

    float heading = 0.0f;
    float pitch = 0.0f;
    float roll = 0.0f;

    pitch = -(static_cast<float>(event->x()) - mCenterX) * 0.2;
    heading = -(static_cast<float>(event->y()) - mCenterY) * 0.2;

    camera.rotate(pitch,heading, 0.0f);

//    mouse.moveToWindowCenter();

    QCursor::setPos(mapToGlobal(QPoint(static_cast<int>(mCenterX),static_cast<int>(mCenterY))));
 	updateGL();
    lastPos = event->pos();
}


