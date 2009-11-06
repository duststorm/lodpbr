#include "myMainWindow.hpp"
#include <iostream>

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


    connect(comboBoxCluster_BuildSurfelSimilarity,SIGNAL(activated(const QString &)),
		   	this->glWidget,SLOT(setClusterBuiltType(const QString &)));

    connect(checkBoxCluster_ShowCluster,SIGNAL(toggled(bool)),
    		this->glWidget,SLOT(setShowCluster(bool )));

    connect(checkBoxCluster_ShowSeed,SIGNAL(toggled(bool)),
    		this->glWidget,SLOT(setShowSeed(bool)));
}


void MyMainWindow::on_action_Cluster_Debug_triggered()
{
	if (action_Cluster_Debug->isChecked())
		dockWidgetCluster->setVisible(true);
	else
		dockWidgetCluster->setVisible(false);
}

