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
    void setName(const string& name);

private:
    string name;
    int32_t currentExerciseId;
    vector<int32_t> exerciseId_list;
};



#endif //TRAINING_H
