#include "training.h"
#include "exercise.h"
#include "user.h"





Training::Training()
{
    currentExercise = 0;
    name = "";
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

    currentExercise++;
    return currentExercise;
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

