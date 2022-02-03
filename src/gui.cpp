﻿#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>


#include <string>

//gui* w_ptr;
//temporario para o login

//const string test_Username = "";
//const string test_Password = "";

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);

    this->guiUser = NULL;
    guiSecond = new GuiSecond(this);
    QObject::connect(guiSecond, &GuiSecond::finished, this, &gui::show);
//    QObject::connect(push_quitApp, &QPushButton::clicked, this, &QCoreApplication::quit, Qt::QueuedConnection);
}

gui::~gui()
{
    delete guiSecond;
    delete ui;
}

/**
 * @brief gui::on_pushButton_clicked
 */
void gui::on_pushButton_clicked()
{
    string user;
    string pass;
    string user_first_name = "Unknown";


    user = ui->line_user->text().toStdString();   //get text from UI
    pass = ui->line_pass->text().toStdString();

    if(User::checkLogin(user, pass, this->guiUser))
    {
        if(!guiUser)
            return;

        QString salute = "Boas meu puto " + QString::fromStdString(this->guiUser->getName());
        QMessageBox::information(this, "Login", salute);

        //pass control to the next window
        this->hide();
        guiSecond->setUserRef(guiUser);
        guiSecond->show();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Login info wrong");
    }
}


void gui::on_push_quitApp_clicked()
{
    QCoreApplication::quit();
}
