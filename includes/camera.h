#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/opencv.hpp"
#include <string>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <stdint.h>

#include <iostream>

using namespace std;
using namespace cv;


class Camera
{


public:
    Camera();
    ~Camera();

    bool open();
    bool open(int32_t dev_id, int32_t api_id);
    void release();

    bool isOpen();

private:
    string dev_name;
    int32_t apiID;
    int32_t deviceID;
    VideoCapture cap;

    Mat frame;



//    char* shmptr;
//    int device;
//    sem_t *shmsem;
};













#endif //CAMERA_H
