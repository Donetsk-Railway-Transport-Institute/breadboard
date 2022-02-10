/****************************************************************************
** Meta object code from reading C++ file 'rw_view_obj.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../rw_view_obj.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rw_view_obj.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_rw_view_obj_t {
    QByteArrayData data[19];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rw_view_obj_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rw_view_obj_t qt_meta_stringdata_rw_view_obj = {
    {
QT_MOC_LITERAL(0, 0, 11), // "rw_view_obj"
QT_MOC_LITERAL(1, 12, 14), // "set_views_data"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "one_cell_base*"
QT_MOC_LITERAL(4, 43, 4), // "data"
QT_MOC_LITERAL(5, 48, 3), // "row"
QT_MOC_LITERAL(6, 52, 6), // "column"
QT_MOC_LITERAL(7, 59, 12), // "depends_sost"
QT_MOC_LITERAL(8, 72, 4), // "name"
QT_MOC_LITERAL(9, 77, 13), // "to_status_bar"
QT_MOC_LITERAL(10, 91, 3), // "msg"
QT_MOC_LITERAL(11, 95, 17), // "msg_info_text_obj"
QT_MOC_LITERAL(12, 113, 1), // "x"
QT_MOC_LITERAL(13, 115, 1), // "y"
QT_MOC_LITERAL(14, 117, 8), // "set_sost"
QT_MOC_LITERAL(15, 126, 8), // "new_sost"
QT_MOC_LITERAL(16, 135, 16), // "set_depends_sost"
QT_MOC_LITERAL(17, 152, 22), // "obj_name_to_status_bar"
QT_MOC_LITERAL(18, 175, 15) // "obj_info_to_scr"

    },
    "rw_view_obj\0set_views_data\0\0one_cell_base*\0"
    "data\0row\0column\0depends_sost\0name\0"
    "to_status_bar\0msg\0msg_info_text_obj\0"
    "x\0y\0set_sost\0new_sost\0set_depends_sost\0"
    "obj_name_to_status_bar\0obj_info_to_scr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rw_view_obj[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       7,    1,   61,    2, 0x06 /* Public */,
       9,    1,   64,    2, 0x06 /* Public */,
      11,    3,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    2,   74,    2, 0x0a /* Public */,
      16,    1,   79,    2, 0x0a /* Public */,
      17,    2,   82,    2, 0x0a /* Public */,
      18,    2,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   10,   12,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,   15,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,

       0        // eod
};

void rw_view_obj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<rw_view_obj *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_views_data((*reinterpret_cast< one_cell_base*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->depends_sost((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->to_status_bar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->msg_info_text_obj((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->set_sost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->set_depends_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->obj_name_to_status_bar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->obj_info_to_scr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< one_cell_base* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (rw_view_obj::*)(one_cell_base * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rw_view_obj::set_views_data)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (rw_view_obj::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rw_view_obj::depends_sost)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (rw_view_obj::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rw_view_obj::to_status_bar)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (rw_view_obj::*)(QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&rw_view_obj::msg_info_text_obj)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject rw_view_obj::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_rw_view_obj.data,
    qt_meta_data_rw_view_obj,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *rw_view_obj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rw_view_obj::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_rw_view_obj.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int rw_view_obj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void rw_view_obj::set_views_data(one_cell_base * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void rw_view_obj::depends_sost(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void rw_view_obj::to_status_bar(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void rw_view_obj::msg_info_text_obj(QString _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
