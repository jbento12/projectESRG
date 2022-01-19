#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QMessageBox>
#include <QPixmap>

#include <iostream>
#include <QThread>
#include <QTimer>


//#include <opencv4/opencv2/opencv.hpp>

//#include <opencv4/opencv2/core.hpp>
//#include <opencv4/opencv2/videoio.hpp>
//#include <opencv4/opencv2/highgui.hpp>
//#include "opencv4/opencv2/imgproc/imgproc.hpp"
//#include <opencv4/opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

inline void my_delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow),
    stop_capture(false)
{
    ui->setupUi(this);


}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_SecondWindow_finished(int result)
{
    emit send_after_second();
}

//void SecondWindow::on_pushButton_clicked()
//{
//    int apiID = cv::CAP_ANY;
//    //video com o OPENVC
//    Mat frame;
//    VideoCapture cap;

//    cap.open(0, apiID);
//    if (!cap.isOpened()) {
//            cerr << "ERROR! Unable to open camera\n";
//            return;
//    }

//    cap.read(frame);

//    imwrite("my_foto.bmp", frame);
//}

/*void SecondWindow::on_pushButton_clicked()
{

    //OutputArray my_image;
    VideoCapture cap;
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
//    Mat src_aux;
    cap.open(0, apiID);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return;
    }

//    //cap.read();
//    while(1)
//    {
//        cap >> src;

////    imwrite("my_foto.bmp", src);
////    imshow(src);
//      imshow("Live", src);
//        if (waitKey(5) >= 0)
//        break;
//    }

    while(1)
    {
        cap >> src;





//    QPixmap local_pix("boas.jpeg");
//    ui->label_pic->setPixmap(local_pix);
        cvtColor(src, src, cv::COLOR_BGR2RGB);
        QPixmap local_pix(QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)));
        ui->label_pic->setPixmap(local_pix);

        my_delay(3);
    //char c=(char)waitKey(20);
//    if(c==27)
//        break;

//    while(1)
//    {
//        cap >> src;
//        //imwrite("boas.jpeg", src);
//        cvtColor(src, src, cv::COLOR_BGR2RGB);
//        ui->label_pic->setPixmap(QPixmap::fromImage(QImage(src.data,
//                 src.cols, src.rows, src.step, QImage::Format_RGB888)));
//        // imshow("Live", src);
//        //if (waitKey(5) >= 0)
//        //break;
//    }

        if(stop_capture)
        {
            stop_capture = false;
            cap.release();
            break;
        }
    }


    cout << "cheguei aqulá\n";
}
*/


void SecondWindow::on_pushButton_clicked()
{
    VideoCapture cap;

    if(!cap.open(0))
        return;

    Mat frame[5];

    for(int i=0; i<5; )
    {

        cap >> frame[i];

        if( !frame[i].empty() )
        {
            cvtColor(frame[i], frame[i], cv::COLOR_BGR2RGB);
            QPixmap local_pix(QPixmap::fromImage(QImage(frame[i].data, frame[i].cols,
                                                        frame[i].rows, frame[i].step,
                                                        QImage::Format_RGB888)));
            ui->label_pic->setPixmap(local_pix);
            i++;
        }
    }

        cout << "cheguei aqulá\n";
}



void SecondWindow::on_pushButton_2_clicked()
{
   on_SecondWindow_finished(10);
   stop_capture = true;
}

void SecondWindow::on_pushButton_3_clicked()
{
        Mat img = imread("ora_boas.jpeg", IMREAD_COLOR);

        QPixmap local_pix(QPixmap::fromImage(QImage(img.data, img.cols,
                                                    img.rows, img.step,
                                                    QImage::Format_RGB888)));
        ui->label_pic->setPixmap(local_pix);
}
