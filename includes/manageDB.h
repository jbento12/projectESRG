#ifndef MANAGE_DB_H__
#define MANAGE_DB_H__


#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <string>
#include <QString>
#include "user.h"
#include "exercise.h"
#include "macros.h"

#ifdef MY_ARCH_PC
#define MY_DATABASE_PATH_U "/home/luiscarlos/Documents/embebidos/sfm_sqlite.db"
#else
#define MY_DATABASE_PATH_U "/etc/sfm_database/sfm_sqlite.db"
#endif



using namespace std;

class ManageDB{


public:

     ManageDB();
     ManageDB(const std::string& name);
     ~ManageDB();

    bool open(const string& name);
    void close();
    bool isOpen();

    //----- To User table --------------
    void populateUserList();
    bool checkLogin(const string& username, const string& password, User& user);
    //----- To User_Trainig table --------------
    void getUserTrainingList(User& user);

    //----- To Exercise table --------------
    void populateExerciseList();




    QSqlDatabase database;
    QSqlQuery *query;
private:

    static uint32_t countCon;
};




#endif//MANAGE_DB_H__
