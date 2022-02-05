#include "guihistory.h"
#include "ui_guihistory.h"
#include "manageDB.h"
#include "applicationInterface.h"

GuiHistory::GuiHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuiHistory)
{
    ui->setupUi(this);
}

GuiHistory::~GuiHistory()
{
    delete ui;
}


//---------------------- Functions ---------------------------
void GuiHistory::setUserRef(User* user)
{
  guiUser = user;
}


void GuiHistory::on_push_GoBack_clicked()
{
    this->on_GuiHistory_finished(0);
}

void GuiHistory::on_GuiHistory_finished(int result)
{
    this->close();
}

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
