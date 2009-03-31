#include <QtGui>
#include <QtOpenGL>

#include <limits>

#include <stdio.h>
#include <stdlib.h>


#include "GLFrame.hpp"
#include "Surfels/MergeEllipses.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

#define DA_APLICACAO_PASSADA 0

GLFrame::GLFrame(QWidget *parent):QGLWidget(parent)
{

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    setMouseTracking(true);

    setFocusPolicy(Qt::StrongFocus);

	Threshold = 1.0;
	CameraStep = 0.01;
	mNumber = 1;
	mode = 0;

	colors.push_back(LAL::Vector4<float>(1.0,0.0,0.0,0.5));
	colors.push_back(LAL::Vector4<float>(1.0,1.0,0.0,0.5));
	colors.push_back(LAL::Vector4<float>(0.0,1.0,0.0,0.5));
	colors.push_back(LAL::Vector4<float>(0.0,1.0,1.0,0.5));
	colors.push_back(LAL::Vector4<float>(0.5,0.5,5.0,0.5));
	colors.push_back(LAL::Vector4<float>(0.5,0.0,0.5,0.5));
	colors.push_back(LAL::Vector4<float>(0.25,0.5,0.25,0.5));
	colors.push_back(LAL::Vector4<float>(0.25,0.0,0.75,0.5));
	colors.push_back(LAL::Vector4<float>(0.0,0.0,1.0,0.5));
	colors.push_back(LAL::Vector4<float>(0.1,0.1,0.5,0.5));
	colors.push_back(LAL::Vector4<float>(1.0,0.1,0.5,0.5));
	colors.push_back(LAL::Vector4<float>(0.1,0.1,0.5,0.5));
	colors.push_back(LAL::Vector4<float>(1.0,1.0,0.5,0.5));



}

void GLFrame::SetNumber(int t)
{
	mNumber = t;
}


void GLFrame::SetThreshold(const float t)
{
	Threshold = t;
}

void GLFrame::SetCameraStep(const float t)
{
	CameraStep = t;
}
void GLFrame::SetMode(bool t)
{
	mode = t;

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
//	GPUKernel.fragment_source("simple.frag");
//	GPUKernel.vertex_source("simple.vert");
//	GPUKernel.install(true);
	
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
 	GLfloat luzDifusa[4]={1.0,1.0,0.0,1.0};         //cor
	//GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};   //brilho
	GLfloat especularidade[4]={1.0,0.0,0.0,1.0};	  //brilho do material

	GLint especMaterial = 64;

	GLfloat light_position0[] = {0.0, 0.5, 10.0, 0.0};

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
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_position0 );


	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);  //cor do material a partir da cor corrente
	glEnable(GL_LIGHTING);        //uso de iluminacao
	glEnable(GL_LIGHT0);          //luz  0
	glEnable(GL_DEPTH_TEST);      //depth-buffering

	//glEnable(GL_NORMALIZE);

}


/// Draw a node's bounding box and it's contained points
/// @param n kd-tree node
/// @return 1 if empty or leaf node, 0 if internal node
bool GLFrame::drawKdNode(const KdTree3DNode* n,int& cont) {

  if (n == NULL)
    return 1;

  GLfloat cur_color[4];
  glGetFloatv(GL_CURRENT_COLOR, cur_color);

  glPointSize(1.0);
  glBegin(GL_POINTS);
  glColor4f(0.3, 0.3, 0.3, 1.0);

  cont += n->mListPtr.size();

  for (unsigned int i = 0; i < n->mListPtr.size(); ++i)
  {
	  glVertex3fv( n->mListPtr[i]->Center() );
  }

  glEnd();

  glColor4fv(cur_color);

  // Only draw leaf node's boxes

  if (!n->IsLeaf())
    return 0;

  //drawBox(n->Box());

  return 1;
}

/// Recursively draw all kd-tree nodes
/// @param n kd-tree node
void GLFrame::drawKdNodeRecursively(const KdTree3DNode* n,int& cont) {
  const KdTree3DNode* leftNode = n->Left();
  const KdTree3DNode* rightNode = n->Right();


  if (!drawKdNode(leftNode,cont))
    drawKdNodeRecursively(leftNode,cont);

  if (!drawKdNode(rightNode,cont))
    drawKdNodeRecursively(rightNode,cont);
}

/// Draw the kd-tree leaf nodes' boxes and all elements stored in all nodes
void GLFrame::drawKdTree(int& cont)
{
  KdTree3DNode* root = kdTree.Begin();

  glColor4f(0.3, 0.3, 1.0, 1.0);
  glLineWidth(1.0);

  drawKdNode(root,cont); //draw root node first

  drawKdNodeRecursively(root,cont); //draw entire tree

}


