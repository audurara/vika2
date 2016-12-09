#ifndef RELATIONSID_H
#define RELATIONSID_H
#include <QtSql>


class RelationsID
{
public:
    RelationsID();
    RelationsID( int id, QString sName, QString cName);
    QString get_SName()
    {
        return _sName;
    }
    QString get_cName()
    {
        return _cName;
    }
    int get_id()
    {
        return _id;
    }

private:
    QString _sName;
    QString _cName;
    int _id;
};

#endif // RELATIONSID_H
