/****************************************************************************
** Meta object code from reading C++ file 'myMainWindow.hpp'
**
** Created: Tue Feb 19 14:00:40 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../interface/myMainWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myMainWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_MyMainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      48,   13,   13,   13, 0x0a,
      79,   13,   13,   13, 0x0a,
     110,   13,   13,   13, 0x0a,
     147,   13,   13,   13, 0x0a,
     176,   13,   13,   13, 0x0a,
     211,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyMainWindow[] = {
    "MyMainWindow\0\0on_action_Wireframe_A_triggered()\0"
    "on_action_Smooth_A_triggered()\0"
    "on_action_Points_A_triggered()\0"
    "on_action_Open_Surface_A_triggered()\0"
    "on_action_Show_A_triggered()\0"
    "on_action_Quit_MainWin_triggered()\0"
    "on_push_Button_Vertex_Around_clicked()\0"
};

const QMetaObject MyMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyMainWindow,
      qt_meta_data_MyMainWindow, 0 }
};

const QMetaObject *MyMainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MyMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyMainWindow))
	return static_cast<void*>(const_cast< MyMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_action_Wireframe_A_triggered(); break;
        case 1: on_action_Smooth_A_triggered(); break;
        case 2: on_action_Points_A_triggered(); break;
        case 3: on_action_Open_Surface_A_triggered(); break;
        case 4: on_action_Show_A_triggered(); break;
        case 5: on_action_Quit_MainWin_triggered(); break;
        case 6: on_push_Button_Vertex_Around_clicked(); break;
        }
        _id -= 7;
    }
    return _id;
}
