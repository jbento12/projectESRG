#ifndef EXERCISE_H_
#define EXERCISE_H_

#include <iostream>
#include <vector>
#include <string>

#include <stdint.h>


using namespace std;



class Exercise
{
public:
    Exercise();
    ~Exercise();

    void setName(string name);
    void setPath(string path);

    string getName();
    string getPath();

private:
    string name;
    string path;
    int32_t id;


//populate with exercises
public:
    static bool addExerciseToMarket(Exercise& exercise);
    static void populateExerciseList();
    static void printMarketExerciseList();

private:
    static vector<Exercise> marketExerciseList;
    static uint32_t exerciseIDcount;
};


#endif //EXERCISE_H_
