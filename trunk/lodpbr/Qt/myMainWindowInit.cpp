#include "myMainWindow.hpp"
#include <iostream>

QProgressBar *MyMainWindow::progress;

MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent)
{
    setupUi (this);


	mdiArea = new QMdiArea(this),
	setCentralWidget(mdiArea);
//    this->glWidget =  new GLWidget(QGLFormat(QGLFormat(QGL::SampleBuffers)),this);
//	this->setCentralWidget(glWidget);

	globalStatusBar()=statusBar();

	progress = new QProgressBar(this);
	progress->setMaximum(100);
	progress->setMinimum(0);

	this->statusBar()->addPermanentWidget(progress,0);


	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateMenus()));
	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateWindowMenu()));
	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateDockCluster()));



	dockWidgetClusterContents->setEnabled(0);

	 // Group Box Draw  -


//    glWidget = new GLWidget(QGLFormat(QGLFormat(QGL::SampleBuffers)),this);
//
//    //       glWidget->show();
//    //
//    //		 WidgetProxy *proxy = new WidgetProxy(glWidget,this);
//
//    mdiArea->addSubWindow(glWidget);

    //     QWidget* w = proxy->createWindow("Embedded window");
    //     w->move(20, 270);
    //     w->layout()->addWidget(new QLineEdit(this));
    //     QPushButton* pb = new QPushButton("Create new toplevel GL widget", this);
    //     w->layout()->addWidget(pb);
    //     proxy->addWidget(w);


}


void MyMainWindow::updateMenus()
{}

void MyMainWindow::updateWindowMenu()
{}

void MyMainWindow::updateDockCluster()
{
	if (GLWIDGET())
	{
		dockWidgetClusterContents->setEnabled(1);
		if(GLWIDGET()->cluster.Clusters.size() > 0)
		{
			dockWidgetClusterContents->setEnabled(1);
			spinBoxCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

			sliderCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

			spinBoxCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
			spinBoxCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());

			sliderCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
			sliderCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());
		}else
		{

		}
	}
	else
	{
		dockWidgetClusterContents->setEnabled(0);
	}
}

void MyMainWindow::on_pushButtonBuild_clicked()
{
	GLWIDGET()->BuildCluster();

	if(GLWIDGET()->cluster.Clusters.size() > 0)
	{
		dockWidgetClusterContents->setEnabled(1);
		spinBoxCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

		sliderCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

		spinBoxCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
		spinBoxCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());

		sliderCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
		sliderCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());
	}else
	{

	}

}

void MyMainWindow::on_spinBoxCluster_DrawClusterWithRangeBegin_valueChanged(int value)
{
	GLWIDGET()->setDrawClusterWithRangeBegin(value-1);

	spinBoxCluster_DrawClusterWithRangeEnd->setMinimum(value);
	sliderCluster_DrawClusterWithRangeEnd->setMinimum(value);
//	if ( spinBoxCluster_DrawClusterWithRangeEnd->value() <= value)
//	{
//		spinBoxCluster_DrawClusterWithRangeEnd->setValue(value);
//		GLWIDGET()->setDrawClusterWithRangeEnd(value);
//	}
}


void MyMainWindow::on_sliderCluster_DrawClusterWithRangeBegin_valueChanged(int value)
{
	GLWIDGET()->setDrawClusterWithRangeBegin(value-1);

	spinBoxCluster_DrawClusterWithRangeEnd->setMinimum(value);
	sliderCluster_DrawClusterWithRangeEnd->setMinimum(value);
//	if ( spinBoxCluster_DrawClusterWithRangeEnd->value() <= value)
//	{
//		spinBoxCluster_DrawClusterWithRangeEnd->setValue(value);
//		GLWIDGET()->setDrawClusterWithRangeEnd(value);
//	}

}

void MyMainWindow::on_sliderCluster_DrawClusterWithRangeEnd_valueChanged(int value)
{
	GLWIDGET()->setDrawClusterWithRangeEnd(value-1);

}

void MyMainWindow::on_spinBoxCluster_DrawClusterWithRangeEnd_valueChanged(int value)
{
	GLWIDGET()->setDrawClusterWithRangeEnd(value-1);

}

void MyMainWindow::on_sliderCluster_DrawClusterWithID_valueChanged(int value)
{
	GLWIDGET()->setDrawClusterWithID(value-1);
}

void MyMainWindow::on_action_Cluster_Debug_triggered()
{
	if (action_Cluster_Debug->isChecked())
		dockWidgetCluster->setVisible(true);
	else
		dockWidgetCluster->setVisible(false);
}

//--------

void MyMainWindow::on_comboBoxCluster_BuildSurfelSimilarity_activated(const QString &s)
{
	GLWIDGET()->setClusterBuiltType(s);
}

void MyMainWindow::on_checkBoxCluster_ShowCluster_toggled(bool checked)
{
	GLWIDGET()->setShowCluster(checked);
}


void MyMainWindow::on_checkBoxCluster_ShowSeed_toggled(bool checked)
{
	GLWIDGET()->setShowSeed(checked);
}

void MyMainWindow::on_checkBoxCluster_ShowModel_toggled(bool checked)
{
	GLWIDGET()->setShowModel(checked);
}

void MyMainWindow::on_radioButtonCluster_DrawIndex_toggled(bool checked)
{
	GLWIDGET()->setShowDrawClusterWithID(checked);
}

void MyMainWindow::on_radioButtonCluster_DrawRange_toggled(bool checked)
{
	GLWIDGET()->setShowDrawClusterWithRange(checked);
}

