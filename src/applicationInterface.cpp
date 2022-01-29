#include "applicationInterface.h"
#include "training.h"
#include "manageDB.h"
#include "gui.h"


#include <iostream>
#include <QPixmap>
#include <time.h>
#include <sched.h>

using namespace std;


pthread_t thManageDB;
pthread_t thProcessImage;
pthread_t thClassification;
pthread_t thTraining;
pthread_t thAcquireImage;

pthread_mutex_t mut_acquireImage = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut_resultLand = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_acquireImage = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_processImage = PTHREAD_COND_INITIALIZER;


ApplicationInterface appInterface;


ApplicationInterface::ApplicationInterface()
{
    toAcquire = false;
    toProcess = false;

}

ApplicationInterface::~ApplicationInterface()
{

}


void ApplicationInterface::init()
{

}




void* thManageDBFunc(void* arg)
{
    cout << "thread - thManageDBFunc\n";

    ManageDB manageDatabase;
    manageDatabase.database = QSqlDatabase::addDatabase("QSQLITE");
    manageDatabase.database.setDatabaseName(MY_DATABASE_PATH_U);

    if(!manageDatabase.database.open())
    {
        qDebug("cant open DATABASE");
    }


    manageDatabase.populateUserList();
    User::printUserList();

    manageDatabase.populateExerciseList();
    Exercise::printMarketExerciseList();





}





void* thClassificationFunc(void* arg)
{
    cout << "thread - thClassificationFunc\n";
}


void* thTrainingFunc(void* arg)
{
    cout << "thread - thTrainingFunc\n";
}

void* thProcessImageFunc(void* arg)
{
    cout << "thread - thProcessImageFunc\n";

    String modelTxt = "/home/luiscarlos/pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt";
    String modelBin = "/home/luiscarlos/pose/mpi/pose_iter_160000.caffemodel";
    String imageFile = "single.jpg";
    String dataset = "MPI";
    int W_in = 368;
    int H_in = 368;
    float thresh = 0.1;
    float scale  = 0.003922;
    Net net = readNet(modelBin, modelTxt);
    Mat frameCopy;


//    while(1)
//    {
////        if(appInterface.getToProcess())
////        {
////            pthread_mutex_trylock(&mut_acquireImage);  //save image to start processing
////                frameCopy = appInterface.camera.frame.clone();
////            pthread_mutex_unlock(&mut_acquireImage);

////                //calculate LandMarks
////                Mat inputBlob = blobFromImage(frameCopy, scale, Size(W_in, H_in), Scalar(0, 0, 0), false, false);
////                net.setInput(inputBlob);
////                //pthread_mutex_lock(&mut_resultLand);
////                appInterface.camera.resultLandMarks = net.forward();
////                //pthread_mutex_unlock(&mut_resultLand);
////        }
////        else
////        {
////            pthread_cond_wait(&cond_processImage, &mut_acquireImage);
////        }
//    }

}

void* thAcquireImageFunc(void* arg)
{
    float thresh = 0.1;
    int midx = 2, npairs = 20, nparts = 22;
    vector<Point> points(22);

    //time the imgage aquire
    struct timespec time_aux;


    //task infinite loop
    for(;;)
    {

        if(appInterface.getToAcquire())
        {
            time_aux.tv_sec = time(NULL);
            time_aux.tv_nsec = 100000000;           //checks every 0.1 secons



            if(appInterface.camera.isOpen())
            {
              //pthread_mutex_lock(&mut_acquireImage);
                pthread_cond_timedwait(&cond_acquireImage, &mut_acquireImage, &time_aux);
                appInterface.camera.cap >> appInterface.camera.frame;   //take picture and store it
              //pthread_mutex_unlock(&mut_acquireImage);
            }

                    pthread_mutex_lock(&mut_resultLand);
                        int H = appInterface.camera.resultLandMarks.size[2];
                        int W = appInterface.camera.resultLandMarks.size[3];
                    pthread_mutex_unlock(&mut_resultLand);


                    // Draw the position of the body parts in the Image
                    for (int n=0; n<nparts; n++)
                    {
                        // Slice heatmap of corresponding body's part.
                        pthread_mutex_lock(&mut_resultLand);
                        Mat heatMap(H, W, CV_32F, appInterface.camera.resultLandMarks.ptr(0,n));
                        pthread_mutex_unlock(&mut_resultLand);
                        // 1 maximum per heatmap
                        Point p(-1,-1),pm;
                        double conf;
                        minMaxLoc(heatMap, 0, &conf, 0, &pm);
                        if (conf > thresh)
                            p = pm;
                        points[n] = p;
                    }

                    // connect body parts and draw it !
                    float SX = float(appInterface.camera.frame.cols) / W;
                    float SY = float(appInterface.camera.frame.rows) / H;
                    for (int n=0; n<npairs; n++)
                    {
                        // lookup 2 connected body/hand parts
                        Point2f a = points[POSE_PAIRS[midx][n][0]];
                        Point2f b = points[POSE_PAIRS[midx][n][1]];

                        // we did not find enough confidence before
                        if (a.x<=0 || a.y<=0 || b.x<=0 || b.y<=0)
                            continue;

                        // scale to image size
                        a.x*=SX; a.y*=SY;
                        b.x*=SX; b.y*=SY;

                        line(appInterface.camera.frame, a, b, Scalar(0,200,0), 2);
                        circle(appInterface.camera.frame, a, 3, Scalar(0,0,200), -1);
                        circle(appInterface.camera.frame, b, 3, Scalar(0,0,200), -1);
                    }



           appInterface.startProcess();
           pthread_cond_signal(&cond_processImage);
        }
        else
        {
            appInterface.stopProcess();
            pthread_cond_wait(&cond_acquireImage, &mut_acquireImage);
        }

    }
}


bool createThreads()
{
    pthread_attr_t tattr;
    pthread_t tid;
    int ret;
    //int newprio = 20;
    sched_param param;

    /* initialized with default attributes */
    ret = pthread_attr_init (&tattr);
    /* safe to get existing scheduling param */
    ret = pthread_attr_getschedparam (&tattr, &param);
    /* set the priority; others are unchanged */
    param.sched_priority = 10;
    /* setting the new scheduling param */
    ret = pthread_attr_setschedparam (&tattr, &param);

    pthread_create(&thAcquireImage,     &tattr,   thAcquireImageFunc,     NULL);
    pthread_detach(thAcquireImage);


    /* set the priority; others are unchanged */
    param.sched_priority = 2;
    /* setting the new scheduling param */
    ret = pthread_attr_setschedparam (&tattr, &param);
    pthread_create(&thProcessImage,     &tattr,   thProcessImageFunc,     NULL);
    pthread_detach(thProcessImage);

    pthread_create(&thManageDB,         NULL,   thManageDBFunc,         NULL);
    pthread_detach(thManageDB);
    pthread_create(&thClassification,   NULL,   thClassificationFunc,   NULL);
    pthread_detach(thClassification);
    pthread_create(&thTraining,         NULL,   thTrainingFunc,         NULL);
    pthread_detach(thTraining);

    return true;
}


void ApplicationInterface::startAcquire()
{
    this->toAcquire = true;
    appInterface.camera.open();
    pthread_cond_signal(&cond_acquireImage);    //tell thread to start aquire


}

void ApplicationInterface::stopAcquire()
{
    this->toAcquire = false;
    appInterface.camera.release();
}
