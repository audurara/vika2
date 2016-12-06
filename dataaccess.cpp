#include "dataaccess.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <QtSql>

DataAccess::DataAccess()
{

}

bool operator == (const Performer& p1, const Performer& p2) //Yfirskrifa samasemvirkjann
{
    return p1.getName() == p2.getName();
}

vector<Performer> DataAccess::readData() //Les upplýsingar úr skrá og setur í vektor
{
    vector<Performer> logs;


    QSqlQuery query;
    query.exec("SELECT * FROM \"main\".\"list\"");
    while (query.next())
    {
        QString name = query.value(0).toString();
        QString gender = query.value(1).toString();
        QString bYear = query.value(2).toString();
        QString dYear = query.value(3).toString();
        QString nation = query.value(4).toString();

        Performer P(name, gender, bYear, dYear, nation);
        logs.push_back(P);

    }

/*
    ifstream myfile ("Info.txt");
    if ( myfile.is_open() )
    {
        while ( ! myfile.eof() )
        {
            //Á meðan skráin er ekki komin út á enda mun fara inn í vektorinn
            //og lesa inn nafn, kyn, fæðingarár, dánarár og þjóðerni í þessari röð
            getline(myfile, name, ',');
            getline(myfile, gender, ',');
            getline(myfile, bYear, ',');
            getline(myfile, dYear, ',');
            getline(myfile, nation, ',');

            Performer P(name, gender, bYear, dYear, nation);
            //Hvert stak í vektornum er strengur með nafni, kyni, fæðingarári, dánarári og þjóðerni

            logs.push_back(P);
        }
        myfile.close();
    }
*/

    return logs;
}


void DataAccess::writeData () //Með þessu falli má skrifa streng inn í skrána
{
/*
    db.setDatabaseName("database1.sqlite");
    if(!db.isOpen())
    {
        //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("database1.sqlite");
        qDebug() << "hello" << endl;
    }*/


        string name, gender, bYear, dYear, nation;
        cin.ignore();
        getline(cin, name);
        getline(cin, gender);
        getline(cin, bYear);
        getline(cin, dYear);
        getline(cin, nation);

        QString Qname = QString::fromStdString(name);
        QString Qgender = QString::fromStdString(gender);
        QString QbYear = QString::fromStdString(bYear);
        QString QdYear = QString::fromStdString(dYear);
        QString Qnation = QString::fromStdString(nation);

        QSqlQuery query;
        query.prepare("INSERT INTO \"main\".\"list\" (name, gender, bYear, dYear, nation) "
                          "VALUES (:name, :gender, :bYear, :dYear, :nation)");
            query.bindValue(":name", Qname);
            query.bindValue(":gender", Qgender);
            query.bindValue(":bYear", QbYear);
            query.bindValue(":dYear", QdYear);
            query.bindValue(":nation", Qnation);
            query.exec();


    //db.close();
}
/*
void DataAccess::removeData(string name) //Þetta fall tekur út tölvunarfræðing sem inniheldur ákveðið nafn
{
    vector<Performer> pf = readData();

    for(size_t i = 0; i < pf.size(); i++) //Nöfn í strengjum borin saman við nafnið sem við viljum eyða
    {
        if(pf[i].getName() == name) //Ef nafn í vektornum er eins og innslegna nafnið er því eytt úr vektornum
        {
            pf.erase(std::remove(pf.begin(), pf.end(), pf[i]), pf.end());
        }

    }

    ofstream outputFile;
    outputFile.open("Info.txt");
    for(size_t i = 0; i < pf.size(); i++) //Strengurinn skrifaður upp aftur án nafnsins sem var eytt
    {

        if(pf[i] == pf[0])
        {
            string all = pf[i].getName() + "," + pf[i].getGender() + "," + pf[i].getbYear() + "," + pf[i].getdYear() + "," + pf[i].getNation();
            outputFile << all;
        }
        else //Ef strengurinn sem var eytt var inni í miðju fallinu þarf að bæta við kommmu.

        {
            string all = "," + pf[i].getName() + "," + pf[i].getGender() + "," + pf[i].getbYear() + "," + pf[i].getdYear() + "," + pf[i].getNation();

            outputFile << all;
        }



    }
    outputFile.close();
}
*/
void DataAccess::openSqlFiles()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database1.sqlite");
    if(db.open())
    {
        qDebug();
    }
}
