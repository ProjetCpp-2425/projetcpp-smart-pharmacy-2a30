/****************************************************************************
** Meta object code from reading C++ file 'dialogmodifier.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../projetcpp - Copie/dialogmodifier.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogmodifier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialogmodifier_t {
    const uint offsetsAndSize[10];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Dialogmodifier_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Dialogmodifier_t qt_meta_stringdata_Dialogmodifier = {
    {
QT_MOC_LITERAL(0, 14), // "Dialogmodifier"
QT_MOC_LITERAL(15, 15), // "employeModified"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 30), // "on_pushButton_Modifier_clicked"
QT_MOC_LITERAL(63, 29) // "on_pushButton_Annuler_clicked"

    },
    "Dialogmodifier\0employeModified\0\0"
    "on_pushButton_Modifier_clicked\0"
    "on_pushButton_Annuler_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialogmodifier[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   33,    2, 0x08,    2 /* Private */,
       4,    0,   34,    2, 0x08,    3 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialogmodifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dialogmodifier *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->employeModified(); break;
        case 1: _t->on_pushButton_Modifier_clicked(); break;
        case 2: _t->on_pushButton_Annuler_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialogmodifier::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialogmodifier::employeModified)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject Dialogmodifier::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Dialogmodifier.offsetsAndSize,
    qt_meta_data_Dialogmodifier,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Dialogmodifier_t
, QtPrivate::TypeAndForceComplete<Dialogmodifier, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Dialogmodifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialogmodifier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialogmodifier.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialogmodifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Dialogmodifier::employeModified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
