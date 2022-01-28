#include "applicationInterface.h"
#include "training.h"
#include "manageDB.h"
#include "gui.h"


#include <iostream>
#include <QPixmap>


using namespace std;


pthread_t thManageDB;
pthread_t thProcessImage;
pthread_t thClassification;
pthread_t thTraining;
pthread_t thAcquireImage;

pthread_mutex_t mut_acquireImage = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_acquireImage = PTHREAD_COND_INITIALIZER;



ApplicationInterface appInterface;


ApplicationInterface::ApplicationInterface()
{
    toAcquire = false;

}

ApplicationInterface::~ApplicationInterface()
{

}


void ApplicationInterface::init()
{
//    pthread_mutex_init(&mut_acquireImage, NULL);

//    this->mut_acquireImage = PTHREAD_MUTEX_INITIALIZER;
//    this->cond_acquireImage = PTHREAD_COND_INITIALIZER;
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


void* thProcessImageFunc(void* arg)
{
    cout << "thread - thProcessImageFunc\n";
//    String modelTxt = "/home/luiscarlos/pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt";
//    String modelBin = "/home/luiscarlos/pose/mpi/pose_iter_160000.caffemodel";
//    String imageFile = "single.jpg";
//    String dataset = "MPI";
//    int W_in = 368;
//    int H_in = 368;
//    float thresh = 0.1;
//    float scale  = 0.003922;
//    int midx = 2, npairs = 20, nparts = 22;
//    Net net = readNet(modelBin, modelTxt);
//    vector<Point> points(22);
//                Mat inputBlob = blobFromImage(appInterface.camera.frame, scale, Size(W_in, H_in), Scalar(0, 0, 0), false, false);
//                net.setInput(inputBlob);
//                Mat result = net.forward();


//                int H = result.size[2];
//                int W = result.size[3];

//                // find the position of the body parts

//                for (int n=0; n<nparts; n++)
//                {
//                    // Slice heatmap of corresponding body's part.
//                    Mat heatMap(H, W, CV_32F, result.ptr(0,n));
//                    // 1 maximum per heatmap
//                    Point p(-1,-1),pm;
//                    double conf;
//                    minMaxLoc(heatMap, 0, &conf, 0, &pm);
//                    if (conf > thresh)
//                        p = pm;
//                    points[n] = p;
//                }

//                // connect body parts and draw it !
//                float SX = float(appInterface.camera.frame.cols) / W;
//                float SY = float(appInterface.camera.frame.rows) / H;
//                for (int n=0; n<npairs; n++)
//                {
//                    // lookup 2 connected body/hand parts
//                    Point2f a = points[POSE_PAIRS[midx][n][0]];
//                    Point2f b = points[POSE_PAIRS[midx][n][1]];

//                    // we did not find enough confidence before
//                    if (a.x<=0 || a.y<=0 || b.x<=0 || b.y<=0)
//                        continue;

//                    // scale to image size
//                    a.x*=SX; a.y*=SY;
//                    b.x*=SX; b.y*=SY;

//                    line(appInterface.camera.frame, a, b, Scalar(0,200,0), 2);
//                    circle(appInterface.camera.frame, a, 3, Scalar(0,0,200), -1);
//                    circle(appInterface.camera.frame, b, 3, Scalar(0,0,200), -1);
//                }


}


void* thClassificationFunc(void* arg)
{
    cout << "thread - thClassificationFunc\n";
}


void* thTrainingFunc(void* arg)
{
    cout << "thread - thTrainingFunc\n";
}


void* thAcquireImageFunc(void* arg)
{

    //task infinite loop
    for(;;)
    {
        pthread_mutex_lock(&mut_acquireImage);

        if(appInterface.getToAcquire())
        {
            if(appInterface.camera.isOpen())
                appInterface.camera.cap >> appInterface.camera.frame;


            //store image with landmarks in frameDisplay (image to display)
            appInterface.camera.frameDisplay = appInterface.camera.frame.clone();


        }
        else
        {
            pthread_cond_wait(&cond_acquireImage, &mut_acquireImage);
        }
        pthread_mutex_unlock(&mut_acquireImage);
    }
}


bool createThreads()
{
    pthread_create(&thManageDB,         NULL,   thManageDBFunc,         NULL);
    pthread_detach(thManageDB);
    pthread_create(&thProcessImage,     NULL,   thProcessImageFunc,     NULL);
    pthread_detach(thProcessImage);
    pthread_create(&thClassification,   NULL,   thClassificationFunc,   NULL);
    pthread_detach(thClassification);
    pthread_create(&thTraining,         NULL,   thTrainingFunc,         NULL);
    pthread_detach(thTraining);
    pthread_create(&thAcquireImage,     NULL,   thAcquireImageFunc,     NULL);
    pthread_detach(thAcquireImage);
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
    this->toAcquire = true;
    appInterface.camera.release();
}
