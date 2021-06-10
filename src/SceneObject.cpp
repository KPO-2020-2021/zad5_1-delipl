#include "SceneObject.hpp"

#include <fstream>

Route::Route(const Vector3 &startPoint, const Vector3 &finishPoint, const double &height) :
    Object("route.dat", Vector3(), Vector3({1, 1, 1}), nullptr),
    startPoint{startPoint},
    finishPoint{finishPoint},
    height{height} {

    this->originPoints[0] = this->startPoint;
    this->originPoints[1] = this->startPoint  + VectorZ * height;
    this->originPoints[2] = this->finishPoint + VectorZ * height;
    this->originPoints[3] = this->finishPoint;

    this->actualPoints = this->originPoints;
}

Rotor::Rotor(const Vector3 &localPosition, const std::shared_ptr<Transform> &pin, const SpinDirection_t &spinDirection) :
    Object("prism.dat", localPosition, Vector3({1,1,1}), (pin)),
    spinDirection{spinDirection} {
}

void Rotor::Update() {
    this->Rotate(this->spinSpeed, VectorZ);

    // Update points
    this->UpdatePoints();
}

SceneObject::SceneObject(const std::string name, const Vector3 &centerPosition,
                       const Vector3 &scale, const std::shared_ptr<Transform> &pin) :
    Object(name, centerPosition, scale, pin) {
        
}

SceneObject::UpdateShadows(){
   
}