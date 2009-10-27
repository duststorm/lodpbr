/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the documentation of Qt. It was originally
** published as part of Qt Quarterly.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include "OpenGLScene.hpp"

#include <QtGui>
#include <QtOpenGL>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


OpenGLScene::OpenGLScene()
{
	CameraStep = 0.01;

	//	GPUKernel.fragment_source("simple.frag");
	//	GPUKernel.vertex_source("simple.vert");
	//	GPUKernel.install(true);

	    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	 	GLfloat luzDifusa[4]={1.0,1.0,0.0,1.0};         //cor
		GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};   //brilho
		GLfloat especularidade[4]={1.0,0.0,0.0,1.0};	  //brilho do material

		GLint especMaterial = 64;

		GLfloat light_position0[] = {0.0, 0.5, 10.0, 0.0};

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);           //cor fundo
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

		glEnable(GL_NORMALIZE);
}


void OpenGLScene::drawBackground(QPainter *painter, const QRectF &)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL) {
        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.SetViewByMouse();
    glLoadMatrixf((~camera.ViewMatrix()));

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

void OpenGLScene::sceneRectChanged ( const QRectF & rect )
{
	int w = GLint(width());
    int h = GLint(height());
    glViewport(0, 0, w, h);
    camera.SetWindowSize(w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(w) / h;
    camera.SetProjectionMatrix(90.0,x,0.1,1000);

    glLoadMatrixf((~camera.PespectiveProjectionMatrix()).ToRealPtr());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mCenterX =  static_cast<float> (w*0.5);
    mCenterY =  static_cast<float> (h*0.5);
}

void OpenGLScene::keyPressEvent(QKeyEvent * event)
{

	QGraphicsScene::keyPressEvent(event);

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

	event->accept();


}

void OpenGLScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if (event->isAccepted())
        return;

    if (event->buttons() & Qt::LeftButton)
    {
    	//camera.SetMouseInfo(event->x(),event->y());
    	float heading = 0.0f;
    	float pitch = 0.0f;
    	float roll = 0.0f;
    	const QPointF delta = event->pos();

    	pitch = -(static_cast<float>(delta.x()) - mCenterX) * 0.2;
    	heading = -(static_cast<float>(delta.y()) - mCenterY) * 0.2;


    	camera.Rotate(pitch,heading, 0.0f);

    	//mouse.moveToWindowCenter();

    	QCursor::setPos(QPoint(static_cast<int>(mCenterX),static_cast<int>(mCenterY)));

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

}

void OpenGLScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (event->isAccepted())
        return;
    if (event->button() == Qt::LeftButton)
    {
    	const QPointF delta = event->pos();
    	camera.lockMouse(true);
        mCenterX = static_cast<float>(delta.x());
        mCenterY = static_cast<float>(delta.y());
    }

    event->accept();
    update();
}

void OpenGLScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (event->isAccepted())
        return;

    event->accept();
    update();
}

void OpenGLScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsScene::wheelEvent(event);
    if (event->isAccepted())
        return;

    event->accept();
    update();
}


