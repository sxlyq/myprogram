/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../final_task/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[351];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 20), // "on_main_menu_clicked"
QT_MOC_LITERAL(4, 55, 31), // "on_actionBack_to_main_triggered"
QT_MOC_LITERAL(5, 87, 26), // "on_actionZoom_in_triggered"
QT_MOC_LITERAL(6, 114, 27), // "on_actionZoom_out_triggered"
QT_MOC_LITERAL(7, 142, 28), // "on_actionAuto_play_triggered"
QT_MOC_LITERAL(8, 171, 33), // "on_actionStop_auto_play_trigg..."
QT_MOC_LITERAL(9, 205, 33), // "on_actionPause_Continue_trigg..."
QT_MOC_LITERAL(10, 239, 18), // "on_new_map_clicked"
QT_MOC_LITERAL(11, 258, 17), // "on_replay_clicked"
QT_MOC_LITERAL(12, 276, 11), // "moveOneStep"
QT_MOC_LITERAL(13, 288, 21), // "on_speed_valueChanged"
QT_MOC_LITERAL(14, 310, 5), // "value"
QT_MOC_LITERAL(15, 316, 34) // "on_heuristicWeight_editingFin..."

    },
    "MainWindow\0on_playButton_clicked\0\0"
    "on_main_menu_clicked\0"
    "on_actionBack_to_main_triggered\0"
    "on_actionZoom_in_triggered\0"
    "on_actionZoom_out_triggered\0"
    "on_actionAuto_play_triggered\0"
    "on_actionStop_auto_play_triggered\0"
    "on_actionPause_Continue_triggered\0"
    "on_new_map_clicked\0on_replay_clicked\0"
    "moveOneStep\0on_speed_valueChanged\0"
    "value\0on_heuristicWeight_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    1,   90,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_playButton_clicked(); break;
        case 1: _t->on_main_menu_clicked(); break;
        case 2: _t->on_actionBack_to_main_triggered(); break;
        case 3: _t->on_actionZoom_in_triggered(); break;
        case 4: _t->on_actionZoom_out_triggered(); break;
        case 5: _t->on_actionAuto_play_triggered(); break;
        case 6: _t->on_actionStop_auto_play_triggered(); break;
        case 7: _t->on_actionPause_Continue_triggered(); break;
        case 8: _t->on_new_map_clicked(); break;
        case 9: _t->on_replay_clicked(); break;
        case 10: _t->moveOneStep(); break;
        case 11: _t->on_speed_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_heuristicWeight_editingFinished(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
