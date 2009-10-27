#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <QtGui/QtGui>
#include <QGLWidget>

#include "ui_lodpbr.h"

#include "Qt/GLWidget/GLWidget.hpp"
#include "Qt/GLWidget/WidgetProxy.hpp"



class MyMainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MyMainWindow (QMainWindow *parent = 0);
    void open(QString fileName=QString(),bool who = true,WidgetProxy * p = 0);

public slots:

 	void on_action_Open_File_triggered();
 	void on_action_Full_Screen_triggered();
 	static void createToplevelGLWidget();

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
	QString              fileModel_Off;


};

#endif
