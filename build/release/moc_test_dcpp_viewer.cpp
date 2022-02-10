/****************************************************************************
** Meta object code from reading C++ file 'test_dcpp_viewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../test_dcpp_viewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_dcpp_viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[7];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 11), // "resultReady"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 6), // "result"
QT_MOC_LITERAL(4, 27, 13), // "end_of_script"
QT_MOC_LITERAL(5, 41, 6), // "doWork"
QT_MOC_LITERAL(6, 48, 8) // "commands"

    },
    "Worker\0resultReady\0\0result\0end_of_script\0"
    "doWork\0commands"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

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
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,    6,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->end_of_script(); break;
        case 2: _t->doWork((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::resultReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::end_of_script)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Worker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Worker.data,
    qt_meta_data_Worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Worker::resultReady(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Worker::end_of_script()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_test_DCPP_viewer_t {
    QByteArrayData data[12];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_DCPP_viewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_DCPP_viewer_t qt_meta_stringdata_test_DCPP_viewer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "test_DCPP_viewer"
QT_MOC_LITERAL(1, 17, 12), // "set_new_sost"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 4), // "name"
QT_MOC_LITERAL(4, 36, 7), // "operate"
QT_MOC_LITERAL(5, 44, 10), // "run_script"
QT_MOC_LITERAL(6, 55, 9), // "file_name"
QT_MOC_LITERAL(7, 65, 3), // "add"
QT_MOC_LITERAL(8, 69, 7), // "command"
QT_MOC_LITERAL(9, 77, 13), // "end_of_script"
QT_MOC_LITERAL(10, 91, 17), // "set_sost_to_board"
QT_MOC_LITERAL(11, 109, 3) // "msg"

    },
    "test_DCPP_viewer\0set_new_sost\0\0name\0"
    "operate\0run_script\0file_name\0add\0"
    "command\0end_of_script\0set_sost_to_board\0"
    "msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test_DCPP_viewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QStringList,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void test_DCPP_viewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<test_DCPP_viewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_new_sost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->operate((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 2: _t->run_script((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->add((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->end_of_script(); break;
        case 5: _t->set_sost_to_board((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (test_DCPP_viewer::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&test_DCPP_viewer::set_new_sost)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (test_DCPP_viewer::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&test_DCPP_viewer::operate)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject test_DCPP_viewer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_test_DCPP_viewer.data,
    qt_meta_data_test_DCPP_viewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *test_DCPP_viewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_DCPP_viewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_test_DCPP_viewer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int test_DCPP_viewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void test_DCPP_viewer::set_new_sost(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void test_DCPP_viewer::operate(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
