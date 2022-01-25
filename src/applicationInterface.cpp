#include "applicationInterface.h"
#include "training.h"
#include "manageDB.h"
#include "gui.h"


#include <iostream>

using namespace std;


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

