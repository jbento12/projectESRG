#ifndef MYEXERCISE_H_
#define MYEXERCISE_H_

#include <iostream>
#include <vector>
#include <string>

#include <stdint.h>


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
    static void populateExerciseList();
    static void printMarketExerciseList();

    static Exercise getExerciseFromId(const int32_t id);

    static vector<Exercise> marketExerciseList;
private:

    static uint32_t exerciseIDcount;
};


#endif //EXERCISE_H_
