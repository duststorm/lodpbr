#include "myMainWindow.hpp"
#include <iostream>

QProgressBar *MyMainWindow::progress;

MyMainWindow::MyMainWindow (QMainWindow *parent): QMainWindow(parent)
{
//	ui = new Ui::MainWindow;
//	ui->setupUi(this);
	setupUi(this);

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

	connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateDockCluster()));

	dockWidgetClusterContents->setEnabled(0);
	dockWidgetDrawClusterContents->setEnabled(0);

	dockWidgetClusterBuild->hide();
	dockWidgetDrawCluster->hide();
	dockWidgetDrawModel->hide();

	this->menuDockWindows->addAction(dockWidgetDrawModel->toggleViewAction());
	dockWidgetDrawModel->toggleViewAction()->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0, QApplication::UnicodeUTF8));

	this->menuDockWindows->addSeparator();

	this->menuDockWindows->addAction(dockWidgetDrawCluster->toggleViewAction());
	dockWidgetDrawCluster->toggleViewAction()->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", 0, QApplication::UnicodeUTF8));
	this->menuDockWindows->addAction(dockWidgetClusterBuild->toggleViewAction());
	dockWidgetClusterBuild->toggleViewAction()->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));

	//Q_FOREACH(QDockWidget* widget, findChildren<QDockWidget*>())
	//{

	//}


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

//==== Tool Bar

//void MyMainWindow::on_action_Snapshot_triggered	()
//{
//	if (GLWIDGET())
//		{
//			GLWIDGET()->takeSnapshot();
//		}
//}

//==== Slot SubWindow Activated ===============================================

void MyMainWindow::updateMenus()
{


}

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

			// -- Atualiza os valores corrente
			// botao cluster esta ativado ?
			toolButtonDrawCluster->setChecked(GLWIDGET()->getShowCluster());
			// botao Draw Seed esta ativado ?
			toolButtonClusterDrawSeed->setChecked(GLWIDGET()->getShowSeed());
			// botao Draw Srufel esta ativado ?
			toolButtonClusterDrawSurfel->setChecked(GLWIDGET()->getShowSurfel());
			// botao Draw Normal esta ativado ?
			toolButtonClusterDrawNormal->setChecked(GLWIDGET()->getShowNormal());

			radioButtonCluster_DrawIndex->setChecked(GLWIDGET()->getShowDrawClusterWithID());
			radioButtonCluster_DrawRange->setChecked(GLWIDGET()->getShowDrawClusterWithRange());

			// Atualiza os valoes dos spinBox que automaticamente atualiza os valos dos sliders
			spinBoxCluster_DrawClusterWithID->setValue(GLWIDGET()->getDrawClusterWithID());
			spinBoxCluster_DrawClusterWithRangeBegin->setValue(GLWIDGET()->getDrawClusterWithRangeBegin());
			spinBoxCluster_DrawClusterWithRangeEnd->setValue(GLWIDGET()->getDrawClusterWithRangeEnd());

		}
		// Nao tem clusters a serem renderizados
		else
		{
			dockWidgetDrawClusterContents->setEnabled(0);
		}
	}
	// Nao ha GLWidget
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

// Model Attributs

void MyMainWindow::on_toolButtonDrawModel_toggled(bool checked)
{
	GLWIDGET()->setShowModel(checked);
}

void MyMainWindow::on_toolButtonModelDrawPoints_toggled(bool checked)
{
	GLWIDGET()->setShowModelPoints(checked);
}

void MyMainWindow::on_toolButtonModelDrawNormal_toggled(bool checked)
{
	GLWIDGET()->setShowModelNormal(checked);
}

void MyMainWindow::on_toolButtonModelDrawSurfel_toggled(bool checked)
{
	GLWIDGET()->setShowModelSurfel(checked);
}

void MyMainWindow::on_toolButtonModelSplatting_toggled (bool checked)
{
	GLWIDGET()->setShowModelSplating(checked);
}

void MyMainWindow::on_sliderModelSurfelRadius_valueChanged (int value)
{
	GLWIDGET()->setModelSurfelRadius(value);
}


//==== DockBuildCluster =======================================================
void  MyMainWindow::on_comboBoxCluster_BuildSurfelSplatShape_activated (const QString &s)
{
	GLWIDGET()->setClusterSplatShape(s);
}

void MyMainWindow::on_comboBoxCluster_BuildSurfelSimilarity_activated(const QString &s)
{
	GLWIDGET()->setClusterBuiltType(s);
}

void MyMainWindow::on_pushButtonInteractive_clicked()
{

	GLWIDGET()->BuildInteractive();
}

void MyMainWindow::on_pushButtonSeed_clicked ()
{

	if (GLWIDGET())
	{
		GLWIDGET()->setSelected(GLWidget::ADD_NEIBORHOO);
	}

}

void MyMainWindow::on_pushButtonBuild_clicked()
{
	GLWIDGET()->BuildCluster(QCallBack);

	if(GLWIDGET()->cluster.Clusters.size() > 0)
	{
		dockWidgetClusterContents->setEnabled(1);
		// Abilita Dock Draw Cluster
		dockWidgetDrawClusterContents->setEnabled(1);
		// Atualiza os limites de renderização
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
	GLWIDGET()->setShowClusters(checked);
}
void MyMainWindow::on_toolButtonClusterDraw_toggled(bool checked)
{
	GLWIDGET()->setShowCluster(checked);
}
void MyMainWindow::on_toolButtonClusterDrawSurfel_toggled(bool checked)
{
	GLWIDGET()->setShowSurfel(checked);
}

void MyMainWindow::on_toolButtonClusterDrawSeed_toggled(bool checked)
{
	GLWIDGET()->setShowSeed(checked);
}
void MyMainWindow::on_toolButtonClusterDrawNormal_toggled(bool checked)
{
	GLWIDGET()->setShowNormal(checked);
}

void MyMainWindow::on_toolButtonClusterSplatting_toggled (bool checked)
{
	GLWIDGET()->setShowClusterSplatting(checked);
}

void MyMainWindow::on_sliderClusterSurfelRadius_valueChanged (int value)
{
	GLWIDGET()->setRadius(value);
}

void MyMainWindow::on_radioButtonCluster_DrawIndex_toggled(bool checked)
{
	GLWIDGET()->setShowDrawClusterWithID(checked);
}

void MyMainWindow::on_radioButtonCluster_DrawRange_toggled(bool checked)
{
	GLWIDGET()->setShowDrawClusterWithRange(checked);
}

