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

void MyMainWindow::on_action_Model_triggered()
{
	glFrame->renderMode_A = GLFrame::Model;
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
    	      	     	     	  	
    	  Surfels<double>::loadPly(text,glFrame->surfels);
    	  glFrame->calLimits();

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
                      tr("Off meshes (*.ply)"));
    
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
#if 0
	int i = 0;
	std::vector<Surfel<double> >::iterator it = glFrame->surfels.surfels.begin(); 
	
	while ( (i < 11) and ( it != glFrame->surfels.surfels.end() ) )
	{
		
		CGL::Point3<double> *p = new CGL::Point3<double>(it->position(0),it->position(1),it->position(2));
		glFrame->octree.insert (p);
		glFrame->surfels.temp.push_back( Surfel<double> (*p) );
		it++;
		i++;
				
	} 
	glFrame->octree.split();
	std::cout << i << " ==OPA== " << glFrame->surfels.temp.size() << " OctreeSize =" << glFrame->octree.root->itemPtrCount() << std::endl;
	
	if ( i != 0 )
	glFrame->surfels.surfels.erase (glFrame->surfels.surfels.begin(),glFrame->surfels.surfels.begin()+i);
#endif
}	
	
