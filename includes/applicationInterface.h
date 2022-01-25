#ifndef APPLICATION_INTERFACE_H
#define APPLICATION_INTERFACE_H

#include "gui.h"
#include <pthread.h>



class ApplicationInterface
{
    //threads
public:
    void thManageDBFunc(void* arg);
    void thProcessImageFunc(void* arg);
    void thClassificationFunc(void* arg);
    void thTrainingFunc(void* arg);
    void thAcquireImageFunc(void* arg);

    bool createThreads();

    static void* thManageDBFunc_wrapper(void* object)
    {
        reinterpret_cast<ApplicationInterface*>(object)->thManageDBFunc(NULL);
        return 0;
    }
    static void* thProcessImageFunc_wrapper(void* object)
    {
        reinterpret_cast<ApplicationInterface*>(object)->thProcessImageFunc(NULL);
        return 0;
    }
    static void* thClassificationFunc_wrapper(void* object)
    {
        reinterpret_cast<ApplicationInterface*>(object)->thClassificationFunc(NULL);
        return 0;
    }
    static void* thTrainingFunc_wrapper(void* object)
    {
        reinterpret_cast<ApplicationInterface*>(object)->thTrainingFunc(NULL);
        return 0;
    }
    static void* thAcquireImageFunc_wrapper(void* object)
    {
        reinterpret_cast<ApplicationInterface*>(object)->thAcquireImageFunc(NULL);
        return 0;
    }

private:
    pthread_t thManageDB;
    pthread_t thProcessImage;
    pthread_t thClassification;
    pthread_t thTraining;
    pthread_t thAcquireImage;



};





#endif //APPLICATION_INTERFACE_H
