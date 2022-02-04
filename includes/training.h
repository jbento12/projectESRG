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
    void nextExercise();

    string getName();
    void getName(string& name);

    void setName(const string& name);

    vector<Exercise> exerciseList;
    int32_t currentExercise;
    string name;
private:


};



#endif //TRAINING_H
