#ifndef PERFORMER_H
#define PERFORMER_H
#include <string>
#include <QtSql>

using namespace std;

class Performer
{
public:
    Performer();
    Performer(int id, QString name, QString gender, QString bYear, QString dYear, QString nation);
    int getId() const
    {
        return _id;
    }
    QString getName() const
    {
        return _name;
    }
    QString getGender() const
    {
        return _gender;
    }
    QString getbYear() const
    {
        return _bYear;
    }

    QString getdYear() const
    {
        return _dYear;
    }
    QString getNation() const
    {
        return _nation;
    }
private:

    int _id;
    QString _name;
    QString _gender;
    QString _bYear;
    QString _dYear;
    QString _nation;
};

#endif // PERFORMER_H
