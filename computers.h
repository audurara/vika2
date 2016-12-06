#ifndef COMPUTERS_H
#define COMPUTERS_H
#include <QtSql>



class computers
{
public:
    computers();
    computers(QString name, QString type, QString bYear, QString constr);
    //nafn, kyn, fæðingarár, dánarár og þjóðerni.

    QString getName() const
    {
        return _name;
    }

    QString getType() const
    {
        return _type;
    }

    QString getbYear() const
    {
        return _bYear;
    }

    QString getConstr() const
    {
        return _constr;
    }
private:
    QString _name;
    QString _type;
    QString _bYear;
    QString _constr;

};

#endif // COMPUTERS_H
