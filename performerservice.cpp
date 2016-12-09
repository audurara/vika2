#include "performerservice.h"
#include "dataaccess.h"
#include <algorithm>
#include <iostream>

using namespace std;
PerformerService::PerformerService() //Tómur smiður
{

}

vector <Performer> PerformerService:: searchpeople(QString name) //Leitar að ákveðnu nafni í listanum
{
    vector<Performer> newVector = _data.searchScientist(name);
    return newVector;
}

vector<computers> PerformerService::searchcomputer(QString name) //Leitar að ákveðinni tölvu í listanum
{
    vector<computers> newVector = _data.searchComputer(name);
    return newVector;
}

void PerformerService::addPerformer(string name, string gender, string birth, string death, string nation) //Bætir nýjum tölvunarfræðingi inn í skrána
{
   _data.writeData(name, gender, birth, death, nation);
}

void PerformerService::addComputer(string name, string buildy, string brand, string constr) //Bætir nýjum tölvunarfræðingi inn í skrána
{
   _data.addCpu(name, buildy, brand, constr);
}

string PerformerService::removeScientist(string name) //Skilar til baka streng eftir að hafa eytt einu tilviki
{
    _data.removeDataScientist(name);
    return name;
}

string PerformerService::removeComputer(string name) //Skilar til baka streng eftir að hafa eytt einu tilviki
{
    _data.removeDataComputer(name);
    return name;
}

void PerformerService::openFiles()
{
    _data.openSqlFiles();
}

vector<Relations> PerformerService::startJoin(string CS,int id)
{
    vector<Relations> join = _data.joinScientists(CS, id);
    return join;
}

vector<RelationsTable2> PerformerService::viewScientist(int counter)
{
    vector<RelationsTable2> pf;
    if(counter == 1)
    {
        vector<RelationsTable2> pf = _data.viewScientist();
        return pf;
    }
    else if(counter == 2)
    {
        vector<RelationsTable2> pf = _data.viewComputer();
        return pf;
    }
    return pf;
}

void PerformerService::addRelations(int sId, int cId)
{
    _data.addRelations(sId, cId);
}

vector<computers> PerformerService::sortComputers(string i1, string i2)
{
    vector<computers> pf = _data.sortCpu(i1, i2);
    return pf;
}

vector<Performer> PerformerService::sortScientists(string i1, string i2)
{
    vector<Performer> pf = _data.sortScientists(i1, i2);
    return pf;
}
vector<RelationsID> PerformerService::viewJoin()
{
    vector<RelationsID> pf = _data.viewJoin();
    return pf;
}

vector<RelationsTable> PerformerService::readData()
{
    vector<RelationsTable> pf = _data.readData();
    return pf;
}

void PerformerService::removeJoin(int id)
{
    _data.removeJoin(id);
}
