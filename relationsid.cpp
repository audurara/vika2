#include "relationsid.h"
#include <QtSql>

RelationsID::RelationsID(QString sName, QString cName, int id)
{
    _sName = sName;
    _cName = cName;
    _id = id;
}
