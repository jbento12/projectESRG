/**
 * @file guihistory.cpp
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "guihistory.h"
#include "ui_guihistory.h"
#include "manageDB.h"
#include "applicationInterface.h"

/**
 * @brief GuiHistory::GuiHistory
 * Costructor created automatically by Qt
 * @param parent
 */
GuiHistory::GuiHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiHistory)
{
    ui->setupUi(this);
}

/**
 * @brief GuiHistory::~GuiHistory
 * Default Destructor
 */
GuiHistory::~GuiHistory()
{
    delete ui;
}


//---------------------- Functions ---------------------------
/**
 * @brief GuiHistory::setUserRef
 * Sets the "pointer reference" to the logged in user
 * @param user
 */
void GuiHistory::setUserRef(User* user)
{
  guiUser = user;
}

/**
 * @brief GuiHistory::on_push_GoBack_clicked
 * Called when User presses "Go Back" button in the UI
 */
void GuiHistory::on_push_GoBack_clicked()
{
    this->on_GuiHistory_finished(0);
}

/**
 * @brief GuiHistory::on_GuiHistory_finished
 * Called from GuiHistory::on_push_GoBack_clicked()
 * @param result
 */
void GuiHistory::on_GuiHistory_finished(int result)
{
    this->close();
}

/**
 * @brief GuiHistory::on_push_history_clicked
 * Responsible for showing the training history of the current logged in User
 */
void GuiHistory::on_push_history_clicked()
{
    ManageDB aux_database;
    QString thisLine;

    aux_database.database.open();

    aux_database.query->prepare("SELECT * FROM training_history WHERE userId=?");
    aux_database.query->bindValue(0, guiUser->getId());
    aux_database.query->exec();

    ui->list_history->clear();      //reset view
    while(aux_database.query->next())   //advance pointer to the next row
    {
        thisLine = aux_database.query->value(0).toString() + '\n'
                 + aux_database.query->value(1).toString() + '\n'
                 + aux_database.query->value(2).toString() + '\n'
                 + aux_database.query->value(3).toString() + '\n'
                 + aux_database.query->value(4).toString() + '\n';
        ui->list_history->addItem(thisLine);
    }

    aux_database.database.close();
}
