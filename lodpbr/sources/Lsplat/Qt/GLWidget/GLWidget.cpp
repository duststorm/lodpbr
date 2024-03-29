#include <QtGui>

#include <limits>

#include <stdio.h>
#include <stdlib.h>


#include "GLWidget.hpp"

#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

#include <wrap/gl/picking.h>


#define DA_APLICACAO_PASSADA 0



// Se quiser usar QPainter Ver exemplo no QT demo - Manda Qt em wave animation !!!


GLWidget::GLWidget(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
        QGLWidget(parent, shareWidget, f)
{
    init();
}

GLWidget::GLWidget(QGLContext* context, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
        QGLWidget(context, parent, shareWidget, f)
{
}

GLWidget::GLWidget(const QGLFormat& format, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
        QGLWidget(format, parent, shareWidget, f)
{
    init();
}

void GLWidget::init()
{
    //setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	makeCurrent();
    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setFocus();

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    setAttribute(Qt::WA_NoSystemBackground);

    setAutoFillBackground(false);

	CameraStep = 0.01;

	mGLInitialized = false;

	mNumber = 4;

	mode = true;

	mRenderer.init();

	settings.setBackgroundColor(QColor(255,255,255));

//    GLfloat x = GLfloat(width()) / height();
//    camera.SetProjectionMatrix(30.0,x,0.1,100000);

	mShowModel 		 = false;
	mShowModelNormal = false;
	mShowModelPoints = false;
	mShowModelSurfel = false;
	mShowModelSplatting = false;
	mSurfelRadius 	= 1.0;

	mSelectionMode = NONE;
	mSelectBuffer = 0;
	setSelectBufferSize(4*1000);
	setSelectRegionWidth(4);
	setSelectRegionHeight(4);

}

void GLWidget::takeSnapshot()
{

}

void GLWidget::setSelectBufferSize(int size)
{
	if (mSelectBuffer)
		delete[] mSelectBuffer;
	mSelectBufferSize = size;
	mSelectBuffer = new GLuint[selectBufferSize()];
}


// Slots

void GLWidget::setClusterBuiltType(const QString & text)
{

	if ( text == "by Normal")
	{
		mClusterLog.maskBuildClusterWith.Set(ClusterLog::NormalOnly);

	}
}

void GLWidget::setClusterSplatShape	(const QString & text)
{
	if 		( text == "Elliptical")
	{
		mClusterLog.maskBuildClusterShape.Set(ClusterLog::ELLIPTICAL);
	}
	else if ( text == "Circular")
	{
		mClusterLog.maskBuildClusterShape.Set(ClusterLog::CIRCULAR);
	}
	else
	{

	}
	update();
}

void GLWidget::setClusterRendererType	(const QString & text)
{
	if 		( text == "Range")
	{
		mClusterLog.maskRenderingClusterBy.Set(ClusterLog::Range);
	}
	else if ( text == "Index")
	{
		mClusterLog.maskRenderingClusterBy.Set(ClusterLog::Index);
	}
	else if ( text == "All")
	{
		mClusterLog.maskRenderingClusterBy.Set(ClusterLog::All);
	}else
	{

	}
	update();

}

void GLWidget::setClusterRenderingMode	(const QString & text)
{
	if 		( text == "GLPoint")
	{
		mClusterLog.maskRenderingClusterWith.Set(ClusterLog::GLPoint);
	}
	else if ( text == "GLPointSmooth")
	{
		mClusterLog.maskRenderingClusterWith.Set(ClusterLog::GLPointSmooth);
	}
	else if ( text == "PyramidSplat")
	{
		mClusterLog.maskRenderingClusterWith.Set(ClusterLog::PyramidSplat);
	}else
	{

	}
	update();
}


void GLWidget::setShowCluster(bool checked)
{
	if (checked == true)
	{
		mClusterLog.maskShow.Add(ClusterLog::Cluster);

	}
	else
	{
		mClusterLog.maskShow.Clear(ClusterLog::Cluster);
		std::cout << "No Cluster" << std::endl;
	}
	update();
}

void GLWidget::setShowClusters(bool checked)
{
	if (checked == true)
	{
		mClusterLog.maskShow.Add(ClusterLog::Clusters);

	}
	else
	{
		mClusterLog.maskShow.Clear(ClusterLog::Clusters);

	}
	update();
}



void GLWidget::setShowSurfel(bool checked)
{
	if (checked == true)
	{
		std::cout << "Set Show Surfel" << std::endl;
		mClusterLog.maskShow.Add(ClusterLog::Surfel);
	}
	else
	{
		mClusterLog.maskShow.Clear(ClusterLog::Surfel);
	}

	update();
}

void GLWidget::setShowSeed(bool checked)
{
	if (checked == true)
	{
		mClusterLog.maskShow.Add(ClusterLog::Seed);
	}
	else
	{
		mClusterLog.maskShow.Clear(ClusterLog::Seed);
	}

	update();
}


void GLWidget::setShowNormal(bool checked)
{
	if (checked == true)
	{
		mClusterLog.maskShow.Add(ClusterLog::Normal);
	}
	else
	{
		mClusterLog.maskShow.Clear(ClusterLog::Normal);
	}

	update();
}

void GLWidget::setShowDrawClusterWithID	(bool checked)
{
	if (checked == true)
	{
		mClusterLog.maskRenderingClusterBy.Set(ClusterLog::Index);
		std::cout << "Index ? : " << mClusterLog.maskRenderingClusterBy.Test(ClusterLog::Index) <<
				    " Range  ?: " << mClusterLog.maskRenderingClusterBy.Test(ClusterLog::Range) << std::endl;
	}
	updateGL();
}

void GLWidget::setShowDrawClusterWithRange	(bool checked)
{
	if (checked == true)
	{
		mClusterLog.maskRenderingClusterBy.Set(ClusterLog::Range);
		std::cout << "Index ? : " << mClusterLog.maskRenderingClusterBy.Test(ClusterLog::Index) <<
				    " Range  ?: " << mClusterLog.maskRenderingClusterBy.Test(ClusterLog::Range) << std::endl;
	}
	update();
}

void GLWidget::setDrawClusterWithID (int value)
{
	mClusterLog.setClusteIndex(value);
	update();
}


void GLWidget::setDrawClusterWithRangeBegin	(int value)
{
	mClusterLog.setClusterRangeBegin(value);
	update();
}

void GLWidget::setDrawClusterWithRangeEnd	(int value)
{
	mClusterLog.setClusterRangeEnd(value);
	update();
}

void GLWidget::setRadius(int value)
{
	mClusterLog.setRadius(value);
	update();
}

void GLWidget::setClusterSplatlRadius (int value)
{
	mClusterLog.setSplatRadius(value);
	update();
}

void GLWidget::SetMode(bool t)
{
	mode = t;

}

// Model
void GLWidget::setShowModel(bool checked)
{
	mShowModel = checked;
	update();
}
void GLWidget::setShowModelPoints(bool checked)
{
	mShowModelPoints = checked;
	update();
}

void GLWidget::setShowModelSurfel(bool checked)
{
	mShowModelSurfel = checked;
	update();
}

void GLWidget::setShowModelSplating(bool checked)
{
	mShowModelSplatting = checked;
	update();
}

void GLWidget::setShowClusterSplatting(bool checked)
{
	if (checked == 1)
	{
		mClusterLog.maskRenderingClusterWith.Add(ClusterLog::EWASplat);
	}
	else
	{
		mClusterLog.maskRenderingClusterWith.Clear(ClusterLog::EWASplat);
	}
	update();

}

void GLWidget::setShowModelNormal(bool checked)
{
	mShowModelNormal = checked;
	update();
}

void GLWidget::setModelSurfelRadius(int value)
{
	mSurfelRadius = value;
	update();
}
void GLWidget::setModelSplatlRadius(int value)
{
	mSplatRadius = value;
	update();
}

// == IO ==

void GLWidget::LoadModel(const char * filename,vcg::CallBackPos *cb=0 )
{

	mClusterLog = ClusterLog();
	mLSplatLog = LSplatLog();
	cluster.Surfels.clear();
	Box = Celer::BoundingBox3<float>();
	Celer::IOSurfels<float>::LoadMesh(filename,cluster.Surfels,Box,cb);
	std::cout << cluster.Surfels.capacity();
}

void GLWidget::SaveLOD(const char * filename,vcg::CallBackPos *cb)
{
	for (int i = 0; i < cluster.NewSurfels.size();++i)
	{
		std::cout << "---Save-------------------------" << std::endl;
		std::cout <<  cluster.NewSurfels[i] << std::endl;
		std::cout << "---Save-------------------------" << std::endl;
	}

	if(cluster.NewSurfels.size() > 0)
		Celer::IOSurfels<float>::SaveSurfels(cluster.NewSurfels,filename,cb);
}

void GLWidget::LoadLOD(const char * filename,vcg::CallBackPos *cb)
{
	if(cluster.NewSurfels.size() == 0)
		Celer::IOSurfels<float>::LoadSurfels(filename,cluster.NewSurfels,cb);
}

void GLWidget::SaveSimplification(const char * filename,vcg::CallBackPos *cb)
{
	if (cluster.NewSurfels.size() > 0 )
		Celer::IOSurfels<float>::SaveMesh(filename,cluster.NewSurfels,cb);
}
// =================================== KD-Tree ================================//
void GLWidget::getKNearestNeighbors(void)
{
	if (cluster.KDTree.root != 0)
	{
		if (result.size() != 0)
		{
			int x = 0;
			Knn.clear();
			Knn = cluster.KDTree.KNearestNeighbors(&result[0],10,x);
		}

	}
}
// ============================================================================//
void GLWidget::DrawGroud()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.2f, 0.2f, 0.2f);

	// draw the lines
	glEnable(GL_MULTISAMPLE);
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
	glDisable(GL_MULTISAMPLE);
	glEnable(GL_LIGHTING);
}

///// Draw a node's bounding box and it's contained points
///// @param n kd-tree node
///// @return 1 if empty or leaf node, 0 if internal node
//bool GLWidget::drawKdNode(const KdTree3DNode* n,int& cont) {
//
//  if (n == NULL)
//    return 1;
//
//  GLfloat cur_color[4];
//  glGetFloatv(GL_CURRENT_COLOR, cur_color);
//
//
//  glPointSize(1.0);
//  //glEnable(GL_MULTISAMPLE);
//
//  glBegin(GL_POINTS);
//  glColor4f(0.3, 0.3, 0.3, 1.0);
//
//  cont += n->mListPtr.size();
//
//  for (unsigned int i = 0; i < n->mListPtr.size(); ++i)
//  {
//	  glVertex3fv( n->mListPtr[i]->Center() );
//  }
//
//  glEnd();
//
//
//  glColor4fv(cur_color);
//
//  // Only draw leaf node's boxes
//
//  if (!n->IsLeaf())
//    return 0;
//
//  //drawBox(n->Box());
//
//  return 1;
//}
//
///// Recursively draw all kd-tree nodes
///// @param n kd-tree node
//void GLWidget::drawKdNodeRecursively(const KdTree3DNode* n,int& cont) {
//  const KdTree3DNode* leftNode = n->Left();
//  const KdTree3DNode* rightNode = n->Right();
//
//
//  if (!drawKdNode(leftNode,cont))
//    drawKdNodeRecursively(leftNode,cont);
//
//  if (!drawKdNode(rightNode,cont))
//    drawKdNodeRecursively(rightNode,cont);
//}
//
///// Draw the kd-tree leaf nodes' boxes and all elements stored in all nodes
//void GLWidget::drawKdTree(int& cont)
//{
//  KdTree3DNode* root = cluster.KDTree.Begin();
//
//  glColor4f(0.3, 0.3, 1.0, 1.0);
//  glLineWidth(1.0);
//
//  drawKdNode(root,cont); //draw root node first
//
//  drawKdNodeRecursively(root,cont); //draw entire tree
//
//}


template <class T>
void GLWidget::drawBox(Celer::BoundingBox3<T> BBox){
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


void GLWidget::glInit()
{
    QGLWidget::glInit();
}

void GLWidget::initializeGL()
{

	makeCurrent();
	mGLInitialized = true;

    GLfloat luzAmbiente[4] ={0.0f, 0.0f, 0.0f,1.0};
 	GLfloat luzDifusa[4]   ={1.0,1.0,1.0,1.0};         //cor
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};   //brilho

	GLfloat lightPos0[] = {0.0, 0.0, 5.0, 0.0};

	glShadeModel(GL_SMOOTH);                      	//gouraud

	//set material properties which will be assigned by glColor

  	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);


	setForegroundColor(settings.getTextColor());
	setBackgroundColor(settings.getBackgroundColor());

}




