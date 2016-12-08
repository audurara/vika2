#ifndef DATAACCESS_H
#define DATAACCESS_H
#include <vector>
#include "performer.h"
#include "computers.h"
#include "relations.h"

using namespace std;

class DataAccess
{

public:

    void writeData();//Með þessu falli má skrifa streng inn í skrána

    void openSqlFiles();//opnar sql files.

    void addCpu();
    void removeDataScientist(string name);//Þetta fall tekur út strenginn sem inniheldur ákveðið nafn
    void removeDataComputer(string name);
    vector<Relations> joinScientists(string CS, int id);

    DataAccess();
    vector<Performer> searchScientist(QString name);
    vector<computers> searchComputer(QString name);
    vector<computers> sortCpu(string input, string input2);
    vector<Performer> sortScientists(string input, string input2);
    vector<computers> readCpuData();
    vector<Performer> readData();//Les upplýsingar úr skrá og setur í vektor
    friend bool operator ==(const Performer& p1, const Performer& p2);
};

#endif // DATAACCESS_H
