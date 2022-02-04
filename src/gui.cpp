#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>


#include <string>



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
    ManageDB auxDB;

    user = ui->line_user->text().toStdString();   //get text from UI
    pass = ui->line_pass->text().toStdString();

    if(auxDB.checkLogin(user, pass, appInterface.currentUser))
    {

        auxDB.getUserTrainingList(appInterface.currentUser);
        guiUser = &appInterface.currentUser;
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