void GLWidget::resizeGL(int width, int height)
{

    glViewport(0, 0, width, height);
    camera.SetWindowSize(width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    camera.SetProjectionMatrix(30.0,x,0.1,100000);

    glMultMatrixf((~camera.PespectiveProjectionMatrix()).ToRealPtr());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mCenterX =  static_cast<float> (width*0.5);
    mCenterY =  static_cast<float> (height*0.5);

}

void GLWidget::calLimits()
{

     cluster.Initialize(Box);

//
//
//     for( std::list<Celer::Surfel<float>*>::iterator it = cluster.Clusters[0].begin(); it !=  cluster.Clusters[0].end();++it)
//     {
//         for( std::list<Celer::Surfel<float>*>::iterator i = cluster.Clusters[500].begin(); i !=  cluster.Clusters[500].end();++i)
//         {
//        	 if((*i)->Center() == (*it)->Center())
//        	 {
//        		std::cout << "=D " << (*i)->Center() << std::endl;
//        	 }
//
//             for( std::list<Celer::Surfel<float>*>::iterator j = cluster.Clusters[800].begin(); j !=  cluster.Clusters[800].end();++j)
//             {
//            	 if(  ((*j)->Center() == (*it)->Center())  && (*j)->Center() == (*i)->Center() )
//            	 {
//            		std::cout << "=D ele ?" << (*i)->Center() <<   distance(cluster.Clusters[500].begin(),i)  << std::endl;
//            		std::cout << "=D ele ?" << (*it)->Center() << distance(cluster.Clusters[0].begin(),it)  << std::endl;
//            		std::cout << "=D ele ?" << (*j)->Center() << distance(cluster.Clusters[800].begin(),j)  << std::endl;
//            	 }
//             }
//
//
//         }
//
//
//
//     }

}

void GLWidget::BuildInteractive()
{
	Celer::Surfel<float>* seed = new Celer::Surfel<float>(mSeed);
	cluster.BuildInteractive<JoinByNormal<float,Celer::Surfel<float>* >,
							 MergeBySize <float,Celer::Surfel<float>* > >(300,seed,mClusterLog);
	result[1] = cluster.GetCurrentEllipse();
	mHeight = result[1].PerpendicularError();
	//mHeight*=10.0;

}

void GLWidget::GetSeed()
{
	mSeed = result[0];
}

void GLWidget::BuildCluster(vcg::CallBackPos *cb=0 )
{
	if (cluster.Surfels.size() > 0)
	{
		if (mClusterLog.maskBuildClusterWith.Test(ClusterLog::NormalOnly))
		{

			Celer::Surfel<float>* seed = new Celer::Surfel<float>(cluster.Surfels[0]);
			cluster.Build2<JoinByNormal<float,Celer::Surfel<float>* >,
						  MergeBySize <float,Celer::Surfel<float>* > >(1000,200,(seed),mClusterLog,cb );

		}
	}
}

void GLWidget::Clear()
{
    cluster.Clear();
}

void GLWidget::draw()
{

}

void GLWidget::paintEvent(QPaintEvent *)
{
	paintGL();
}


void GLWidget::paintGL()
{

    //saveGLState();
	makeCurrent();
    //initializeGL();
	glShadeModel(GL_SMOOTH);                      	//gouraud

	//set material properties which will be assigned by glColor

  	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.LoadProjectionMatrix();
    camera.SetViewByMouse();
    camera.LoadModelViewMatrix();

    mClusterLog.setCamera(camera);

    fps.nextFrame();

    static float lightPos[4];

    lightPos[0] = camera.Eyes().x;
    lightPos[1] = camera.Eyes().y;
    lightPos[2] = camera.Eyes().z;
    lightPos[3] = 0.0f;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


//--
	//select(lastPos);
//
//--
    if (  (cluster.Surfels.size() != 0) || (cluster.NewSurfels.size() != 0) )
    {
    	if (mShowModel)
    	{


    		if (mShowModelSplatting)
    		{
    			mRenderer.beginVisibilityPass();
    			glBegin(GL_POINTS);
    			for (std::vector<Surfel>::iterator s = cluster.Surfels.begin(); s != cluster.Surfels.end();++s)
    			{
    				if(mShowModelSplatting)
    				{
    					glMultiTexCoord1f(GL_TEXTURE2,(s->Radius() * mSplatRadius * 0.01) );
    					glNormal3fv(s->Normal());
    					glColor4f(0.0f,0.0f,1.0f,0.7f);
    					glVertex3fv(s->Center());
    				}
    			}
    			glEnd();

    			mRenderer.beginAttributePass();
    			glBegin(GL_POINTS);
    			for (std::vector<Surfel>::iterator s = cluster.Surfels.begin(); s != cluster.Surfels.end();++s)
    			{
    				glMultiTexCoord1f(GL_TEXTURE2,(s->Radius() * mSplatRadius * 0.01));
    				glNormal3fv(s->Normal());
    				glColor4f(0.0f,0.0f,1.0f,0.7f);
    				glVertex3fv(s->Center());
    			}
    			glEnd();
    			mRenderer.finalize();
    		}


    		if (mShowModelSurfel)
    		{
    			std::list<Celer::Point3<float> > lBoundaries;
    			glPushMatrix();
    			glEnable(GL_POLYGON_OFFSET_FILL | GL_POLYGON_SMOOTH_HINT | GL_MULTISAMPLE);
    			glPolygonOffset(1,1);
    			glEnable (GL_BLEND);
    			glEnable(GL_MULTISAMPLE);
    			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    			//glColor4f(0.5f,0.5f,0.5f,1.0f);
    			glColor4f(1.0,0.5,0.0,0.75);
    			//glColor4f(0.0f,0.0f,1.0f,0.8f);
    			for (std::vector<Surfel>::iterator s = cluster.Surfels.begin(); s != cluster.Surfels.end();++s)
    			{
    				if ( (camera.Eyes().Norm() * s->Normal() ) > -0.2f )
    				{
    					lBoundaries = s->BoundariesSamples(32,mSurfelRadius * 0.01);
    					glBegin (GL_TRIANGLE_FAN);
    					for(std::list<Celer::Point3<float> >::iterator  it = lBoundaries.begin();it != lBoundaries.end();++it)
    					{
    						glVertex3fv( *it );
    					}
    					glEnd();
    				}
    			}
    			glPopMatrix();
    		}

    		if (mShowModelPoints)
    		{
				glColor3f(0.5f,0.5f,0.5f);
				glDisable(GL_LIGHTING);
				glPointSize(2.0);
				glBegin(GL_POINTS);

    			for (std::vector<Surfel>::iterator s = cluster.Surfels.begin(); s != cluster.Surfels.end();++s)
    			{

//    				if( (s->Curvature() >= 0.0)       && (s->Curvature() < 0.25) )
//    					glColor3f(1.0f,1.0f,1.0f);
//    				else if ( (s->Curvature() > 0.25) && (s->Curvature() < 0.50) )
//    					glColor3f(0.0,1.0f,1.0f);
//    				else if ( (s->Curvature() > 0.5)  && (s->Curvature() < 0.75) )
//    					glColor3f(1.0f,1.0f,0.0f);
//    				else if ( (s->Curvature() > 0.75) && (s->Curvature() <= 1.0) )
//    					glColor3f(1.0f,0.0f,0.0);
//
					if ((camera.Eyes().Norm()* s->Normal()) > -0.2)
					{
    				//std::cout << "Normal " <<  (camera.Eyes().Norm()* s->Normal()) << std::endl;
						glVertex3fv( s->Center().ToRealPtr() );
					}
    			}
				glEnd();
				glEnable(GL_LIGHTING);
    		}
    	}

    	for (size_t i = 0; i != Knn.size();++i)
    	{
    		result[1].DrawTriangleFan(64,0.5);
    		result[1].DrawEllpsoid(16,16,1.0,mHeight);//DrawTriangleFan(64,0.5);
    	}

    	if (mClusterLog.maskShow.Test(ClusterLog::Clusters))
    	{

    		if 	   (mClusterLog.maskRenderingClusterBy.Test(ClusterLog::Index))
    		{
    			if (mClusterLog.maskShow.Test(ClusterLog::Cluster))
    				cluster.DrawClustersIndex(camera.Eyes().Norm(),mClusterLog.getClusteIndex(),(mClusterLog.maskShow.Test(ClusterLog::Seed)));

    			if (mClusterLog.maskShow.Test(ClusterLog::Surfel))
    				cluster.DrawSurfels(mClusterLog,32);
    			if (mClusterLog.maskRenderingClusterWith.Test(ClusterLog::EWASplat))
    			{

    			}

    		}
    		else if (mClusterLog.maskRenderingClusterBy.Test(ClusterLog::Range))
    		{

    			if (mClusterLog.maskShow.Test(ClusterLog::Cluster))
    				cluster.DrawClustersRange(camera.Eyes().Norm(),mClusterLog.getClusterRangeBegin(),mClusterLog.getClusterRangeEnd(),(mClusterLog.maskShow.Test(ClusterLog::Seed)));

    			if  (mClusterLog.maskRenderingClusterWith.Test(ClusterLog::EWASplat))
    			{
        			mRenderer.beginVisibilityPass();
        			glBegin(GL_POINTS);
        			for (unsigned int i = mClusterLog.getClusterRangeBegin(); i <= mClusterLog.getClusterRangeEnd() ; ++i)
        			{
        				glMultiTexCoord1f(GL_TEXTURE2,(cluster.NewSurfels[i].MajorAxis().first  * mClusterLog.getSplatRadiusf()) );
        				glNormal3fv(cluster.NewSurfels[i].Normal());
        				glColor4f(0.0f,0.0f,1.0f,0.7f);
        				glVertex3fv(cluster.NewSurfels[i].Center());
        			}
        			glEnd();

        			mRenderer.beginAttributePass();

        			glBegin(GL_POINTS);
        			for (unsigned int i = mClusterLog.getClusterRangeBegin(); i <= mClusterLog.getClusterRangeEnd() ; ++i)
        			{
        				glMultiTexCoord1f(GL_TEXTURE2,(cluster.NewSurfels[i].MajorAxis().first * mClusterLog.getSplatRadiusf()));
        				glNormal3fv(cluster.NewSurfels[i].Normal());
        				glColor4f(0.0f,0.0f,1.0f,0.7f);
        				glVertex3fv(cluster.NewSurfels[i].Center());
        			}
        			glEnd();
        			mRenderer.finalize();
    			}
    			if (mClusterLog.maskShow.Test(ClusterLog::Surfel))
    			{
    				cluster.DrawSurfels(mClusterLog,32);
    			}
    		}
    	}

    	//DrawGroud();
    	if ( (mSelectionMode == ADD_NEIBORHOO) || (mSelectionMode == DEL_NEIBORHOO))
    		drawSelectionRectangle();
    }


    //restoreGLState();
    QPainter p; // used for text overlay
    p.begin(this);
//    p.setRenderHint(QPainter::Antialiasing);
//    // save the GL state set for QPainter
//    //draw the overlayed text using QPainter
//    p.setPen(QColor(197, 197, 197, 157));
//    p.setBrush(QColor(197, 197, 197, 127));
//    p.drawRect(QRect(0, 0, width(), 50));
//    p.setBrush(QColor(197, 0, 0, 127));
//
//    p.drawRect(10 ,(height()-90) ,100,10);
//
//    p.drawRect(10 ,(height()-70) ,100,10);
//    //p.drawRect(QRect(10 , height()-(2*(height()*0.01)),100,height()-((height()*0.01)) ));
//    p.setPen(settings.getTextColor());
//    p.setBrush(Qt::NoBrush);
//    const QString str1(tr("A simple OpenGL pbuffer example."));
//    const QString str2(tr("Use the mouse wheel to zoom, press buttons and move mouse to rotate, double-click to flip."));
//    QFontMetrics fm(p.font());
//    p.drawText(width()/2 - fm.width(str1)/2, 20, str1);
//    p.drawText(width()/2 - fm.width(str2)/2, 20 + fm.lineSpacing(), str2);
//    p.setPen(QColor(197, 197, 197, 157));
    p.end();


}

void GLWidget::keyPressEvent(QKeyEvent * event)
{
	event->accept();

	if (event->key() == Qt::Key_Q)
	{
		camera.MoveUpward(CameraStep);
		update();

	}else if (event->key() == Qt::Key_E)
	{
		camera.MoveUpward(-CameraStep);
		update();

	}
	else if (event->key() == Qt::Key_W)
	{
		camera.MoveForward(CameraStep);
		update();

	}
	else if (event->key() == Qt::Key_S){
		camera.MoveForward(-CameraStep);
		update();

	}
	else if (event->key() == Qt::Key_A){
		camera.StrafeRight(-CameraStep);
		update();

	}
	else if (event->key() == Qt::Key_D){
		camera.StrafeRight(CameraStep);
		update();

	}
	else if (event->key() == Qt::Key_R){

		camera.Reset();
		update();
	}
	else if (event->key() == Qt::Key_Plus){

		if (CameraStep < 2.0)
			CameraStep += 0.01;
		update();
	}
	else if (event->key() == Qt::Key_Minus){

		if (CameraStep > 0.0)
			CameraStep -= 0.01;
		update();
	}
	else {}
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
	event->accept();
	if( (mSelectionMode == ADD_NEIBORHOO) || (mSelectionMode == DEL_NEIBORHOO))
		rectangle = QRect(event->pos(), event->pos());

    if (event->button() == Qt::LeftButton)
    {
    	camera.lockMouse(true);
        mCenterX = static_cast<float>(event->x());
        mCenterY = static_cast<float>(event->y());
        update();
    }
    if(event->button() == Qt::MidButton)
    {
    	camera.OnRotationBegin(event->x(), height()-event->y());
    }
    if (event->button() == Qt::RightButton)
    {
    	lastPos = event->pos();
	}
    if ((event->button() == Qt::RightButton) && (event->modifiers() == Qt::ShiftModifier))
    {
    	 mSelectionMode = ADD_NEIBORHOO;
    }
    else if ((event->button() == Qt::RightButton) && (event->modifiers() == Qt::AltModifier))
    {
    	 mSelectionMode = DEL_NEIBORHOO;
    }
    update();


}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	event->accept();
	if( (mSelectionMode == ADD_NEIBORHOO) || (mSelectionMode == DEL_NEIBORHOO))
	{
		rectangle = rectangle.normalized();
		setSelectRegionHeight(rectangle.height());
		setSelectRegionWidth(rectangle.width());
        select(rectangle.center());

	}else if (mSelectionMode == SEED)
	{
		setSelectRegionHeight(4);
		setSelectRegionWidth(4);
        select(event->pos());
	}else
	{

	}

    if (event->button() == Qt::LeftButton)
    {
    	camera.lockMouse(false);

    }else if(event->button() == Qt::RightButton)
    {

    }

    update();

}

