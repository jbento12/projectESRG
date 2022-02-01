#include "gui.h"
#include "applicationInterface.h"
#include "exercise.h"
#include "user.h"
#include <QApplication>
#include <string>
#include <QDebug>
//#include <QQuickView>
//#include <QGuiApplication>
//#include <QQmlEngine>
#include "macros.h"

using namespace std;


/**
 * @brief 
 * 
 * @param argc  
 * @param argv parameter that identifies the platform in which the program is running
 * @return int 
 */
int main(int argc, char *argv[])
{


     QApplication a(argc, argv);
     appInterface.init();
     appInterface.createThreads();
     gui w;
     w.show();
     return a.exec();

//    appInterface.createThreads();

    pthread_join(appInterface.thManageDB     ,NULL);
    pthread_join(appInterface.thProcessImage ,NULL);
    pthread_join(appInterface.thClassification,NULL);
    pthread_join(appInterface.thTraining     ,NULL);
    pthread_join(appInterface.thAcquireImage ,NULL);
    return 0;
}





