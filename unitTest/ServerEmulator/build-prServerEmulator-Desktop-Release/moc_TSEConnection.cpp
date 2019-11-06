/****************************************************************************
** Meta object code from reading C++ file 'TSEConnection.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../prServerEmulator/TSEConnection.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TSEConnection.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_connection__TSEConnection_t {
    QByteArrayData data[10];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_connection__TSEConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_connection__TSEConnection_t qt_meta_stringdata_connection__TSEConnection = {
    {
QT_MOC_LITERAL(0, 0, 25), // "connection::TSEConnection"
QT_MOC_LITERAL(1, 26, 19), // "signalHostConnected"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 22), // "signalHostDisconnected"
QT_MOC_LITERAL(4, 70, 15), // "signalHostError"
QT_MOC_LITERAL(5, 86, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(6, 115, 17), // "slotHostConnected"
QT_MOC_LITERAL(7, 133, 20), // "slotHostDisconnected"
QT_MOC_LITERAL(8, 154, 13), // "slotHostError"
QT_MOC_LITERAL(9, 168, 17) // "slotHostReadyRead"

    },
    "connection::TSEConnection\0signalHostConnected\0"
    "\0signalHostDisconnected\0signalHostError\0"
    "QAbstractSocket::SocketError\0"
    "slotHostConnected\0slotHostDisconnected\0"
    "slotHostError\0slotHostReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_connection__TSEConnection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    2,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,

       0        // eod
};

void connection::TSEConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TSEConnection *_t = static_cast<TSEConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalHostConnected((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->signalHostDisconnected((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 2: _t->signalHostError((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[2]))); break;
        case 3: _t->slotHostConnected(); break;
        case 4: _t->slotHostDisconnected(); break;
        case 5: _t->slotHostError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->slotHostReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (TSEConnection::*_t)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TSEConnection::signalHostConnected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TSEConnection::*_t)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TSEConnection::signalHostDisconnected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TSEConnection::*_t)(quint32 , QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TSEConnection::signalHostError)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject connection::TSEConnection::staticMetaObject = {
    { &TConnection::staticMetaObject, qt_meta_stringdata_connection__TSEConnection.data,
      qt_meta_data_connection__TSEConnection,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *connection::TSEConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *connection::TSEConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_connection__TSEConnection.stringdata0))
        return static_cast<void*>(this);
    return TConnection::qt_metacast(_clname);
}

int connection::TSEConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TConnection::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void connection::TSEConnection::signalHostConnected(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void connection::TSEConnection::signalHostDisconnected(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void connection::TSEConnection::signalHostError(quint32 _t1, QAbstractSocket::SocketError _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
