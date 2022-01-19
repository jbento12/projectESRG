#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QMessageBox>
#include <QDialog>
#include <secondwindow.h>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sec_window = new SecondWindow(this);

    QObject::connect(ui->horizontalSlider, &QSlider::valueChanged, ui->progressBar, &QProgressBar::setValue);

    //pushButton (clicked)    ->         progressBar (setValue)
    QObject::connect(this, &MainWindow::meu_sinal, ui->progressBar, &QProgressBar::setValue);

     QObject::connect(sec_window, &SecondWindow::send_after_second, this, &MainWindow::continue_after_second);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::on_pushButton_clicked()
{
    static bool state = true;

    if(state)
    {
        ui->label->setText("nao chavalo");
        //valorVariavel = 33;
    }
    else
    {
        ui->label->setText("ya chavalo");
        //valorVariavel = 69;
    }
    state = !state;
    //ui->progressBar->setValue(valorVariavel);

    emit meu_sinal(65);
       return 0;
}



void MainWindow::on_pushButton_2_clicked()
{
    emit meu_sinal(45);
    QMessageBox::critical(this, "Meu tits", "que andas a fazer a tua vida",
                          QMessageBox::Abort,
                          QMessageBox::Yes,
                          QMessageBox::NoAll);
}

void MainWindow::on_pushButton_3_clicked()
{
//    SecondWindow sec_window;


    this->hide();
    sec_window->show();


//      sec_window.setModal(true);
//      sec_window.exec();
}

void MainWindow::continue_after_second(void)
{
    this->show();
}
