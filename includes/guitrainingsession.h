#ifndef GUITRAININGSESSION_H
#define GUITRAININGSESSION_H

#include <QDialog>

#include "user.h"
#include "manageDB.h"


namespace Ui {
class GuiTrainingSession;
}

class GuiTrainingSession : public QDialog
{
    Q_OBJECT

public:
    explicit GuiTrainingSession(QWidget *parent = nullptr);
    ~GuiTrainingSession();

    void setUserRef(User* user);

    QTimer *timer; // NEW

private slots:
    void TimerSlot(); // NEW slot
    void on_GuiTrainingSession_finished(int result);
    void on_push_GoBack_clicked();


    void on_GuiTrainingSession_accepted();

    void on_pushButton_clicked();

signals:
    void signal_GuiTrainingSession_finished();

private:

    User* guiUser;
public:
    Ui::GuiTrainingSession *ui;
};

#endif // GUITRAININGSESSION_H
