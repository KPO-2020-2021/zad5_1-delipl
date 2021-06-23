/**
 * @file Animation.cpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief Definitions of the Animation's methods.
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Animation.hpp"

void Animation::SetGoalPosition(const Vector3 &vec) {
    translateStep = vec - goalPosition;
    translateStep = translateStep / translateStep.Length();
    translateStep = translateStep * speed;
    goalPosition = vec;
}


void Animation::SetGoalOrientation(const double &d) {
    goalOrientation += d;
    if (this->goalOrientation >= 360)
        goalOrientation -= 360;

    rotateStep = 10;
}