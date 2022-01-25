#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <opencv2/opencv.hpp>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgcodecs.hpp>

#define SHM_NAME "/smart_acqImage"


using namespace std;
using namespace cv;

struct AcquireImage
{
    bool sig_capturing;
    Mat frame;
    

    AcquireImage(){sig_capturing = false;}
    void startAquire(){this->sig_capturing = true;}
    void stopAquire(){this->sig_capturing = false;}
    bool aquire(){return sig_capturing;}
};


int main(int argc, char *argv[])
{



    
    
    return 0;
}



/*
    //-------- shared memory varibles --------
    int shmfd;
    int shm_size = 10* sizeof(AcquireImage);
    Mat frame;

    AcquireImage* acquireImage;
    


                shmfd = shm_open(SHM_NAME, O_RDWR, S_IRWXU | S_IRWXG);
                if (shmfd < 0) {
                    perror("In shm_open()");
                    exit(1);
                }

                acquireImage = (AcquireImage*)mmap(NULL, shm_size, 0, MAP_SHARED, shmfd, 0);
                if (acquireImage == NULL) {
                    perror("In mmap()");
                    exit(1);
                }

        
    imshow("Frame2", acquireImage->frame);
    waitKey(5000);
    //imwrite("my_foto.bmp", frame);
*/