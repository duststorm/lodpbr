#ifndef MYGLFRAME_H
#define MYGLFRAME_H

 
#include <QGLWidget>
#include <vector>

#include "support/arcball.hpp"
#include "support/atmatrix.hpp"

#include "lcgOctree/ocTree.hpp"
#include "lcgOctree/ocTreeBox.hpp"

#include "slal/Point3.hpp"
#include "slal/Vector3.hpp"


#include "surfels/surfel.hpp"
#include "surfels/surfels.hpp"


class GLFrame : public QGLWidget
{
    Q_OBJECT

public:
    GLFrame(QWidget *parent = 0);
    
    inline bool isVisible_A() const {  return this->show_A;  };
    inline void setVisible_A (const bool visible)  { this->show_A = visible; };
    
    void calLimits();
        
    void zoomIn();
   	void zoomOut();
    typedef enum RenderMode {WireFrame=0, PolygonWireFrame, Smooth, Points,Model};   
       
    RenderMode renderMode_A;
       
    Surfels<double> surfels;
    
    Octree<double,CGL::Point3<double>*> octree;
    
    CGL::Point3<double> midlePoint;
                      
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
    void screenToWorld(int x, int y, double &xw, double &yw, double &zw);
    
    template < class T>
    CGL::BoundingBox3<T> limits();
    template < class T>
    void drawBox(CGL::BoundingBox3<T> BBox);

    GLfloat 			rotationX;
    GLfloat 			rotationY;
    GLfloat 			rotationZ;
    
    QPoint 				lastPos;
    GLfloat 			zoomFactor;
       
    double  			mousePositionX; 
    double  			mousePositionY; 
    double				mousePositionZ;
    
    AMatrix<GLfloat> 	sceneTransformation;
    AMatrix<GLfloat> 	sceneInitialTransformation; 
    ArcBall 			arcball;
   

    
	bool show_A;
    
};

#endif