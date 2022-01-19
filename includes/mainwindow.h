#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    int on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void continue_after_second(void);

private:
    Ui::MainWindow *ui;
    int valorVariavel;
    SecondWindow* sec_window;

signals:
      void meu_sinal(int val);
};

#endif // MAINWINDOW_H
