/**
 * @file poseClassification.h
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef poseClassification__H
#define poseClassification__H

#include <cmath>
#include <vector>
#include "camera.h"

#define nParts 16

#define RSHOULDER 2
#define LSHOULDER 5
#define RELBOW 3
#define RWRIST 4
#define LELBOW 6
#define LWRIST 7
#define HEAD 0
#define NECK 1
#define RHIP 8
#define RKNEE 9
#define RANKLE 10
#define LHIP 11
#define LKNEE 12
#define LANKLE 13
#define CHEST 14
#define BACKGROUND 15

#define PI 3.14159

struct POINT2D{
    int x;
    int y;
};


class PoseClassification{



    public:
    PoseClassification();
    ~PoseClassification();

    string get_exercise_name();
    int calculateAngle();
    int attribute_score(int Angle, string exercise_name);

public:
    vector<Point> pontos;

};











#endif
