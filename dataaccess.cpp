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
    query.exec("SELECT * FROM \"Computers\"");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString buildy = query.value(2).toString();
        QString brand = query.value(3).toString();
        QString constr = query.value(4).toString();

        computers P(id, name, buildy, brand, constr);
        pc.push_back(P);


    }

    return pc;
}
vector<Performer> DataAccess::readData() //Les upplýsingar úr skrá og setur í vektor
{
    vector<Performer> logs;


    QSqlQuery query;
    query.exec("SELECT * FROM \"Scientists\"");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString gender = query.value(2).toString();
        QString bYear = query.value(3).toString();
        QString dYear = query.value(4).toString();
        QString nation = query.value(5).toString();

        Performer P(id, name, gender, bYear, dYear, nation);
        logs.push_back(P);

    }

    return logs;
}
void DataAccess::writeData () //Með þessu falli má skrifa streng inn í skrána
{

        string name, gender, bYear, dYear, nation;
        cout << "Name: ";
        getline(cin, name);
        cout << "Gender: ";
        getline(cin, gender);
        cout << "Birth year: ";
        getline(cin, bYear);
        cout << "Death year: ";
        getline(cin, dYear);
        cout << "Nationality: ";
        getline(cin, nation);

        QString Qname = QString::fromStdString(name);
        QString Qgender = QString::fromStdString(gender);
        QString QbYear = QString::fromStdString(bYear);
        QString QdYear = QString::fromStdString(dYear);
        QString Qnation = QString::fromStdString(nation);

        QSqlQuery query;
        query.prepare("INSERT INTO \"Scientists\" (name, gender, bYear, dYear, nation) "
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
    cout << "Name: ";
    getline(cin, name);
    cout << "Build year: ";
    getline(cin, buildy);
    cout << "Brand: ";
    getline(cin, brand);
    cout << "Constr: ";
    getline(cin, constr);

    QString Qname = QString::fromStdString(name);
    QString Qbuildy = QString::fromStdString(buildy);
    QString Qbrand = QString::fromStdString(brand);
    QString Qconstr = QString::fromStdString(constr);

    QSqlQuery query;
    query.prepare("INSERT INTO \"Computers\" (name, buildy, brand, constr) "
                      "VALUES (:name, :buildy, :brand, :constr)");
        query.bindValue(":name", Qname);
        query.bindValue(":buildy", Qbuildy);
        query.bindValue(":brand", Qbrand);
        query.bindValue(":constr", Qconstr);

        query.exec();

}
void DataAccess::removeDataScientist(string name) //Þetta fall tekur út tölvunarfræðing sem inniheldur ákveðið nafn
{
    string str =  "DELETE FROM \"Scientists\" where name = \"" + name;
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);

}
void DataAccess::removeDataComputer(string name)
{
    string str =  "DELETE FROM \"Computers\" where name = \"" + name + "\" ";
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);

}
void DataAccess::openSqlFiles()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.sqlite");
    if(db.open())
    {
        qDebug();
    }
}
void DataAccess::addRelations(int sId, int cId)
{
    QString QsId = QString::number(sId);
    QString QcId = QString::number(cId);

    QSqlQuery query;
    query.prepare("INSERT INTO \"Relations\" (SID, CID) VALUES (:SID, :CID)");
        query.bindValue(":SID", QsId);
        query.bindValue(":CID", QcId);

        query.exec();
}

vector<computers> DataAccess::sortCpu(string input, string input2)
{
    vector<computers> sort;
    string str = "SELECT * FROM \"Computers\" ORDER BY " + input + " " + input2;
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString buildy = query.value(2).toString();
        QString brand = query.value(3).toString();
        QString constr = query.value(4).toString();


        computers P(id, name, buildy, brand, constr);
        sort.push_back(P);


    }

    return sort;
}
vector<Relations> DataAccess::joinScientists(string CS, int id)
{
    vector<Relations> join;
    string s = std::to_string(id);
    string str =  "SELECT S.name, C.name From \"Scientists\" S Join relations R on R.Sid = S.id Join Computers C on R.cid = C.id WHERE " + CS + " = " + s;
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);
    while (query.next())
    {
        QString sName = query.value(0).toString();
        QString cName = query.value(1).toString();
        Relations P(sName, cName);
        join.push_back(P);
    }
    return join;
}
vector<Performer> DataAccess::searchScientist(QString name) //Les upplýsingar úr skrá og setur í vektor
{
    vector<Performer> newVector;

    QString qstr = "SELECT * FROM \"Scientists\" WHERE name LIKE \'%" + name + "%\'";
    QSqlQuery query;
    query.exec(qstr);
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString gender = query.value(2).toString();
        QString bYear = query.value(3).toString();
        QString dYear = query.value(4).toString();
        QString nation = query.value(5).toString();

        Performer P(id, name, gender, bYear, dYear, nation);
        newVector.push_back(P);

    }

    return newVector;
}
vector<computers> DataAccess::searchComputer(QString name)
{
    vector<computers> newVector;

    QString qstr = "SELECT * FROM \"Computers\" WHERE name LIKE \'%" + name + "%\'";
    QSqlQuery query;
    query.exec(qstr);
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString buildY = query.value(2).toString();
        QString type = query.value(3).toString();
        QString constr = query.value(4).toString();
        QString nation = query.value(5).toString();

        computers P(id, name, buildY, type, constr);
        newVector.push_back(P);

    }

    return newVector;
}
vector<Performer> DataAccess::sortScientists(string input, string input2)
{
    vector<Performer> sort;
    string str = "SELECT * FROM \"Scientists\" ORDER BY " + input + " " + input2;
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString gender = query.value(2).toString();
        QString bYear = query.value(3).toString();
        QString dYear = query.value(4).toString();
        QString nation = query.value(5).toString();


        Performer P(id, name, gender, bYear, dYear, nation);
        sort.push_back(P);


    }

    return sort;
}
void DataAccess::removeJoin(string CS, int id) //Þetta fall tekur út tölvunarfræðing sem inniheldur ákveðið nafn
{
    std::string s = std::to_string(id);
    string str =  "DELETE FROM \"Relations\" where " + CS + " = " + s;
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);

}
