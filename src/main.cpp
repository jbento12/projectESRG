#include <QApplication>
#include <QPushButton>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
//    QPushButton hello("Hello world!");
//    hello.show();
    MainWindow my_window;
    //SecondWindow my_scond;

    my_window.show();

    return app.exec();
}
