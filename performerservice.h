#ifndef PERFORMERSERVICE_H
#define PERFORMERSERVICE_H
#include "performer.h"
#include "dataaccess.h"

using namespace std;

class PerformerService
{
public:
    PerformerService();
    //
    void openFiles();//opnar sql files um leið og forritið er keyrt, einu sinni.
    vector<Performer> getPerformers(); //Nær í gögn úr skrá og skilar þeim í vector
    vector<Performer> search(QString name); //Leitar að ákveðnu nafni í listanum
    vector<Performer> sortByName(); //Ber saman nöfn og raðar þeim í stafrófsröð
    vector<Performer> sortBybYear(); //Ber saman ár og raðar þeim frá því lægsta til þess hæsta
    vector<Performer> sortByGender(); //Ber saman kyn
    vector<Performer> sortByNationality(); //Ber saman þjóðerni og raðar þeim eftir stafrófsröð
    vector<computers> getComputers(); //vektor fyrir computers.
    string removeScientist(string name); //Skilar til baka streng eftir að hafa eytt einu tilviki.
    string removeComputer(string name);
    string addPerformer(string name, string gender, string birth, string death, string nation); //Bætir nýjum tölvunarfræðingi inn í skrána
private:
    DataAccess _data;// Sækir upplýsingar og leyfir virkni úr DataAccess.
};

#endif // PERFORMERSERVICE_H
