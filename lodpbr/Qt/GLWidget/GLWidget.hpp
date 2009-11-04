#ifndef MYGLFRAME_H
#define MYGLFRAME_H

#include <QGLWidget>
#include <QMdiSubWindow>
#include <vector>

#include "Kd-Tree/Kd-Tree.hpp"

#include "Surfels/Surfel.hpp"
#include "Surfels/SurfelContainer.hpp"

#include "Surfels/MergeEllipses.hpp"

#include "Clustering/Cluster.hpp"

#include "Math/Point3.hpp"
#include "Math/Vector3.hpp"

#include "Scene/Camera.hpp"

#include "Qt/Tools/FPSCounter.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // From QGLWidget

    explicit GLWidget(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    explicit GLWidget(QGLContext* context, QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    explicit GLWidget(const QGLFormat& format, QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *e);
    void keyPressEvent ( QKeyEvent * e);
    void glInit();

    // From kglib
    bool glInitialized() const  { return mGLInitialized; }

    // From lodpbr
    void calLimits();
    void DrawGroud();
    void SetMode(bool);
    void SetCluster(const int);


    SurfelContainer<float> surfels;

    Cluster<float,Celer::Surfel<float>*> cluster;

    KdTree<float,Celer::Surfel<float>* > kdTree;

    typedef  KdTree<float,Celer::Surfel<float>* >::Node KdTree3DNode;

    std::vector<Celer::Surfel<float>* > KNeibor;
    std::vector< std::vector<Celer::Surfel<float>* > > clusters;
    std::vector<Celer::Surfel<float>* >  newSurfel;
    std::vector<Celer::Vector4<float> > colors;

protected:


private:

	void init();

    void drawKdTree(int& cont);
    void drawKdNodeRecursively(const KdTree3DNode* n,int& cont);
    bool drawKdNode(const KdTree3DNode* n,int& cont);


    template < class T>
    Celer::BoundingBox3<T> limits();

    template < class T>
    void drawBox(Celer::BoundingBox3<T> BBox);

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



};

#endif