void GLWidget::wheelEvent(QWheelEvent *event)
{
   event->accept();
   camera.Zoom(event->delta()/120.0);
   update();
}



void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

	if( (mSelectionMode == ADD_NEIBORHOO) || (mSelectionMode == DEL_NEIBORHOO))
		rectangle.setBottomRight(event->pos());

    if (event->buttons() & Qt::LeftButton)
    {
    	//camera.SetMouseInfo(event->x(),event->y());
        float heading 	= 0.0f;
        float pitch 	= 0.0f;
        float roll 		= 0.0f;

        pitch = -(static_cast<float>(event->x()) - mCenterX) * 0.2;
        heading = -(static_cast<float>(event->y()) - mCenterY) * 0.2;

        camera.Rotate(pitch,heading,roll);

        /*!
         *  event->pos() retorna coordenadas x e y relativa a widget que recebeu o evento.
         *  mapToGlobla mapei as coordenadas da widget para coordenada global da tela.
         *  QCurso::setPos() posiciona o mouse em coordenada global.
         *  tudo o que eu queria para implementar a First Person Camera !
        */
        QCursor::setPos(mapToGlobal(QPoint(static_cast<int>(mCenterX),static_cast<int>(mCenterY))));

        update();
    }else if (event->buttons() & Qt::RightButton)
    {

    	update();

    }else if ((event->button() == Qt::RightButton) && (event->modifiers() == Qt::ShiftModifier))
    {


    }else if (event->buttons() & Qt::MidButton)
    {

    	camera.OnRotationMove(event->x(),height()- event->y());
    	update();
    }

}

