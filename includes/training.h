#ifndef training__H
#define training__H

#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <vector> 
#include "../includes/exercise.h"
#include "../includes/user.h"
using namespace std;
extern pthread_mutex_t training_mutex;



class training
{

    string training_id;
    string training_name;
    int training_length;
    int training_points;
    vector<exercise *> exercises;

    public:

    training();
    ~training();

    int get_Ex_ID();
    bool get_tr_name();    
    int update_score();
    bool get_score();
    bool get_maxHR();
    bool get_avgHR();
    bool get_length();

};


#endif