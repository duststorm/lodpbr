#include "myMainWindow.hpp"


MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent)
{
    setupUi (this);

    glWidget = new GLWidget(this);

    //       glWidget->show();
    //
    //		 WidgetProxy *proxy = new WidgetProxy(glWidget,this);

    mdiArea->addSubWindow(glWidget);

    //     QWidget* w = proxy->createWindow("Embedded window");
    //     w->move(20, 270);
    //     w->layout()->addWidget(new QLineEdit(this));
    //     QPushButton* pb = new QPushButton("Create new toplevel GL widget", this);
    //     w->layout()->addWidget(pb);
    //     proxy->addWidget(w);

}


void MyMainWindow::on_action_Cluster_Debug_triggered()
{
	if (action_Cluster_Debug->isChecked())
		dockWidgetCluster->setVisible(true);
	else
		dockWidgetCluster->setVisible(false);
}
