#ifndef exercise__H
#define exercise__H

#include <string>
#include <pthread.h>
#include <semaphore.h>


using namespace std;
class exercise
{

    string exercise_id;
    string exercise_name;
    string exercise_path;
    int exercise_length;


    public:

    exercise();
    bool get_training_name();    
    int update_score();
    string set_exercise_path();
    ~exercise();

    
    

};






#endif