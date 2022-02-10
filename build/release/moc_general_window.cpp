/****************************************************************************
** Meta object code from reading C++ file 'general_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../general_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'general_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DigitalClock_t {
    QByteArrayData data[4];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DigitalClock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DigitalClock_t qt_meta_stringdata_DigitalClock = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DigitalClock"
QT_MOC_LITERAL(1, 13, 8), // "set_size"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 2) // "sz"

    },
    "DigitalClock\0set_size\0\0sz"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DigitalClock[] = {

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
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void DigitalClock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DigitalClock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_size((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DigitalClock::staticMetaObject = { {
    &QLCDNumber::staticMetaObject,
    qt_meta_stringdata_DigitalClock.data,
    qt_meta_data_DigitalClock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DigitalClock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DigitalClock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DigitalClock.stringdata0))
        return static_cast<void*>(this);
    return QLCDNumber::qt_metacast(_clname);
}

int DigitalClock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_DClock_t {
    QByteArrayData data[3];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DClock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DClock_t qt_meta_stringdata_DClock = {
    {
QT_MOC_LITERAL(0, 0, 6), // "DClock"
QT_MOC_LITERAL(1, 7, 10), // "show_clock"
QT_MOC_LITERAL(2, 18, 0) // ""

    },
    "DClock\0show_clock\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DClock[] = {

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
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DClock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DClock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->show_clock(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DClock::staticMetaObject = { {
    &DigitalClock::staticMetaObject,
    qt_meta_stringdata_DClock.data,
    qt_meta_data_DClock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DClock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DClock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DClock.stringdata0))
        return static_cast<void*>(this);
    return DigitalClock::qt_metacast(_clname);
}

int DClock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DigitalClock::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_StopWatch_t {
    QByteArrayData data[7];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StopWatch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StopWatch_t qt_meta_stringdata_StopWatch = {
    {
QT_MOC_LITERAL(0, 0, 9), // "StopWatch"
QT_MOC_LITERAL(1, 10, 12), // "sw_stop_time"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "sw_start"
QT_MOC_LITERAL(4, 33, 10), // "sw_restart"
QT_MOC_LITERAL(5, 44, 7), // "sw_stop"
QT_MOC_LITERAL(6, 52, 14) // "show_stopwatch"

    },
    "StopWatch\0sw_stop_time\0\0sw_start\0"
    "sw_restart\0sw_stop\0show_stopwatch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StopWatch[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   42,    2, 0x0a /* Public */,
       4,    0,   43,    2, 0x0a /* Public */,
       5,    0,   44,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StopWatch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StopWatch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sw_stop_time((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sw_start(); break;
        case 2: _t->sw_restart(); break;
        case 3: _t->sw_stop(); break;
        case 4: _t->show_stopwatch(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StopWatch::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StopWatch::sw_stop_time)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StopWatch::staticMetaObject = { {
    &DigitalClock::staticMetaObject,
    qt_meta_stringdata_StopWatch.data,
    qt_meta_data_StopWatch,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StopWatch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StopWatch::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StopWatch.stringdata0))
        return static_cast<void*>(this);
    return DigitalClock::qt_metacast(_clname);
}

int StopWatch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DigitalClock::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void StopWatch::sw_stop_time(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_general_window_t {
    QByteArrayData data[23];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_general_window_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_general_window_t qt_meta_stringdata_general_window = {
    {
QT_MOC_LITERAL(0, 0, 14), // "general_window"
QT_MOC_LITERAL(1, 15, 11), // "windowShown"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "windowClose"
QT_MOC_LITERAL(4, 40, 11), // "show_camera"
QT_MOC_LITERAL(5, 52, 31), // "AutomaticTrainTrafficController"
QT_MOC_LITERAL(6, 84, 9), // "reset_all"
QT_MOC_LITERAL(7, 94, 11), // "normal_exit"
QT_MOC_LITERAL(8, 106, 20), // "set_horizontal_value"
QT_MOC_LITERAL(9, 127, 8), // "newValue"
QT_MOC_LITERAL(10, 136, 18), // "set_vertical_value"
QT_MOC_LITERAL(11, 155, 10), // "set_cursor"
QT_MOC_LITERAL(12, 166, 16), // "set_section_size"
QT_MOC_LITERAL(13, 183, 2), // "sz"
QT_MOC_LITERAL(14, 186, 14), // "set_views_data"
QT_MOC_LITERAL(15, 201, 14), // "one_cell_base*"
QT_MOC_LITERAL(16, 216, 4), // "data"
QT_MOC_LITERAL(17, 221, 3), // "row"
QT_MOC_LITERAL(18, 225, 6), // "column"
QT_MOC_LITERAL(19, 232, 17), // "dlg_control_panel"
QT_MOC_LITERAL(20, 250, 1), // "x"
QT_MOC_LITERAL(21, 252, 1), // "y"
QT_MOC_LITERAL(22, 254, 9) // "about_box"

    },
    "general_window\0windowShown\0\0windowClose\0"
    "show_camera\0AutomaticTrainTrafficController\0"
    "reset_all\0normal_exit\0set_horizontal_value\0"
    "newValue\0set_vertical_value\0set_cursor\0"
    "set_section_size\0sz\0set_views_data\0"
    "one_cell_base*\0data\0row\0column\0"
    "dlg_control_panel\0x\0y\0about_box"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_general_window[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    1,   85,    2, 0x0a /* Public */,
      10,    1,   88,    2, 0x0a /* Public */,
      11,    1,   91,    2, 0x0a /* Public */,
      12,    1,   94,    2, 0x0a /* Public */,
      14,    3,   97,    2, 0x0a /* Public */,
      19,    2,  104,    2, 0x0a /* Public */,
      22,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QCursor,    9,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, QMetaType::Int,   16,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   20,   21,
    QMetaType::Void,

       0        // eod
};

void general_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<general_window *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->windowShown(); break;
        case 1: _t->windowClose(); break;
        case 2: _t->show_camera(); break;
        case 3: _t->AutomaticTrainTrafficController(); break;
        case 4: _t->reset_all(); break;
        case 5: _t->normal_exit(); break;
        case 6: _t->set_horizontal_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->set_vertical_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->set_cursor((*reinterpret_cast< QCursor(*)>(_a[1]))); break;
        case 9: _t->set_section_size((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->set_views_data((*reinterpret_cast< one_cell_base*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->dlg_control_panel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->about_box(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
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
            using _t = void (general_window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&general_window::windowShown)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (general_window::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&general_window::windowClose)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject general_window::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_general_window.data,
    qt_meta_data_general_window,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *general_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *general_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_general_window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int general_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void general_window::windowShown()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void general_window::windowClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
