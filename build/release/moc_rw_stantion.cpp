/****************************************************************************
** Meta object code from reading C++ file 'rw_stantion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../rw_stantion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rw_stantion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_rw_poligon_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rw_poligon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rw_poligon_t qt_meta_stringdata_rw_poligon = {
    {
QT_MOC_LITERAL(0, 0, 10) // "rw_poligon"

    },
    "rw_poligon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rw_poligon[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void rw_poligon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject rw_poligon::staticMetaObject = { {
    &rw_view_obj::staticMetaObject,
    qt_meta_stringdata_rw_poligon.data,
    qt_meta_data_rw_poligon,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *rw_poligon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rw_poligon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_rw_poligon.stringdata0))
        return static_cast<void*>(this);
    return rw_view_obj::qt_metacast(_clname);
}

int rw_poligon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rw_view_obj::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_rw_stantion_t {
    QByteArrayData data[3];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rw_stantion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rw_stantion_t qt_meta_stringdata_rw_stantion = {
    {
QT_MOC_LITERAL(0, 0, 11), // "rw_stantion"
QT_MOC_LITERAL(1, 12, 10), // "first_init"
QT_MOC_LITERAL(2, 23, 0) // ""

    },
    "rw_stantion\0first_init\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rw_stantion[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void rw_stantion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<rw_stantion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->first_init(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject rw_stantion::staticMetaObject = { {
    &rw_poligon::staticMetaObject,
    qt_meta_stringdata_rw_stantion.data,
    qt_meta_data_rw_stantion,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *rw_stantion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rw_stantion::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_rw_stantion.stringdata0))
        return static_cast<void*>(this);
    return rw_poligon::qt_metacast(_clname);
}

int rw_stantion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rw_poligon::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_rw_peregon_t {
    QByteArrayData data[3];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rw_peregon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rw_peregon_t qt_meta_stringdata_rw_peregon = {
    {
QT_MOC_LITERAL(0, 0, 10), // "rw_peregon"
QT_MOC_LITERAL(1, 11, 10), // "first_init"
QT_MOC_LITERAL(2, 22, 0) // ""

    },
    "rw_peregon\0first_init\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rw_peregon[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void rw_peregon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<rw_peregon *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->first_init(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject rw_peregon::staticMetaObject = { {
    &rw_poligon::staticMetaObject,
    qt_meta_stringdata_rw_peregon.data,
    qt_meta_data_rw_peregon,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *rw_peregon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rw_peregon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_rw_peregon.stringdata0))
        return static_cast<void*>(this);
    return rw_poligon::qt_metacast(_clname);
}

int rw_peregon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rw_poligon::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
