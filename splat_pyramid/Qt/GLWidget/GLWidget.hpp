#ifndef MYGLFRAME_H
#define MYGLFRAME_H

// From Meshlab
#include "render_splatpyramid/object.h"

#include <QGLWidget>
#include <QMdiSubWindow>
#include <vector>

// From Celer Library
#include "Celer/Math/Point3.hpp"
#include "Celer/Math/Vector3.hpp"
#include "Celer/Scene/Camera.hpp"
#include "Surfels/IOSurfels.hpp"


//From VcgLib
#include <wrap/callback.h>


class GLWidget : public QGLWidget
{
    Q_OBJECT

public:


    // From QGLWidget
    explicit GLWidget		(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    explicit GLWidget		(QGLContext* context, QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    explicit GLWidget		(const QGLFormat& format, QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    void initializeGL		();
    void resizeGL			(int width, int height);


    void paintEvent			(QPaintEvent *);

    void draw				();
    void paintGL			();
    void mousePressEvent	(QMouseEvent *event);
    void mouseMoveEvent		(QMouseEvent *event);
    void mouseReleaseEvent	(QMouseEvent *event);
    void wheelEvent			(QWheelEvent *e);
    void keyPressEvent 		(QKeyEvent * e);


    void LoadModel			(const char * filename,bool eliptical,vcg::CallBackPos *cb);

    void glInit();

    // From kglib
    bool glInitialized() const  { return mGLInitialized; }


    void DrawGroud();
    //
    void setCamera(Celer::Camera pCamera){ this->camera = pCamera;}
    Celer::Camera Camera() {return this->camera;}

public slots:

	void setBackgroundColor(const QColor& color) { backgroundColor=color; qglClearColor(color); };
	void setForegroundColor(const QColor& color) { foregroundColor = color; };

protected:

private:

	void init();

	void saveGLState();
	void restoreGLState();

    QPoint 				lastPos;

    float mCenterX;
    float mCenterY;

    Celer::Camera camera;

    float CameraStep;

    bool mGLInitialized;

    std::vector<Object> objects;

    QRect rectangle;
	// C o l o r s
	QColor backgroundColor, foregroundColor;



};

#endif
