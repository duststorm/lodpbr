#ifndef MYGLFRAME_H
#define MYGLFRAME_H

#include <QGLWidget>
#include <deque>

#include "Kd-Tree/Kd-Tree.hpp"

#include "math/Point3.hpp"
#include "math/Vector3.hpp"

#include "surfels/surfel.hpp"
#include "surfels/surfels.hpp"

#include "Scene/Camera.hpp"
#include "surfels/MergeEllipses.hpp"

class GLFrame : public QGLWidget
{
    Q_OBJECT

public:
    GLFrame(QWidget *parent = 0);


    void calLimits();


    void DrawGroud();

    void SetThreshold(const float&);
    void SetCameraStep(const float&);
    void SetMode(bool);

    Surfels<float> surfels;

    KdTree<float,LAL::Point3<float> > kdTree;

    typedef  KdTree<float,LAL::Point3<float> >::Node KdTree3DNode;
	
    std::deque<LAL::Point3<float> > ItemList;

public slots:


protected:

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *e);
    void keyPressEvent ( QKeyEvent * e);

private:
    void draw();

    void drawKdTree(int& cont);
    void drawKdNodeRecursively(const KdTree3DNode* n,int& cont);
    bool drawKdNode(const KdTree3DNode* n,int& cont);

    void model();
    
    template < class T>
    LAL::BoundingBox3<T> limits();
    
    template < class T>
    void drawBox(LAL::BoundingBox3<T> BBox);

    QPoint 				lastPos;

    float mCenterX;
    float mCenterY;

    LAL::Camera camera;

    float Threshold;
    float CameraStep;
    bool mode;


};

#endif
