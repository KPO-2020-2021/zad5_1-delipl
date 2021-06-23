/**
 * @file Transform.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief File describes class Transform which is an interface of moving and collecting spatial parameters.
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "Matrixes.hpp"

/**
 * @brief Collects position, angles (roll, pitch, Yaw) and scale of whole object. It describes every center point of Objects.
 * This interface also menages Rotation and Translation.
 */
struct Transform {
  public:
    /**
     * @brief Pinned Transform to following for this Transform.
     */
    Transform *const pinnedTransform;

    /**
     * @brief Center position.
     */
    Vector3 position;

    /**
     * @brief Orientation matrix. It has rotations by anglesRPY.
     */
    MatrixRot orientation;

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

    /**
     * @brief Apply Rotate and Translate to @p point
     * 
     * @param point point to transform.
     * @return Vector3 transformed @p point.
     */
    Vector3 UpdatePoint(Vector3 &point) const;

    /**
     * @brief Convering @p point to global Transform if this Transform is pinned.
     * 
     * @param point converting point.
     * @return Vector3 converted point
     */
    Vector3 ConvertToGlobal(Vector3 &point) const;

    /**
     * @brief Destroy the Transform object
     */
    virtual ~Transform() = 0;

    /**
     * @brief Translate position by Vector3
     * 
     * @param v Translate Vector3
     */
    void Translate(const Vector3 &v = Vector3());

    /**
     * @brief Rotate orientation by angle in the axis Vector3 (VectorX, VectorY, VectorZ)
     * 
     * @param angle Angle of rotation.
     * @param v Rotation axis.
     */
    void Rotate(const double &angle, const Vector3 &v);
};

#endif