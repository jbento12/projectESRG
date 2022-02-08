/**
 * @file poseClassification.cpp
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "poseClassification.h"
#include "camera.h"


PoseClassification::PoseClassification()
{


}

PoseClassification::~PoseClassification()
{


}



int PoseClassification::calculateAngle(){

//    struct POINT2D ab;
//    struct POINT2D cb;


//    /*  Calculate right arm angle  */

//    Point a, b, c;



//    a = pontos[RWRIST];
//    b = pontos[RELBOW];
//    c = pontos[RSHOULDER];

//    ab.x= b.x - a.x;
//    ab.y =b.y - a.y ;

//    cb.x = b.x - c.x;
//    cb.y = b.y - c.y ;

//    int dot = (ab.x * cb.x + ab.y * cb.y); // dot product
//    int cross = (ab.x * cb.y - ab.y * cb.x); // cross product

//    float alpha = atan2(cross, dot);

//    return (int) floor(alpha * 180. / PI + 0.5);

}

int32_t PoseClassification::scoreCalculation(string name)
{
    return 51;
}
