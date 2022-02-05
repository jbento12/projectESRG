#ifndef GUIHISTORY_H
#define GUIHISTORY_H

#include <QDialog>

#include "user.h"


namespace Ui {
class GuiHistory;
}

class GuiHistory : public QDialog
{
    Q_OBJECT

public:
    explicit GuiHistory(QWidget *parent = nullptr);
    ~GuiHistory();

    void setUserRef(User* user);


private slots:
    void on_push_GoBack_clicked();

    void on_GuiHistory_finished(int result);

    void on_push_history_clicked();

private:
    Ui::GuiHistory *ui;
    User* guiUser;
};

#endif // GUIHISTORY_H
