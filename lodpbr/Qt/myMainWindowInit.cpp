#include "myMainWindow.hpp"
#include <iostream>

QProgressBar *MyMainWindow::progress;

MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent)
{
    setupUi (this);


//    this->glWidget =  new GLWidget(QGLFormat(QGLFormat(QGL::SampleBuffers)),this);
//	  this->setCentralWidget(glWidget);

    // Loucuras do MeshLab
	globalStatusBar()=statusBar();

	progress = new QProgressBar(this);
	progress->setMaximum(100);
	progress->setMinimum(0);

	this->statusBar()->addPermanentWidget(progress,0);


	//Atualiza para a GLWidget corrente ...
	// .. os menus da barras de menus
	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateMenus()));

	// .. Nao sei =)
	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateWindowMenu()));

	//.. as possiveis acoes - (Construir, Renderizar ...)
	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateDockCluster()));

	dockWidgetClusterContents->setEnabled(0);
	dockWidgetDrawClusterContents->setEnabled(0);

	dockWidgetClusterBuilder->hide();
	dockWidgetDrawCluster->hide();

// Loucuras da KglLib
//	glWidget = new GLWidget(QGLFormat(QGLFormat(QGL::SampleBuffers)),this);
//	glWidget->show();
//	WidgetProxy *proxy = new WidgetProxy(glWidget,this);
//	mdiArea->addSubWindow(glWidget);

//	QWidget* w = proxy->createWindow("Embedded window");
//	w->move(20, 270);
//	w->layout()->addWidget(new QLineEdit(this));
//	QPushButton* pb = new QPushButton("Create new toplevel GL widget", this);
//	w->layout()->addWidget(pb);
//	proxy->addWidget(w);


}

//==== Slot SubWindow Activated ===============================================

void MyMainWindow::updateMenus()
{}

void MyMainWindow::updateWindowMenu()
{}

void MyMainWindow::updateDockCluster()
{
	if (GLWIDGET())
	{
		dockWidgetClusterContents->setEnabled(1);
		// Atualiza os Menus para GLWidget Corrente
		if(GLWIDGET()->cluster.Clusters.size() > 0)
		{
			// Atualiza os limites de renderização
			dockWidgetDrawClusterContents->setEnabled(1);
			spinBoxCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

			sliderCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

			spinBoxCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
			spinBoxCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());

			sliderCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
			sliderCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());
		}
		// Não tem clusters a serem renderizados
		else
		{
			dockWidgetDrawClusterContents->setEnabled(0);
		}
	}
	// Não há GLWidget
	else
	{
		dockWidgetClusterContents->setEnabled(0);
		dockWidgetDrawClusterContents->setEnabled(0);
	}
}

//==== Actions ================================================================

void MyMainWindow::on_action_Full_Screen_triggered()
{

	if (action_Full_Screen->isChecked())
	{
		this->showFullScreen();
	}
	else
	{
		this->showMaximized();
	}

}

void MyMainWindow::on_action_Show_Points_toggled(bool checked)
{
	GLWIDGET()->setShowModel(checked);
}

//==== DockBuildCluster =======================================================

void MyMainWindow::on_comboBoxCluster_BuildSurfelSimilarity_activated(const QString &s)
{
	GLWIDGET()->setClusterBuiltType(s);
}

void MyMainWindow::on_pushButtonBuild_clicked()
{
	GLWIDGET()->BuildCluster();

	if(GLWIDGET()->cluster.Clusters.size() > 0)
	{
		dockWidgetClusterContents->setEnabled(1);
		dockWidgetDrawClusterContents->setEnabled(1);
		spinBoxCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

		sliderCluster_DrawClusterWithID->setMaximum(GLWIDGET()->cluster.Clusters.size());

		spinBoxCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
		spinBoxCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());

		sliderCluster_DrawClusterWithRangeBegin->setMaximum(GLWIDGET()->cluster.Clusters.size());
		sliderCluster_DrawClusterWithRangeEnd->setMaximum(GLWIDGET()->cluster.Clusters.size());
	}
	else
	{
		dockWidgetDrawClusterContents->setEnabled(0);
	}

}

//==== DockWidget Draw Cluster ================================================


void MyMainWindow::on_spinBoxCluster_DrawClusterWithRangeBegin_valueChanged(int value)
{
	GLWIDGET()->setDrawClusterWithRangeBegin(value-1);

	spinBoxCluster_DrawClusterWithRangeEnd->setMinimum(value);
	sliderCluster_DrawClusterWithRangeEnd->setMinimum(value);

}


void MyMainWindow::on_sliderCluster_DrawClusterWithRangeBegin_valueChanged(int value)
{
	GLWIDGET()->setDrawClusterWithRangeBegin(value-1);

	spinBoxCluster_DrawClusterWithRangeEnd->setMinimum(value);
	sliderCluster_DrawClusterWithRangeEnd->setMinimum(value);

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



void MyMainWindow::on_toolButtonDrawCluster_toggled(bool checked)
{
	GLWIDGET()->setShowCluster(checked);
}

void MyMainWindow::on_radioButtonCluster_DrawIndex_toggled(bool checked)
{
	GLWIDGET()->setShowDrawClusterWithID(checked);
}

void MyMainWindow::on_radioButtonCluster_DrawRange_toggled(bool checked)
{
	GLWIDGET()->setShowDrawClusterWithRange(checked);
}

