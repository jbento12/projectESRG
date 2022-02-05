#ifndef TRAINING_H
#define TRAINING_H

#include <vector>
#include "exercise.h"


class Training
{

public:
    Training();
    ~Training();

    bool insertExercise(const Exercise& exercise);
    Exercise removeExercise();
    int32_t nextExercise();

    string getName();
    void getName(string& name);
    void setName(const string& name);

    int32_t getCurrExer(){return this->currentExercise;};

public:
    vector<Exercise> exerciseList;

private:
    int32_t currentExercise;
    string name;

    //---- for history saving -------


};



#endif //TRAINING_H
