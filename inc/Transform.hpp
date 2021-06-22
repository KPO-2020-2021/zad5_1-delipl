/**
 * @file Transform.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "Matrixes.hpp"
/**
 * @brief Collects position, anglesRPY and scale of whole object. 
 */
struct Transform {
  public:
    /**
     * @brief Pinned Transform
     */
    Transform *const pinnedTransform;

    /**
     * @brief Center local Position
     */
    Vector3 position;

    /**
     * @brief Local Rotation Matrix
     */
    MatrixRot localRotation;

    /**
     * @brief anglesRPY in 3 axis anglesRPY[0] - roll, anglesRPY[1] - pitch, 
     * anglesRPY[2] - yall
     */
    Vector3 anglesRPY;

    /**
     * @brief Scale as a unit matrix
     */
    MatrixRot scale;

    /**
     * @brief Construct a new Transform object
     */
    Transform(Transform *const &pin = nullptr);

    Vector3 UpdatePoint(Vector3 &point) const;

    Vector3 ConvertToPinned(Vector3 &point) const;

    virtual ~Transform();

    void Translate(const Vector3 &v = Vector3());

    void Rotate(const double &angle, const Vector3 &v);
};

#endif