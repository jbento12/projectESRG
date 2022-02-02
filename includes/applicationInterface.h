#ifndef APPLICATION_INTERFACE_H
#define APPLICATION_INTERFACE_H

#include "gui.h"
#include <pthread.h>
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QApplication>
#include <unistd.h>
#include <mqueue.h>   /* mq_* functions */
#include <sys/stat.h>
#include <stdlib.h>
#include <string>

#include "camera.h"

#include "manageDB.h"
#include "user.h"


#define MSGQOBJ_NAME    "/daemonMessage"
#define MAX_MSG_LEN     10000
#define MSG_PRIO 1


extern pthread_mutex_t mut_acquireImage;
extern pthread_mutex_t mut_processImage;
extern pthread_mutex_t mut_resultLand;
extern pthread_mutex_t mut_frame;

extern pthread_cond_t cond_acquireImage;
extern pthread_cond_t cond_processImage;

/**
 * @brief 
 * 
 */
class ApplicationInterface
{
public:
    ApplicationInterface();
    ~ApplicationInterface();

    pid_t pidDaemon;

    /**
     * @brief 
     * 
     */
    void init();

    //threads
    pthread_t thManageDB;
    pthread_t thProcessImage;
    pthread_t thClassification;
    pthread_t thTraining;
    pthread_t thAcquireImage;

    static void* thManageDBFunc(void* arg);
    static void* thProcessImageFunc(void* arg);
    static void* thClassificationFunc(void* arg);
    static void* thTrainingFunc(void* arg);
    static void* thAcquireImageFunc(void* arg);

    bool createThreads();


    void startAcquire();
    void stopAcquire();
    bool getToAcquire(){return this->toAcquire;};
    void startProcess(){this->toProcess = true;};
    void stopProcess(){this->toProcess = false;};
    bool getToProcess(){return this->toProcess;};




    string heartRate;

public:
    Camera camera;

private:
    bool toAcquire;
    bool toProcess;


};




extern ApplicationInterface appInterface;


#endif //APPLICATION_INTERFACE_H
