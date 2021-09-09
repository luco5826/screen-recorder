/****************************************************************************
** Meta object code from reading C++ file 'recorder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../recorder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recorder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Recorder_t {
    QByteArrayData data[9];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Recorder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Recorder_t qt_meta_stringdata_Recorder = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Recorder"
QT_MOC_LITERAL(1, 9, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 22), // "on_pauseButton_clicked"
QT_MOC_LITERAL(4, 55, 13), // "updateCaption"
QT_MOC_LITERAL(5, 69, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(6, 91, 40), // "on_resolutionComboBox_current..."
QT_MOC_LITERAL(7, 132, 4), // "arg1"
QT_MOC_LITERAL(8, 137, 27) // "on_drawRegionButton_clicked"

    },
    "Recorder\0on_playButton_clicked\0\0"
    "on_pauseButton_clicked\0updateCaption\0"
    "on_stopButton_clicked\0"
    "on_resolutionComboBox_currentTextChanged\0"
    "arg1\0on_drawRegionButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Recorder[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    1,   48,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

       0        // eod
};

void Recorder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Recorder *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_playButton_clicked(); break;
        case 1: _t->on_pauseButton_clicked(); break;
        case 2: _t->updateCaption(); break;
        case 3: _t->on_stopButton_clicked(); break;
        case 4: _t->on_resolutionComboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_drawRegionButton_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Recorder::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Recorder.data,
    qt_meta_data_Recorder,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Recorder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Recorder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Recorder.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Recorder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
