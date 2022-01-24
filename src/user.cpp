#include "user.h"
#include "poseClassification.h"



User::User()
{

}

User::~User()
{


}


bool User::setWeight(float weight)
{
    this->weight = weight;
    return true;
}

bool User::setHeight(float height)
{
    this->height = height;
    return true;
}
