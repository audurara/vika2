#include "dataaccess.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <QtSql>


DataAccess::DataAccess()
{

}

vector<RelationsTable> DataAccess::readData() //þetta fall er notað til að skila vektor samkvæmt sql skipun
{
    vector<RelationsTable> logs;

    QSqlQuery query;
    query.exec("SELECT S.id, S.name,C.id, C.name From Scientists S LEFT OUTER JOIN Computers C on C.id = S.id ");
    while (query.next())
    {
        int sId = query.value(0).toInt();
        QString sName = query.value(1).toString();
        int cId = query.value(2).toInt();
        QString cName = query.value(3).toString();


        RelationsTable P(sId, sName, cId, cName);
        logs.push_back(P);
    }

    return logs;
}

void DataAccess::writeData (string name, string gender, string bYear, string dYear, string nation) //Með þessu falli má skrifa streng inn í skrána
{
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
}

void DataAccess::addCpu (string name, string buildy, string brand, string constr) //Með þessu falli má skrifa streng inn í skrána
{
    QString Qname = QString::fromStdString(name);
    QString Qbuildy = QString::fromStdString(buildy);
    QString Qbrand = QString::fromStdString(brand);
    QString Qconstr = QString::fromStdString(constr);

    QSqlQuery query;
    query.prepare("INSERT INTO \"Computers\" (name, buildy, type, constr) "
                      "VALUES (:name, :buildy, :type, :constr)");
        query.bindValue(":name", Qname);
        query.bindValue(":buildy", Qbuildy);
        query.bindValue(":type", Qbrand);
        query.bindValue(":constr", Qconstr);

        query.exec();
}

void DataAccess::removeDataScientist(string id) //Þetta fall tekur út tölvunarfræðing og röð hennar/hans samkvæmt ID.
{
    string str =  "DELETE FROM \"Scientists\" WHERE ID = " + id;
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);
}

void DataAccess::removeDataComputer(string id) // þetta fall er notað til að eyða tölvu og röð hennar samkvæmt ID tölvu.
{
    string str =  "DELETE FROM \"Computers\" where ID = \"" + id + "\" ";
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);

}
void DataAccess::openSqlFiles() // Þetta fall er notað til að opna database og er það fall bara kallað upp einu sinni og helst tengingin við það database út allt forritið.
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.sqlite");
    if(db.open())
    {
        qDebug();
    }
}
void DataAccess::addRelations(int sId, int cId) //Þetta fall er notað til þess að bæta við tengingum hjá tölvum við fræðinga og öfugt.
{
    QString QsId = QString::number(sId);
    QString QcId = QString::number(cId);

    QSqlQuery query;
    query.prepare("INSERT INTO \"Relations\" (SID, CID) VALUES (:SID, :CID)");
        query.bindValue(":SID", QsId);
        query.bindValue(":CID", QcId);

        query.exec();
}

vector<computers> DataAccess::sortCpu(string input, string input2) //þetta fall er notað til að sortera tölvur eftir  nafni, árgerð, tegund og byggingu.
{                                                                  //input = name, buildy, brand eða constr.
    vector<computers> sort;                                        //input2 = Ascending eða descending.
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

vector<Relations> DataAccess::joinScientists(string CS, int id) //þetta fall er notað til að sýna bæði hvaða tölva er tengd hvaða fræðingi og öfugt.
{                                                               //CS = scientist id eða Computer id.
    vector<Relations> join;                                     //id = hvaða id notandi velur
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

vector<computers> DataAccess::searchComputer(QString name) //þetta fall tekur inn QStreng til að breyta sql skipun
{                                                          //svo að fallið skili réttum vektor samkvæmt streng "name".
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

vector<Performer> DataAccess::sortScientists(string input, string input2)              //þetta fall tekur inn 2 strengi.
{                                                                                      //input = name, gender, bYear, dYear eða nation.
    vector<Performer> sort;                                                            //input2 = Ascending eða descending.
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

void DataAccess::removeJoin(int id) //Þetta fall tekur út tölvunarfræðing sem inniheldur ákveðið ID
{
    std::string s = std::to_string(id);
    string str =  "DELETE FROM \"Relations\" where ID  = " + s;
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);
}

vector<RelationsID> DataAccess::viewJoin() //þetta fall er notað með vektorinn <RelationsID>.
{                                          // fallið skilar út vektor samkvæmt sql skipun á Scientists.
    vector<RelationsID> sort;
    string str = "SELECT R.ID, S.name, C.name From \"Scientists\" S Join relations R on R.Sid = S.id Join Computers C on R.cid = C.id";
    QString qstr = QString::fromStdString(str);
    QSqlQuery query;
    query.exec(qstr);
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString sName = query.value(1).toString();
        QString cName = query.value(2).toString();

        RelationsID P(id, sName, cName);
        sort.push_back(P);
    }

    return sort;
}

vector<RelationsTable2> DataAccess::viewScientist()//þetta fall er notað til að sjá id og nafn frá table scientists
{
    vector<RelationsTable2> logs;

    QSqlQuery query;
    query.exec("SELECT id, name FROM \"Scientists\" ");
    while (query.next())
    {
        int sId = query.value(0).toInt();
        QString sName = query.value(1).toString();

        RelationsTable2 P(sId, sName);
        logs.push_back(P);
    }

    return logs;
}

vector<RelationsTable2> DataAccess::viewComputer()//þetta fall er notað til að sjá id og nafn frá table Computers
{
    vector<RelationsTable2> logs;

    QSqlQuery query;
    query.exec("SELECT id, name FROM \"Computers\" ");
    while (query.next())
    {
        int sId = query.value(0).toInt();
        QString sName = query.value(1).toString();

        RelationsTable2 P(sId, sName);
        logs.push_back(P);
    }

    return logs;
}
