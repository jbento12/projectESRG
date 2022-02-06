/**
 * @file training.cpp
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "exercise.h"
#include "user.h"





Training::Training()
{
    currentExercise = 0;
    name = "";

    heartCount = 0;
    maxHeartRate = 0;
    avgHeartRate =0;
    scoreCount  = 0;
    avgScore    = 0;
}

Training::~Training()
{

}


bool Training::insertExercise(const Exercise& exercise)
{
    return true;
}


Exercise Training::removeExercise()
{

}


int32_t Training::nextExercise()
{
    if(currentExercise >= this->exerciseList.size())
        return -1;

    return currentExercise++;
}


string Training::getName()
{
    return this->name;
}

void Training::getName(string& name)
{
    name = this->name;
}

void Training::setName(const string& name)
{
    this->name = name;
}

string Training::getCurrExerName()
{
    return this->exerciseList[currentExercise].getName();
}


/**
 * @brief Training::HeartRateCalculation
 * @param heartRate for the calculation
 */
void Training::HeartRateCalculation(int32_t heartRate)
{
    if(heartRate > this->maxHeartRate)
       this->maxHeartRate = heartRate;

    avgHeartRate = ((avgHeartRate * heartCount) + heartRate);
    heartCount++;
    avgHeartRate = avgHeartRate/heartCount;
}

void Training::avgScoreCalculation(int32_t score)
{
    avgScore = ((avgScore * scoreCount) + score);
    scoreCount++;
    avgScore = avgScore/scoreCount;
}

