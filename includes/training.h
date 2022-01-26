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

private:
    vector<Exercise> exercise_list;

};



#endif //TRAINING_H