void GLFrame::calLimits()
{

    LAL::BoundingBox3<float> world =     LAL::BoundingBox3<float>( LAL::Point3<float>(surfels.box().xMin(),surfels.box().yMin(),surfels.box().zMin()),
				   						 LAL::Point3<float>(surfels.box().xMax(),surfels.box().yMax(),surfels.box().zMax()));

	if (kdTree.root ==  0)
	{
		kdTree = KdTree<float,Surfel<float>* >(world);
	}
	else
	{
		delete kdTree.root;
		kdTree = KdTree<float,Surfel<float>* >(world);
	}



	std::cout << "Entrando" << std::endl;
	for (std::vector<Surfel<float> >::iterator surf =  surfels.surfels.begin();surf != surfels.surfels.end(); ++ surf )
	{
	    kdTree.Insert ( new Surfel<float>(*surf) );
	}
	std::cout << "Saindo" << std::endl;

	std::cout << "Total = " << surfels.surfels.size() << std::endl;

    int k_nearest_search_comps = 0;

    Surfel<float>* s = new Surfel<float>();

    *s = surfels.surfels[0];

    std::cout << "s0" << s->Center() << std::endl;
    
    int SIZE = 2000;

    KNeibor = kdTree.KNearestNeighbors(s ,SIZE, k_nearest_search_comps);
      KNeibor.push_back(new Surfel<float>(*s));
      *s = *KNeibor[0];
      
      if (KNeibor.size() > SIZE)
      {
      	for( int i=0; i<SIZE*0.75 ;++i)
      	{
      		KNeibor[i]->SetMarked(0);	
      	}
      	KNeibor.erase(KNeibor.begin(),KNeibor.begin()+SIZE*0.75);
      }
      
      KNeibor.erase(KNeibor.begin());

      std::cout << KNeibor.size() <<  " KNN " << std::endl;

      cluster.push_back(KNeibor);



      //nao ta adicionando o propio ponto na busca =\ ai fica dificil !!


      while (KNeibor.size() > 0)
      {
      	KNeibor = kdTree.KNearestNeighborsClustering(s ,SIZE, k_nearest_search_comps);
          KNeibor.push_back(new Surfel<float>(*s));
          *s = *KNeibor[0];
          if (KNeibor.size() > SIZE)
          {
          	for( int i=0; i<SIZE*0.75 ;++i)
          	{
          		KNeibor[i]->SetMarked(0);	
          	}
          	KNeibor.erase(KNeibor.begin(),KNeibor.begin()+SIZE*0.75);
          }

          KNeibor.erase(KNeibor.begin());
      	cluster.push_back(KNeibor);

      }



    MergeEllipses<float> me;

    for (std::vector< std::vector<Surfel<float>* > >::iterator i = cluster.begin(); i != cluster.end();++i)
    {
    	std::list<Surfel<float>* > l;
    	for(std::vector<Surfel<float>* >::iterator j = i->begin(); j != i->end(); ++j)
    	{
    		l.push_back((*j));
    	}
//    	std::cout << "--------------------- ="<< l.size() <<  std::endl;
//    	for (std::list<Surfel<float>* >::iterator y = l.begin(); y != l.end(); ++y)
//    	{
//    		std::cout << " =  "<<  (*y)->Normal()<< "-" <<  (*y)->Center() << std::endl;
//    	}
//    	std::cout << "---------------------"<< std::endl;
    	if(l.size() > 0)
    		me = MergeEllipses<float>(l);

    	Surfel<float>* su1 = new Surfel<float>();

    	su1 = me.NewPtrSurfel();

//    	std::cout << su1->Normal()<< "-" <<  su1->Center()<<  " New Surfel " << std::endl;

    	newSurfel.push_back(me.NewPtrSurfel());

    }

//    Surfel<float>* su1 =  new Surfel<float>(LAL::Point3<float>(7.938756, 8.396816, 5.958447),
//                    LAL::Vector3<float>(0.000000, 0.000000, 1.000000),1.0f,1.0f,0.0f);
//
//
//    su1->SetMinorAxis(std::make_pair(0.1,LAL::Vector3<float>(1.000000, 0.000000, 0.000000)));
//    su1->SetMajorAxis(std::make_pair(0.5,LAL::Vector3<float>(0.000000, 1.000000, 0.00000)));
//
//
//    Surfel<float>* su2 =  new Surfel<float>(LAL::Point3<float>(6.632136, 7.704408, 5.995052),
//                            LAL::Vector3<float>(0.000000, 0.000000, 1.000000),1.0f,1.0f,0.0f);
//
//
//    su2->SetMinorAxis(std::make_pair(0.4,LAL::Vector3<float>(1.000000, 0.000000, 0.000000)));
//    su2->SetMajorAxis(std::make_pair(0.2,LAL::Vector3<float>(0.000000, 1.000000, 0.000000)));
//
//    std::list<Surfel<float>* > sl;
//
//    sl.push_back(su1);
//    sl.push_back(su2);
//
//
//    MergeEllipses<float> me = MergeEllipses<float>(sl);


    std::cout << cluster.size() <<  "cluster size" << std::endl;
    std::cout << newSurfel.size() <<  "new " << std::endl;

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

    glLoadMatrixf((~camera.PespectiveProjectionMatrix()).ToRealPtr());

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

    camera.SetViewByMouse();
    glLoadMatrixf((~camera.ViewMatrix()));

    int cont = 0;

    glDisable(GL_LIGHTING);
    if ( surfels.surfels.size() != 0 )
    {
    	drawKdTree(cont);


    	glPointSize(5.0);
    	glEnable(GL_POINT_SMOOTH);
    	glBegin(GL_POINTS);
    	glPushMatrix();

    	std::vector<LAL::Vector4<float> >::iterator c = colors.begin();

    	int cont = 0;

    	if(mode)
    	{

//    		for (std::vector< std::vector<Surfel<float>* > >::iterator i = cluster.begin(); i != cluster.end();++i)
    		c = colors.begin();
//    		GPUKernel.use(true);
    		for (int i = 0;i < mNumber; ++i)
    		{


    			glColor3fv(*c);
    			++c;
    			if(c == colors.end())
    				c = colors.begin();
    			for (std::vector<Surfel<float>* >::iterator j = cluster[i].begin(); j != cluster[i].end();++j)
    			{
    				glVertex3fv((*j)->Center());
    			}
    			glPointSize(7.0);
    	    	//glColor3f(0.5f,0.5f,0.5f);//glColor4fv(*c);
				glVertex3fv((newSurfel[i])->Center());//(newSurfel[i])->drawTriangleFan();//
    			//    		glColor3fv(*c);
    			//			++c;
    			//			if(c == colors.end())
    			//				c = colors.begin();
    			//    		for (std::vector<Surfel<float> >::iterator j = cluster[1].begin(); j != cluster[1].end();++j)
    			//    		{
    			//    			glVertex3fv(j->Center());
    			//    		}
    			//    		glColor3fv(*c);
    			//			++c;
    			//			if(c == colors.end())
    			//				c = colors.begin();
    			//    		for (std::vector<Surfel<float> >::iterator j = cluster[2].begin(); j != cluster[2].end();++j)
    			//    		{
    			//    			glVertex3fv(j->Center());
    			//    		}
    			//    		glColor3fv(*c);
    			//			++c;
    			//			if(c == colors.end())
    			//				c = colors.begin();
    			//    		for (std::vector<Surfel<float> >::iterator j = cluster[3].begin(); j != cluster[3].end();++j)
    			//    		{
    			//    			glVertex3fv(j->Center());
    			//    		}

    		}
//    		GPUKernel.use(false);
    	}else
    	{

//    		for (std::vector<Surfel<float>*  >::iterator i = newSurfel.begin(); i != newSurfel.end();++i)
    		
    		c = colors.begin();
//    		GPUKernel.use(true);
    	    for (int i = 0;i < mNumber ; ++i)
    		{
    	    	//glColor4fv(*c);
    			++c;
    			if(c == colors.end())
    				c = colors.begin();
					glVertex3fv((newSurfel[i])->Center());//(newSurfel[i])->drawTriangleFan();//

    		}
//    	    GPUKernel.use(false);
    	}


    	glEnd();
    	glPopMatrix();
    	
    	glColor3f(0.5,0.5,0.5);
    	renderText(10,5,QString("___________________________"));
    	renderText(10,25,QString("Number of Points :"));renderText(145,25,QString::number(cont));
    	renderText(10,30,QString("___________________________"));
    	DrawGroud();
    }
    glEnable(GL_LIGHTING);
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

    if (event->button() == Qt::LeftButton)
    {
    	camera.lockMouse(true);
        mCenterX = static_cast<float>(event->x());
        mCenterY = static_cast<float>(event->y());
    }

    lastPos = event->pos();
}

void GLFrame::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
    	camera.lockMouse(false);
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
    	//camera.SetMouseInfo(event->x(),event->y());
        float heading = 0.0f;
        float pitch = 0.0f;
        float roll = 0.0f;

        pitch = -(static_cast<float>(event->x()) - mCenterX) * 0.2;
        heading = -(static_cast<float>(event->y()) - mCenterY) * 0.2;


        camera.Rotate(pitch,heading, 0.0f);

    //    mouse.moveToWindowCenter();

        QCursor::setPos(mapToGlobal(QPoint(static_cast<int>(mCenterX),static_cast<int>(mCenterY))));

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


 	updateGL();
    lastPos = event->pos();
}