void GLWidget::beginSelection(const QPoint& point)
{
	// Make OpenGL context current (may be needed with several viewers ?)
	makeCurrent();

	result.clear();

	int bufferSize = int(cluster.Surfels.size())*5;

	setSelectBufferSize(bufferSize);

	glSelectBuffer(selectBufferSize(), selectBuffer());
	glRenderMode(GL_SELECT);
	glInitNames();

	/* Because LoadName() won't work with no names on the stack */
	glPushName(-1);
	float mp[16];

	GLint viewport[4];
	camera.getViewport(viewport);
	glPushAttrib(GL_TRANSFORM_BIT);
	camera.LoadProjectionMatrix();
	glGetFloatv(GL_PROJECTION_MATRIX ,mp);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix(point.x(), height()-point.y(),selectRegionWidth(),selectRegionHeight() , viewport);
	glMultMatrixf(mp);
	camera.LoadModelViewMatrix();
	glPushMatrix();
	drawWithNames();
	glPopMatrix();

}

void GLWidget::endSelection(const QPoint& point)
{

	Q_UNUSED(point);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	long hits = glRenderMode(GL_RENDER);

	if (hits <= 0)
	{
		//nada
	}
	else
	{
		std::vector< std::pair<double,unsigned int> > Selected;
		for(int i = 0; i < hits; i++)
		{
			Selected.push_back( std::pair<double,unsigned int>(mSelectBuffer[i*4+1]/4294967295.0,mSelectBuffer[i*4+3]));
		}
		std::sort(Selected.begin(),Selected.end());
		result.resize(Selected.size());
		for(int i = 0; i < hits; i++)
		{
			std::vector<Celer::Surfel<float> >::iterator elements=cluster.Surfels.begin();
			std::advance(elements ,Selected[i].second);
			result[i]=(*elements);
		}
		glPopAttrib();
	}
	mSelectionMode = NONE;
	getKNearestNeighbors();
	if (result.size()>0)
	{
		GetSeed();
	}

}

