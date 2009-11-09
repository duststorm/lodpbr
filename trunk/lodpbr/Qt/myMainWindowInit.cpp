#include "myMainWindow.hpp"
#include <iostream>

MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent)
{
    setupUi (this);

    glWidget = new GLWidget(QGLFormat(QGLFormat(QGL::SampleBuffers)),this);

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
// Group Box Draw  -

    connect(checkBoxCluster_ShowCluster,SIGNAL(toggled(bool)),
    		this->glWidget,SLOT(setShowCluster(bool )));

    connect(checkBoxCluster_ShowSeed,SIGNAL(toggled(bool)),
    		this->glWidget,SLOT(setShowSeed(bool)));

    connect(checkBoxCluster_ShowModel,SIGNAL(toggled(bool)),
    		this->glWidget,SLOT(setShowModel(bool)));

    connect(radioButtonCluster_DrawIndex,SIGNAL(toggled(bool)),
    		this->glWidget,SLOT(setShowDrawClusterWithID(bool)));

    connect(radioButtonCluster_DrawRange,SIGNAL(toggled(bool)),
    		this->glWidget,SLOT(setShowDrawClusterWithRange(bool)));

	connect(sliderCluster_DrawClusterWithID,SIGNAL(valueChanged(int)),
			this->glWidget,SLOT(setDrawClusterWithID(int)));

}

void MyMainWindow::on_spinBoxCluster_DrawClusterWithRangeBegin_valueChanged(int value)
{
	glWidget->setDrawClusterWithRangeBegin(value);

	spinBoxCluster_DrawClusterWithRangeEnd->setMinimum(value);
	sliderCluster_DrawClusterWithRangeEnd->setMinimum(value);
	if ( spinBoxCluster_DrawClusterWithRangeEnd->value() <= value)
	{
		spinBoxCluster_DrawClusterWithRangeEnd->setValue(value);
		glWidget->setDrawClusterWithRangeEnd(value);
	}
}


void MyMainWindow::on_sliderCluster_DrawClusterWithRangeBegin_valueChanged(int value)
{
	glWidget->setDrawClusterWithRangeBegin(value);

	spinBoxCluster_DrawClusterWithRangeEnd->setMinimum(value);
	sliderCluster_DrawClusterWithRangeEnd->setMinimum(value);
	if ( spinBoxCluster_DrawClusterWithRangeEnd->value() <= value)
	{
		spinBoxCluster_DrawClusterWithRangeEnd->setValue(value);
		glWidget->setDrawClusterWithRangeEnd(value);
	}

}

void MyMainWindow::on_sliderCluster_DrawClusterWithRangeEnd_valueChanged(int value)
{
	glWidget->setDrawClusterWithRangeEnd(value);

}

void MyMainWindow::on_spinBoxCluster_DrawClusterWithRangeEnd_valueChanged(int value)
{
	glWidget->setDrawClusterWithRangeEnd(value);

}


void MyMainWindow::on_action_Cluster_Debug_triggered()
{
	if (action_Cluster_Debug->isChecked())
		dockWidgetCluster->setVisible(true);
	else
		dockWidgetCluster->setVisible(false);
}

