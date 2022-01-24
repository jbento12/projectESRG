#include "gui.h"

#include <QApplication>
//#include <QQuickView>
//#include <QGuiApplication>
//#include <QQmlEngine>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;
    w.show();
    return a.exec();
}
