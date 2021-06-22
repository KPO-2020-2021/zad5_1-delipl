/**
 * @file SceneObject.hpp
 * @author Jakub Delicat
 * @brief Describes SceneObject, Route, Rotor and RotorBlades.
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
 * @brief Modeling SceneObject with shadows on every axis. Inplements collision
 * 
 */
class SceneObject : public Object {
  public:
    std::vector<Vector3> shadowX;
    std::vector<Vector3> shadowY;
    std::vector<Vector3> shadowZ;

    SceneObject(const std::string name, const Vector3 &centerPosition = Vector3(),
                const Vector3 &scale = {1, 1 ,1}, Transform *const pin= nullptr);

    virtual ~SceneObject();

    void UpdateShadows();
    bool IsOverlapping(const SceneObject &obj);

    virtual void Update() = 0;

    virtual bool CanLand() = 0;

    virtual void Draw();
};

#endif  // !SCENEOBJECT_HPP

