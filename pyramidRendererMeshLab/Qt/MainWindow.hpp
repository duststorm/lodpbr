#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <QtGui/QtGui>

#include "ui_pyramidRendererMeshLab.h"

#include "Qt/GLWidget/GLWidget.hpp"

class QWorkspace;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow (QMainWindow *parent = 0);
    void open(QString fileName=QString(),bool who = true);
    void keyPressEvent(QKeyEvent *e);

public slots:

 	void on_action_Open_File_triggered								();

signals:


private:

	GLWidget*       	 glWidget;
};

#endif
