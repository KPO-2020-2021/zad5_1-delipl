#include "Drone.hpp"

#include "Scene.hpp"
extern bool DISPLAY;
Drone::Drone(const Vector3 &position, const Vector3 &scale) :
    Cuboid(scale, position, nullptr) {
    Vector3 rotorScale = scale * 10;
    auto
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise,  (*(this->vertexes[0])) + VectorZ * this->dimentions[2] , rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, (*(this->vertexes[1])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise,  (*(this->vertexes[6])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise,  (*(this->vertexes[7])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));

    // this->rotors.push_back(Rotor(Vector3({30, -20, 0}),  this, SpinDirection_t::CounterClockwise));
    // this->rotors.push_back(Rotor(Vector3({-30, -20, 0}), this, SpinDirection_t::Clockwise));
    // this->rotors.push_back(Rotor(Vector3({-30, 20, 0}),  this, SpinDirection_t::CounterClockwise));
}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    this->Translate(this->localRotation * VectorY * length);
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

void Drone::Left(const double &angle) {
    this->Rotate(angle, VectorZ);
}

void Drone::Right(const double &angle) {
    this->Rotate(-angle, VectorZ);
}
