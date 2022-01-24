#include "gui.h"
#include "ui_gui.h"

#include <QMessageBox>


#include <string>

//temporario para o login

const string test_Username = "";
const string test_Password = "";

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);

    guiSecond = new GuiSecond(this);
    QObject::connect(guiSecond, &GuiSecond::finished, this, &gui::show);
}

gui::~gui()
{
    delete guiSecond;
    delete ui;
}


void gui::on_pushButton_clicked()
{
    string user;
    string pass;
    string user_first_name = "Unknown";

    user = ui->line_user->text().toStdString();   //get text from UI
    pass = ui->line_pass->text().toStdString();

    if(checkLogin(user, pass, user_first_name))
    {
        QString salute = "Boas meu puto " + QString::fromStdString(user_first_name);
        QMessageBox::information(this, "Login", salute);
        this->hide();
        guiSecond->show();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Login info wrong");
    }
}


bool gui::checkLogin(const string& user, const string& pass, string& user_first_name)
{
    if(user == test_Username && pass == test_Password)
    {
        user_first_name = "Keidje";
        return true;
    }
    else
    {
        user_first_name = "Unknown";
        return false;
    }
}

