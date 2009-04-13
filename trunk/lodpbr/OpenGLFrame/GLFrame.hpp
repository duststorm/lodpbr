#ifndef MYGLFRAME_H
#define MYGLFRAME_H

#include <QGLWidget>
#include <vector>

#include "Kd-Tree/Kd-Tree.hpp"

#include "Math/Point3.hpp"
#include "Math/Vector3.hpp"

#include "Surfels/surfel.hpp"
#include "Surfels/surfels.hpp"

#include "Scene/Camera.hpp"
#include "Surfels/MergeEllipses.hpp"



class GLFrame : public QGLWidget
{
    Q_OBJECT

public:
    GLFrame(QWidget *parent = 0);


    void calLimits();


    void DrawGroud();

    void SetThreshold(const float);
    void SetCameraStep(const float);
    void SetNumber(int);

//    glslKernel GPUKernel;

    void SetCluster(const int);

    void SetMode(bool);

    Surfels<float> surfels;

    KdTree<float,LAL::Surfel<float>* > kdTree;

    typedef  KdTree<float,LAL::Surfel<float>* >::Node KdTree3DNode;

    std::vector<LAL::Surfel<float>* > KNeibor;
    std::vector< std::vector<LAL::Surfel<float>* > > cluster;
    std::vector<LAL::Surfel<float>* >  newSurfel;
    std::vector<LAL::Vector4<float> > colors;

public slots:


protected:

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
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
    int mCluster;
    int mNumber;
    bool mode;



};

#endif
