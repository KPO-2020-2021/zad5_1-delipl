#include "Drone.hpp"

#include "Scene.hpp"

Drone::Drone(const Vector3 &position, const Vector3 &scale) :
    Cuboid(scale * 10 + VectorY * scale[0] * 10, position, nullptr) {


        

        auto 
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, *(this->vertexes[0])+ VectorZ*this->dimentions[2]/2, scale*20 - VectorZ*10, this));
        this->rotors.push_back(std::move(tmpPtr));
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, *(this->vertexes[1]) + VectorZ * this->dimentions[2] / 2, scale * 20 - VectorZ * 10, this));
        this->rotors.push_back(std::move(tmpPtr));
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, *(this->vertexes[6]) + VectorZ * this->dimentions[2] / 2, scale * 20 - VectorZ * 10, this));
        this->rotors.push_back(std::move(tmpPtr));
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, *(this->vertexes[7]) + VectorZ * this->dimentions[2] / 2, scale * 20 - VectorZ * 10, this));
        this->rotors.push_back(std::move(tmpPtr));

        std::cout << this->dimentions << std::endl;
        auto tmpPtr2 = std::shared_ptr<Cuboid>(new Cuboid({3, 3, 5}, {this->dimentions[0]/3, -this->dimentions[1], 0}, this));
        this->eyes.push_back(std::move(tmpPtr2));
         tmpPtr2 = std::shared_ptr<Cuboid>(new Cuboid({3, 3, 5}, {-this->dimentions[0]/3, -this->dimentions[1], 0}, this));
        this->eyes.push_back(std::move(tmpPtr2));

        // this->rotors.push_back(Rotor(Vector3({30, -20, 0}),  this, SpinDirection_t::CounterClockwise));
        // this->rotors.push_back(Rotor(Vector3({-30, -20, 0}), this, SpinDirection_t::Clockwise));
        // this->rotors.push_back(Rotor(Vector3({-30, 20, 0}),  this, SpinDirection_t::CounterClockwise));
}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    this->Translate(this->localRotation * Vector3({1, 1, 1}) * length);
}

void Drone::Update() {
    for (auto &rotor : this->rotors) {
        rotor->Update();
        Scene::Draw(rotor.get());
    }
    this->UpdatePoints();
}

void Drone::Draw() {
    for (auto &rotor : this->rotors)
        Scene::Draw(rotor.get());
    for (auto &eye : this->eyes)
        Scene::Draw(eye.get());
    Scene::Draw(this);
}