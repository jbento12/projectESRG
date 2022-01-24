#include <iostream>
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
    AcquireImage(){sig_capturing = false;}
    void startAquire(){this->sig_capturing = true;}
    void stopAquire(){this->sig_capturing = false;}
    bool aquire(){return sig_capturing;}

    Mat frame;
private:
    bool sig_capturing;
};


int main()
{
    
    //-------- shared memory varibles --------
    int shmfd;
    int shm_size = sizeof(AcquireImage);
    AcquireImage* acquireImage;
    
    //-------- camera varibles -----------
    VideoCapture cap;
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API

    shmfd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
    if (shmfd < 0) {
        perror("In shm_open()");
        exit(1);
    }
    ftruncate(shmfd, shm_size);
    acquireImage = (AcquireImage*)mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (acquireImage == NULL) {
        perror("In mmap()");
        exit(1);
    }


    //open object
    cap.open(deviceID, apiID);
    if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
    }


    cap >> acquireImage->frame;


    // Capture frame-by-frame
    
    if (acquireImage->frame.empty())
        return -1;

    

    

    
    
    return 0;
}


/*

VideoCapture cap(0); 
   
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	
  while(1){

    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Display the resulting frame
    imshow( "Frame", frame );

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
  */


/*

// open selected camera using selected API
cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    
     //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    

        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
        }


        imwrite("my_foto.bmp", frame);

    
    cout << "terminou a leitura\n";
    
    //imwritemulti("my_foto.bmp", frame);

*/