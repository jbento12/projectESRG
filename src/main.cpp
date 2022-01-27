#include "gui.h"
#include "applicationInterface.h"
#include "exercise.h"
#include "user.h"
#include <QApplication>
#include <string>
//#include <QQuickView>
//#include <QGuiApplication>
//#include <QQmlEngine>


using namespace std;



int main(int argc, char *argv[])
{

    Exercise::populateExerciseList();
    Exercise::printMarketExerciseList();

    User::populateUserList();



    User::printUserList();
    appInterface.init();
    createThreads();

     QApplication a(argc, argv);
     gui w;
     w.show();
     return a.exec();
}
