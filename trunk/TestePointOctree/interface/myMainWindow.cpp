#include <QtGui/QInputDialog>
#include <iostream>


#include "myMainWindow.hpp"

using namespace std;

MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent) 
{
    setupUi (this);
   
}

void MyMainWindow::on_doubleSpinBoxThreshold_valueChanged(double d)
{
	
	glFrame->SetThreshold(d);
	glFrame->updateGL();
}

void MyMainWindow::on_doubleSpinBoxCameraStep_valueChanged(double d)
{
	
	glFrame->SetCameraStep(d);
	glFrame->updateGL();
}

void MyMainWindow::on_action_NewSurfel_triggered()
{
	action_NewSurfel->setChecked(1);
	action_OldSurfels->setChecked(0);
	glFrame->SetMode(true);
}

void MyMainWindow::on_action_OldSurfels_triggered()
{
	action_OldSurfels->setChecked(1);
	action_NewSurfel->setChecked(0);
	glFrame->SetMode(false);
}

void MyMainWindow::on_action_Model_triggered()
{
	glFrame->updateGL();
}


void MyMainWindow::open(QString filename,bool who) {
   
   if (filename != "") {
          
      QByteArray filename_ = filename.toLatin1();
      fileModel_Off = filename;
       
      if (who)
      {
    	  const char * text = filename.toLatin1();
    	  
    	  glFrame->surfels.temp.clear();
    	  	
    	  glFrame->surfels.surfels.clear();
    	      	     	     	  	
    	  Surfels<float>::loadPly(text,glFrame->surfels);
    	  glFrame->calLimits();

      }
      
      this->setWindowTitle("");
   }
}

void MyMainWindow::on_action_Open_File_triggered()
{
    // Asks for a file name to open.
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






void MyMainWindow::on_action_Quit_MainWin_triggered()
{
	this->~QMainWindow();
}

void MyMainWindow::on_push_Button_Vertex_Around_clicked()
{

}	
	
