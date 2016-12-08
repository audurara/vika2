#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include "performerservice.h"

class ConsoleUI
{
public:
    ConsoleUI();
    void run();

private:

    void displayListOfPerformers(vector<Performer> pf); //Prentar lista af tölvunarfræðingum eins og þeir eru í skránni.
    void displaySearch(); // Prentar niðurstöður leitar
    void tableLook();
    void displaySort(vector<Performer> newVector);//Prentar út raðaða lista
    void chooseSort(); //Velur eftir hverju á að raða
    void commandHelp();// Prentar út lista af skipunum
    void commandAdd();//Bætir við tölvunarfræðing við listann
    void intro();//Prentar upphafsskilaboð
    void displayTopTable();//Prentar út lista af tölvunarfræðingum, sum önnur föll nota þetta fall.
    void displayComputers(vector<computers> pc);
    void displayTopComputers();
    void sortComputers(); // sortar tölvur.
    void sortScientists(); // sortar tölvufræðinga.
    void displayJoin();
    void addJoin();
    void removeJoin();
    void addComputer();
    void displayTable();
    string deleteElement();//Eyðir staki úr vektor
    string inputName();
    string inputGender();
    string inputBirth();
    string inputDeath();
    string inputNation();
    void displayChoice();
    int checkInput(int val1, int val2);


private: //Eftirfarandi breytur sækja upplýsingar og leyfa virkni sitthvort úr PerformerService og DataAccess.
    PerformerService _service;
    DataAccess _data;
};

#endif // CONSOLEUI_H
