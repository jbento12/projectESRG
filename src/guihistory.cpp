#include "guihistory.h"
#include "ui_guihistory.h"

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
    this->on_GuiHistory_finished(NULL);
}

void GuiHistory::on_GuiHistory_finished(int result)
{
    this->close();
}
