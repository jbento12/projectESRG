/**
 * @file camera.cpp
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "camera.h"
#include <QDebug>
/**
 * @brief Construct a new Camera:: Camera object
 * 
 */
Camera::Camera()
{
    apiID = cv::CAP_ANY;
    deviceID = 0;

//      qDebug() << cap.get(CAP_PROP_FRAME_WIDTH);
//      qDebug() <<   cap.get(cv::CAP_PROP_FRAME_HEIGHT);
//            cap.set(CAP_PROP_FRAME_WIDTH, 600);
//            cap.set(cv::CAP_PROP_FRAME_HEIGHT, 400);
//            qDebug() << cap.get(CAP_PROP_FRAME_WIDTH);
//            qDebug() <<  cap.get(cv::CAP_PROP_FRAME_HEIGHT);
}

/**
 * @brief Destroy the Camera:: Camera object
 * 
 */
Camera::~Camera()
{
}

/**
 * @brief open
 * 
 * @return true in case it can open device 
 * @return false in case it can't open device
 */
bool Camera::open()
{
    apiID = cv::CAP_V4L2;
    deviceID = 0;

    return cap.open(deviceID, apiID);
}

/**
 * @brief 
 * 
 * @param dev_id specify which device to use 
 * @param api_id specify which video API to use
 * @return true true in case it can open device 
 * @return false false in case it can't open device
 */
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


