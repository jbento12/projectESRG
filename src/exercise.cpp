#include "exercise.h"
#include "poseClassification.h"

#include <string>

//global varibles

vector<Exercise> Exercise::marketExerciseList;
uint32_t Exercise::exerciseIDcount = 0;


Exercise::Exercise()
{
 name = "Unknown";

}

Exercise::~Exercise()
{
}


void Exercise::setName(std::string name)
{
    this->name = name;
}


void Exercise::setPath(std::string path)
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





bool Exercise::addExerciseToMarket(Exercise& exercise)
{
    exercise.id = Exercise::exerciseIDcount;
    Exercise::exerciseIDcount++;
    Exercise::marketExerciseList.push_back(exercise);
    return true;
}

void Exercise::populateExerciseList()
{
    Exercise aux;
    string s_aux;

    s_aux = "Bicep Curl";
    aux.setName(s_aux);
    s_aux = "/boasCurl";
    aux.setPath(s_aux);
    addExerciseToMarket(aux);

    s_aux = "Lat PullDown";
    aux.setName(s_aux);
    s_aux = "/boasPullDown";
    aux.setPath(s_aux);
    addExerciseToMarket(aux);

    s_aux = "Row";
    aux.setName(s_aux);
    s_aux = "/boasRow";
    aux.setPath(s_aux);
    addExerciseToMarket(aux);

    s_aux = "Barbell";
    aux.setName(s_aux);
    s_aux = "/boasBarbell";
    aux.setPath(s_aux);
    addExerciseToMarket(aux);
}

void Exercise::printMarketExerciseList()
{
    cout << "Comecar a imprimer os exercicios" << endl;
    for(uint32_t i = 0; i < Exercise::marketExerciseList.size(); i++)
    {
        cout << Exercise::marketExerciseList[i].name << endl;
        cout << Exercise::marketExerciseList[i].path << endl;
        cout << Exercise::marketExerciseList[i].id   << endl << endl;
    }
}
