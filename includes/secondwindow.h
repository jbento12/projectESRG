#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
//#include <opencv4/opencv2/opencv.hpp>

//#include <opencv4/opencv2/core.hpp>
//#include <opencv4/opencv2/videoio.hpp>
//#include <opencv4/opencv2/highgui.hpp>
//#include "opencv4/opencv2/imgproc/imgproc.hpp"
//#include <opencv4/opencv2/imgcodecs.hpp>

#include <opencv2/opencv.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void on_SecondWindow_finished(int result);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void send_after_second(void);

private:
    Ui::SecondWindow *ui;
    QPixmap my_pix;
    Mat src;

    bool stop_capture;
};

#endif // SECONDWINDOW_H
