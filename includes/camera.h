#ifndef camera__H
#define camera__H

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
#include <stdio.h>

using namespace std;
using namespace cv;

class camera
{
    private: 
    
    char* shmptr;
    int device;
    sem_t *shmsem;


    public:
    camera();
    ~camera();
    




};













#endif