#include "Drone.hpp"

#include "Scene.hpp"
extern bool DISPLAY;
Drone::Drone(const Vector3 &position, const Vector3 &scale) :
    Cuboid(scale, position, nullptr) {
    this->eulerAngles[2] = 90;
    Vector3 rotorScale = scale * 10;
    this->route = nullptr;
    auto
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, (*(this->vertexes[0])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, (*(this->vertexes[1])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, (*(this->vertexes[6])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, (*(this->vertexes[7])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    auto moving = Vector3({cos(this->eulerAngles[2] * M_PI / 180), sin(this->eulerAngles[2] * M_PI / 180), 0});
    this->animation.SetTranslateGoal(moving*length);
}
void Drone::TookOff(const double &length) {
    this->animation.SetTranslateGoal(VectorZ * length);
}

void Drone::Update() {
    if (this->eulerAngles[2] != this->animation.goalRotation) {
        this->Rotate(this->animation.rotateStep, VectorZ);
    }
    else if(this->localPosition != this->animation.goalPosition){
        this->Translate(this->animation.translateStep);
    }
    this->UpdatePoints();
    if (DISPLAY)
        if (this->route != nullptr)
            Scene::Draw(this->route);
    for (auto &rotor : this->rotors) {
        rotor->Update();
        if (DISPLAY) {
            Scene::Draw(rotor.get());
        }
    }
}

void Drone::Draw() {
    for (auto &rotor : this->rotors)
        if (DISPLAY)
            Scene::Draw(rotor.get());

    Scene::Draw(this);
}

void Drone::Left(const double &angle) {
    this->animation.SetRotationGoal(angle);
}

void Drone::Right(const double &angle) {
    this->animation.SetRotationGoal(-angle);
}
void Drone::FlyTo(const Vector3 &position, const double &height) {
    Vector3 moving = position - this->localPosition;
    Vector3 direction = {cos(this->eulerAngles[2]), sin(this->eulerAngles[2]), 0};
    double angle = std::acos((direction & moving) / (moving.Length() * direction.Length()));
    angle = angle * 180 / M_PI;
    this->Left(this->eulerAngles[0] - angle);
    this->TookOff(height);
    this->Forward(moving.Length());
    this->TookOff(-height);
}
void Drone::MakeRoute(const Vector3 &startPosition, const Vector3 landPosition, const double &height) {
    delete this->route;
    this->route = new Route(startPosition, startPosition - landPosition, height, nullptr);
}
