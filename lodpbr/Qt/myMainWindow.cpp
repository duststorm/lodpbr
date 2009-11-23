#include <QtGui>
#include <QtGui/QInputDialog>
#include <iostream>


#include <QtOpenGL>


#include "myMainWindow.hpp"

using namespace std;



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

//form Meshlab
bool MyMainWindow::QCallBack(const int pos, const char * str)
{
	int static lastPos=-1;
	if(pos==lastPos) return true;
	lastPos=pos;

	static QTime currTime;
	if(currTime.elapsed()< 100) return true;
	currTime.start();
	MyMainWindow::globalStatusBar()->showMessage(str,5000);
	progress->show();
	progress->setEnabled(true);
	progress->setValue(pos);
	MyMainWindow::globalStatusBar()->update();
	qApp->processEvents();
	return true;
}


void MyMainWindow::open(QString pFilename,bool who,WidgetProxy * p ) {

   if (pFilename != "") {

      std::string filename =  QFile::encodeName(pFilename).constData ();

      if (who)
      {

//    	  glWidget->Clear();
//    	  glWidget->show();
//    	  WidgetProxy *proxy = new WidgetProxy(glWidget,this);

    	  GLWidget*  gl = new GLWidget(QGLFormat(QGLFormat(QGL::SampleBuffers)),this);
    	  gl->setAttribute(Qt::WA_DeleteOnClose);
    	  mdiArea->addSubWindow(gl);

    	  gl->show();
    	  gl->LoadModel(filename.c_str(),QCallBack);
    	  gl->calLimits();

			toolButtonDrawCluster->setChecked(gl->getShowCluster());
			toolButtonClusterDrawSeed->setChecked(gl->getShowSeed());
			toolButtonClusterDrawSurfel->setChecked(gl->getShowSurfel());
			toolButtonClusterDrawNormal->setChecked(gl->getShowNormal());

//			bool getShowModel				() {return mClusterLog.Test(ClusterLog::Model);};

			radioButtonCluster_DrawIndex->setChecked(gl->getShowDrawClusterWithID());
			radioButtonCluster_DrawRange->setChecked(gl->getShowDrawClusterWithRange());

			spinBoxCluster_DrawClusterWithID->setValue(gl->getDrawClusterWithID());
			spinBoxCluster_DrawClusterWithRangeBegin->setValue(gl->getDrawClusterWithRangeBegin());
			spinBoxCluster_DrawClusterWithRangeEnd->setValue(gl->getDrawClusterWithRangeEnd());

    	  progress->reset();

      }

      this->setWindowTitle("");
   }
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

void MyMainWindow::keyPressEvent(QKeyEvent *e)
{
  if(e->key()==Qt::Key_Return && e->modifiers()==Qt::AltModifier)
  {
//    fullScreen();
    e->accept();
  }
  else e->ignore();
}
