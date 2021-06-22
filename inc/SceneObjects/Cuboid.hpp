/**
 * @file Cuboid.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CUBOID_HPP
#define CUBOID_HPP
#include "SceneObject.hpp"

class Cuboid : public SceneObject {
  protected:
    std::vector<Vector3 *> vertexes;
    
    std::vector<Vector3 *> centers;

  public:
    const Vector3 dimentions;

    Cuboid(const Vector3 &dimentions, const Vector3 &localPositio = Vector3(), Transform *const pin = nullptr);
    
    virtual void Update() override{};

    virtual bool CanLand() override { return true; };
};
#endif // !CUBOID_HPP