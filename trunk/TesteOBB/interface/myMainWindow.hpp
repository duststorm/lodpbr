#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <QtGui/QtGui>

#include "ui_interface.h"

class MyMainWindow : public QMainWindow, private Ui::MainWindow 
{
    Q_OBJECT
    
public:
    MyMainWindow (QMainWindow *parent = 0);
    void open(QString fileName=QString(),bool who = true);
    
public slots:
	
	void on_action_Wireframe_A_triggered();

	void on_action_Smooth_A_triggered();
	
	void on_action_Points_A_triggered();

	void on_action_Open_Surface_A_triggered();
	
	void on_action_Show_A_triggered();

	void on_action_Quit_MainWin_triggered();
	void on_push_Button_Vertex_Around_clicked();

private:
	QString              fileModel_Off;
		
};

#endif
