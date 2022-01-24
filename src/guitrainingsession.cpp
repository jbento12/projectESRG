#include "guitrainingsession.h"
#include "ui_guitrainingsession.h"

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



void GuiTrainingSession::on_GuiTrainingSession_finished(int result)
{
   this->close();
}


// -------------------- Button events ------------------------------
void GuiTrainingSession::on_push_GoBack_clicked()
{
    on_GuiTrainingSession_finished(NULL);
}
