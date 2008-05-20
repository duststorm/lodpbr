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

#include "slal/Camera.hpp"

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
    void drawPoints();
    void model();
    void LODSelection( OctreeNode<float,Surfel<float>* > * pNode, int& cont);
    void SIZE( OctreeNode<float,Surfel<float>* > * pNode, long int& cont);
    
    template < class T>
    LAL::BoundingBox3<T> limits();
    template < class T>
    void drawBox(LAL::BoundingBox3<T> BBox);
  
    QPoint 				lastPos;
    
    LAL::Camera camera;
    
    float Threshold;
    float CameraStep;
    bool mode;
    
	bool show_A;
    
};

#endif
