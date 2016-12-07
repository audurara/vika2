#ifndef RELATIONS_H
#define RELATIONS_H
#include <QtSql>


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

#endif // RELATIONS_H
