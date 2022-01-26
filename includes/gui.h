#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

#include "guisecond.h"
#include "user.h"
#include <string>


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

private:
    Ui::gui *ui;
    GuiSecond* guiSecond;
    User* guiUser;
};
#endif // GUI_H
