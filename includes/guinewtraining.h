#ifndef GUINEWTRAINING_H
#define GUINEWTRAINING_H

#include <QDialog>

#include "guitrainingsession.h"
#include "user.h"


namespace Ui {
class GuiNewTraining;
}

class GuiNewTraining : public QDialog
{
    Q_OBJECT

public:
    explicit GuiNewTraining(QWidget *parent = nullptr);
    ~GuiNewTraining();

    void setUserRef(User* user);

private slots:
    void on_push_GoBack_clicked();

    void on_GuiNewTraining_finished(int result);

    void on_push_Select_clicked();

signals:
    void signal_GuiNewTraining_finished();

private:
    Ui::GuiNewTraining *ui;

    User* guiUser;
public:
    GuiTrainingSession* guiTrainingSession;
};

#endif // GUINEWTRAINING_H
