#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

#include "guisecond.h"

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

    bool checkLogin(const string& user, const string& pass, string& user_first_name);

private slots:
    void on_pushButton_clicked();

private:
    Ui::gui *ui;
    GuiSecond* guiSecond;
};
#endif // GUI_H
