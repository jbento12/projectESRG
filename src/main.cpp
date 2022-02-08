/**
 * @file main.cpp
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "applicationInterface.h"
#include "exercise.h"
#include "user.h"
// #include <QApplication>
#include <string>
// #include <QDebug>
//#include <QQuickView>
//#include <QGuiApplication>
//#include <QQmlEngine>
#include "macros.h"


#define BUTTON_NAME "/dev/button"

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
    int gui_ret = 0;
    int buttonFd = 0;
    char buttonValue = 0;
    int count = 0;

     QApplication a(argc, argv);
     appInterface.init();
     appInterface.createThreads();
     gui w;
     w.show();


#ifdef MY_ARCH_PC
     return a.exec();
#else
     while(true)       //if it is running on the board it never exits this loop
     {
            cout << "Opening button driver\n";
            buttonFd = open(BUTTON_NAME, O_RDWR);
            if(buttonFd < 0) {
                     cout << "Cannot open device file...\n";
              return 0;
            }
            cout << "Button driver opened\n";

                while(true)
                {
                     read(buttonFd, &buttonValue, count);
                     if(buttonValue == 1)
                     {
                         cout << "Init button pushed ...\n";
                        break;
                     }
                     usleep(500000);    //check button every half second
                }
            close(buttonFd);

          gui_ret = a.exec();
          w.hide();
     }
    #endif

    //appInterface.createThreads();

    pthread_join(appInterface.thManageDB,       NULL);
    pthread_join(appInterface.thProcessImage,   NULL);
    pthread_join(appInterface.thClassification, NULL);
    pthread_join(appInterface.thTraining,       NULL);
    pthread_join(appInterface.thAcquireImage,   NULL);
    return gui_ret;
}





