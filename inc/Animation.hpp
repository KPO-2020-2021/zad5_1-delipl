/**
 * @file Animation.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief File includes Animation struct which has properties for animation.
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ANIMATION_HH
#define ANIMATION_HH
#include "Vectors.hpp"


/**
 * @brief Includes all properites which are nessesery to provide animation. 
 * This is a constant velocity animation.
 * It can be used as class member. Example in class @p Drone
 */
struct Animation {
    /**
     * @brief Position where @p Drone finishes its move. If it goes from {0, 0, 0} to {100, 0, 0} 
     * goalPosition takes Vector3 (100, 0, 0). Default velue is {0, 0, 0}.
     */
    Vector3 goalPosition = Vector3();

    /**
     * @brief Yaw angle of Z axis where @p Drone finishes rotation.
     * 
     */
    double goalOrientation = 0;

    /**
     * @brief Translate Vector3 targeted from position of @p Drone to @p goalPosition .
     * @p Drone will Translate by this Vector3 every frame of the animation till its @p position equals @p goalPosition .
     */
    Vector3 translateStep = Vector3();

    /**
     * @brief Angle of Rotation in the every \p Animation frame.
     */
    double rotateStep = 0;

    /**
     * @brief Forward speed of Drone.
     */
    uint8_t speed = 10;

    /**
     * @brief Setting the end drone's position of the Animation.
     * @param vec The end position of the translate Animation.
     */
    void SetGoalPosition(const Vector3 &vec);

    /**
     * @brief Setting the end drone's yaw angle.
     * @param angle The end angle of the rotate Animation.
     */
    void SetGoalOrientation(const double &angle);
};
#endif  // !ANIMATION_HH