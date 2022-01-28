#ifndef MANAGE_DB_H__
#define MANAGE_DB_H__


#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <string>
#include <QString>
#include "user.h"
#include "exercise.h"

#define MY_DATABASE_PATH_U "/home/luiscarlos/Documents/embebidos/sfm_sqlite.db"
//#define MY_DATABASE_PATH_U "/etc/sfm_database/user_sqlite.db"


using namespace std;

class ManageDB{


public:

     ManageDB();
     ManageDB(const std::string& name);
     ~ManageDB();

    bool open(const string& name);
    void close();
    bool isOpen();

    void populateUserList();
    void populateExerciseList();




    QSqlDatabase database;

private:


};




#endif//MANAGE_DB_H__
