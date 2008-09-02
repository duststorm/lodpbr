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


	su1 =  new Surfel<float>(LAL::Point3<float>(7.938756, 8.396816, 5.958447),
			LAL::Vector3<float>(0.000000, 0.000000, 1.000000),1.0f,1.0f,0.0f);

	su1->SetMinorAxis(std::make_pair(0.1,LAL::Vector3<float>(1.000000, 0.000000, 0.000000)));
	su1->SetMajorAxis(std::make_pair(0.5,LAL::Vector3<float>(0.000000, 1.000000, 0.00000)));

	su2 =  new Surfel<float>(LAL::Point3<float>(6.632136, 7.704408, 5.995052),
				LAL::Vector3<float>(0.000000, 0.000000, 1.000000),1.0f,1.0f,0.0f);

	su2->SetMinorAxis(std::make_pair(0.4,LAL::Vector3<float>(1.000000, 0.000000, 0.000000)));
	su2->SetMajorAxis(std::make_pair(0.2,LAL::Vector3<float>(0.000000, 1.000000, 0.000000)));


	su3 = new Surfel<float>(LAL::Point3<float>(7.285446, 8.050611, 5.976750),
				LAL::Vector3<float>(0.000000, 0.000000, 1.000000),1.0f,1.0f,0.0f);

	su3->SetMinorAxis(std::make_pair(2.48653545051,LAL::Vector3<float>(0.460895, -0.887455, 0.000000)));
	su3->SetMajorAxis(std::make_pair(1.91656134622,LAL::Vector3<float>(-0.887455, -0.460895, 0.000000)));

	Surfel<float> * s = new Surfel<float>(LAL::Point3<float>(2.127096,-0.876474,1.482297),
			LAL::Vector3<float>(-0.291764,-0.174345,0.940467),1.0f,1.0f,0.0f);






	s->SetMinorAxis(std::make_pair(1.0,LAL::Vector3<float>(0.807313f, 0.482415f, 0.339886f)));
	s->SetMajorAxis(std::make_pair(2.0,LAL::Vector3<float>(-0.512952f, 0.858417f, 0.000000f)));

	std::list<Surfel<float>* > sl;

	//sl.push_back(s);



	s = new Surfel<float>(LAL::Point3<float>(0.459231f, 0.489174f, 1.334823f),
			LAL::Vector3<float>(0.444927f, -0.059414f, 0.893594f),1.0f,1.0f,0.0f);

	s->SetMinorAxis(std::make_pair(1.0,LAL::Vector3<float>(0.879801, -0.157404, -0.448525)));
	s->SetMajorAxis(std::make_pair(2.0,LAL::Vector3<float>(0.167304, 0.985745, -0.017761)));

	sl.push_back(su1);
	sl.push_back(su2);

	me = MergeEllipses<float>(sl);


	std::cout << me.mProjectedPoint.size() << "AAAAA" << std::endl;

	su = me.NewPtrSurfel();


//	camera.SetUp(su1->MinorAxis().second);
//	camera.SetPosition(LAL::Vector3<float>(su1->Center().x,su1->Center().y,su1->Center().z));
//	camera.SetEyes(LAL::Vector3<float>(su1->Center().x,su1->Center().y,su1->Center().z)+(-su1->Normal()*1.0f));


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

		//oi[lInternalNode->level()].push_back(lInternalNode->perpendicularError(camera.Eyes()));

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
			LAL::Vector3<float> eye =  camera.Eyes();
			LAL::Vector3<float> p ((*surfe)->Center().x,(*surfe)->Center().y,(*surfe)->Center().z);
			LAL::Vector3<float> dir = p - eye;

			dir.Normalize();

			float cosNDir = (dir*(*surfe)->Normal());

			if ( cosNDir < 0.0)
			{
				//						LAL::Point3<float> point = (*surfe)->Center();
				glPointSize(3.0);
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
				//(*surfe)->draw(20);
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
						glPointSize(3.0);

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

						//lInternalNode->surfel()->draw(20);
						//LAL::Point3<float> p = lInternalNode->surfel()->Center();
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

  glPointSize(5.0);
  glBegin(GL_POINTS);
  glColor4f(0.3, 0.3, 0.3, 1.0);

  for (int i = 0; i < n->itemPtrCount(); ++i) {

	LAL::Vector3<float> p( n->element(i)->x,n->element(i)->y,n->element(i)->z );
    glVertex3fv( p.ToRealPtr() );

  }

  glEnd();

  glColor4fv(cur_color);

  // Only draw leaf node's boxes

   if (!n->isLeaf())
    return 0;

  drawBox(n->getBox());

  return 1;
}

/// Recursively draw all kd-tree nodes
/// @param n kd-tree node
void GLFrame::drawKdNodeRecursively(const KdTree3DNode* n) {
  const KdTree3DNode* leftNode = n->left();
  const KdTree3DNode* rightNode = n->right();

  if (!drawKdNode(leftNode))
    drawKdNodeRecursively(leftNode);

  if (!drawKdNode(rightNode))
    drawKdNodeRecursively(rightNode);
}

/// Draw the kd-tree leaf nodes' boxes and all elements stored in all nodes
void GLFrame::drawKdTree(void)
{
  KdTree3DNode* root = kdTree.begin();

  glColor4f(0.3, 0.3, 1.0, 1.0);
  glLineWidth(1.0);

  drawKdNode(root); //draw root node first

  drawKdNodeRecursively(root); //draw entire tree

}



