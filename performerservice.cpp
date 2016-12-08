#include "performerservice.h"
#include "dataaccess.h"
#include <algorithm>
#include <iostream>

using namespace std;
PerformerService::PerformerService() //Tómur smiður
{

}

vector<Performer> PerformerService::getPerformers() //Nær í gögn úr skrá og skilar þeim í vector
{

   vector<Performer> getPerformers = _data.readData();

   return getPerformers;
}

vector <Performer> PerformerService:: searchpeople(QString name) //Leitar að ákveðnu nafni í listanum
{
    vector<Performer> newVector = _data.searchScientist(name);
    return newVector;
}

vector<computers> PerformerService::searchcomputer(QString name) //Leitar að ákveðnari tölvu í listanum
{
    vector<computers> newVector = _data.searchComputer(name);
    return newVector;
}

 string PerformerService::addPerformer(string name, string gender, string birth, string death, string nation) //Bætir nýjum tölvunarfræðingi inn í skrána
 {
    string all = "," + name + "," + gender + "," + birth + "," + death + "," + nation;
    _data.writeData();
    return all;
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

vector<computers> PerformerService::getComputers() //Nær í gögn úr skrá og skilar þeim í vector
{

   vector<computers> getComputers = _data.readCpuData();

   return getComputers;
}

vector<Relations> PerformerService::startJoin(string CS,int id)
{
    vector<Relations> join = _data.joinScientists(CS, id);

    return join;
}
