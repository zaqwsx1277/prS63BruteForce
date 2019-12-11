/****************************************************************************
** Meta object code from reading C++ file 'prS63BruteForceServer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../prS63BruteForceServer/prS63BruteForceServer.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'prS63BruteForceServer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_server__prS63BruteForceServer_t {
    QByteArrayData data[10];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_server__prS63BruteForceServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_server__prS63BruteForceServer_t qt_meta_stringdata_server__prS63BruteForceServer = {
    {
QT_MOC_LITERAL(0, 0, 29), // "server::prS63BruteForceServer"
QT_MOC_LITERAL(1, 30, 17), // "on_btnRun_clicked"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 25), // "on_spPathFrom_textChanged"
QT_MOC_LITERAL(4, 75, 4), // "arg1"
QT_MOC_LITERAL(5, 80, 28), // "on_spThreadCount_textChanged"
QT_MOC_LITERAL(6, 109, 25), // "on_spKeyStart_textChanged"
QT_MOC_LITERAL(7, 135, 24), // "on_spKeyStop_textChanged"
QT_MOC_LITERAL(8, 160, 17), // "slotHostConnected"
QT_MOC_LITERAL(9, 178, 11) // "QTcpSocket*"

    },
    "server::prS63BruteForceServer\0"
    "on_btnRun_clicked\0\0on_spPathFrom_textChanged\0"
    "arg1\0on_spThreadCount_textChanged\0"
    "on_spKeyStart_textChanged\0"
    "on_spKeyStop_textChanged\0slotHostConnected\0"
    "QTcpSocket*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_server__prS63BruteForceServer[] = {

 // content:
       7,       // revision
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
       3,    1,   45,    2, 0x08 /* Private */,
       5,    1,   48,    2, 0x08 /* Private */,
       6,    1,   51,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       8,    1,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void server::prS63BruteForceServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        prS63BruteForceServer *_t = static_cast<prS63BruteForceServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnRun_clicked(); break;
        case 1: _t->on_spPathFrom_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_spThreadCount_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_spKeyStart_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_spKeyStop_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slotHostConnected((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTcpSocket* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject server::prS63BruteForceServer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_server__prS63BruteForceServer.data,
      qt_meta_data_server__prS63BruteForceServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *server::prS63BruteForceServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *server::prS63BruteForceServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_server__prS63BruteForceServer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int server::prS63BruteForceServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