void GLWidget::drawWithNames()
{
	std::vector<Celer::Surfel<float> >::iterator  surfel;
	int cnt = 0;
	for(surfel = cluster.Surfels.begin(); surfel != cluster.Surfels.end(); ++surfel)
	{
			glLoadName(cnt);
			surfel->DrawCenter(3.0);
			cnt++;
	}

}

void GLWidget::select(const QPoint& point)
{
	beginSelection(point);
	drawWithNames();
	endSelection(point);
}


void GLWidget::drawSelectionRectangle() const
{

  startScreenCoordinatesSystem();
  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);
  glColor4f(0.0, 0.0, 0.7f, 0.3f);
  glBegin(GL_QUADS);
  glVertex2i(rectangle.left(),  rectangle.top());
  glVertex2i(rectangle.right(), rectangle.top());
  glVertex2i(rectangle.right(), rectangle.bottom());
  glVertex2i(rectangle.left(),  rectangle.bottom());
  glEnd();

//  Surfel s;
//  s.SetCenter(Celer::Point3<float>(lastPos.x(),lastPos.y(),0.0));
//  s.SetMajorAxis(std::make_pair(15.0,Celer::Vector3<float>(0.0,1.0,0.0)));
//  s.SetMinorAxis(std::make_pair(15.0,Celer::Vector3<float>(1.0,0.0,0.0)));
//
//  s.DrawTriangleFan(50,1.0);

  glLineWidth(2.0);
  qglColor(settings.getTextColor());
  glBegin(GL_LINE_LOOP);
  glVertex2i(rectangle.left(),  rectangle.top());
  glVertex2i(rectangle.right(), rectangle.top());
  glVertex2i(rectangle.right(), rectangle.bottom());
  glVertex2i(rectangle.left(),  rectangle.bottom());
  glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);
  stopScreenCoordinatesSystem();
}

void GLWidget::startScreenCoordinatesSystem(bool upward) const
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
//	if (tileRegion_ != NULL)
//	  if (upward)
//	    glOrtho(tileRegion_->xMin, tileRegion_->xMax, tileRegion_->yMin, tileRegion_->yMax, 0.0, -1.0);
//	  else
//	    glOrtho(tileRegion_->xMin, tileRegion_->xMax, tileRegion_->yMax, tileRegion_->yMin, 0.0, -1.0);
//	else
	  if (upward)
	    glOrtho(0, width(), 0, height(), 0.0, -1.0);
	  else
	    glOrtho(0, width(), height(), 0, 0.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void GLWidget::stopScreenCoordinatesSystem() const
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void GLWidget::saveGLState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void GLWidget::restoreGLState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}

