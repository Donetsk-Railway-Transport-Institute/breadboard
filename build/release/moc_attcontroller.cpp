/****************************************************************************
** Meta object code from reading C++ file 'attcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../attcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ATTController_t {
    QByteArrayData data[16];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ATTController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ATTController_t qt_meta_stringdata_ATTController = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ATTController"
QT_MOC_LITERAL(1, 14, 11), // "send_button"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "a_set_new_sost"
QT_MOC_LITERAL(4, 42, 4), // "name"
QT_MOC_LITERAL(5, 47, 8), // "new_sost"
QT_MOC_LITERAL(6, 56, 18), // "a_set_sost_from_at"
QT_MOC_LITERAL(7, 75, 8), // "str_sost"
QT_MOC_LITERAL(8, 84, 19), // "a_set_new_bind_sost"
QT_MOC_LITERAL(9, 104, 27), // "a_change_control_panel_sost"
QT_MOC_LITERAL(10, 132, 13), // "button_signal"
QT_MOC_LITERAL(11, 146, 14), // "send_ctr_panel"
QT_MOC_LITERAL(12, 161, 6), // "button"
QT_MOC_LITERAL(13, 168, 13), // "set_sycle_num"
QT_MOC_LITERAL(14, 182, 3), // "num"
QT_MOC_LITERAL(15, 186, 13) // "get_sycle_num"

    },
    "ATTController\0send_button\0\0a_set_new_sost\0"
    "name\0new_sost\0a_set_sost_from_at\0"
    "str_sost\0a_set_new_bind_sost\0"
    "a_change_control_panel_sost\0button_signal\0"
    "send_ctr_panel\0button\0set_sycle_num\0"
    "num\0get_sycle_num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ATTController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   57,    2, 0x0a /* Public */,
       6,    1,   62,    2, 0x0a /* Public */,
       8,    1,   65,    2, 0x0a /* Public */,
       9,    1,   68,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    1,   71,    2, 0x02 /* Public */,
      13,    1,   74,    2, 0x02 /* Public */,
      15,    0,   77,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,   10,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Int,

       0        // eod
};

void ATTController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ATTController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_button((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->a_set_new_sost((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->a_set_sost_from_at((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->a_set_new_bind_sost((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->a_change_control_panel_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->send_ctr_panel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->set_sycle_num((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { int _r = _t->get_sycle_num();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ATTController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ATTController::send_button)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ATTController::staticMetaObject = { {
    &at_script_canvas::staticMetaObject,
    qt_meta_stringdata_ATTController.data,
    qt_meta_data_ATTController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ATTController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ATTController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ATTController.stringdata0))
        return static_cast<void*>(this);
    return at_script_canvas::qt_metacast(_clname);
}

int ATTController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = at_script_canvas::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ATTController::send_button(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