//
//#include "openglscene.h"
//#include "model.h"
//
//#include <QtGui>
//#include <QtOpenGL>
//
//#ifndef GL_MULTISAMPLE
//#define GL_MULTISAMPLE  0x809D
//#endif
//
//QDialog *OpenGLScene::createDialog(const QString &windowTitle) const
//{
//    QDialog *dialog = new QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//
//    dialog->setWindowOpacity(0.8);
//    dialog->setWindowTitle(windowTitle);
//    dialog->setLayout(new QVBoxLayout);
//
//    return dialog;
//}
//
//OpenGLScene::OpenGLScene()
//    : m_wireframeEnabled(false)
//    , m_normalsEnabled(false)
//    , m_modelColor(153, 255, 0)
//    , m_backgroundColor(0, 170, 255)
//    , m_model(0)
//    , m_lastTime(0)
//    , m_distance(1.4f)
//    , m_angularMomentum(0, 40, 0)
//{
//    QWidget *controls = createDialog(tr("Controls"));
//
//    m_modelButton = new QPushButton(tr("Load model"));
//    connect(m_modelButton, SIGNAL(clicked()), this, SLOT(loadModel()));
//#ifndef QT_NO_CONCURRENT
//    connect(&m_modelLoader, SIGNAL(finished()), this, SLOT(modelLoaded()));
//#endif
//
//
//
//
//			QFrame *frameHUD;
//			QGridLayout *gridLayout;
//			QLabel *labelTitle;
//			QPushButton *pushButtonHUD;
//			QFrame *framePointDisplay;
//			QHBoxLayout *horizontalLayout;
//			QLabel *labelPointCount;
//			QLabel *labelDisplayPoint;
//			QSpacerItem *verticalSpacerHUD;
//			frameHUD = new QFrame();
//		    //frameHUD->setWindowOpacity(0.8);
//		    frameHUD->setAttribute(Qt::WA_NoSystemBackground);
//			        frameHUD->setObjectName(QString::fromUtf8("frameHUD"));
//			        frameHUD->setGeometry(QRect(0, 0, 201, 111));
//			        frameHUD->setLayoutDirection(Qt::RightToLeft);
//			        frameHUD->setFrameShape(QFrame::StyledPanel);
//			        frameHUD->setFrameShadow(QFrame::Plain);
//			        //frameHUD->setFrameShadow(QFrame::Raised);
//			        gridLayout = new QGridLayout(frameHUD);
//			        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
//			        labelTitle = new QLabel(frameHUD);
//			        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
//			        QFont font;
//			        font.setBold(true);
//			        font.setWeight(75);
//			        labelTitle->setFont(font);
//			        labelTitle->setFrameShape(QFrame::StyledPanel);
//			        labelTitle->setTextFormat(Qt::AutoText);
//			        labelTitle->setAlignment(Qt::AlignCenter);
//			        labelTitle->setText("FPS Monitor");
//			        labelTitle->setWindowOpacity(0.5);
//			        labelTitle->setStyleSheet("background-color: rgb(0, 141, 215);"
//											  "color: rgb(255, 255, 255)");
//
//
//			        gridLayout->addWidget(labelTitle, 0, 1, 1, 1);
//
//			        verticalSpacerHUD = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
//
//			        gridLayout->addItem(verticalSpacerHUD, 3, 1, 1, 1);
//
//			        pushButtonHUD = new QPushButton(frameHUD);
//			        pushButtonHUD->setObjectName(QString::fromUtf8("pushButtonHUD"));
//			        pushButtonHUD->setText("Close");
//
//			        gridLayout->addWidget(pushButtonHUD, 4, 1, 1, 1);
//
//			        framePointDisplay = new QFrame(frameHUD);
//			        framePointDisplay->setObjectName(QString::fromUtf8("framePointDisplay"));
//			        framePointDisplay->setFrameShape(QFrame::NoFrame);
//			        framePointDisplay->setFrameShadow(QFrame::Raised);
//			        horizontalLayout = new QHBoxLayout(framePointDisplay);
//			        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
//			        labelPointCount = new QLabel(framePointDisplay);
//			        labelPointCount->setObjectName(QString::fromUtf8("labelPointCount"));
//			        labelPointCount->setFont(font);
//			        labelPointCount->setText("Point Count:");
//			        labelPointCount->setStyleSheet("color: rgb(255, 255, 255)");
//
//			        horizontalLayout->addWidget(labelPointCount);
//
//			        labelDisplayPoint = new QLabel(framePointDisplay);
//			        labelDisplayPoint->setObjectName(QString::fromUtf8("labelDisplayPoint"));
//			        labelPointCount->setFont(font);
//			        labelDisplayPoint->setText("100000");
//			        labelDisplayPoint->setStyleSheet("color: rgb(255, 255, 255)");
//
//			        horizontalLayout->addWidget(labelDisplayPoint);
//
//
//			        gridLayout->addWidget(framePointDisplay, 2, 1, 1, 1);
//
//			        QGraphicsProxyWidget *proxy = addWidget(frameHUD);
//
//
//
//
//
//
//
//
//    QCheckBox *wireframe = new QCheckBox(tr("Render as wireframe"));
//    connect(wireframe, SIGNAL(toggled(bool)), this, SLOT(enableWireframe(bool)));
//    controls->layout()->addWidget(wireframe);
//
//    QCheckBox *normals = new QCheckBox(tr("Display normals vectors"));
//    connect(normals, SIGNAL(toggled(bool)), this, SLOT(enableNormals(bool)));
//    controls->layout()->addWidget(normals);
//
//    QPushButton *colorButton = new QPushButton(tr("Choose model color"));
//    connect(colorButton, SIGNAL(clicked()), this, SLOT(setModelColor()));
//    controls->layout()->addWidget(colorButton);
//
//    QPushButton *backgroundButton = new QPushButton(tr("Choose background color"));
//    connect(backgroundButton, SIGNAL(clicked()), this, SLOT(setBackgroundColor()));
//    controls->layout()->addWidget(backgroundButton);
//
//    QWidget *statistics = createDialog(tr("Model info"));
//    statistics->layout()->setMargin(20);
//
//    for (int i = 0; i < 4; ++i) {
//        m_labels[i] = new QLabel;
//        statistics->layout()->addWidget(m_labels[i]);
//    }
//
//    QWidget *instructions = createDialog(tr("Instructions"));
//    instructions->layout()->addWidget(new QLabel(tr("Use mouse wheel to zoom model, and click and drag to rotate model")));
//    instructions->layout()->addWidget(new QLabel(tr("Move the sun around to change the light position")));
//
//    addWidget(instructions);
//    addWidget(controls);
//    addWidget(statistics);
//
//    QPointF pos(10, 10);
//    foreach (QGraphicsItem *item, items()) {
//        item->setFlag(QGraphicsItem::ItemIsMovable);
//        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
//
//        const QRectF rect = item->boundingRect();
//        item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
//        pos += QPointF(0, 10 + rect.height());
//    }
//
//    QRadialGradient gradient(40, 40, 40, 40, 40);
//    gradient.setColorAt(0.2, Qt::yellow);
//    gradient.setColorAt(1, Qt::transparent);
//
//    m_lightItem = new QGraphicsRectItem(0, 0, 80, 80);
//    m_lightItem->setPen(Qt::NoPen);
//    m_lightItem->setBrush(gradient);
//    m_lightItem->setFlag(QGraphicsItem::ItemIsMovable);
//    m_lightItem->setPos(800, 200);
//    addItem(m_lightItem);
//
//    loadModel(QLatin1String("qt.obj"));
//    m_time.start();
//}
//
//void OpenGLScene::drawBackground(QPainter *painter, const QRectF &)
//{
//    if (painter->paintEngine()->type() != QPaintEngine::OpenGL) {
//        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
//        return;
//    }
//
//    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    if (!m_model)
//        return;
//
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    gluPerspective(70, width() / height(), 0.01, 1000);
//
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//
//    const float pos[] = { m_lightItem->x() - width() / 2, height() / 2 - m_lightItem->y(), 512, 0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, pos);
//    glColor4f(m_modelColor.redF(), m_modelColor.greenF(), m_modelColor.blueF(), 1.0f);
//
//    const int delta = m_time.elapsed() - m_lastTime;
//    m_rotation += m_angularMomentum * (delta / 1000.0);
//    m_lastTime += delta;
//
//    glTranslatef(0, 0, -m_distance);
//    glRotatef(m_rotation.x, 1, 0, 0);
//    glRotatef(m_rotation.y, 0, 1, 0);
//    glRotatef(m_rotation.z, 0, 0, 1);
//
//    glEnable(GL_MULTISAMPLE);
//    m_model->render(m_wireframeEnabled, m_normalsEnabled);
//    glDisable(GL_MULTISAMPLE);
//
//    glPopMatrix();
//
//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();
//
//    QTimer::singleShot(20, this, SLOT(update()));
//}
//
//static Model *loadModel(const QString &filePath)
//{
//    return new Model(filePath);
//}
//
//void OpenGLScene::loadModel()
//{
//    loadModel(QFileDialog::getOpenFileName(0, tr("Choose model"), QString(), QLatin1String("*.obj")));
//}
//
//void OpenGLScene::loadModel(const QString &filePath)
//{
//    if (filePath.isEmpty())
//        return;
//
//    m_modelButton->setEnabled(false);
//    QApplication::setOverrideCursor(Qt::BusyCursor);
//#ifndef QT_NO_CONCURRENT
//    m_modelLoader.setFuture(QtConcurrent::run(::loadModel, filePath));
//#else
//    setModel(::loadModel(filePath));
//    modelLoaded();
//#endif
//}
//
//void OpenGLScene::modelLoaded()
//{
//#ifndef QT_NO_CONCURRENT
//    setModel(m_modelLoader.result());
//#endif
//    m_modelButton->setEnabled(true);
//    QApplication::restoreOverrideCursor();
//}
//
//void OpenGLScene::setModel(Model *model)
//{
//    delete m_model;
//    m_model = model;
//
//    m_labels[0]->setText(tr("File: %0").arg(m_model->fileName()));
//    m_labels[1]->setText(tr("Points: %0").arg(m_model->points()));
//    m_labels[2]->setText(tr("Edges: %0").arg(m_model->edges()));
//    m_labels[3]->setText(tr("Faces: %0").arg(m_model->faces()));
//
//    update();
//}
//
//void OpenGLScene::enableWireframe(bool enabled)
//{
//    m_wireframeEnabled = enabled;
//    update();
//}
//
//void OpenGLScene::enableNormals(bool enabled)
//{
//    m_normalsEnabled = enabled;
//    update();
//}
//
//void OpenGLScene::setModelColor()
//{
//    const QColor color = QColorDialog::getColor(m_modelColor);
//    if (color.isValid()) {
//        m_modelColor = color;
//        update();
//    }
//}
//
//void OpenGLScene::setBackgroundColor()
//{
//    const QColor color = QColorDialog::getColor(m_backgroundColor);
//    if (color.isValid()) {
//        m_backgroundColor = color;
//        update();
//    }
//}
//
//void OpenGLScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsScene::mouseMoveEvent(event);
//    if (event->isAccepted())
//        return;
//    if (event->buttons() & Qt::LeftButton) {
//        const QPointF delta = event->scenePos() - event->lastScenePos();
//        const Point3d angularImpulse = Point3d(delta.y(), delta.x(), 0) * 0.1;
//
//        m_rotation += angularImpulse;
//        m_accumulatedMomentum += angularImpulse;
//
//        event->accept();
//        update();
//    }
//}
//
//void OpenGLScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsScene::mousePressEvent(event);
//    if (event->isAccepted())
//        return;
//
//    m_mouseEventTime = m_time.elapsed();
//    m_angularMomentum = m_accumulatedMomentum = Point3d();
//    event->accept();
//}
//
//void OpenGLScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsScene::mouseReleaseEvent(event);
//    if (event->isAccepted())
//        return;
//
//    const int delta = m_time.elapsed() - m_mouseEventTime;
//    m_angularMomentum = m_accumulatedMomentum * (1000.0 / qMax(1, delta));
//    event->accept();
//    update();
//}
//
//void OpenGLScene::wheelEvent(QGraphicsSceneWheelEvent *event)
//{
//    QGraphicsScene::wheelEvent(event);
//    if (event->isAccepted())
//        return;
//
//    m_distance *= qPow(1.2, -event->delta() / 120);
//    event->accept();
//    update();
//}
