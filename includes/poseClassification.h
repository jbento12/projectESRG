#ifndef poseClassification__H
#define poseClassification__H

#include <string>
#include <pthread.h>
#include <semaphore.h>

enum limbPairs_t{
   
    PAIR0, PAIR1, PAIR2, PAIR3, PAIR4, ANDSOON

};




class poseClassification
{


    public:

    poseClassification();
    ~poseClassification();

    bool get_landmarks();   
    limbPairs_t detect_person();
    int compare_landmarks();


};









#endif