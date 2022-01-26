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


void Exercise::setName(const string& name)
{
    this->name = name;
}


void Exercise::setPath(const string& path)
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










// ---------------- Used to populate ------------------------------



bool Exercise::addExerciseToMarket(Exercise& exercise)
{
    exercise.id = Exercise::exerciseIDcount;
    Exercise::exerciseIDcount++;
    Exercise::marketExerciseList.push_back(exercise);
    return true;
}


void Exercise::populateExerciseList()
{
    //----------- Just a dummy populate (for now (testing)) -----------
    Exercise aux;

    aux.setName("Bicep Curl");
    aux.setPath("/boasCurl");
    addExerciseToMarket(aux);

    aux.setName("Lat PullDown");
    aux.setPath("/boasPullDown");
    addExerciseToMarket(aux);

    aux.setName("Row");
    aux.setPath("/boasRow");
    addExerciseToMarket(aux);

    aux.setName("Barbell");
    aux.setPath("/boasBarbell");
    addExerciseToMarket(aux);

    aux.setName("Supino");
    aux.setPath("/boasSupino");
    addExerciseToMarket(aux);

    aux.setName("Bench");
    aux.setPath("/boasBench");
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
