/****************************************************************************
** Meta object code from reading C++ file 'at_script_canvas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../at_script_canvas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'at_script_canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_worker_sleep_signal_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_worker_sleep_signal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_worker_sleep_signal_t qt_meta_stringdata_worker_sleep_signal = {
    {
QT_MOC_LITERAL(0, 0, 19), // "worker_sleep_signal"
QT_MOC_LITERAL(1, 20, 11), // "resultReady"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 1) // "s"

    },
    "worker_sleep_signal\0resultReady\0\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_worker_sleep_signal[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void worker_sleep_signal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<worker_sleep_signal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (worker_sleep_signal::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&worker_sleep_signal::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject worker_sleep_signal::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_worker_sleep_signal.data,
    qt_meta_data_worker_sleep_signal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *worker_sleep_signal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *worker_sleep_signal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_worker_sleep_signal.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int worker_sleep_signal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void worker_sleep_signal::resultReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_worker_blink_signals_t {
    QByteArrayData data[6];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_worker_blink_signals_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_worker_blink_signals_t qt_meta_stringdata_worker_blink_signals = {
    {
QT_MOC_LITERAL(0, 0, 20), // "worker_blink_signals"
QT_MOC_LITERAL(1, 21, 11), // "resultReady"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 1), // "s"
QT_MOC_LITERAL(4, 36, 10), // "stop_blink"
QT_MOC_LITERAL(5, 47, 8) // "end_sost"

    },
    "worker_blink_signals\0resultReady\0\0s\0"
    "stop_blink\0end_sost"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_worker_blink_signals[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void worker_blink_signals::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<worker_blink_signals *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->stop_blink((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (worker_blink_signals::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&worker_blink_signals::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject worker_blink_signals::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_worker_blink_signals.data,
    qt_meta_data_worker_blink_signals,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *worker_blink_signals::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *worker_blink_signals::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_worker_blink_signals.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int worker_blink_signals::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void worker_blink_signals::resultReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_at_script_canvas_t {
    QByteArrayData data[52];
    char stringdata0[550];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_at_script_canvas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_at_script_canvas_t qt_meta_stringdata_at_script_canvas = {
    {
QT_MOC_LITERAL(0, 0, 16), // "at_script_canvas"
QT_MOC_LITERAL(1, 17, 12), // "set_new_sost"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 4), // "name"
QT_MOC_LITERAL(4, 36, 8), // "new_sost"
QT_MOC_LITERAL(5, 45, 16), // "set_sost_from_at"
QT_MOC_LITERAL(6, 62, 8), // "str_sost"
QT_MOC_LITERAL(7, 71, 17), // "set_new_bind_sost"
QT_MOC_LITERAL(8, 89, 25), // "change_control_panel_sost"
QT_MOC_LITERAL(9, 115, 13), // "button_signal"
QT_MOC_LITERAL(10, 129, 8), // "set_sost"
QT_MOC_LITERAL(11, 138, 22), // "set_control_panel_sost"
QT_MOC_LITERAL(12, 161, 20), // "set_mouse_press_sost"
QT_MOC_LITERAL(13, 182, 18), // "mouse_press_signal"
QT_MOC_LITERAL(14, 201, 14), // "set_sost_to_at"
QT_MOC_LITERAL(15, 216, 3), // "msg"
QT_MOC_LITERAL(16, 220, 14), // "set_delay_sost"
QT_MOC_LITERAL(17, 235, 6), // "signal"
QT_MOC_LITERAL(18, 242, 12), // "sleep_signal"
QT_MOC_LITERAL(19, 255, 8), // "obj_sost"
QT_MOC_LITERAL(20, 264, 5), // "msecs"
QT_MOC_LITERAL(21, 270, 17), // "start_blink_board"
QT_MOC_LITERAL(22, 288, 3), // "obj"
QT_MOC_LITERAL(23, 292, 3), // "com"
QT_MOC_LITERAL(24, 296, 16), // "stop_blink_board"
QT_MOC_LITERAL(25, 313, 8), // "end_sost"
QT_MOC_LITERAL(26, 322, 14), // "is_blink_board"
QT_MOC_LITERAL(27, 337, 18), // "start_blink_signal"
QT_MOC_LITERAL(28, 356, 17), // "stop_blink_signal"
QT_MOC_LITERAL(29, 374, 15), // "is_blink_signal"
QT_MOC_LITERAL(30, 390, 8), // "s_button"
QT_MOC_LITERAL(31, 399, 8), // "obj_name"
QT_MOC_LITERAL(32, 408, 10), // "get_button"
QT_MOC_LITERAL(33, 419, 9), // "sz_button"
QT_MOC_LITERAL(34, 429, 1), // "s"
QT_MOC_LITERAL(35, 431, 2), // "st"
QT_MOC_LITERAL(36, 434, 6), // "m_time"
QT_MOC_LITERAL(37, 441, 3), // "pct"
QT_MOC_LITERAL(38, 445, 2), // "ss"
QT_MOC_LITERAL(39, 448, 2), // "to"
QT_MOC_LITERAL(40, 451, 3), // "spl"
QT_MOC_LITERAL(41, 455, 2), // "dt"
QT_MOC_LITERAL(42, 458, 6), // "to_int"
QT_MOC_LITERAL(43, 465, 6), // "to_str"
QT_MOC_LITERAL(44, 472, 10), // "int_signal"
QT_MOC_LITERAL(45, 483, 13), // "double_signal"
QT_MOC_LITERAL(46, 497, 7), // "indexOf"
QT_MOC_LITERAL(47, 505, 3), // "str"
QT_MOC_LITERAL(48, 509, 6), // "substr"
QT_MOC_LITERAL(49, 516, 11), // "dlg_m_press"
QT_MOC_LITERAL(50, 528, 10), // "msg_script"
QT_MOC_LITERAL(51, 539, 10) // "msg_to_log"

    },
    "at_script_canvas\0set_new_sost\0\0name\0"
    "new_sost\0set_sost_from_at\0str_sost\0"
    "set_new_bind_sost\0change_control_panel_sost\0"
    "button_signal\0set_sost\0set_control_panel_sost\0"
    "set_mouse_press_sost\0mouse_press_signal\0"
    "set_sost_to_at\0msg\0set_delay_sost\0"
    "signal\0sleep_signal\0obj_sost\0msecs\0"
    "start_blink_board\0obj\0com\0stop_blink_board\0"
    "end_sost\0is_blink_board\0start_blink_signal\0"
    "stop_blink_signal\0is_blink_signal\0"
    "s_button\0obj_name\0get_button\0sz_button\0"
    "s\0st\0m_time\0pct\0ss\0to\0spl\0dt\0to_int\0"
    "to_str\0int_signal\0double_signal\0indexOf\0"
    "str\0substr\0dlg_m_press\0msg_script\0"
    "msg_to_log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_at_script_canvas[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  179,    2, 0x06 /* Public */,
       5,    1,  184,    2, 0x06 /* Public */,
       7,    1,  187,    2, 0x06 /* Public */,
       8,    1,  190,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  193,    2, 0x0a /* Public */,
      11,    1,  196,    2, 0x0a /* Public */,
      12,    1,  199,    2, 0x0a /* Public */,
      14,    1,  202,    2, 0x0a /* Public */,
      16,    1,  205,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      18,    2,  208,    2, 0x02 /* Public */,
      21,    3,  213,    2, 0x02 /* Public */,
      24,    2,  220,    2, 0x02 /* Public */,
      26,    1,  225,    2, 0x02 /* Public */,
      27,    3,  228,    2, 0x02 /* Public */,
      28,    2,  235,    2, 0x02 /* Public */,
      29,    1,  240,    2, 0x02 /* Public */,
      30,    1,  243,    2, 0x02 /* Public */,
      32,    0,  246,    2, 0x02 /* Public */,
      33,    0,  247,    2, 0x02 /* Public */,
      34,    1,  248,    2, 0x02 /* Public */,
      35,    1,  251,    2, 0x02 /* Public */,
      36,    2,  254,    2, 0x02 /* Public */,
      36,    1,  259,    2, 0x22 /* Public | MethodCloned */,
      38,    1,  262,    2, 0x02 /* Public */,
      40,    2,  265,    2, 0x02 /* Public */,
      40,    1,  270,    2, 0x22 /* Public | MethodCloned */,
      42,    1,  273,    2, 0x02 /* Public */,
      43,    1,  276,    2, 0x02 /* Public */,
      43,    1,  279,    2, 0x02 /* Public */,
      46,    2,  282,    2, 0x02 /* Public */,
      49,    1,  287,    2, 0x02 /* Public */,
      50,    1,  290,    2, 0x02 /* Public */,
      51,    1,  293,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   17,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::ULong,   19,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::ULong,   22,   23,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,   25,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::ULong,   22,   23,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,   25,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   31,
    QMetaType::QString, QMetaType::QString,   31,
    QMetaType::Int, QMetaType::QString, QMetaType::Int,   31,   37,
    QMetaType::Int, QMetaType::QString,   31,
    QMetaType::Int, QMetaType::QString,   39,
    QMetaType::QStringList, QMetaType::QString, QMetaType::QString,   17,   41,
    QMetaType::QStringList, QMetaType::QString,   17,
    QMetaType::Int, QMetaType::QString,   17,
    QMetaType::QString, QMetaType::Int,   44,
    QMetaType::QString, QMetaType::Double,   45,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   47,   48,
    QMetaType::Int, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void at_script_canvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<at_script_canvas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_new_sost((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->set_sost_from_at((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->set_new_bind_sost((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->change_control_panel_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->set_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->set_control_panel_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->set_mouse_press_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->set_sost_to_at((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->set_delay_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->sleep_signal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2]))); break;
        case 10: _t->start_blink_board((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< ulong(*)>(_a[3]))); break;
        case 11: _t->stop_blink_board((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 12: { int _r = _t->is_blink_board((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->start_blink_signal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< ulong(*)>(_a[3]))); break;
        case 14: _t->stop_blink_signal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: { int _r = _t->is_blink_signal((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->s_button((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: { QString _r = _t->get_button();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 18: { int _r = _t->sz_button();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 19: { int _r = _t->s((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 20: { QString _r = _t->st((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 21: { int _r = _t->m_time((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: { int _r = _t->m_time((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 23: { int _r = _t->ss((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 24: { QStringList _r = _t->spl((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 25: { QStringList _r = _t->spl((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 26: { int _r = _t->to_int((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 27: { QString _r = _t->to_str((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 28: { QString _r = _t->to_str((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 29: { int _r = _t->indexOf((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 30: { int _r = _t->dlg_m_press((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 31: _t->msg_script((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: _t->msg_to_log((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (at_script_canvas::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&at_script_canvas::set_new_sost)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (at_script_canvas::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&at_script_canvas::set_sost_from_at)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (at_script_canvas::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&at_script_canvas::set_new_bind_sost)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (at_script_canvas::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&at_script_canvas::change_control_panel_sost)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject at_script_canvas::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_at_script_canvas.data,
    qt_meta_data_at_script_canvas,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *at_script_canvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *at_script_canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_at_script_canvas.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int at_script_canvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void at_script_canvas::set_new_sost(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void at_script_canvas::set_sost_from_at(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void at_script_canvas::set_new_bind_sost(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void at_script_canvas::change_control_panel_sost(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
