#include "manageDB.h"
#include <sys/types.h>
#include "training.h"
#include "exercise.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

uint32_t ManageDB::countCon = 0;


ManageDB::ManageDB()
{
    countCon++;

    string aux = "SFM";
    aux = aux + std::to_string(countCon);
    QString aux2 = QString::fromStdString(aux);
    database = QSqlDatabase::addDatabase("QSQLITE", aux2);
    database.setDatabaseName(MY_DATABASE_PATH_U);

    query = new QSqlQuery(database);
}

ManageDB::ManageDB(const string& name)
{

}


ManageDB::~ManageDB()
{
    delete(query);
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


/**
 * @brief ManageDB::populateUserList is responsible to "download" and "populate" the user vector
 * list from user database table
 */
void ManageDB::populateUserList()
{
    int index = 0;
    User aux;
    QString user_aux;
    QString pass_aux;

    query->exec("SELECT * from user");

    while(query->next()) //advance the pointer
    {
        aux.setId(query->value(0).toInt());
        aux.setName(query->value(1).toString().toStdString());
        aux.setUsername(query->value(2).toString().toStdString());
        aux.setPassword(query->value(3).toString().toStdString());

        User::addUserToUserListFromDatabase(aux);
//      this->getTraingFromDatabse();
        index ++;
    }

    User::userIDcount = index;      //save the number of users

    database.close();

}

bool ManageDB::checkLogin(const string &username, const string &password, User &user)
{
    int index = 0;
    User aux;
    QString user_aux = QString::fromStdString(username);
    QString pass_aux = QString::fromStdString(password);
    User userClass_aux;

    //if(!database.isOpen())
        database.open();

    query->exec("SELECT * FROM user where username='"+user_aux  +"' and password='"+pass_aux +"'");

    query->next();
    if(query->value(2).toString() == user_aux && query->value(3).toString() == pass_aux)
    {
        userClass_aux.setId(query->value(0).toInt());
        userClass_aux.setName(query->value(1).toString().toStdString());
        userClass_aux.setUsername(query->value(2).toString().toStdString());
        userClass_aux.setPassword(query->value(3).toString().toStdString());
        user = userClass_aux;
        database.close();
        return true;
    }

    database.close();
    return false;

}

void ManageDB::getUserTrainingList(User &user)
{
    stringstream ss;
    vector<string> result;

    Exercise exer_aux;
    QString trainExerVec;

    if(!database.isOpen())
        database.open();

    query->prepare("SELECT * FROM user_training WHERE userId=?");
    query->bindValue(0, user.getId());
    query->exec();

    while(query->next())//advance the poiter
    {
        Training train_aux;
        train_aux.setName(query->value(0).toString().toStdString());  //training name  is in the 1st colum
        ss << query->value(2).toString().toStdString();          //get execise list

        while( ss.good() )
        {
            int32_t exerId;
            string substr;
            getline( ss, substr, ',' );
            exerId = stoi(substr);
            exer_aux = Exercise::getExerciseFromId(exerId);
            train_aux.exerciseList.push_back(exer_aux);
        }

        user.userTrainingList.push_back(train_aux);
    }

    database.close();
}


/**
 * @brief ManageDB::populateExerciseList is responsible to "download" and "populate" the exercise vector
 * list from user database table
 */
void ManageDB::populateExerciseList()
{
    //----------- Just a dummy populate (for now (testing)) -----------
    Exercise aux;
    QString name_aux;


//    if(!database.isOpen())
        database.open();

    query->exec("SELECT * FROM exercise");

    while(query->next())//advance the poiter
    {
        aux.setIDfromDatabase(query->value(0).toInt());
        name_aux = query->value(1).toString();
        aux.setName(name_aux.toStdString());
        Exercise::addExerciseToMarketFromDatabase(aux);
    }

    database.close();
}

