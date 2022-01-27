#include "guitrainingsession.h"
#include "ui_guitrainingsession.h"

#include "applicationInterface.h"


GuiTrainingSession::GuiTrainingSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiTrainingSession)
{
    ui->setupUi(this);
}

GuiTrainingSession::~GuiTrainingSession()
{
    delete ui;
}


//---------------------- Functions ---------------------------
void GuiTrainingSession::setUserRef(User* user)
{
  guiUser = user;
}



void GuiTrainingSession::on_GuiTrainingSession_finished(int result)
{
   appInterface.stopAcquire();
   this->close();
}


// -------------------- Button events ------------------------------
void GuiTrainingSession::on_push_GoBack_clicked()
{

    on_GuiTrainingSession_finished(NULL);
}

void GuiTrainingSession::on_GuiTrainingSession_accepted()
{
    qDebug("Iniciada uma nova sessao de treino");
}

void GuiTrainingSession::on_pushButton_clicked()
{
    appInterface.startAcquire();
}
