/********************************************************************************
** Form generated from reading ui file 'interface.ui'
**
** Created: Thu May 28 16:33:03 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <GLFrame.hpp>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open_File;
    QAction *action_Quit_MainWin;
    QAction *action_Wireframe_A;
    QAction *action_NewSurfel;
    QAction *action_OldSurfels;
    QAction *action_Points_A;
    QAction *action_Model;
    QAction *action_Next;
    QAction *action_Previous;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    GLFrame *glFrame;
    QHBoxLayout *hboxLayout;
    QLabel *label_3;
    QSpinBox *SpinBoxNumber;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBoxCameraStep;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBoxThreshold;
    QPushButton *push_Button_Vertex_Around;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuSair;
    QMenu *menuHelp;
    QToolBar *toolBar_2;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(783, 671);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setDockNestingEnabled(true);
        action_Open_File = new QAction(MainWindow);
        action_Open_File->setObjectName(QString::fromUtf8("action_Open_File"));
        action_Quit_MainWin = new QAction(MainWindow);
        action_Quit_MainWin->setObjectName(QString::fromUtf8("action_Quit_MainWin"));
        action_Wireframe_A = new QAction(MainWindow);
        action_Wireframe_A->setObjectName(QString::fromUtf8("action_Wireframe_A"));
        action_NewSurfel = new QAction(MainWindow);
        action_NewSurfel->setObjectName(QString::fromUtf8("action_NewSurfel"));
        action_NewSurfel->setCheckable(true);
        action_NewSurfel->setChecked(false);
        action_OldSurfels = new QAction(MainWindow);
        action_OldSurfels->setObjectName(QString::fromUtf8("action_OldSurfels"));
        action_OldSurfels->setCheckable(true);
        action_OldSurfels->setChecked(true);
        action_OldSurfels->setEnabled(true);
        action_OldSurfels->setShortcutContext(Qt::WidgetShortcut);
        action_Points_A = new QAction(MainWindow);
        action_Points_A->setObjectName(QString::fromUtf8("action_Points_A"));
        action_Model = new QAction(MainWindow);
        action_Model->setObjectName(QString::fromUtf8("action_Model"));
        action_Next = new QAction(MainWindow);
        action_Next->setObjectName(QString::fromUtf8("action_Next"));
        action_Previous = new QAction(MainWindow);
        action_Previous->setObjectName(QString::fromUtf8("action_Previous"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        glFrame = new GLFrame(centralwidget);
        glFrame->setObjectName(QString::fromUtf8("glFrame"));

        vboxLayout->addWidget(glFrame);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        hboxLayout->addWidget(label_3);

        SpinBoxNumber = new QSpinBox(centralwidget);
        SpinBoxNumber->setObjectName(QString::fromUtf8("SpinBoxNumber"));
        SpinBoxNumber->setMinimum(0);
        SpinBoxNumber->setMaximum(100000);
        SpinBoxNumber->setValue(1);

        hboxLayout->addWidget(SpinBoxNumber);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout->addWidget(label_2);

        doubleSpinBoxCameraStep = new QDoubleSpinBox(centralwidget);
        doubleSpinBoxCameraStep->setObjectName(QString::fromUtf8("doubleSpinBoxCameraStep"));
        doubleSpinBoxCameraStep->setDecimals(4);
        doubleSpinBoxCameraStep->setMinimum(-99.99);
        doubleSpinBoxCameraStep->setSingleStep(0.0001);
        doubleSpinBoxCameraStep->setValue(0.1);

        hboxLayout->addWidget(doubleSpinBoxCameraStep);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        doubleSpinBoxThreshold = new QDoubleSpinBox(centralwidget);
        doubleSpinBoxThreshold->setObjectName(QString::fromUtf8("doubleSpinBoxThreshold"));
        doubleSpinBoxThreshold->setLayoutDirection(Qt::LeftToRight);
        doubleSpinBoxThreshold->setAutoFillBackground(false);
        doubleSpinBoxThreshold->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        doubleSpinBoxThreshold->setAccelerated(true);
        doubleSpinBoxThreshold->setDecimals(8);
        doubleSpinBoxThreshold->setMinimum(-99.99);
        doubleSpinBoxThreshold->setSingleStep(0.001);
        doubleSpinBoxThreshold->setValue(1);

        hboxLayout->addWidget(doubleSpinBoxThreshold);

        push_Button_Vertex_Around = new QPushButton(centralwidget);
        push_Button_Vertex_Around->setObjectName(QString::fromUtf8("push_Button_Vertex_Around"));

        hboxLayout->addWidget(push_Button_Vertex_Around);


        vboxLayout->addLayout(hboxLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 783, 25));
        menuSair = new QMenu(menubar);
        menuSair->setObjectName(QString::fromUtf8("menuSair"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuSair->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuSair->addAction(action_Open_File);
        menuSair->addSeparator();
        menuSair->addAction(action_Quit_MainWin);
        toolBar_2->addAction(action_NewSurfel);
        toolBar_2->addAction(action_OldSurfels);
        toolBar->addAction(action_Next);
        toolBar->addAction(action_Previous);

        retranslateUi(MainWindow);
        QObject::connect(MainWindow, SIGNAL(destroyed()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Open_File->setText(QApplication::translate("MainWindow", "Open &O", 0, QApplication::UnicodeUTF8));
        action_Open_File->setIconText(QApplication::translate("MainWindow", "Open StanFord Ply (*.ply)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Open_File->setToolTip(QApplication::translate("MainWindow", "Open ", "StanFord Ply (*.ply)", QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Open_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        action_Quit_MainWin->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Wireframe_A->setText(QApplication::translate("MainWindow", "Wireframe", 0, QApplication::UnicodeUTF8));
        action_NewSurfel->setText(QApplication::translate("MainWindow", "New Surfel", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_NewSurfel->setToolTip(QApplication::translate("MainWindow", "Usa todos abaixo para o c\303\241lculo do erro perpendicular", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_OldSurfels->setText(QApplication::translate("MainWindow", "Old Surfels", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_OldSurfels->setToolTip(QApplication::translate("MainWindow", "Usa apenas os filhos para o c\303\241lculo do erro perpendicular", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Points_A->setText(QApplication::translate("MainWindow", "Points", 0, QApplication::UnicodeUTF8));
        action_Model->setText(QApplication::translate("MainWindow", "Draw Model", 0, QApplication::UnicodeUTF8));
        action_Next->setText(QApplication::translate("MainWindow", "Next", 0, QApplication::UnicodeUTF8));
        action_Previous->setText(QApplication::translate("MainWindow", "Previous", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Number ?", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Camera Step ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Threshold", 0, QApplication::UnicodeUTF8));
        doubleSpinBoxThreshold->setSpecialValueText(QApplication::translate("MainWindow", "0.01", 0, QApplication::UnicodeUTF8));
        push_Button_Vertex_Around->setText(QApplication::translate("MainWindow", "Intersection", 0, QApplication::UnicodeUTF8));
        menuSair->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
