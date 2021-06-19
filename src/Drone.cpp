#include "Drone.hpp"

#include "Scene.hpp"
extern bool DISPLAY;
Drone::Drone(const Vector3 &position, const Vector3 &scale) :
    Cuboid(scale, position, nullptr) {
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

    // this->rotors.push_back(Rotor(Vector3({30, -20, 0}),  this, SpinDirection_t::CounterClockwise));
    // this->rotors.push_back(Rotor(Vector3({-30, -20, 0}), this, SpinDirection_t::Clockwise));
    // this->rotors.push_back(Rotor(Vector3({-30, 20, 0}),  this, SpinDirection_t::CounterClockwise));
}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    this->Translate(this->localRotation * Vector3({1,1,1}) * length);
}
void Drone::TookOff(const double &length) {
    this->Translate(VectorZ * length);
}

void Drone::Update() {
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
    this->Rotate(angle, VectorZ);
}

void Drone::Right(const double &angle) {
    this->Rotate(-angle, VectorZ);
}
void Drone::FlyTo(const Vector3 &position, const double &height) {
    Vector3 moving = position - this->localPosition;
    // // std::cout << direction << std::endl;
    
    Vector3 direction = {cos(this->eulerAngles[0]), sin(this->eulerAngles[1]), 0};
    double angle = std::acos((direction & moving) / (moving.Length()* direction.Length() ));
    angle = angle * 180/ M_PI;
    std::cout << height << std::endl;
    std::cout << "Angle: " << angle << std::endl;

    std::cout << this->eulerAngles << std::endl;
    std::cout << position << std::endl;

    
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    this->Left(this->eulerAngles[0] - angle + 90);
    this->Update();

    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    this->TookOff(height);
    this->Update();

    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    this->Translate(moving);this->Update();

    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<int>().max(), '\n');
    this->TookOff(-height);
    this->Update();
}
void Drone::MakeRoute(const Vector3 &startPosition, const Vector3 landPosition, const double &height){
    delete this->route;
    this->route = new Route(startPosition, startPosition - landPosition, height, nullptr);
}