#include "applicationInterface.h"
#include "training.h"
#include "manageDB.h"
#include "gui.h"

#include "camera.h"

#include <iostream>

using namespace std;


pthread_t thManageDB;
pthread_t thProcessImage;
pthread_t thClassification;
pthread_t thTraining;
pthread_t thAcquireImage;

pthread_mutex_t mut_acquireImage = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_acquireImage = PTHREAD_COND_INITIALIZER;



ApplicationInterface appInterface;


ApplicationInterface::ApplicationInterface()
{
    toAcquire = false;

}

ApplicationInterface::~ApplicationInterface()
{

}


void ApplicationInterface::init()
{
//    pthread_mutex_init(&mut_acquireImage, NULL);

//    this->mut_acquireImage = PTHREAD_MUTEX_INITIALIZER;
//    this->cond_acquireImage = PTHREAD_COND_INITIALIZER;
}




void* thManageDBFunc(void* arg)
{
    cout << "thread - thManageDBFunc\n";

}


void* thProcessImageFunc(void* arg)
{
    cout << "thread - thProcessImageFunc\n";
}


void* thClassificationFunc(void* arg)
{
    cout << "thread - thClassificationFunc\n";
}


void* thTrainingFunc(void* arg)
{
    cout << "thread - thTrainingFunc\n";
}


void* thAcquireImageFunc(void* arg)
{
    cout << "thread - thAcquireImageFunc\n";


    //task infinite loop
    for(;;)
    {
        pthread_mutex_lock(&mut_acquireImage);
        if(appInterface.getToAcquire())
        {

            appInterface.camera.cap >> appInterface.camera.frame;

        }
        else
        {
            pthread_cond_wait(&cond_acquireImage, &mut_acquireImage);
        }
        pthread_mutex_unlock(&mut_acquireImage);
    }
}


bool createThreads()
{
    pthread_create(&thManageDB,         NULL,   thManageDBFunc,         NULL);
    pthread_detach(thManageDB);
    pthread_create(&thProcessImage,     NULL,   thProcessImageFunc,     NULL);
    pthread_detach(thProcessImage);
    pthread_create(&thClassification,   NULL,   thClassificationFunc,   NULL);
    pthread_detach(thClassification);
    pthread_create(&thTraining,         NULL,   thTrainingFunc,         NULL);
    pthread_detach(thTraining);
    pthread_create(&thAcquireImage,     NULL,   thAcquireImageFunc,     NULL);
    pthread_detach(thAcquireImage);
    return true;
}


void ApplicationInterface::startAcquire()
{
    this->toAcquire = true;
    appInterface.camera.open();
    pthread_cond_signal(&cond_acquireImage);    //tell thread to start aquire
}

void ApplicationInterface::stopAcquire()
{
    this->toAcquire = true;
    appInterface.camera.release();
}
