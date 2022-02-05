/**
 * @file guisecond.cpp
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ui_guisecond.h"
#include "applicationInterface.h"

GuiSecond::GuiSecond(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiSecond)
{
    ui->setupUi(this);
    guiNewTraining = new GuiNewTraining(this);
    guiHistory = new GuiHistory(this);

    QObject::connect(guiNewTraining, &GuiNewTraining::finished, this, &GuiSecond::show);
    QObject::connect(guiHistory, &GuiHistory::finished, this, &GuiSecond::show);

    fillComboBox();
}

GuiSecond::~GuiSecond()
{
    delete guiHistory;
    delete guiNewTraining;
    delete ui;
}

//---------------------- Functions ---------------------------
void GuiSecond::setUserRef(User* user)
{
  guiUser = user;
}



void GuiSecond::on_push_GoBack_clicked()
{
    on_GuiSecond_finished(10);
}


void GuiSecond::on_GuiSecond_finished(int result)
{
    this->close();
}


//----------------- button events ---------------------

void GuiSecond::on_push_NewTraining_clicked()
{
    this->hide();
    guiNewTraining->setUserRef(guiUser);
    guiNewTraining->fillComboBox();
    guiNewTraining->show();
}

void GuiSecond::on_push_TrainHistory_clicked()
{
    this->hide();
    guiHistory->setUserRef(guiUser);
    guiHistory->show();
}




//---------------------------------------- New Training Model ------------------------------------
void GuiSecond::fillComboBox() {

    for(uint32_t i = 0; i < Exercise::marketExerciseList.size(); i++)
    {
        ui->combo_MarketExer->addItem(QString::fromStdString(Exercise::marketExerciseList[i].getName()),
                                      QVariant(Exercise::marketExerciseList[i].getId()));
    }
}


//Add the selected exercise to user
void GuiSecond::on_push_AddExercises_clicked()
{
    Exercise aux_exer;
    int id = ui->combo_MarketExer->itemData(ui->combo_MarketExer->currentIndex()).toInt();

    aux_exer = Exercise::getExerciseFromId(id);

    this->guiUser->addExerciseToNewModel(aux_exer);
    ui->listWidget_UserList->clear();
    listNewModelExercises();
}


void GuiSecond::listNewModelExercises()
{
    int id = 0;
    id = ui->combo_MarketExer->itemData(ui->combo_MarketExer->currentIndex()).toInt();

    for (int32_t i = 0; i < this->guiUser->newModel.exerciseList.size(); i++)
    {
        QString thisLine = QString::fromStdString(this->guiUser->newModel.exerciseList[i].getName());
        ui->listWidget_UserList->addItem(thisLine);
    }
}

void GuiSecond::on_push_CreatModel_clicked()
{
    int32_t ret;
    int32_t userId;
    QString exerciseList;
    QString query;

    string trainingName = ui->lineEdit_NewTrainingName->text().toStdString();
    ret = this->guiUser->addNewModel(trainingName, userId, exerciseList);

    if(ret == 0)
    {
        query = "INSERT INTO user_training (Name, userId, exercises) VALUES(";
        query += "'";
        query += QString::fromStdString(trainingName);
        query += "','";
        query += QString::number(userId);
        query += "','";
        query += exerciseList;
        query += "')";

        ManageDB::manageDBaddQuery(query);
        pthread_cond_signal(&cond_manageDB);
        QMessageBox::information(this, "Add New Model", "New Model Added");
    }
    else if(ret == USER_ERR_TRAIN_NAME_INVAL){
        QMessageBox::warning(this, "Add New Model", "Invalid Model Name");
    }
    else if(ret == USER_ERR_TRAIN_NAME_EXISTS){
        QMessageBox::warning(this, "Add New Model", "Model Name already exists");
    }
}

void GuiSecond::on_push_ResetNewModel_clicked()
{
    this->guiUser->newModel = Training();
    ui->listWidget_UserList->clear();
    ui->lineEdit_NewTrainingName->clear();
}


