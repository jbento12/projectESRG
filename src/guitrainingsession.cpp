#include "guitrainingsession.h"
#include "ui_guitrainingsession.h"

#include "applicationInterface.h"
#include <ctime>

GuiTrainingSession::GuiTrainingSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiTrainingSession)
{
    ui->setupUi(this);
     timer = new QTimer(this); // create it
   connect(timer, &QTimer::timeout, this, &GuiTrainingSession::TimerSlot ); // connect it
}

GuiTrainingSession::~GuiTrainingSession()
{
    delete ui;
    delete timer;
}


void GuiTrainingSession::TimerSlot()
{
    Mat src;
    if (appInterface.camera.frame.empty())
        return;

    src = appInterface.camera.frame;

    pthread_mutex_lock(&mut_frame);
        ui->label_ImageDisplay->setPixmap(QPixmap::fromImage(QImage(src.data, src.cols,
                   src.rows, src.step, QImage::Format_RGB888)).scaled(500,500,Qt::KeepAspectRatio));
    pthread_mutex_unlock(&mut_frame);

    ui->label_heartRate->setText(QString::number(appInterface.heartSensor.getHeartRate()));
    ui->label_Stamp->setText(QString::number(appInterface.heartSensor.getHeartStamp()));
    ui->label_currExer->setText(exerciseName);
}

//---------------------- Functions ---------------------------
void GuiTrainingSession::setUserRef(User* user)
{
  guiUser = user;
}



void GuiTrainingSession::on_GuiTrainingSession_finished(int result)
{
   QString query;
   time_t now = time(0);
   char* dt = ctime(&now);
   timer->stop();
   appInterface.stopAcquire();
   this->close();

   query = "INSERT INTO training_history (userId, train_name, train_date, avgScore, avgHeart) VALUES(";
   query += "'";
   query += QString::number(this->guiUser->getId());    //userId
   query += "','";
   query += QString::fromStdString(this->guiUser->toPlay.getName()); //trainning name
   query += "','";
   query += QString::fromLocal8Bit(dt);     //date of finish
   query += "','";
   query += QString::number(this->guiUser->toPlay.getAvgHeart());
   query += "','";
   query += QString::number(this->guiUser->toPlay.getAvgScore());
   query += "')";

   ManageDB::manageDBaddQuery(query);
   pthread_cond_signal(&cond_manageDB);
}


// -------------------- Button events ------------------------------
void GuiTrainingSession::on_push_GoBack_clicked()
{

    on_GuiTrainingSession_finished(0);
}

void GuiTrainingSession::on_GuiTrainingSession_accepted()
{
    qDebug("Iniciada uma nova sessao de treino");
}

void GuiTrainingSession::on_pushButton_clicked()
{
    string aux;
    int32_t curr_aux;

   //---------- set name of the training --------------
    aux = this->guiUser->toPlay.getName();
    trainingName = QString::fromStdString(aux);
    ui->label_TraningName->setText(trainingName);

    //---------- set first exercise -------------------
    curr_aux = this->guiUser->toPlay.getCurrExer();
    aux = this->guiUser->toPlay.exerciseList[curr_aux].getName();
    exerciseName = QString::fromStdString(aux);
    ui->label_currExer->setText(exerciseName);

    //---------- start camera acquire -----------------
    appInterface.startAcquire();
    timer->start(100); // camera timer
}

void GuiTrainingSession::on_push_goNext_clicked()
{
    string aux;
    int32_t aux_curr = this->guiUser->toPlay.nextExercise();


    if(aux_curr >= 0)
    {
        aux = this->guiUser->toPlay.exerciseList[aux_curr].getName();
        exerciseName = QString::fromStdString(aux);
    }
    else {
        QMessageBox::warning(this, "End of training", "There are no more exercises in this model");
    }
}
