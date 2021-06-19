#include "SceneObject.hpp"



#include <fstream>

#include "Scene.hpp"
SceneObject::SceneObject(const std::string name, const Vector3 &centerPosition,
                         const Vector3 &scale, Transform *const pin) :
    Object(name, centerPosition, scale, pin) {
}
void SceneObject::Draw() {
    Scene::Draw(this);
}

Route::Route(const Vector3 &startPoint, const Vector3 &finishPoint, const double &height, Transform *pin) :
    SceneObject("route.dat", startPoint, Vector3({1, 1, 1}),  pin),
    startPoint{startPoint},
    finishPoint{finishPoint},
    height{height} {
    this->originPoints[0] = Vector3();
    this->originPoints[1] = VectorZ * height;
    this->originPoints[2] = this->finishPoint *(-1) + VectorZ * height;
    this->originPoints[3] = this->finishPoint * (-1);

    this->actualPoints = this->originPoints;
    this->UpdatePoints();
}

Cuboid::Cuboid(const Vector3 &dimentions, const Vector3 &localPosition, Transform *const pin) :
    SceneObject("cube.dat", localPosition, dimentions, pin),
    dimentions{dimentions} {

    for (std::size_t i = 0; i < 5; ++i) {
        this->centers.push_back(&(this->originPoints[i * 4]));
        this->vertexes.push_back(&(this->originPoints[i * 4 + 1]));
        this->vertexes.push_back(&(this->originPoints[i * 4 + 2]));
        this->centers.push_back(&(this->originPoints[i*4+3]));

    }
}

Rotor::Rotor(const SpinDirection_t &direction, const Vector3 &localPosition, const Vector3 &scale, Transform *const pin) :
    SceneObject("prism.dat", localPosition, scale, pin),
    spinSpeed{10},
    spinDirection{direction} {}

void Rotor::Update() {
    this->Rotate(this->spinSpeed * static_cast<int>(spinDirection), VectorZ);

    // Update points
    this->UpdatePoints();
}


// std::ostream &operator<<(std::ostream &strm, const Cuboid &cub){

//     for (std::size_t i = 0; i < 4; ++i) {
//         cub.centers[0];
//         cub.vertexes[i];
//         cub.vertexes[i+1];
//         cub.centers[1];
//         if (!strm)
//             throw std::logic_error("Cannot read Object!");
//     }
//     return strm;
// }