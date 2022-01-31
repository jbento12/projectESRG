
#include "camera.h"


Camera::Camera()
{
    apiID = cv::CAP_ANY;
    deviceID = 0;
}

Camera::~Camera()
{
}


bool Camera::open()
{
    apiID = cv::CAP_V4L2;
    deviceID = 0;

    return cap.open(deviceID, apiID);
}

bool Camera::open(int32_t dev_id, int32_t api_id)
{
    return cap.open(dev_id, api_id);
}


void Camera::release()
{
    cap.release();
}


bool Camera::isOpen()
{
    return cap.isOpened();
}


