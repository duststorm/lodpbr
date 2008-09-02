#ifndef MYGLFRAME_H
#define MYGLFRAME_H

#include <QGLWidget>
#include <vector>

#include "Octree/ocTree.hpp"
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

    inline bool isVisible_A() const {  return this->show_A;  };
    inline void setVisible_A (const bool visible)  { this->show_A = visible; };

    void calLimits();

    typedef enum RenderMode {WireFrame=0, PolygonWireFrame, Smooth, Points,Model};

    void DrawGroud();

    RenderMode renderMode_A;

    void SetThreshold(const float&);
    void SetCameraStep(const float&);
    void SetMode(bool);

    Surfels<float> surfels;

    Octree<float,Surfel<float>* > octree;
    KdTree<float,LAL::Point3<float>* > kdTree;


    typedef  KdTree<float,LAL::Point3<float>* >::Node KdTree3DNode;
    KdTree3DNode* searchIt;

    LAL::Point3<float> midlePoint;

    Surfel<float>*  su;
    Surfel<float>* su1;
    Surfel<float>*su2;
    Surfel<float>*su3;

    MergeEllipses<float> me;

	float pxmax,pymax, paux;
	float pxmin,pymin;

	LAL::Point3<float> p1,p2,p11,p12,p21,p22;

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
    void drawPoints(int& cont);

    void drawKdTree(void);
    void drawKdNodeRecursively(const KdTree3DNode* n);
    bool drawKdNode(const KdTree3DNode* n);

    void model();
    void LODSelection( OctreeNode<float,Surfel<float>* > * pNode, int& cont);
    void SIZE( OctreeNode<float,Surfel<float>* > * pNode, long int& cont,std::map < int , std::vector<float> >& oi);

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

	bool show_A;

};

#endif
