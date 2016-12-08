#include "relationsid.h"
#include <QtSql>

RelationsID::RelationsID(int id, QString sName, QString cName)
{
    _sName = sName;
    _cName = cName;
    _id = id;
}
