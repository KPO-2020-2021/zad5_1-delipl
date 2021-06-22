/**
 * @file Terrain.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef Terrain_HPP
#define Terrain_HPP
#include "SceneObject.hpp"
class Terrain : public SceneObject {
  public:
    Terrain() :
        SceneObject("surface.dat", {-300, -300, 0}, {4, 4, 4}) {
    }
    void Update() override{};
    
    bool CanLand() override { return true; };
};
#endif // !Terrain_HPP