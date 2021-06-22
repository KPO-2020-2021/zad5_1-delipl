/**
 * @file Animation.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ANIMATION_HH
#define ANIMATION_HH
#include "Vectors.hpp"

struct Animation {
    Vector3 goalPosition = Vector3();

    double goalRotation = 0;

    Vector3 translateStep = Vector3();

    double rotateStep = 0;

    uint8_t speed = 10;

    void SetPositionGoal(const Vector3 &vec);

    void SetOrientationGoal(const double &d);
};
#endif  // !ANIMATION_HH