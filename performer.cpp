#include "performer.h"

Performer::Performer()
{

}


 Performer::Performer(int id, QString name, QString gender, QString bYear, QString dYear, QString nation)
{
    _id = id;
    _name = name;
    _gender = gender;
    _bYear = bYear;
    _dYear = dYear;
    _nation = nation;

}
