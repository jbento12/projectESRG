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


     QApplication a(argc, argv);
     appInterface.init();
     createThreads();
     gui w;
     w.show();
     return a.exec();
}
