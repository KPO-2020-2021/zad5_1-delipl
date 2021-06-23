/**
 * @file SceneObject.hpp
 * @author Jakub Delicat
 * @brief Describes SceneObject which can be displayed in GNUPlot. 
 * @version 0.1
 * @date 2021-06-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP


#include "Object.hpp"

/**
 * @brief Modeling SceneObject with collider shadows on every axis. Inplements collisions 
 */
class SceneObject : public Object {
  public:
    /**
     * @brief Collision shadow on the Y Z plane.
     */
    std::vector<Vector3> shadowX;

    /**
     * @brief Collision shadow on the X Z plane.
     */
    std::vector<Vector3> shadowY;

    /**
     * @brief Collision shadow on the Y X plane.
     */
    std::vector<Vector3> shadowZ;

    /**
     * @brief Construct a new Scene Object object
     * 
     * @param name Name of SceneObject and .dat file.
     * @param centerPosition Position of SceneObject.
     * @param scale Scale of SceneObject.
     * @param pin Every rotation and translation for pin will be applyed on this ScaleObject. Default nullptr
     */
    SceneObject(const std::string name, const Vector3 &centerPosition = Vector3(),
                const Vector3 &scale = {1, 1 ,1}, Transform *const pin= nullptr);

    /**
     * @brief Destroy the Scene Object object
     */
    virtual ~SceneObject();

    /**
     * @brief Update XYZ shadows.
     */
    void UpdateShadows();

    /**
     * @brief Check if this shadows are overlapping with another SceneObject.
     * 
     * @param obj SceneObjcet to check if is overlapping with this SceneObject.
     * @return true if they are overlapping.
     * @return false 
     */
    bool IsOverlapping(const SceneObject &obj);

    /**
     * @brief Abstract method for use in every frame of the Animation.
     */
    virtual void Update() = 0;

    /**
     * @brief Abstact method specifying if Drone can land on this SceneObject.
     * 
     * @return true 
     * @return false 
     */
    virtual bool CanLand() = 0;

    /**
     * @brief One time draw SceneObject. If there is not any GNUPlot window this will create it.
     */
    virtual void Draw();
};

#endif  // !SCENEOBJECT_HPP

