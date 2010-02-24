#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <QtGui/QtGui>

#include "ui_lodpbr.h"

#include "Qt/GLWidget/GLWidget.hpp"
#include "Qt/GLWidget/WidgetProxy.hpp"

class QWorkspace;

class MyMainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MyMainWindow (QMainWindow *parent = 0);
    void open(QString fileName=QString(),bool who = true,WidgetProxy * p = 0);
    void keyPressEvent(QKeyEvent *e);
    static bool QCallBack(const int pos, const char * str);

    //from meshlab
    GLWidget *GLWIDGET() const
    {
    	if(mdiArea->currentSubWindow()==0)
    		return 0;
    	GLWidget *lglWiget = qobject_cast<GLWidget *>(mdiArea->currentSubWindow());
    	if(lglWiget)
    		return lglWiget;
    	lglWiget = qobject_cast<GLWidget *>(mdiArea->currentSubWindow()->widget());
    	assert(lglWiget);
    	return lglWiget;
    }


    static QStatusBar *&globalStatusBar()
    {
      static QStatusBar *_qsb=0;
      return _qsb;
    }

public slots:

	// ToolBar
//	void on_action_Snapshot_triggered								();
	//
	void updateMenus												();
	void updateWindowMenu											();
	// para cada janela opengl, atualizar a janela de atributos do cluster
	void updateDockCluster											();

 	void on_action_Open_File_triggered								();
 	void on_action_Save_As_Simplification_triggered					();
 	void on_action_Open_LOD_triggered								();
 	void on_action_Save_As_LOD_triggered							();
 	void on_action_Full_Screen_triggered							();


 	// -- Visible Dock Widgets
//
// 	void on_action_Cluster_Draw_toggled								(bool);
// 	void on_action_Cluster_Build_toggled							(bool);
// 	void on_action_Model_Draw_toggled								(bool);

 	// tool bar -- atributos do modelo

 	void on_pushButtonBuild_clicked									();
 	void on_pushButtonInteractive_clicked							();
 	void on_pushButtonSeed_clicked									();

 	// --Model   Dock Widget Draw
 	void on_toolButtonDrawModel_toggled								(bool checked);
 	void on_toolButtonModelDrawPoints_toggled						(bool checked);
 	void on_toolButtonModelDrawNormal_toggled						(bool checked);
 	void on_toolButtonModelDrawSurfel_toggled						(bool checked);
 	void on_toolButtonModelSplatting_toggled						(bool checked);
 	void on_sliderModelSurfelRadius_valueChanged					(int value);

 	// --Cluster Dock Widget Draw--
 	//
 	void on_toolButtonDrawCluster_toggled							(bool checked);
 	void on_toolButtonClusterDraw_toggled							(bool checked);
 	void on_toolButtonClusterDrawSurfel_toggled						(bool checked);
 	void on_toolButtonClusterSplatting_toggled 					(bool checked);
 	void on_toolButtonClusterDrawSeed_toggled						(bool checked);
 	void on_toolButtonClusterDrawNormal_toggled						(bool checked);

 	void on_spinBoxCluster_DrawClusterWithRangeBegin_valueChanged	(int);
 	void on_sliderCluster_DrawClusterWithRangeBegin_valueChanged	(int);

 	void on_spinBoxCluster_DrawClusterWithRangeEnd_valueChanged		(int value);
 	void on_sliderCluster_DrawClusterWithRangeEnd_valueChanged		(int value);

	void on_comboBoxCluster_BuildSurfelSimilarity_activated			(const QString &);
	void on_comboBoxCluster_BuildSurfelSplatShape_activated			(const QString &);

//	void on_checkBoxCluster_ShowCluster_toggled						(bool checked);
//	void on_checkBoxCluster_ShowSeed_toggled						(bool checked);
//	void on_checkBoxCluster_ShowModel_toggled						(bool checked);

	void on_radioButtonCluster_DrawIndex_toggled					(bool checked);
	void on_radioButtonCluster_DrawRange_toggled					(bool checked);
	void on_sliderCluster_DrawClusterWithID_valueChanged			(int value);
	void on_sliderClusterSurfelRadius_valueChanged					(int value);

	// coisas da kglib
 	static void createToplevelGLWidget();


signals:



//
//	void on_action_NewSurfel_triggered();
//
//	void on_action_OldSurfels_triggered();
//
//	void on_action_Next_triggered();
//	void on_action_Previous_triggered();
//
//	void on_SpinBoxNumber_valueChanged(int);
//	void on_doubleSpinBoxThreshold_valueChanged(double);
//	void on_doubleSpinBoxCameraStep_valueChanged(double);
//
//	void on_action_Model_triggered();
//
//	void on_action_Quit_MainWin_triggered();
//	void on_push_Button_Vertex_Around_clicked();

private:
	static QProgressBar *progress;
 	QWorkspace  		*workspace;
	QString              fileModel_Off;
	GLWidget*       	 glWidget;
};

#endif
