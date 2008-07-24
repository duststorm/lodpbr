#ifndef MYGLFRAME_H
#define MYGLFRAME_H

#include <QGLWidget>
#include <vector>

#include "lcgOctree/ocTree.hpp"
#include "lcgOctree/ocTreeLeafNode.hpp"
#include "lcgOctree/ocTreeBox.hpp"

#include "slal/Point3.hpp"
#include "slal/Vector3.hpp"

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
