#include "applicationInterface.h"
#include "training.h"
#include "manageDB.h"
#include "gui.h"

#include <iostream>
#include <QPixmap>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include "macros.h"

#ifdef MY_ARCH_PC
#define MODEL_TXT "/home/luiscarlos/pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt"
#define MODEL_BIN "/home/luiscarlos/pose/mpi/pose_iter_160000.caffemodel"
#else
#define MODEL_TXT "/etc/pose/mpi/pose_deploy_linevec_faster_4_stages.prototxt"
#define MODEL_BIN "/etc/pose/mpi/pose_iter_160000.caffemodel"
#endif

uint64_t increDebug = 0;

using namespace std;

//pthread_t thManageDB;
//pthread_t thProcessImage;
//pthread_t thClassification;
//pthread_t thTraining;
//pthread_t thAcquireImage;

pthread_mutex_t mut_acquireImage;
pthread_mutex_t mut_processImage;
pthread_mutex_t mut_resultLand;
pthread_mutex_t mut_frame;

pthread_cond_t cond_acquireImage;
pthread_cond_t cond_processImage;

ApplicationInterface appInterface;

/**
 * @brief Construct a new Application Interface:: Application Interface object
 * 
 */
ApplicationInterface::ApplicationInterface()
{
    toAcquire = false;
    toProcess = false;
}


/**
 * @brief Destroy the Application Interface:: Application Interface object
 * 
 * 
 */
ApplicationInterface::~ApplicationInterface()
{
}

/**
 * @brief 
 * 
 */
void ApplicationInterface::init()
{
    //    camera.cap.set ( CV_CAP_PROP_FRAME_WIDTH , 640) ;
    //    camera.cap.set ( CV_CAP_PROP_FRAME_HEIGHT , 480) ;
    //    camera.cap.set ( CV_CAP_PROP_BRIGHTNESS , 100) ;
    //    camera.cap.set ( CV_CAP_PROP_EXPOSURE , 100) ;
    //    camera.cap.set ( CV_CAP_PROP_CONTRAST , 100) ;
    //    camera.cap.set ( CV_CAP_PROP_SATURATION , 100) ;
}

/**
 * @brief 
 * 
 */
void ApplicationInterface::startAcquire()
{
    this->toAcquire = true;
    this->camera.open();
    pthread_cond_signal(&cond_acquireImage); //tell thread to start aquire
}

/**
 * @brief 
 * 
 */
void ApplicationInterface::stopAcquire()
{
    this->toAcquire = false;
    this->camera.release();
}


/**
 * @brief 
 * 
 * @param arg 
 * @return void* 
 */
void* ApplicationInterface::thManageDBFunc(void *arg)
{
    cout << "thread - thManageDBFunc\n";

    ManageDB manageDatabase;
    manageDatabase.database = QSqlDatabase::addDatabase("QSQLITE");
    manageDatabase.database.setDatabaseName(MY_DATABASE_PATH_U);

    if (!manageDatabase.database.open())
    {
        qDebug("cant open DATABASE");
    }

    manageDatabase.populateUserList();
    User::printUserList();

    manageDatabase.populateExerciseList();
    Exercise::printMarketExerciseList();
}

/**
 * @brief 
 * 
 * @param arg 
 * @return void* 
 */
void* ApplicationInterface::thClassificationFunc(void *arg)
{
    cout << "thread - thClassificationFunc\n";
}

/**
 * @brief 
 * 
 * @param arg 
 * @return void* 
 */
void* ApplicationInterface::thTrainingFunc(void *arg)
{
    cout << "thread - thTrainingFunc\n";

    mqd_t msgq_id;
    int mq_recv_ret;
    char buffer[MAX_MSG_LEN];
    unsigned int m_prio = MSG_PRIO;
    unsigned int msg_num = 0;

    /* opening the queue using default attributes  --  mq_open() */
    msgq_id = mq_open(MSGQOBJ_NAME, O_RDWR | O_CREAT , S_IRWXU | S_IRWXG, NULL);
    if (msgq_id == (mqd_t)-1) {
        perror("In mq_open()");
        exit(1);
    }

    while(1)
    {
        mq_recv_ret = mq_receive(msgq_id, buffer, MAX_MSG_LEN, NULL);
        if (mq_recv_ret == -1) {
            perror("In mq_receive()");
            exit(1);
        }

        cout << buffer << " - " << mq_recv_ret << endl;
//        printf("%s - %d", buffer, mq_recv_ret);

    }
}

/**
 * @brief thread responssible to process the most recent frame sample
 * 
 * @param arg 
 * @return void* 
 */
void* ApplicationInterface::thProcessImageFunc(void *arg)
{
    cout << "thread - thProcessImageFunc\n";
    String modelTxt = MODEL_TXT;
    String modelBin = MODEL_BIN;
    String imageFile = "single.jpg";
    String dataset = "MPI";
//    int W_in = 368;
//    int H_in = 368;
#ifdef MY_ARCH_PC
    int W_in = 128;
    int H_in = 72;
#else
    int W_in = 100;
    int H_in = 75;
#endif

    float thresh = 0.1;
//    float scale = 0.003922;
    float scale = 0.001;
    Net net = readNet(modelBin, modelTxt);
//    Net net = cv::dnn::readNetFromONNX("/home/luiscarlos/pose/poseEstimationModel.onnx");

    Mat frameCopy;
    Mat landMarks;

    cout << "thread - thProcessImageFunc 22222222222222222\n";
    //task infinite loop
    while (1)
    {
        if (appInterface.getToProcess())
        {
            pthread_mutex_lock(&mut_frame); //save image to start processing    most recent frame
            frameCopy = appInterface.camera.frame.clone();
            pthread_mutex_unlock(&mut_frame);

            //calculate LandMarks
            Mat inputBlob = blobFromImage(frameCopy, scale, Size(W_in, H_in), Scalar(0, 0, 0), false, false);
            net.setInput(inputBlob);
            landMarks = net.forward();
            qDebug() << "Calculo das LANDMARKS completo\n";
            pthread_mutex_lock(&mut_resultLand);
            appInterface.camera.resultLandMarks = landMarks.clone();
            pthread_mutex_unlock(&mut_resultLand);
//        }
//        else
//        {
            pthread_cond_wait(&cond_processImage, &mut_processImage);
        }
    }
}

