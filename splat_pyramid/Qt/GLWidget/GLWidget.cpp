#include <QtGui>

#include <limits>

#include <stdio.h>
#include <stdlib.h>


#include "GLWidget.hpp"

#include "Celer/Math/Vector3.hpp"
#include "Celer/Math/Vector4.hpp"

#include <wrap/gl/picking.h>



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

	glewInit();

	const char* rs = (const char*)glGetString(GL_RENDERER);

	cout << "GL_RENDERER : " << rs << endl;
	if (!GLEW_ARB_texture_float)
		std::cout << "SplatPyramid: warning floating point textures are not supported.\n";

	canvas_width  = width();
	canvas_height = height();

	render_mode = PYRAMID_POINTS;
	point_based_render = NULL;

	fps_loop = 0;

	rotating = 0;
	show_points = false;
	selected = 0;
	scale_factor = 1.0;


    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setFocus();

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    setAttribute(Qt::WA_NoSystemBackground);

    setAutoFillBackground(false);

	CameraStep = 0.01;

	mGLInitialized = false;

}


void GLWidget::createPointRenderer( void ) {

	if (point_based_render)
		delete point_based_render;

	if (render_mode == PYRAMID_POINTS)
		point_based_render = new PyramidPointRenderer(canvas_width, canvas_height);
	else if (render_mode == PYRAMID_POINTS_COLOR)
		point_based_render = new PyramidPointRendererColor(canvas_width, canvas_height);

	assert (point_based_render);

	((PyramidPointRendererBase*)point_based_render)->setShadersDir(QDir::currentPath());
	((PyramidPointRendererBase*)point_based_render)->createShaders();
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


}

void GLWidget::LoadModel(const char * filename,bool eliptical, vcg::CallBackPos *cb=0 )
{
	objects.push_back( Object( objects.size() ) );
	bool color_per_vertex = false;

	if(eliptical)
	{
		IOSurfels<double>::LoadSurfels(filename, (objects.back()).getSurfels());

	}else
	{
		IOSurfels<double>::LoadMesh(filename, (objects.back()).getSurfels());
	}


	if (color_per_vertex)
		render_mode =  PYRAMID_POINTS_COLOR;
	else
		render_mode =  PYRAMID_POINTS;

	createPointRenderer( );

	/// Sets the default rendering algorithm and loads display lists
	for (unsigned int i = 0; i < objects.size(); ++i)
		objects[i].setRendererType( render_mode );

}

void GLWidget::resizeGL(int width, int height)
{

    glViewport(0, 0, width, height);
    camera.SetWindowSize(width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width) / height;
    camera.SetProjectionMatrix(30.0,x,0.1,100000);

	canvas_width  = width;
	canvas_height = height;

	createPointRenderer( );

    glMultMatrixf((~camera.PespectiveProjectionMatrix()).ToRealPtr());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mCenterX =  static_cast<float> (width*0.5);
    mCenterY =  static_cast<float> (height*0.5);

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
    saveGLState();
	makeCurrent();
    initializeGL();
	glShadeModel(GL_SMOOTH);                      	//gouraud

	//set material properties which will be assigned by glColor

  	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.LoadProjectionMatrix();
    camera.SetViewByMouse();
    camera.LoadModelViewMatrix();

    static float globalAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    static float lightPos[4] ={0.0, 0.0, 1.0, 0.0};;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    if (objects.size() > 0)
    {


    	point_based_render->clearBuffers();

    	glPushMatrix();

    	// Set eye for back face culling in vertex shader of projection phase
    	point_based_render->setEye( Point3f(camera.Eyes().x,camera.Eyes().y,camera.Eyes().z) );

    	for (unsigned int i = 0; i < objects.size(); ++i)
    		point_based_render->projectSamples( &objects[i] );

    	point_based_render->interpolate();

    	point_based_render->draw();
    	glPopMatrix();

//    	glColor3f(1.0f,1.0f,1.0f);
//    	glDisable(GL_LIGHTING);
//    	glPointSize(2.0);
//    	glBegin(GL_POINTS);
//
//    	for (std::vector<Surfel<double> >::iterator s = objects.back().getSurfels().begin(); s != objects.back().getSurfels().end();++s)
//    	{
//    		glVertex3d(s->Center()[0],s->Center()[1],s->Center()[2]);
//    	}
//    	glEnd();
//    	glEnable(GL_LIGHTING);
    }

  	DrawGroud();
//================================HUD DISPLAY==================================
    restoreGLState();
    QPainter p; // used for text overlay
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing);
    // save the GL state set for QPainter
    //draw the overlayed text using QPainter
    p.setPen(QColor(197, 197, 197, 157));
    p.setBrush(QColor(197, 197, 197, 127));
    p.drawRect(QRect(0, 0, width(), 50));
    p.setBrush(QColor(197, 0, 0, 127));

    p.drawRect(10 ,(height()-90) ,100,10);

    p.drawRect(10 ,(height()-70) ,100,10);
    //p.drawRect(QRect(10 , height()-(2*(height()*0.01)),100,height()-((height()*0.01)) ));
    p.setPen(QColor(0, 0, 0, 255));
    p.setBrush(Qt::NoBrush);
    const QString str1(tr("A simple OpenGL pbuffer example."));
    const QString str2(tr("Use the mouse wheel to zoom, press buttons and move mouse to rotate, double-click to flip."));
    QFontMetrics fm(p.font());
    p.drawText(width()/2 - fm.width(str1)/2, 20, str1);
    p.drawText(width()/2 - fm.width(str2)/2, 20 + fm.lineSpacing(), str2);
    p.setPen(QColor(197, 197, 197, 157));
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

    if (event->button() == Qt::LeftButton)
    {
    	camera.lockMouse(true);
        mCenterX = static_cast<float>(event->x());
        mCenterY = static_cast<float>(event->y());
        update();
    }

    if (event->button() == Qt::RightButton)
    {
    	lastPos = event->pos();
	}

    update();


}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	event->accept();


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
    }

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

