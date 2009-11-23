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
#include "Qt/Tools/Settings.hpp"

#include "Log/ClusterLog.hpp"
#include "Log/LSplatLog.hpp"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:

    typedef Celer::Surfel<float>  					Surfel;


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


//    int selectedName() const { return selectedObjectId; };
//    int selectBufferSize() const { return selectBufferSize; };
//    GLuint* selectBuffer() { return selectBuffer; };
//    virtual void select(const QMouseEvent* event);
//    virtual void select(const QPoint& point);
//    void setSelectBufferSize(int size);
//    void setSelectedName(int id) { selectedObjectId=id; };
//    int selectRegionWidth() const { return selectRegionWidth; };
//    int selectRegionHeight() const { return selectRegionHeight; };
//    void setSelectRegionWidth(int width) { selectRegionWidth = width; };
//    void setSelectRegionHeight(int height) { selectRegionHeight = height; };
//    virtual void beginSelection(const QPoint& point);
//    virtual void drawWithNames() {};
//    virtual void endSelection(const QPoint& point);
//    virtual void postSelection(const QPoint& point) { Q_UNUSED(point); };


    void glInit();

    // From kglib
    bool glInitialized() const  { return mGLInitialized; }

    // From lodpbr
    void LoadModel(const char * filename,vcg::CallBackPos *cb);
    void calLimits();
    void DrawGroud();
    void SetMode(bool);
    void SetCluster(const int);

    ClusterLog mClusterLog;
    LSplatLog  mLSplatLog;

    Cluster<float> 										cluster;

    std::vector<Surfel> 								Surfels;

    Celer::BoundingBox3<float>   	   					Box;


public slots:
	void Clear();

	void setBackgroundColor(const QColor& color) { backgroundColor=color; qglClearColor(color); };
	void setForegroundColor(const QColor& color) { foregroundColor = color; };
	//@}

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

	void BuildCluster					 (void);


protected:

private:

	void init();

	enum StateMode {CRUDE,CLUSTER,LOD};
	StateMode mStateMode;

	enum SelectionMode {SEED,ADD_NEIBORHOO,DEL_NEIBORHOO};
	SelectionMode mSelectionMode;

	void drawSelectionRectangle() const;
	void startScreenCoordinatesSystem(bool upward = 0) const;
	void stopScreenCoordinatesSystem() const;

	int selectRegionWidth() const { return mSelectRegionWidth; };
	int selectRegionHeight() const { return mSelectRegionHeight; };

	void setSelectRegionWidth(int width) { mSelectRegionWidth = width; };
	void setSelectRegionHeight(int height) { mSelectRegionHeight = height; };

	GLuint* selectBuffer() { return mSelectBuffer; };
	void setSelectBufferSize(int size);
	int selectBufferSize() const { return mSelectBufferSize; };

	void beginSelection(const QPoint& point);
	void drawWithNames();
	void endSelection(const QPoint& point);
	void select(const QPoint& point);

	void saveGLState();
	void restoreGLState();


	std::vector<Celer::Surfel<float> > result;

//    void drawKdTree(int& cont);
//    void drawKdNodeRecursively(const KdTree3DNode* n,int& cont);
//    bool drawKdNode(const KdTree3DNode* n,int& cont);


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
    Settings   settings;

    bool mGLInitialized;

    //lodpbr

	// S e l e c t i o n
	int mSelectRegionWidth, mSelectRegionHeight;
	int mSelectBufferSize;
	GLuint* mSelectBuffer;
	int selectedObjectId;

    QRect rectangle;
	// C o l o r s
	QColor backgroundColor, foregroundColor;



};

#endif
