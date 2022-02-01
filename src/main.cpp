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
 * @param argv string that tells the platform in which the program is running
 * @return int 
 */
int main(int argc, char *argv[])
{


     QApplication a(argc, argv);
//     appInterface.init();
     createThreads();
     gui w;
     w.show();
     return a.exec();
}
