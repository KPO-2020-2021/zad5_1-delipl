#include "SceneObject.hpp"



#include <fstream>

#include "Scene.hpp"
SceneObject::SceneObject(const std::string name, const Vector3 &centerPosition,
                         const Vector3 &scale, Transform *const pin) :
    Object(name, centerPosition, scale, pin) {
}

 SceneObject ::~SceneObject(){}
void SceneObject::Draw() {
    Scene::Draw(this);
}



