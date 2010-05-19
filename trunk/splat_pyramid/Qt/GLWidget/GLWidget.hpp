#ifndef MYGLFRAME_H
#define MYGLFRAME_H

// From Meshlab
#include <GL/glew.h>
#include "render_splatpyramid/object.h"

#include <QGLWidget>
#include <QMdiSubWindow>
#include <vector>

// From Celer Library
#include "Celer/Math/Point3.hpp"
#include "Celer/Math/Vector3.hpp"
#include "Celer/Scene/Camera.hpp"
#include "Surfels/IOSurfels.hpp"

#include <vcg/math/matrix44.h>

#include "render_splatpyramid/pyramid_point_renderer_base.h"
#include "render_splatpyramid/pyramid_point_renderer.h"
#include "render_splatpyramid/pyramid_point_renderer_color.h"
//#include "pyramid_point_renderer_er.h"

#include "render_splatpyramid/shaderStructs.h"

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
	void createPointRenderer( void );

	void saveGLState();
	void restoreGLState();

	// Pyramid Splat Renderer

	 // Generic class, is instanced as one of the inherited classes (rendering algorithms)
	  PointBasedRenderer *point_based_render;

	  int canvas_width, canvas_height;
	  int windows_width, windows_height;

	  float clipRatioNear, clipRatioFar;
	  float fov;
	  float scale_factor;

	  // Lists of objects (usually one ply file is associated to one object in list)
	  vector<Object> objects;

	  // Determines which rendering class to use (Pyramid points, with color per vertex, templates version ...)
	  // see objects.h for the complete list (point_render_type_enum).
	  GLint render_mode;

	  // Flags on/off
	  bool show_points;
	  bool rotating;

	  int selected;

	  /***** Frames per second and Surfels per second vars ******/
	  double sps, fps;
	  int fps_loop;
	  double start_time, end_time;
	  int timing_profile;

	  /*************************************/

	// End -

    QPoint 				lastPos;

    float mCenterX;
    float mCenterY;

    Celer::Camera camera;

    float CameraStep;

    bool mGLInitialized;

    QRect rectangle;
	// C o l o r s
	QColor backgroundColor, foregroundColor;



};

#endif
