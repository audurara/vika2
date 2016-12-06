#ifndef COMPUTERS_H
#define COMPUTERS_H
#include <QtSql>



class computers
{
public:
    computers();
    computers(QString name, QString buildy, QString brand, QString constr);
    //nafn, kyn, fæðingarár, dánarár og þjóðerni.

    QString getName() const
    {
        return _name;
    }

    QString getBuildy() const
    {
        return _buildy;
    }

    QString getBrand() const
    {
        return _brand;
    }

    QString getConstr() const
    {
        return _constr;
    }
private:
    QString _name;
    QString _buildy;
    QString _brand;
    QString _constr;

};

#endif // COMPUTERS_H
