#include "exercise.h"
#include "poseClassification.h"

#include <string>
#include <QString>
#include <QDebug>
//global varibles

vector<Exercise> Exercise::marketExerciseList;
uint32_t Exercise::exerciseIDcount = 0;


Exercise::Exercise()
{
    id = -1;
    name = "Unknown";
}


Exercise::~Exercise()
{
}


void Exercise::setIDfromDatabase(int32_t idDatabase)
{
    this->id = idDatabase;
}

void Exercise::setName(const string& name)
{
    this->name = name;
}


void Exercise::setPath(const string& path)
{
    this->path = path;
}


string Exercise::getName()
{
    return this->name;
}


string Exercise::getPath()
{
    return this->path;
}










// ---------------- Used to populate ------------------------------



bool Exercise::addExerciseToMarket(Exercise& exercise)
{
    exercise.id = Exercise::exerciseIDcount;
    Exercise::exerciseIDcount++;
    Exercise::marketExerciseList.push_back(exercise);
    return true;
}

bool Exercise::addExerciseToMarketFromDatabase(Exercise& exercise)
{
    Exercise::exerciseIDcount++;
    Exercise::marketExerciseList.push_back(exercise);
    return true;
}

void Exercise::populateExerciseList()
{
    //----------- Just a dummy populate (for now (testing)) -----------
    Exercise aux;
    QString name_aux;
    QSqlDatabase exercise_db = QSqlDatabase::addDatabase("QSQLITE");

    exercise_db.setDatabaseName("/home/luiscarlos/Documents/embebidos/exercise_sqlite.db");


    if(!exercise_db.open())
    {
        cout << "Failed to open Database";
        return;
    }

    QSqlQuery exer_db_qry;
    exer_db_qry.exec("SELECT * FROM exercise");

    while(exer_db_qry.next())//advance the poiter
    {
        aux.setIDfromDatabase(exer_db_qry.value(0).toInt());
        name_aux = exer_db_qry.value(1).toString();
        aux.setName(name_aux.toStdString());
        addExerciseToMarketFromDatabase(aux);
    }

//    aux.setName("Bicep Curl");
//    aux.setPath("/boasCurl");
//    addExerciseToMarket(aux);

//    aux.setName("Lat PullDown");
//    aux.setPath("/boasPullDown");
//    addExerciseToMarket(aux);

//    aux.setName("Row");
//    aux.setPath("/boasRow");
//    addExerciseToMarket(aux);

//    aux.setName("Barbell");
//    aux.setPath("/boasBarbell");
//    addExerciseToMarket(aux);

//    aux.setName("Supino");
//    aux.setPath("/boasSupino");
//    addExerciseToMarket(aux);

//    aux.setName("Bench");
//    aux.setPath("/boasBench");
//    addExerciseToMarket(aux);
}

void Exercise::printMarketExerciseList()
{
    cout << "Comecar a imprimer os exercicios" << endl;
    for(uint32_t i = 0; i < Exercise::marketExerciseList.size(); i++)
    {
        cout << Exercise::marketExerciseList[i].id   << " ";
        cout << Exercise::marketExerciseList[i].name << " ";
        cout << Exercise::marketExerciseList[i].path << endl;
    }
}

Exercise Exercise::getExerciseFromId(const int32_t id)
{
    Exercise aux;
    for(uint32_t i = 0; i < Exercise::marketExerciseList.size(); i++)
    {
        if(id == Exercise::marketExerciseList[i].getId())
        {
            return Exercise::marketExerciseList[i];
        }
    }

    return aux;
}
