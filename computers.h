#ifndef COMPUTERS_H
#define COMPUTERS_H
#include <QtSql>



class computers
{
public:
    computers();
    computers(int id, QString name, QString buildy, QString brand, QString constr);
    //nafn, kyn, fæðingarár, dánarár og þjóðerni.

    int getId() const
    {
        return _id;
    }

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
    int _id;
    QString _name;
    QString _buildy;
    QString _brand;
    QString _constr;
};

#endif // COMPUTERS_H
