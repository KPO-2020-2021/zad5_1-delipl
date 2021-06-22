#include "Cuboid.hpp"

Cuboid::Cuboid(const Vector3 &dimentions, const Vector3 &position, Transform *const pin) :
    SceneObject("cube.dat", position, dimentions, pin),
    dimentions{dimentions} {
    for (std::size_t i = 0; i < 5; ++i) {
        this->centers.push_back(&(this->originPoints[i * 4]));
        this->vertexes.push_back(&(this->originPoints[i * 4 + 1]));
        this->vertexes.push_back(&(this->originPoints[i * 4 + 2]));
        this->centers.push_back(&(this->originPoints[i * 4 + 3]));
    }
}