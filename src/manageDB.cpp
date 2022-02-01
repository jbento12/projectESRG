#include "manageDB.h"


ManageDB::ManageDB()
{

}

ManageDB::ManageDB(const string& name)
{

}


ManageDB::~ManageDB()
{

}


//bool ManageDB::open(const string& name)
//{
////    this->database = QSqlDatabase::addDatabase("QSQLITE");
////    this->database.setDatabaseName(QString::fromStdString(name));
//    return database.open();
//}

//bool ManageDB::isOpen()
//{
//    return database.isOpen();
//}

//void ManageDB::close()
//{
//    database.close();
//}



void ManageDB::populateUserList()
{
    int index = 0;
    User aux;
    QString user_aux;
    QString pass_aux;
    QSqlQuery query;

    query.exec("SELECT * from user");

    while(query.next()) //advance the pointer
    {
//        aux.userId   = query.value(0).toInt();     //id is 1th colum
//        aux.name     = query.value(1).toString().toStdString();
//        aux.username = query.value(2).toString().toStdString();     //username is 3th colum
//        aux.password = query.value(3).toString().toStdString();     //password is 4th colum

        aux.setId(query.value(0).toInt());
        aux.setName(query.value(1).toString().toStdString());
        aux.setUsername(query.value(2).toString().toStdString());
        aux.setPassword(query.value(3).toString().toStdString());

        User::addUserToUserListFromDatabase(aux);
//      this->getTraingFromDatabse();
        index ++;
    }

    User::userIDcount = index;      //save the number of users

    database.close();


//    aux.setName("Luca");
//    aux.setUsername("");
//    aux.password = "";
//    addUserToUserList(aux);

}


void ManageDB::populateExerciseList()
{
    //----------- Just a dummy populate (for now (testing)) -----------
    Exercise aux;
    QString name_aux;
    QSqlQuery query;

    if(!database.isOpen())
        database.open();

    query.exec("SELECT * FROM exercise");

    while(query.next())//advance the poiter
    {
        aux.setIDfromDatabase(query.value(0).toInt());
        name_aux = query.value(1).toString();
        aux.setName(name_aux.toStdString());
        Exercise::addExerciseToMarketFromDatabase(aux);
    }

    database.close();
}

