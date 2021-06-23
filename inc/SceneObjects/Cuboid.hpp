/**
 * @file Cuboid.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief File describes Cuboid class.
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CUBOID_HPP
#define CUBOID_HPP
#include "SceneObject.hpp"

/**
 * @brief Cuboid class which is the base of many objects on scene.
 */
class Cuboid : public SceneObject {   

  public:
    /**
     * @brief vector of pointers to vertexes of Cuboid
     */
    std::vector<Vector3 *> vertexes;

    /**
     * @brief vector of pointers to surface centers of Cuboid
     */
    std::vector<Vector3 *> centers;

    /**
     * @brief dimentions of Cuboid in every axis.
     */
    const Vector3 dimentions;

    /**
     * @brief Construct a new Cuboid object
     * 
     * @param dimentions of Cuboid in every axis.
     * @param localPosition center position of cuboid
     * @param pin Every rotation and translation for pin will be applyed on this ScaleObject. Default nullptr
     */
    Cuboid(const Vector3 &dimentions, const Vector3 &localPosition = Vector3(), Transform *const pin = nullptr);

    /**
     * @brief Destroy the Cuboid object
     */
    ~Cuboid();

    /**
     * @brief Apply rotation, scale and translation.
     */
    virtual void Update() override { this->UpdatePoints(); };

    /**
     * @brief Drones can land on Cuboids
     */
    virtual bool CanLand() override { return true; };
};
#endif // !CUBOID_HPP