#include <QtGui>
#include <QtGui/QInputDialog>
#include <iostream>

#include "MainWindow.hpp"

MainWindow::MainWindow (QMainWindow *parent): QMainWindow(parent)
{

	setupUi(this);

    this->glWidget =  new GLWidget(QGLFormat(QGLFormat(QGL::SampleBuffers)),this);
    this->setCentralWidget(glWidget);

}

void MainWindow::open(QString pFilename,bool who )
{

	std::string filename =  QFile::encodeName(pFilename).constData ();

	if (pFilename.contains(".Surfels",Qt::CaseInsensitive) == 0)
	{
		glWidget->LoadModel(filename.c_str(),0,0);
	}else
	{
		glWidget->LoadModel(filename.c_str(),1,0);
	}

}


void MainWindow::on_action_Open_File_triggered()
{
    // Asks for a file name to open.


    QString filename = QFileDialog::getOpenFileName (
                      this,
                      tr("Choose a ply file"),
                      ".",
                      tr("ply model (*.ply)"));

    // Tries to load file if filename not empty.
    if (filename != "") {

     open(filename,true);

    }
}
//
//void MyMainWindow::on_action_Quit_MainWin_triggered()
//{
//	this->~QMainWindow();
//}
//


void MainWindow::keyPressEvent(QKeyEvent *e)
{
  if(e->key()==Qt::Key_Return && e->modifiers()==Qt::AltModifier)
  {
//    fullScreen();
    e->accept();
  }
  else e->ignore();
}
