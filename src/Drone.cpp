#include "Drone.hpp"

#include "Scene.hpp"
extern bool DISPLAY ;
Drone::Drone(const Vector3 &position, const Vector3 &scale) :
    Cuboid(scale * 10 + VectorY * scale[0] * 10, position, nullptr) {
    auto
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, this->scale * (*(this->vertexes[0])) + VectorZ * this->dimentions[2] / 2, scale * 20 - VectorZ * 10, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, this->scale * (*(this->vertexes[1])) + VectorZ * this->dimentions[2] / 2, scale * 20 - VectorZ * 10, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, this->scale * (*(this->vertexes[6])) + VectorZ * this->dimentions[2] / 2, scale * 20 - VectorZ * 10, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, this->scale * (*(this->vertexes[7])) + VectorZ * this->dimentions[2] / 2, scale * 20 - VectorZ * 10, this));
    this->rotors.push_back(std::move(tmpPtr));

    // this->rotors.push_back(Rotor(Vector3({30, -20, 0}),  this, SpinDirection_t::CounterClockwise));
    // this->rotors.push_back(Rotor(Vector3({-30, -20, 0}), this, SpinDirection_t::Clockwise));
    // this->rotors.push_back(Rotor(Vector3({-30, 20, 0}),  this, SpinDirection_t::CounterClockwise));
}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    this->Translate(this->localRotation * VectorY* length);
}
void Drone::TookOff(const double &length) {
    this->Translate(VectorZ * length);
}

void Drone::Update() {
    this->UpdatePoints();
    for (auto &rotor : this->rotors) {
        rotor->Update();
        if (DISPLAY)
            Scene::Draw(rotor.get());
    }
}

void Drone::Draw() {
    for (auto &rotor : this->rotors)
        if (DISPLAY)
            Scene::Draw(rotor.get());

    Scene::Draw(this);
}