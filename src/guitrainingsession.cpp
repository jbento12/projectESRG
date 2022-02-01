#include "guitrainingsession.h"
#include "ui_guitrainingsession.h"

#include "applicationInterface.h"


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
}


void GuiTrainingSession::TimerSlot()
{
    Mat src;
    if (appInterface.camera.frame.empty())
        return;

    src = appInterface.camera.frame;
    ui->label_ImageDisplay->setPixmap(QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)).scaled(500,500,Qt::KeepAspectRatio));
}

//---------------------- Functions ---------------------------
void GuiTrainingSession::setUserRef(User* user)
{
  guiUser = user;
}



void GuiTrainingSession::on_GuiTrainingSession_finished(int result)
{
   timer->stop();
   appInterface.stopAcquire();
   this->close();
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
    appInterface.startAcquire();
    timer->start(100); // camera timer
}
