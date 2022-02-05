/**
 * @file exercise.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define MYEXERCISE_H__

#include <iostream>
#include <vector>
#include <string>

#include <stdint.h>

#include <QtSql>
#include <QDebug>
#include <QFileInfo>


using namespace std;



//struct LandMark
//{


//}

//struct LandMarkList
//{
//    vector
//}


class Exercise
{
public:
    Exercise();
    ~Exercise();
    void setIDfromDatabase(int32_t idDatabase);
    void setName(const string& name);
    void setPath(const string& path);


    string getName();
    string getPath();
    int32_t getId(){return this->id;};

private:
    string name;
    string path;
    int32_t id;


//populate with exercises
public:
    static bool addExerciseToMarket(Exercise& exercise);
    static bool addExerciseToMarketFromDatabase(Exercise& exercise);
    static void populateExerciseList();
    static void printMarketExerciseList();

    static Exercise getExerciseFromId(const int32_t id);

    static vector<Exercise> marketExerciseList;
private:

    static uint32_t exerciseIDcount;
};


#endif //EXERCISE_H_
