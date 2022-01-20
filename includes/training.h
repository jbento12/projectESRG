#ifndef training__H
#define training__H

#include <string>
#include <pthread.h>
#include <semaphore.h>

using namespace std;
extern pthread_mutex_t training_mutex;



class training
{

    string training_id;
    string training_name;
    int training_length;
    int training_points;

    public:

    training();
    ~training();

    bool get_training_name();    
    int update_score();
    

};


#endif