#include "Rotor.hpp"

Rotor::Rotor(const SpinDirection_t &direction, const Vector3 &position, const Vector3 &scale, Transform *const pin) :
    SceneObject("prism.dat", position, scale, pin),
    spinSpeed{100},
    spinDirection{direction} {}

Rotor::~Rotor(){}

void Rotor::Update() {
    this->Rotate(this->spinSpeed * static_cast<int>(spinDirection), VectorZ);
    this->UpdatePoints();
}
