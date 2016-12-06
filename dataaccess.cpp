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
vector<computers> DataAccess::readCpuData()
{
    vector<computers> pc;


    QSqlQuery query;
    query.exec("SELECT * FROM \"main\".\"Computers\"");
    while (query.next())
    {
        QString name = query.value(0).toString();
        QString buildy = query.value(1).toString();
        QString brand = query.value(2).toString();
        QString constr = query.value(3).toString();

        computers P(name, buildy, brand, constr);
        pc.push_back(P);


    }

    return pc;
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

    return logs;
}


void DataAccess::writeData () //Með þessu falli má skrifa streng inn í skrána
{

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
void DataAccess::addCpu () //Með þessu falli má skrifa streng inn í skrána
{

    string name, buildy, brand, constr;
    cin.ignore();
    getline(cin, name);
    getline(cin, buildy);
    getline(cin, brand);
    getline(cin, constr);

    QString Qname = QString::fromStdString(name);
    QString Qbuildy = QString::fromStdString(buildy);
    QString Qbrand = QString::fromStdString(brand);
    QString Qconstr = QString::fromStdString(constr);

    QSqlQuery query;
    query.prepare("INSERT INTO \"main\".\"Computers\" (name, buildy, brand, constr) "
                      "VALUES (:name, :buildy, :brand, :constr)");
        query.bindValue(":name", Qname);
        query.bindValue(":buildy", Qbuildy);
        query.bindValue(":brand", Qbrand);
        query.bindValue(":constr", Qconstr);

        query.exec();

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


