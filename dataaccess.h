#ifndef DATAACCESS_H
#define DATAACCESS_H
#include <vector>
#include "performer.h"
#include "computers.h"
#include "relations.h"
#include "relationsid.h"

using namespace std;

class DataAccess
{

public:
    void writeData(string name, string gender, string bYear, string dYear, string nation);//Með þessu falli má skrifa streng inn í skrána
    void openSqlFiles();//opnar sql files.
    void addCpu(string name, string buildy, string brand, string constr);
    void removeDataScientist(string name);//Þetta fall tekur út strenginn sem inniheldur ákveðið nafn
    void removeDataComputer(string name);
    void addRelations(int sId, int cId);
    void removeJoin(int id);
    vector<RelationsID> viewJoin();
    vector<Relations> joinScientists(string CS, int id);
    DataAccess();
    vector<Performer> searchScientist(QString name);
    vector<computers> searchComputer(QString name);
    vector<computers> sortCpu(string input, string input2);
    vector<Performer> sortScientists(string input, string input2);
    vector<RelationsTable> readCpuData();
    vector<RelationsTable> readData();//Les upplýsingar úr skrá og setur í vektor
    vector<RelationsTable2> viewScientist();
    vector<RelationsTable2> viewComputer();
    friend bool operator ==(const Performer& p1, const Performer& p2);
};

#endif // DATAACCESS_H
