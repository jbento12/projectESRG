#ifndef APPLICATION_INTERFACE_H
#define APPLICATION_INTERFACE_H

#include "gui.h"
#include <pthread.h>
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QApplication>
//#include <dos.h>
#include <unistd.h>
#include <string>

#include "camera.h"

#include "manageDB.h"
#include "user.h"


extern bool createThreads();

/**
 * @brief 
 * 
 */
class ApplicationInterface
{
public:
    ApplicationInterface();
    ~ApplicationInterface();


    /**
     * @brief 
     * 
     */
    void init();

    //threads
    void thManageDBFunc(void* arg);
    void thProcessImageFunc(void* arg);
    void thClassificationFunc(void* arg);
    void thTrainingFunc(void* arg);

    void thAcquireImageFunc(void* arg);

    bool createThreads();

                        //    static void* thManageDBFunc_wrapper(void* object)
                        //    {
                        //        reinterpret_cast<ApplicationInterface*>(object)->thManageDBFunc(NULL);
                        //        return 0;
                        //    }



    void startAcquire();
    void stopAcquire();
    bool getToAcquire(){return this->toAcquire;};
    void startProcess(){this->toProcess = true;};
    void stopProcess(){this->toProcess = false;};
    bool getToProcess(){return this->toProcess;};


public:
    Camera camera;

private:
    bool toAcquire;
    bool toProcess;



};



extern ApplicationInterface appInterface;



#endif //APPLICATION_INTERFACE_H
