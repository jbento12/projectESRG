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

    void HeartRateCalculation(int32_t heartRate);
    void avgScoreCalculation(int32_t score);

public:
    vector<Exercise> exerciseList;

private:
    int32_t currentExercise;
    string name;

    //----- training history ---------
    uint32_t heartCount;
    int32_t maxHeartRate;
    int32_t avgHeartRate;
    uint32_t scoreCount;
    int32_t avgScore;

};



#endif //TRAINING_H
