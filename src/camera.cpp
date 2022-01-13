
#include "camera.h"


// camera::camera()
// {
//     int apiID = cv::CAP_ANY;
//     device = 0;

//     cap.open()
// }

// camera::camera()


//   // Check if camera opened successfully
//   if(!cap.isOpened()){

//     cout << "Error opening video stream or file" << endl;

//     return -1;

//   }



// using namespace std;
// using namespace cv;

// int counter;
// int main(){

//   // Create a VideoCapture object and open the input file
//   // If the input is the web camera, pass 0 instead of the video file name
//   VideoCapture cap(0); 
   
//   // Check if camera opened successfully
//   if(!cap.isOpened()){
//     cout << "Error opening video stream or file" << endl;
//     return -1;
//     counter = 0;
//   }
	
//   while(1){

//     // string path ="home/bento/Desktop/Project_ESRG/Smart_Fitness_Mirror/code/images/";
//     string file = "images/image";
//     Mat frame;

//     // // Capture frame-by-frame
//     // cap >> frame;
 
//     // // If the frame is empty, break immediately
//     // if (frame.empty())
//     //   break;

//      cap.read(frame);
//     if (frame.empty())
//     cout << "frame is empty";
//       break;

//     file.append(to_string(counter));
//     file.append(".jpg");
//     // path.append(file);
//     counter ++;
//     // Display the resulting frame
//     imshow( "Frame", frame );
//     imwrite(file, frame);

//     // Press  ESC on keyboard to exit
//     char c=(char)waitKey(25);
//     if(c==27)
//       break;

 
//   // When everything done, release the video capture object
//   cap.release();

//   // Closes all the frames
//   destroyAllWindows();
	
//   return 0;
// }

//  system("rm images/*");

// }

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
// #include <opencv2/opencv_modules.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap(0);
 

 
  int counter;
  counter = 0;
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  while(1){

    string file = "images/image";
    Mat frame;

    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    file.append(to_string(counter));
    file.append(".jpg");


    // path.append(file);
    counter ++;
    // Display the resulting frame
    imshow( "Frame", frame );
    imwrite(file, frame);
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }

    system("rm images/*");

  // When everything done, release the video capture object
  cap.release();


  // Closes all the frames
  destroyAllWindows();

  return 0;
}
                  


