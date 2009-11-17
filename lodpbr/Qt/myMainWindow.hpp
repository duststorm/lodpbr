#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <QtGui/QtGui>
#include <QGLWidget>

#include "ui_lodpbr.h"

#include "Qt/GLWidget/GLWidget.hpp"
#include "Qt/GLWidget/WidgetProxy.hpp"

class QWorkspace;

class MyMainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MyMainWindow (QMainWindow *parent = 0);
    void open(QString fileName=QString(),bool who = true,WidgetProxy * p = 0);
    void keyPressEvent(QKeyEvent *e);
    static bool QCallBack(const int pos, const char * str);

    static QStatusBar *&globalStatusBar()
    {
      static QStatusBar *_qsb=0;
      return _qsb;
    }

public slots:

 	void on_action_Open_File_triggered();
 	void on_action_Full_Screen_triggered();
 	void on_action_Cluster_Debug_triggered();

 	void on_pushButtonBuild_clicked();

 	void on_spinBoxCluster_DrawClusterWithRangeBegin_valueChanged(int);
 	void on_sliderCluster_DrawClusterWithRangeBegin_valueChanged(int);

 	void on_spinBoxCluster_DrawClusterWithRangeEnd_valueChanged(int value);
 	void on_sliderCluster_DrawClusterWithRangeEnd_valueChanged(int value);

 	static void createToplevelGLWidget();

signals:


//
//	void on_action_NewSurfel_triggered();
//
//	void on_action_OldSurfels_triggered();
//
//	void on_action_Next_triggered();
//	void on_action_Previous_triggered();
//
//	void on_SpinBoxNumber_valueChanged(int);
//	void on_doubleSpinBoxThreshold_valueChanged(double);
//	void on_doubleSpinBoxCameraStep_valueChanged(double);
//
//	void on_action_Model_triggered();
//
//	void on_action_Quit_MainWin_triggered();
//	void on_push_Button_Vertex_Around_clicked();

private:
	static QProgressBar *progress;
 	QWorkspace  		*workspace;
	QString              fileModel_Off;
	GLWidget*       	 glWidget;
};

#endif
