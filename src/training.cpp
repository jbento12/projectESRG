#include "training.h"
#include "exercise.h"
#include "user.h"





Training::Training()
{

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


void Training::nextExercise()
{


}


string Training::getName()
{
    return this->name;
}


void Training::setName(const string& name)
{
    this->name = name;
}

