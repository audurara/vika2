#ifndef RELATIONS_H
#define RELATIONS_H
#include <QtSql>

//Allir klasarnir eru gerðir eins nema þeir eru allir gerðir
//til að skila mismunandi vektorum t.d. (2 QStrings) eða (2 integer og 2 QStrings).
//Mjög hentugt að búa þá til.

class Relations
{
public:
    Relations();
    Relations(QString sName, QString cName);
    QString getSName()
    {
        return _sName;
    }
    QString getCName()
    {
        return _cName;
    }
private:
    QString _sName;
    QString _cName;
};

class RelationsTable
{
public:
    RelationsTable();
    RelationsTable(int sId, QString sName,int cId, QString cName);

    QString getSName()
    {
        return _sName;
    }
    int getSId()
    {
        return _sId;
    }
    QString getCName()
    {
        return _cName;
    }
    int getCId()
    {
        return _cId;
    }

private:
    QString _sName;
    QString _cName;
    int _sId;
    int _cId;
};

class RelationsTable2
{
public:
    RelationsTable2();
    RelationsTable2(int sId, QString sName);

    QString getSName()
    {
        return _sName;
    }
    int getSId()
    {
        return _sId;
    }

private:
    QString _sName;
    int _sId;
};

#endif // RELATIONS_H
