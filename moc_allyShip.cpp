/****************************************************************************
** Meta object code from reading C++ file 'allyShip.hpp'
**
** Created: Wed Jan 18 11:07:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "allyShip.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'allyShip.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_sceneElements__AllyShip[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,
      44,   24,   24,   24, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_sceneElements__AllyShip[] = {
    "sceneElements::AllyShip\0\0energyChanged(int)\0"
    "destroyed()\0"
};

const QMetaObject sceneElements::AllyShip::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_sceneElements__AllyShip,
      qt_meta_data_sceneElements__AllyShip, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sceneElements::AllyShip::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sceneElements::AllyShip::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sceneElements::AllyShip::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sceneElements__AllyShip))
        return static_cast<void*>(const_cast< AllyShip*>(this));
    if (!strcmp(_clname, "Ship"))
        return static_cast< Ship*>(const_cast< AllyShip*>(this));
    return QObject::qt_metacast(_clname);
}

int sceneElements::AllyShip::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: energyChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: destroyed(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void sceneElements::AllyShip::energyChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sceneElements::AllyShip::destroyed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
