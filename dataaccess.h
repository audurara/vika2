#ifndef DATAACCESS_H
#define DATAACCESS_H
#include <vector>
#include "performer.h"
#include "computers.h"

using namespace std;

class DataAccess
{

public:

    void writeData();//Með þessu falli má skrifa streng inn í skrána

    void openSqlFiles();//opnar sql files.

    void addCpu();
    void removeDataScientist(string name);//Þetta fall tekur út strenginn sem inniheldur ákveðið nafn
    void removeDataComputer(string name);

    DataAccess();
    vector<computers> readCpuData();
    vector<Performer> readData();//Les upplýsingar úr skrá og setur í vektor
    friend bool operator ==(const Performer& p1, const Performer& p2);
};

#endif // DATAACCESS_H
