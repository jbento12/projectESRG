/**
 * @file guinewtraining.cpp
 * @author ESRG group 3 
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
    on_GuiNewTraining_finished(0);
}

void GuiNewTraining::on_GuiNewTraining_finished(int result)
{
    this->close();
}

void GuiNewTraining::on_push_Select_clicked()
{
    int32_t ret;
    QString train_name;

    train_name = ui->comboBox_ChooseTrain->currentText();

    if(train_name == "")
    {
        QMessageBox::warning(this, "Select Model", "Please choose a Model");
        return;
    }

    this->guiUser->setToPlayTraining(train_name.toStdString());
    guiTrainingSession->setUserRef(guiUser);
    this->hide();
    guiTrainingSession->show();
}


//List Training models
void GuiNewTraining::fillComboBox() {
    ui->comboBox_ChooseTrain->clear();

    for(uint32_t i = 0; i < this->guiUser->userTrainingList.size(); i++)
    {
        ui->comboBox_ChooseTrain->addItem(QString::fromStdString(this->guiUser->userTrainingList[i].getName()));
    }

//                                          QVariant(Exercise::marketExerciseList[i].getId()));
}
