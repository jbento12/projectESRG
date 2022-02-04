#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <string>
#include "user.h"
#include "guisecond.h"
#include "manageDB.h"
#include "applicationInterface.h"



using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);
    ~gui();


private slots:
    void on_pushButton_clicked();

    void on_push_quitApp_clicked();

private:
    Ui::gui *ui;

    User* guiUser;
public:
    GuiSecond* guiSecond;
};


//gui* w_ptr;

#endif // GUI_H
