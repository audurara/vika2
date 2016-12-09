#include "computers.h"

computers::computers()
{

}
computers::computers(int id, QString name, QString buildy, QString brand, QString constr)
{
   _id = id;
   _name = name;
   _buildy = buildy;
   _brand = brand;
   _constr = constr;
}
