#include "guisecond.h"
#include "ui_guisecond.h"

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
    guiNewTraining->show();
}

void GuiSecond::on_push_TrainHistory_clicked()
{
    this->hide();
    guiHistory->setUserRef(guiUser);
    guiHistory->show();
}


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

    this->guiUser->addExercise(aux_exer);
    ui->listWidget_UserList->clear();
    listUserExercises();
}

void GuiSecond::listUserExercises()
{
    int id = 0;
    id = ui->combo_MarketExer->itemData(ui->combo_MarketExer->currentIndex()).toInt();

    for (int32_t i = 0; i < this->guiUser->userExercisesList.size(); i++)
    {
        QString thisLine = QString::fromStdString(this->guiUser->userExercisesList[i].getName());
        ui->listWidget_UserList->addItem(thisLine);
    }
}
