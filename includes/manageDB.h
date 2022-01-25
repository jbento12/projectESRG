#ifndef manageDB__H
#define manageDB__H

#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <sqlite3.h> 




struct User_s{
    string name;
    string password;
    int height;
    int weight;
     // name
};

struct training_s{

    int max
}





class manageDB{

    char *zErrMsg = 0;
    int rc;
    sqlite3 *db;


    public:

    manageDB();
    ~manageDB();

    /* 
        add user;
        complete training;
        check history -> list all trainings
                    -> list everything in each training : maximum heart rate, length, score, average heart , each exercise( name, score, reps)
                
        */

    int printHistory()
    int uploadTraining();
    int insertUser();
    int insertTraining();
    int insertExercise();
};

#endif