/**
 * @brief thread responsible to capture a frame every sample period
 *
 * @param arg N/D
 * @return void*
 */
void* ApplicationInterface::thAcquireImageFunc(void *arg)
{
    float thresh = 0.1;
    int midx = 1, npairs = 14, nparts = 16;
    vector<Point> points(22);

    //time the imgage aquire
    struct timespec time_aux;

    cout << "THREAD - thAcquireImageFunc\n";

    while (1)
    {
        if (appInterface.getToAcquire())
        {

            if (appInterface.camera.isOpen())
            {
                pthread_mutex_lock(&mut_frame);
                appInterface.camera.cap >> appInterface.camera.frame; //take picture and store it
                cv::cvtColor(appInterface.camera.frame, appInterface.camera.frame,   cv::COLOR_BGR2RGB );    //change to RGB
                pthread_mutex_unlock(&mut_frame);
            }

            pthread_mutex_lock(&mut_resultLand);
            int H = appInterface.camera.resultLandMarks.size[2];
            int W = appInterface.camera.resultLandMarks.size[3];
//            pthread_mutex_unlock(&mut_resultLand);

            // Draw the position of the body parts in the Image
            for (int n = 0; n < nparts; n++)
            {
                // Slice heatmap of corresponding body's part.
//                pthread_mutex_lock(&mut_resultLand);
                Mat heatMap(H, W, CV_32F, appInterface.camera.resultLandMarks.ptr(0, n));
//                pthread_mutex_unlock(&mut_resultLand);
                // 1 maximum per heatmap
                Point p(-1, -1), pm;
                double conf;
                minMaxLoc(heatMap, 0, &conf, 0, &pm);
                if (conf > thresh)
                    p = pm;
                points[n] = p;
            }
            pthread_mutex_unlock(&mut_resultLand);

            // connect body parts and draw it !
            float SX = float(appInterface.camera.frame.cols) / W;
            float SY = float(appInterface.camera.frame.rows) / H;
            for (int n = 0; n < npairs; n++)
            {
                // lookup 2 connected body/hand parts
                Point2f a = points[POSE_PAIRS[midx][n][0]];
                Point2f b = points[POSE_PAIRS[midx][n][1]];

                // we did not find enough confidence before
                if (a.x <= 0 || a.y <= 0 || b.x <= 0 || b.y <= 0)
                    continue;

                // scale to image size
                a.x *= SX;
                a.y *= SY;
                b.x *= SX;
                b.y *= SY;

                line(appInterface.camera.frame, a, b, Scalar(0, 200, 0), 3);
                circle(appInterface.camera.frame, a, 6, Scalar(0, 0, 200), -1);
                circle(appInterface.camera.frame, b, 6, Scalar(0, 0, 200), -1);
            }


            appInterface.startProcess();
            pthread_cond_signal(&cond_processImage);

            usleep(100000);
        }
        else
        {
            appInterface.stopProcess();
            pthread_cond_wait(&cond_acquireImage, &mut_acquireImage);
        }
    }
}

/**
 * @brief Create a Threads object
 * 
 * @return true 
 * @return false 
 */
bool ApplicationInterface::createThreads()
{
    pthread_attr_t tattr;
    pthread_t tid;
    int ret;
    //int newprio = 20;
    sched_param param;

    pthread_mutex_init(&mut_acquireImage, NULL);
    pthread_mutex_init(&mut_resultLand, NULL);
    pthread_mutex_init(&mut_frame, NULL);
    pthread_mutex_init(&mut_processImage, NULL);

    pthread_cond_init(&cond_acquireImage, NULL);
    pthread_cond_init(&cond_processImage, NULL);

    ret = pthread_attr_init(&tattr);

    //    ret = pthread_attr_getschedparam (&tattr, &param);

    /* setting the new scheduling param */

    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    param.sched_priority = 0;
    ret = pthread_attr_setschedparam(&tattr, &param);

    pthread_create(&thAcquireImage, &tattr, thAcquireImageFunc, NULL);
    //pthread_detach(thAcquireImage);

    /* set the priority; others are unchanged */
    param.sched_priority = 75;
    /* setting the new scheduling param */
    ret = pthread_attr_setschedparam(&tattr, &param);
    pthread_create(&thProcessImage, &tattr, thProcessImageFunc, NULL);
    //pthread_detach(thProcessImage);

    pthread_create(&thManageDB, NULL, thManageDBFunc, NULL);
    // pthread_detach(thManageDB);
    pthread_create(&thClassification, NULL, thClassificationFunc, NULL);
    //    pthread_detach(thClassification);
    pthread_create(&thTraining, NULL, thTrainingFunc, NULL);
    //    pthread_detach(thTraining);

    return true;
}
