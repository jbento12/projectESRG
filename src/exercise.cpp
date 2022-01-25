#include "exercise.h"
#include "poseClassification.h"






bool Exercise::setName(const string& name)
{
    this->name = name;
}


bool Exercise::setPath(const string& path)
{
    this->path = path;
}


string Exercise::getName()
{
    return this->name;
}


string Exercise::getPath()
{
    return this->path;
}
