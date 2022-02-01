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

    //get the training name on the combo seltector
 //   train_name = ui->comboBox_ChooseTrain->itemData().toString;
    //set the "to play" trianing based on the name from the combo box
//    ret = this->guiUser->setToPlayTraining(QString::toStdString(train_name));
//    if(ret == 0)
//    {
        this->hide();
        guiTrainingSession->show();
//    }else {
//        QMessageBox::warning(this, "Add New Model", "Could not set training");
//    }
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
