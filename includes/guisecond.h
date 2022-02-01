#ifndef GUISECOND_H
#define GUISECOND_H

#include <QDialog>
#include <QTimer>
#include <QMessageBox>

#include "guinewtraining.h"
#include "guihistory.h"
#include "user.h"
#include "exercise.h"



namespace Ui {
class GuiSecond;
}

class GuiSecond : public QDialog
{
    Q_OBJECT

public:
    explicit GuiSecond(QWidget *parent = nullptr);
    ~GuiSecond();

    void setUserRef(User* user);
    void fillComboBox();
    void listNewModelExercises();

private slots:
    void on_push_GoBack_clicked();
    void on_push_TrainHistory_clicked();
    void on_push_NewTraining_clicked();
    void on_GuiSecond_finished(int result);
    void on_push_AddExercises_clicked();

    void on_push_CreatModel_clicked();

    void on_push_ResetNewModel_clicked();

private:
    Ui::GuiSecond *ui;

    GuiHistory      *guiHistory;
    User* guiUser;
public:
    GuiNewTraining  *guiNewTraining;
};

#endif // GUISECOND_H
