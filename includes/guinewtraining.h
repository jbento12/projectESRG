/**
 * @file guinewtraining.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GUINEWTRAINING_H
#define GUINEWTRAINING_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
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
    void fillComboBox();

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
