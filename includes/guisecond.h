#ifndef GUISECOND_H
#define GUISECOND_H

#include <QDialog>

#include "guinewtraining.h"
#include "guihistory.h"
#include "user.h"


namespace Ui {
class GuiSecond;
}

class GuiSecond : public QDialog
{
    Q_OBJECT

public:
    explicit GuiSecond(QWidget *parent = nullptr);
    ~GuiSecond();

private slots:
    void on_push_GoBack_clicked();
    void on_push_TrainHistory_clicked();
    void on_push_NewTraining_clicked();


    void on_GuiSecond_finished(int result);

private:
    Ui::GuiSecond *ui;
    GuiNewTraining  *guiNewTraining;
    GuiHistory      *guiHistory;
    User* guiUser;
};

#endif // GUISECOND_H
