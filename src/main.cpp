#include "gui.h"
#include "applicationInterface.h"

#include <QApplication>
//#include <QQuickView>
//#include <QGuiApplication>
//#include <QQmlEngine>


ApplicationInterface appInterface;


int main(int argc, char *argv[])
{

    appInterface.createThreads();


     QApplication a(argc, argv);
     gui w;
     w.show();
     return a.exec();
}
