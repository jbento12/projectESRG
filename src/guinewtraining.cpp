#include "guinewtraining.h"
#include "ui_guinewtraining.h"

GuiNewTraining::GuiNewTraining(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiNewTraining)
{
    ui->setupUi(this);

    guiTrainingSession = new GuiTrainingSession(this);

    QObject::connect(guiTrainingSession, &GuiTrainingSession::finished, this, &GuiNewTraining::show);
}

GuiNewTraining::~GuiNewTraining()
{
    delete guiTrainingSession;
    delete ui;
}


//---------------------- Functions ---------------------------
void GuiNewTraining::setUserRef(User* user)
{
  guiUser = user;
}


// -------------- Events ------------------------------------
void GuiNewTraining::on_push_GoBack_clicked()
{
    on_GuiNewTraining_finished(NULL);
}

void GuiNewTraining::on_GuiNewTraining_finished(int result)
{
    this->close();
}

void GuiNewTraining::on_push_Select_clicked()
{

    //somehow get the training selected on the combo seltector

    this->hide();
    guiTrainingSession->show();
}
