#ifndef GUIHISTORY_H
#define GUIHISTORY_H

#include <QDialog>

namespace Ui {
class GuiHistory;
}

class GuiHistory : public QDialog
{
    Q_OBJECT

public:
    explicit GuiHistory(QWidget *parent = nullptr);
    ~GuiHistory();

private slots:
    void on_push_GoBack_clicked();

    void on_GuiHistory_finished(int result);

private:
    Ui::GuiHistory *ui;
};

#endif // GUIHISTORY_H
