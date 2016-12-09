#include "performerservice.h"
#include "dataaccess.h"
#include <algorithm>
#include <iostream>

using namespace std;

// PerformerService (miðlag Kerfisins) hjá okkur er notað
// til að tengja ConsoleUI (efsta lag kerfisins) við
// DataAccess (neðstalag kerfisins) og eru þá þau föll
// mjög einföld sem sagt, sum þeirra taka við streng, integer eða QStreng
// og senda það til dataAccess. önnur einungis framlengja skipun frá ConsoleUI
// og taka ekkert inn.
// flest skila vector en þau sem gera það ekki eru föll sem eyða eða bæta við.

PerformerService::PerformerService()
{

}

vector <Performer> PerformerService:: searchpeople(QString name) //Leitar að nafni í Scientist töflunni, getur verið bókstafur, fyrranafn , eftirnafn eða partur af nafni.
{
    vector<Performer> newVector = _data.searchScientist(name);
    return newVector;
}

vector<computers> PerformerService::searchcomputer(QString name) //Leitar að nafni í Computers töflunni, getur verið bókstafur eða partur af nafni.
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

void PerformerService::removeScientist(string name) //Tekur inn streng sem notandi slær inn og eyðir því tilviki úr database frá Scientists töflu.
{
    _data.removeDataScientist(name);
}

void PerformerService::removeComputer(string name) //Tekur inn streng sem notandi slær inn og eyðir því tilviki úr database frá Computers töflu.
{
    _data.removeDataComputer(name);
}

void PerformerService::openFiles() //kallar á fall úr dataaccess sem opnar database.sqlite og viðheldur þeirri tengingu, er notað einungis einu sinni þegar forrit er opnað.
{
    _data.openSqlFiles();
}

vector<Relations> PerformerService::startJoin(string CS,int id) //Tekur inn integer og streng sem koma frá ConsoleUI og kallar á fall sem býr til vektor sem er svo skilað til COnsoleUI
{
    vector<Relations> join = _data.joinScientists(CS, id);
    return join;
}

vector<RelationsTable2> PerformerService::viewScientist(int counter)//Þetta fall tekur inn eitt integer sem frá ConsoleUI sem segir til hvort að það er verið að sækja vektor fyrir Scientist eða Computer.
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

void PerformerService::addRelations(int sId, int cId)//Þetta fall tekur inn 2 integer og framlengir það til dataAccess til að bæta við tengingum í relations.
{
    _data.addRelations(sId, cId);
}

vector<computers> PerformerService::sortComputers(string i1, string i2)//þetta fall tekur inn 2 strengi og býr til vektor frá falli úr dataAccess fyrir Scientists.
{
    vector<computers> pf = _data.sortCpu(i1, i2);
    return pf;
}

vector<Performer> PerformerService::sortScientists(string i1, string i2)//þetta fall tekur inn 2 strengi og býr til vektor frá falli úr dataAccess fyrir Scientists.
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
