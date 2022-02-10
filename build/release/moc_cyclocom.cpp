/****************************************************************************
** Meta object code from reading C++ file 'cyclocom.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../cyclocom.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cyclocom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_script_thread_t {
    QByteArrayData data[8];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_script_thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_script_thread_t qt_meta_stringdata_script_thread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "script_thread"
QT_MOC_LITERAL(1, 14, 15), // "script_readData"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "set_e_data"
QT_MOC_LITERAL(4, 42, 6), // "r_data"
QT_MOC_LITERAL(5, 49, 9), // "get_count"
QT_MOC_LITERAL(6, 59, 10), // "msg_to_log"
QT_MOC_LITERAL(7, 70, 3) // "msg"

    },
    "script_thread\0script_readData\0\0"
    "set_e_data\0r_data\0get_count\0msg_to_log\0"
    "msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_script_thread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   37,    2, 0x02 /* Public */,
       5,    0,   40,    2, 0x02 /* Public */,
       6,    1,   41,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::UInt,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void script_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<script_thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->script_readData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->set_e_data((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { uint _r = _t->get_count();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->msg_to_log((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (script_thread::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&script_thread::script_readData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject script_thread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_script_thread.data,
    qt_meta_data_script_thread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *script_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *script_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_script_thread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int script_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void script_thread::script_readData(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ESerialPort_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ESerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ESerialPort_t qt_meta_stringdata_ESerialPort = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ESerialPort"
QT_MOC_LITERAL(1, 12, 13), // "test_readData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 19), // "change_count_cycles"
QT_MOC_LITERAL(4, 47, 1), // "c"
QT_MOC_LITERAL(5, 49, 15), // "script_readData"
QT_MOC_LITERAL(6, 65, 4) // "data"

    },
    "ESerialPort\0test_readData\0\0"
    "change_count_cycles\0c\0script_readData\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ESerialPort[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    6,

       0        // eod
};

void ESerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ESerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->test_readData(); break;
        case 1: _t->change_count_cycles((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->script_readData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ESerialPort::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ESerialPort::test_readData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ESerialPort::*)(uint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ESerialPort::change_count_cycles)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ESerialPort::staticMetaObject = { {
    &QSerialPort::staticMetaObject,
    qt_meta_stringdata_ESerialPort.data,
    qt_meta_data_ESerialPort,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ESerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ESerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ESerialPort.stringdata0))
        return static_cast<void*>(this);
    return QSerialPort::qt_metacast(_clname);
}

int ESerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ESerialPort::test_readData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ESerialPort::change_count_cycles(uint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_cyclocom_t {
    QByteArrayData data[15];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cyclocom_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cyclocom_t qt_meta_stringdata_cyclocom = {
    {
QT_MOC_LITERAL(0, 0, 8), // "cyclocom"
QT_MOC_LITERAL(1, 9, 12), // "set_new_sost"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 16), // "write_cycle_code"
QT_MOC_LITERAL(4, 40, 15), // "read_cycle_code"
QT_MOC_LITERAL(5, 56, 13), // "ansver_module"
QT_MOC_LITERAL(6, 70, 16), // "time_limit_error"
QT_MOC_LITERAL(7, 87, 16), // "msg_to_statusbar"
QT_MOC_LITERAL(8, 104, 8), // "readData"
QT_MOC_LITERAL(9, 113, 8), // "set_sost"
QT_MOC_LITERAL(10, 122, 8), // "str_sost"
QT_MOC_LITERAL(11, 131, 17), // "reset_controllers"
QT_MOC_LITERAL(12, 149, 20), // "ansver_timer_control"
QT_MOC_LITERAL(13, 170, 13), // "get_port_name"
QT_MOC_LITERAL(14, 184, 19) // "next_control_object"

    },
    "cyclocom\0set_new_sost\0\0write_cycle_code\0"
    "read_cycle_code\0ansver_module\0"
    "time_limit_error\0msg_to_statusbar\0"
    "readData\0set_sost\0str_sost\0reset_controllers\0"
    "ansver_timer_control\0get_port_name\0"
    "next_control_object"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cyclocom[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    1,   77,    2, 0x06 /* Public */,
       4,    1,   80,    2, 0x06 /* Public */,
       5,    1,   83,    2, 0x06 /* Public */,
       6,    1,   86,    2, 0x06 /* Public */,
       7,    2,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   94,    2, 0x0a /* Public */,
       9,    1,   95,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,

       0        // eod
};

void cyclocom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cyclocom *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_new_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->write_cycle_code((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->read_cycle_code((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->ansver_module((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->time_limit_error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->msg_to_statusbar((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->readData(); break;
        case 7: _t->set_sost((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->reset_controllers(); break;
        case 9: _t->ansver_timer_control(); break;
        case 10: { QString _r = _t->get_port_name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->next_control_object(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cyclocom::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cyclocom::set_new_sost)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (cyclocom::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cyclocom::write_cycle_code)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (cyclocom::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cyclocom::read_cycle_code)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (cyclocom::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cyclocom::ansver_module)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (cyclocom::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cyclocom::time_limit_error)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (cyclocom::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cyclocom::msg_to_statusbar)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cyclocom::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_cyclocom.data,
    qt_meta_data_cyclocom,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *cyclocom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cyclocom::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cyclocom.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int cyclocom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void cyclocom::set_new_sost(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cyclocom::write_cycle_code(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cyclocom::read_cycle_code(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void cyclocom::ansver_module(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void cyclocom::time_limit_error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void cyclocom::msg_to_statusbar(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
