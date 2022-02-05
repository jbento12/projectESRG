/**
 * @file exercise.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "exercise.h"
#include "poseClassification.h"

#include <string>
#include <QString>
#include <QDebug>


#define EXERCISE_DATABASE_PATH "/home/luiscarlos/Documents/embebidos/exercise_sqlite.db"
//#define EXERCISE_DATABASE_PATH "/etc/sfm_database/exercise_sqlite.db"


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
