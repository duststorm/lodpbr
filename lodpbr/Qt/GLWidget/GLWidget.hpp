#ifndef MYGLFRAME_H
#define MYGLFRAME_H

#include <QGLWidget>
#include <QMdiSubWindow>
#include <vector>

#include "Surfels/Surfel.hpp"
#include "Surfels/IOSurfels.hpp"
#include "Surfels/MergeEllipses.hpp"

#include "Clustering/Cluster.hpp"

#include "Math/Point3.hpp"
#include "Math/Vector3.hpp"

#include "Scene/Camera.hpp"

#include "Qt/Tools/FPSCounter.h"

#include "Log/ClusterLog.hpp"
#include "Log/LSplatLog.hpp"

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
    void paintGL			();
    void mousePressEvent	(QMouseEvent *event);
    void mouseMoveEvent		(QMouseEvent *event);
    void mouseReleaseEvent	(QMouseEvent *event);
    void wheelEvent			(QWheelEvent *e);
    void keyPressEvent 		(QKeyEvent * e);
    void glInit();

    // From kglib
    bool glInitialized() const  { return mGLInitialized; }

    // From lodpbr
    void LoadModel(const char * filename);
    void calLimits();
    void DrawGroud();
    void SetMode(bool);
    void SetCluster(const int);

    ClusterLog mClusterLog;
    LSplatLog  mLSplatLog;

    Cluster<Celer::Surfel<float> > 				cluster;

    std::vector<Celer::Surfel<float> > 					lSurfels;

    Celer::BoundingBox3<float>   	   					mBox;


public slots:
	void setClusterBuiltType	(const QString & text);
	void setClusterBuiltSystem	(const QString & text);

	void setClusterRendererType	(const QString & text);
	void setClusterRenderingMode(const QString & text);

	void setShowCluster				(bool checked);
	void setShowSeed				(bool checked);
	void setShowModel				(bool checked);

	void setShowDrawClusterWithID		(bool checked);
	void setShowDrawClusterWithRange	(bool checked);

	void setDrawClusterWithID 	 (int values);
	void setDrawClusterWithRangeBegin 	 (int value);
	void setDrawClusterWithRangeEnd 	 (int value);


protected:

private:

	void init();

    QPoint 				lastPos;

    float mCenterX;
    float mCenterY;

    Celer::Camera camera;

    float CameraStep;

    int mCluster;
    int mNumber;
    bool mode;

    FPSCounter fps;

    bool mGLInitialized;

    //lodpbr


};

#endif