void GLFrame::drawPoints(int& cont) {

   glDisable(GL_DEPTH_TEST);
   glDisable(GL_LIGHTING);
   glPointSize(3.0);
   glBegin(GL_POINTS);

   drawKdTree();

   //LODSelection(octree.root,cont);

   //me.NewSurfel().draw();

   //glVertex3fv( su.Center().ToRealPtr() );


//   su3.draw();
//   su1->draw();
//   su2.draw();

   glEnd();

//
//   glColor3f(1.0,0.0,0.0);
//   glBegin(GL_TRIANGLE_FAN);
//   me.NewSurfel().draw();
//   glEnd();
//
//   glColor3f(0.0,1.0,0.0);
//   glBegin(GL_TRIANGLE_FAN);
//   su1->draw();
//   glEnd();
//
//   glBegin(GL_TRIANGLE_FAN);
//   su2->draw();
//   glEnd();

   glEnable(GL_LIGHTING);
   glPointSize(1.0);

   glEnable(GL_DEPTH_TEST);


}

void GLFrame::calLimits()
{

	Box_3<float> world = Box_3<float>( LAL::Point3<float>(surfels.box().xmin(),surfels.box().ymin(),surfels.box().zmin()),
				   						 LAL::Point3<float>(surfels.box().xmax(),surfels.box().ymax(),surfels.box().zmax()));

	octree = Octree<float,Surfel<float>* >(world,mode) ;
	kdTree = KdTree<float,LAL::Point3<float>* >(world);

	for (std::vector<Surfel<float> >::iterator surf =  surfels.surfels.begin();surf != surfels.surfels.end(); ++ surf )
	{

		//octree.insert (new Surfel<float>(*surf));
	    kdTree.insert (new LAL::Point3<float>( (*surf).Center() ) );
	    midlePoint += surf->Center();

	}

	midlePoint /= surfels.surfels.size();

    std::cout << octree.root->itemPtrCount() <<  " AAA" << std::endl;
    std::cout << kdTree.root->itemPtrCount() <<  " BBB" << std::endl;

    octree.split();

    GLuint fbo;
    //frame begin

    //save viewport and set up new one
//    int viewport[4];
//    glGetIntegerv(GL_VIEWPORT,(int*)viewport);
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

//    glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);

    // frame end


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
    camera.SetWindowSize(width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    camera.SetProjectionMatrix(90.0,x,0.1,1000);

//    camera.SetProjectionMatrix(-p,p,-p,p/*(GLfloat(height)/width)*/,-100.0f,100.0f);
//    camera.SetProjectionMatrix(-su1->MajorAxis().first,su1->MajorAxis().first,-su1->MinorAxis().first,su1->MinorAxis().first/*(GLfloat(height)/width)*/,-100.0f,100.0f);

    glLoadMatrixf((~camera.PespectiveProjectionMatrix()).ToRealPtr());
//    glLoadMatrixf((~camera.OrthographicProjectionMatrix()).ToRealPtr());
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
    	if (renderMode_A == Points)
    	{
    		drawPoints(cont);
    		glColor3f(1.0,1.0,1.0);
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

//glLoadIdentity();
//
//	camera.SetUp(me.MinorAxis().second);
//	camera.SetPosition(LAL::Vector3<float>(me.Center().x,me.Center().y,me.Center().z));
//	camera.SetEyes(LAL::Vector3<float>(me.Center().x,me.Center().y,me.Center().z)+(-me.Normal()*1.0f));
//
//   camera.SetProjectionMatrix(-me.MajorAxis().first,me.MajorAxis().first,-me.MinorAxis().first,me.MinorAxis().first,-100.0f,100.0f);
//
//   glLoadMatrixf((~camera.OrthographicProjectionMatrix()).ToRealPtr());
//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();
//
//   glMultMatrixf((~camera.ViewMatrixNormal()).ToRealPtr());
//
//   glClearColor(0.0f,0.0f,0.0f,0.0f);
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   glDrawBuffer(GL_BACK);
//   glColor3f(1.0,0.0,0.0);
//
//   glDisable(GL_DEPTH_TEST);
//   glBegin(GL_TRIANGLE_FAN);
//   	me.NewSurfel().draw(8);
//   glEnd();
//   glColor3f(0.0,1.0,0.0);
//	int cont = 0;
//	std::list<LAL::Point3<float>* >::iterator it;
//
//   for( it = me.mProjectedPoint.begin(); it != me.mProjectedPoint.end(); ++it  )
//   {
//   	if ( (cont % 8) == 0)
//   		glBegin(GL_TRIANGLE_FAN);
//
//   			glVertex3fv(  (*it)->ToRealPtr()  );
//
//   		cont++;
//   	if ( (cont % 8) == 0)
//   		glEnd();
//
//   }
//
////	   glBegin(GL_TRIANGLE_FAN);
////	   su1->draw();
////	   glEnd();
////
////	   glBegin(GL_TRIANGLE_FAN);
////	   su2->draw();
////	   glEnd();
//
//   glFlush();
//
//   glEnable(GL_DEPTH_TEST);
//   GLfloat *outputBuffer = new GLfloat[width * height * 4];
//   glReadBuffer(GL_BACK);
//   glReadPixels(0, 0, width , height, GL_RGBA, GL_FLOAT, &outputBuffer[0]);
//   glPopMatrix();
//
//
//   float red   = 0 ;
//   float green = 0;
//
//   for (int i = 0; i < width * height * 4; i+=4)
//   {
//       red   += outputBuffer[i + 0];
//       green += outputBuffer[i + 1];
//   }
//
//   std::cout << "cont " << me.mProjectedPoint.size() << std::endl;
//   std::cout << "red " << red << std::endl;
//
//   std::cout << "green " << green << std::endl;
//
//   std::cout << "% " << green/(red+green) << std::endl;
