/****************************************************************************
** Meta object code from reading C++ file 'play_breadboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../play_breadboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'play_breadboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_moving_train_t {
    QByteArrayData data[10];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_moving_train_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_moving_train_t qt_meta_stringdata_moving_train = {
    {
QT_MOC_LITERAL(0, 0, 12), // "moving_train"
QT_MOC_LITERAL(1, 13, 12), // "train_signal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "train_on_track"
QT_MOC_LITERAL(4, 42, 8), // "power_on"
QT_MOC_LITERAL(5, 51, 4), // "rail"
QT_MOC_LITERAL(6, 56, 9), // "next_rail"
QT_MOC_LITERAL(7, 66, 9), // "power_off"
QT_MOC_LITERAL(8, 76, 18), // "sleep_train_signal"
QT_MOC_LITERAL(9, 95, 1) // "s"

    },
    "moving_train\0train_signal\0\0train_on_track\0"
    "power_on\0rail\0next_rail\0power_off\0"
    "sleep_train_signal\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_moving_train[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   45,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void moving_train::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<moving_train *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->train_signal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->train_on_track((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->power_on((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->power_off((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->sleep_train_signal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (moving_train::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&moving_train::train_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (moving_train::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&moving_train::train_on_track)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject moving_train::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_moving_train.data,
    qt_meta_data_moving_train,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *moving_train::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *moving_train::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_moving_train.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int moving_train::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void moving_train::train_signal(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void moving_train::train_on_track(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_play_breadboard_t {
    QByteArrayData data[47];
    char stringdata0[459];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_play_breadboard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_play_breadboard_t qt_meta_stringdata_play_breadboard = {
    {
QT_MOC_LITERAL(0, 0, 15), // "play_breadboard"
QT_MOC_LITERAL(1, 16, 12), // "init_poligon"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "set_new_sost"
QT_MOC_LITERAL(4, 43, 4), // "name"
QT_MOC_LITERAL(5, 48, 8), // "power_on"
QT_MOC_LITERAL(6, 57, 9), // "this_rail"
QT_MOC_LITERAL(7, 67, 9), // "next_rail"
QT_MOC_LITERAL(8, 77, 9), // "power_off"
QT_MOC_LITERAL(9, 87, 4), // "rail"
QT_MOC_LITERAL(10, 92, 8), // "sw_start"
QT_MOC_LITERAL(11, 101, 7), // "sw_stop"
QT_MOC_LITERAL(12, 109, 17), // "set_sost_to_board"
QT_MOC_LITERAL(13, 127, 3), // "msg"
QT_MOC_LITERAL(14, 131, 12), // "sw_stop_time"
QT_MOC_LITERAL(15, 144, 6), // "s_time"
QT_MOC_LITERAL(16, 151, 9), // "init_game"
QT_MOC_LITERAL(17, 161, 25), // "change_control_panel_sost"
QT_MOC_LITERAL(18, 187, 13), // "button_signal"
QT_MOC_LITERAL(19, 201, 14), // "train_on_track"
QT_MOC_LITERAL(20, 216, 10), // "name_track"
QT_MOC_LITERAL(21, 227, 19), // "on_pb_again_pressed"
QT_MOC_LITERAL(22, 247, 19), // "on_pb_other_pressed"
QT_MOC_LITERAL(23, 267, 18), // "on_pb_exit_pressed"
QT_MOC_LITERAL(24, 286, 12), // "create_train"
QT_MOC_LITERAL(25, 299, 3), // "num"
QT_MOC_LITERAL(26, 303, 6), // "t_rail"
QT_MOC_LITERAL(27, 310, 6), // "m_time"
QT_MOC_LITERAL(28, 317, 8), // "obj_name"
QT_MOC_LITERAL(29, 326, 3), // "pct"
QT_MOC_LITERAL(30, 330, 10), // "first_help"
QT_MOC_LITERAL(31, 341, 11), // "w_game_ower"
QT_MOC_LITERAL(32, 353, 3), // "set"
QT_MOC_LITERAL(33, 357, 7), // "command"
QT_MOC_LITERAL(34, 365, 3), // "run"
QT_MOC_LITERAL(35, 369, 11), // "script_name"
QT_MOC_LITERAL(36, 381, 10), // "head_train"
QT_MOC_LITERAL(37, 392, 9), // "train_num"
QT_MOC_LITERAL(38, 402, 10), // "tail_train"
QT_MOC_LITERAL(39, 413, 3), // "spl"
QT_MOC_LITERAL(40, 417, 6), // "signal"
QT_MOC_LITERAL(41, 424, 2), // "dt"
QT_MOC_LITERAL(42, 427, 7), // "indexOf"
QT_MOC_LITERAL(43, 435, 3), // "str"
QT_MOC_LITERAL(44, 439, 6), // "substr"
QT_MOC_LITERAL(45, 446, 1), // "s"
QT_MOC_LITERAL(46, 448, 10) // "msg_to_log"

    },
    "play_breadboard\0init_poligon\0\0"
    "set_new_sost\0name\0power_on\0this_rail\0"
    "next_rail\0power_off\0rail\0sw_start\0"
    "sw_stop\0set_sost_to_board\0msg\0"
    "sw_stop_time\0s_time\0init_game\0"
    "change_control_panel_sost\0button_signal\0"
    "train_on_track\0name_track\0on_pb_again_pressed\0"
    "on_pb_other_pressed\0on_pb_exit_pressed\0"
    "create_train\0num\0t_rail\0m_time\0obj_name\0"
    "pct\0first_help\0w_game_ower\0set\0command\0"
    "run\0script_name\0head_train\0train_num\0"
    "tail_train\0spl\0signal\0dt\0indexOf\0str\0"
    "substr\0s\0msg_to_log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_play_breadboard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  154,    2, 0x06 /* Public */,
       3,    1,  155,    2, 0x06 /* Public */,
       5,    2,  158,    2, 0x06 /* Public */,
       8,    1,  163,    2, 0x06 /* Public */,
      10,    0,  166,    2, 0x06 /* Public */,
      11,    0,  167,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  168,    2, 0x0a /* Public */,
      14,    1,  171,    2, 0x0a /* Public */,
      16,    0,  174,    2, 0x0a /* Public */,
      17,    1,  175,    2, 0x0a /* Public */,
      19,    1,  178,    2, 0x0a /* Public */,
      21,    0,  181,    2, 0x0a /* Public */,
      22,    0,  182,    2, 0x0a /* Public */,
      23,    0,  183,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      24,    2,  184,    2, 0x02 /* Public */,
      27,    2,  189,    2, 0x02 /* Public */,
      27,    1,  194,    2, 0x22 /* Public | MethodCloned */,
      30,    0,  197,    2, 0x02 /* Public */,
      31,    0,  198,    2, 0x02 /* Public */,
      32,    1,  199,    2, 0x02 /* Public */,
      34,    1,  202,    2, 0x02 /* Public */,
      36,    1,  205,    2, 0x02 /* Public */,
      38,    1,  208,    2, 0x02 /* Public */,
      39,    2,  211,    2, 0x02 /* Public */,
      39,    1,  216,    2, 0x22 /* Public | MethodCloned */,
      42,    2,  219,    2, 0x02 /* Public */,
      45,    1,  224,    2, 0x02 /* Public */,
      46,    1,  227,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   25,   26,
    QMetaType::Int, QMetaType::QString, QMetaType::Int,   28,   29,
    QMetaType::Int, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::QString, QMetaType::QString,   37,
    QMetaType::QString, QMetaType::QString,   37,
    QMetaType::QStringList, QMetaType::QString, QMetaType::QString,   40,   41,
    QMetaType::QStringList, QMetaType::QString,   40,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   43,   44,
    QMetaType::Int, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void play_breadboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<play_breadboard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->init_poligon(); break;
        case 1: _t->set_new_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->power_on((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->power_off((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->sw_start(); break;
        case 5: _t->sw_stop(); break;
        case 6: _t->set_sost_to_board((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->sw_stop_time((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->init_game(); break;
        case 9: _t->change_control_panel_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->train_on_track((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->on_pb_again_pressed(); break;
        case 12: _t->on_pb_other_pressed(); break;
        case 13: _t->on_pb_exit_pressed(); break;
        case 14: _t->create_train((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: { int _r = _t->m_time((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: { int _r = _t->m_time((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->first_help(); break;
        case 18: _t->w_game_ower(); break;
        case 19: _t->set((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->run((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: { QString _r = _t->head_train((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 22: { QString _r = _t->tail_train((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 23: { QStringList _r = _t->spl((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 24: { QStringList _r = _t->spl((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 25: { int _r = _t->indexOf((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: { int _r = _t->s((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->msg_to_log((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (play_breadboard::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&play_breadboard::init_poligon)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (play_breadboard::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&play_breadboard::set_new_sost)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (play_breadboard::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&play_breadboard::power_on)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (play_breadboard::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&play_breadboard::power_off)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (play_breadboard::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&play_breadboard::sw_start)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (play_breadboard::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&play_breadboard::sw_stop)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject play_breadboard::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_play_breadboard.data,
    qt_meta_data_play_breadboard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *play_breadboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *play_breadboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_play_breadboard.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int play_breadboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void play_breadboard::init_poligon()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void play_breadboard::set_new_sost(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void play_breadboard::power_on(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void play_breadboard::power_off(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void play_breadboard::sw_start()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void play_breadboard::sw_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
