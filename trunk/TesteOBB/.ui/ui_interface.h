/********************************************************************************
** Form generated from reading ui file 'interface.ui'
**
** Created: Wed Feb 27 13:03:05 2008
**      by: Qt User Interface Compiler version 4.3.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "GLFrame.hpp"

class Ui_MainWindow
{
public:
    QAction *action_Open_Surface_A;
    QAction *action_Quit_MainWin;
    QAction *action_Wireframe_A;
    QAction *action_Smooth_A;
    QAction *action_Show_A;
    QAction *action_Points_A;
    QAction *action_Model;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    GLFrame *glFrame;
    QPushButton *push_Button_Vertex_Around;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuSair;
    QMenu *menuHelp;
    QToolBar *toolBar_A;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->setWindowModality(Qt::WindowModal);
    MainWindow->resize(665, 550);
    MainWindow->setLayoutDirection(Qt::LeftToRight);
    MainWindow->setDockNestingEnabled(true);
    action_Open_Surface_A = new QAction(MainWindow);
    action_Open_Surface_A->setObjectName(QString::fromUtf8("action_Open_Surface_A"));
    action_Quit_MainWin = new QAction(MainWindow);
    action_Quit_MainWin->setObjectName(QString::fromUtf8("action_Quit_MainWin"));
    action_Wireframe_A = new QAction(MainWindow);
    action_Wireframe_A->setObjectName(QString::fromUtf8("action_Wireframe_A"));
    action_Smooth_A = new QAction(MainWindow);
    action_Smooth_A->setObjectName(QString::fromUtf8("action_Smooth_A"));
    action_Show_A = new QAction(MainWindow);
    action_Show_A->setObjectName(QString::fromUtf8("action_Show_A"));
    action_Show_A->setCheckable(true);
    action_Show_A->setChecked(true);
    action_Show_A->setEnabled(true);
    action_Points_A = new QAction(MainWindow);
    action_Points_A->setObjectName(QString::fromUtf8("action_Points_A"));
    action_Model = new QAction(MainWindow);
    action_Model->setObjectName(QString::fromUtf8("action_Model"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    vboxLayout = new QVBoxLayout(centralwidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    glFrame = new GLFrame(centralwidget);
    glFrame->setObjectName(QString::fromUtf8("glFrame"));

    vboxLayout->addWidget(glFrame);

    push_Button_Vertex_Around = new QPushButton(centralwidget);
    push_Button_Vertex_Around->setObjectName(QString::fromUtf8("push_Button_Vertex_Around"));

    vboxLayout->addWidget(push_Button_Vertex_Around);

    MainWindow->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 665, 25));
    menuSair = new QMenu(menubar);
    menuSair->setObjectName(QString::fromUtf8("menuSair"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    MainWindow->setMenuBar(menubar);
    toolBar_A = new QToolBar(MainWindow);
    toolBar_A->setObjectName(QString::fromUtf8("toolBar_A"));
    toolBar_A->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_A);

    menubar->addAction(menuSair->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuSair->addAction(action_Open_Surface_A);
    menuSair->addSeparator();
    menuSair->addAction(action_Quit_MainWin);
    toolBar_A->addAction(action_Show_A);
    toolBar_A->addAction(action_Wireframe_A);
    toolBar_A->addAction(action_Smooth_A);
    toolBar_A->addAction(action_Points_A);
    toolBar_A->addAction(action_Model);

    retranslateUi(MainWindow);
    QObject::connect(MainWindow, SIGNAL(destroyed()), MainWindow, SLOT(close()));

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    action_Open_Surface_A->setText(QApplication::translate("MainWindow", "Open Surface &A", 0, QApplication::UnicodeUTF8));
    action_Open_Surface_A->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0, QApplication::UnicodeUTF8));
    action_Quit_MainWin->setText(QApplication::translate("MainWindow", "&Quit", 0, QApplication::UnicodeUTF8));
    action_Wireframe_A->setText(QApplication::translate("MainWindow", "Wireframe", 0, QApplication::UnicodeUTF8));
    action_Smooth_A->setText(QApplication::translate("MainWindow", "Smooth", 0, QApplication::UnicodeUTF8));
    action_Show_A->setText(QApplication::translate("MainWindow", "Show A", 0, QApplication::UnicodeUTF8));
    action_Points_A->setText(QApplication::translate("MainWindow", "Points", 0, QApplication::UnicodeUTF8));
    action_Model->setText(QApplication::translate("MainWindow", "Draw Model", 0, QApplication::UnicodeUTF8));
    push_Button_Vertex_Around->setText(QApplication::translate("MainWindow", "Intersection", 0, QApplication::UnicodeUTF8));
    menuSair->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    toolBar_A->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_INTERFACE_H
