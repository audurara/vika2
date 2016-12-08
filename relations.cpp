#include "relations.h"

Relations::Relations()
{

}

Relations::Relations(QString sName, QString cName)
{
    _sName = sName;
    _cName = cName;
}

RelationsTable::RelationsTable(int sId, QString sName, int cId, QString cName)
{
    _sName = sName;
    _sId = sId;
    _cId = cId;
    _cName = cName;
}
