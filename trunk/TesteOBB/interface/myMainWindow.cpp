#include <QtGui/QInputDialog>
#include <iostream>


#include "myMainWindow.hpp"

using namespace std;

MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent) 
{
    setupUi (this);
   
}

void MyMainWindow::on_action_Wireframe_A_triggered()
{
	glFrame->renderMode_A = GLFrame::WireFrame;
	glFrame->updateGL();
}

void MyMainWindow::on_action_Smooth_A_triggered()
{
	glFrame->renderMode_A = GLFrame::PolygonWireFrame;
	glFrame->updateGL();
}

void MyMainWindow::on_action_Points_A_triggered()
{
	glFrame->renderMode_A = GLFrame::Points;
	glFrame->updateGL();
}

void MyMainWindow::open(QString filename,bool who) {
   
   if (filename != "") {
      QFileInfo fi(filename);
      QString extension = fi.suffix();
      
      if (extension != "off") {
         QString errorMsgFormat = "Error encountered while opening file:\n\"%1\"\n\nError details: The \"%2\" file extension is not supported. \nYou must open < off > format models.";
         QMessageBox::critical(this, tr("Opening Error"), errorMsgFormat.arg(filename, extension));
         return;
      }
      
           
      QByteArray filename_ = filename.toLatin1();
      fileModel_Off = filename;
       
      if (who)
      {
    	  glFrame->A  = new Polyhedron ( Polyhedron::load_off(filename_.data()) );
    	  glFrame->A->setColor (1.0,1.0,0.5);
    	  glFrame->calLimits();
    	    //o = OctreeRefine<float,SLAL::Point3<float>*>() ;
    		
    		/*for(Facet_iterator f = A->facets_begin(); f != A->facets_end(); ++f) {
    			Facet_handle *fh = new Facet_handle(f->halfedge()->facet());
    			octree.insert(fh);
    		}*/
    		
      }
      
      this->setWindowTitle("");
   }
}

void MyMainWindow::on_action_Open_Surface_A_triggered()
{
    // Asks for a file name to open.
    QString filename = QFileDialog::getOpenFileName (
                      this, 
                      tr("Choose a mesh file"),
                      ".",
                      tr("Off meshes (*.off)"));
    
    // Tries to load file if filename not empty.
    if (filename != "") {
      	
      open(filename,true);
    }
}




void MyMainWindow::on_action_Show_A_triggered()
{
	if(true){}
	
		
	glFrame->updateGL();

}



void MyMainWindow::on_action_Quit_MainWin_triggered()
{
	this->~QMainWindow();
}

void MyMainWindow::on_push_Button_Vertex_Around_clicked()
{
	if(true){}
}	
	
