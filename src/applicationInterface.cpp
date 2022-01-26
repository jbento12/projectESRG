#include "applicationInterface.h"
#include "training.h"
#include "manageDB.h"
#include "gui.h"

#include "camera.h"

#include <iostream>

using namespace std;


pthread_mutex_t mut_acquireImage = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_acquireImage = PTHREAD_COND_INITIALIZER;




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




void ApplicationInterface::thManageDBFunc(void* arg)
{
    cout << "thread - thManageDBFunc\n";

}


void ApplicationInterface::thProcessImageFunc(void* arg)
{
    cout << "thread - thProcessImageFunc\n";
}


void ApplicationInterface::thClassificationFunc(void* arg)
{
    cout << "thread - thClassificationFunc\n";
}


void ApplicationInterface::thTrainingFunc(void* arg)
{
    cout << "thread - thTrainingFunc\n";
}


void ApplicationInterface::thAcquireImageFunc(void* arg)
{
    cout << "thread - thAcquireImageFunc\n";

    int ola = 1;


    //task infinite loop
    for(;;)
    {
        pthread_mutex_lock(&mut_acquireImage);
        if(ola)
        {
            cout<< "cheguei ao acccccccccccCCCC\n";
            ola = 0;
        }
        else
        {
            cout<< "vou dormir ate logo\n";
            pthread_cond_wait(&cond_acquireImage, &mut_acquireImage);
        }
        pthread_mutex_unlock(&mut_acquireImage);
    }
}


bool ApplicationInterface::createThreads()
{
    pthread_create(&thManageDB, NULL,       &ApplicationInterface::thManageDBFunc_wrapper, NULL);
    pthread_create(&thProcessImage, NULL,   &ApplicationInterface::thProcessImageFunc_wrapper, NULL);
    pthread_create(&thClassification, NULL, &ApplicationInterface::thClassificationFunc_wrapper, NULL);
    pthread_create(&thTraining, NULL,       &ApplicationInterface::thTrainingFunc_wrapper, NULL);
    pthread_create(&thAcquireImage, NULL,   &ApplicationInterface::thAcquireImageFunc_wrapper, NULL);

    return true;
}


void ApplicationInterface::startAcquire()
{
    this->toAcquire = true;
    pthread_cond_signal(&cond_acquireImage);    //tell thread to start aquire
}

void ApplicationInterface::stopAcquire()
{
    this->toAcquire = true;
}
