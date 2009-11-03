#include <QtGui>
#include <QtGui/QInputDialog>
#include <iostream>


#include "myMainWindow.hpp"

using namespace std;

MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent)
{
    setupUi (this);


//    GLWidget * gl    = new GLWidget(this);
//     WidgetProxy *proxy = new WidgetProxy(gl,this);
////
//	 //QMdiSubWindow *subWindow1 = new QMdiSubWindow;
//	 //subWindow1->setWidget(proxy);
//     //subWindow1->setAttribute(Qt::WA_DeleteOnClose);
//     mdiArea->addSubWindow(proxy);
////
//	 QMdiSubWindow *subWindow2 = new QMdiSubWindow;
////	 subWindow2->setWidget(proxy);
//     subWindow2->setAttribute(Qt::WA_DeleteOnClose);
//     mdiArea->addSubWindow(subWindow2);
////
//     QWidget* w = proxy->createWindow("Embedded window");
//     w->move(20, 270);
//     w->layout()->addWidget(new QLineEdit(this));
//     QPushButton* pb = new QPushButton("Create new toplevel GL widget", this);
//     w->layout()->addWidget(pb);
//     proxy->addWidget(w);
     //	setCentralWidget(contextGraphicView);

}

//void MyMainWindow::on_doubleSpinBoxThreshold_valueChanged(double d)
//{
//
//	glFrame->SetThreshold(d);
//	glFrame->updateGL();
//}
//
//void MyMainWindow::on_doubleSpinBoxCameraStep_valueChanged(double d)
//{
//
//	glFrame->SetCameraStep(d);
//	glFrame->updateGL();
//}
//
//void MyMainWindow::on_SpinBoxNumber_valueChanged(int d)
//{
//	glFrame->SetNumber(d);
//	glFrame->updateGL();
//}
//
//
//void MyMainWindow::on_action_NewSurfel_triggered()
//{
//	action_NewSurfel->setChecked(1);
//	action_OldSurfels->setChecked(0);
//	glFrame->SetMode(true);
//}
//
//void MyMainWindow::on_action_OldSurfels_triggered()
//{
//	action_OldSurfels->setChecked(1);
//	action_NewSurfel->setChecked(0);
//	glFrame->SetMode(false);
//}
//
//void MyMainWindow::on_action_Model_triggered()
//{
//	glFrame->updateGL();
//}
//
//void MyMainWindow::on_action_Next_triggered()
//{
//	glFrame->updateGL();
//}
//
//void MyMainWindow::on_action_Previous_triggered()
//{
//	glFrame->updateGL();
//}
//
//


void MyMainWindow::open(QString filename,bool who,WidgetProxy * p ) {

   if (filename != "") {

      QByteArray filename_ = filename.toLatin1();
      fileModel_Off = filename;

      if (who)
      {
    	  const char * text = filename.toLatin1();

    	  std::cout << "Felipe" << std::endl;
    	  SurfelContainer<float>::LoadPly(text,this->glWidget->surfels);

    	  this->glWidget->calLimits();
    	  std::cout << "Felipe2" << std::endl;

      }

      this->setWindowTitle("");
   }
}

void MyMainWindow::on_action_Full_Screen_triggered()
{

	this->showFullScreen();

}


void MyMainWindow::createToplevelGLWidget()
{
    // Create a toplevel GLWidget
    GLWidget* gl = new GLWidget();
    // Create a proxy for the gl widget. Note that this could be done inside
    //  GLWidget, so the client (that creates the GLWidget) needn't know
    //  anything about the WidgetProxy.
    WidgetProxy* proxy = new WidgetProxy(gl);
    gl->show();

    QWidget* hintWin = proxy->createWindow("Hint");
    hintWin->layout()->addWidget(new QLabel("This is another toplevel GLwidget,\n with embedded proxy", hintWin));
    hintWin->move(10, 100);
    proxy->addWidget(hintWin);
    proxy->showFullScreen();
    // This will crash on app shutdown, but thiago said it's probably internal
    //  Qt issue.
}


void MyMainWindow::on_action_Open_File_triggered()
{
    // Asks for a file name to open.


//	if(mdiArea->subWindowList().size() == 0)
//	{
//	     GLWidget * gl    = new GLWidget(this);
//	 	 WidgetProxy * proxy = new WidgetProxy(gl,this);
//
//
//
//
////	     QWidget* w = proxy->createWindow("Embedded window");
////	     w->move(20, 270);
////	     w->layout()->addWidget(new QLineEdit(this));
////	     QPushButton* pb = new QPushButton("Create new toplevel GL widget", this);
////	     connect(pb, SIGNAL(clicked()), this, SLOT(createToplevelGLWidget()));
////	     w->layout()->addWidget(pb);
////	     proxy->addWidget(w);
//
//
//	     mdiArea->addSubWindow(proxy);
//	     proxy->show();
//	//}

    QString filename = QFileDialog::getOpenFileName (
                      this,
                      tr("Choose a mesh file"),
                      ".",
                      tr("Off meshes (*.ply)"));

    // Tries to load file if filename not empty.
    if (filename != "") {

     open(filename,true);

    }
}
//
//
//
//
//
//
//void MyMainWindow::on_action_Quit_MainWin_triggered()
//{
//	this->~QMainWindow();
//}
//
//void MyMainWindow::on_push_Button_Vertex_Around_clicked()
//{
//
//}

