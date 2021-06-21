#include "Drone.hpp"

#include "Scene.hpp"
extern bool DISPLAY;
Drone::Drone(const Vector3 &position, const Vector3 &scale) :
    Cuboid(scale, position, nullptr) {
    // this->eulerAngles[2] = 90;
    // this->animation.goalRotation =
    // this->eulerAngles[2]=90;
    Vector3 rotorScale = scale * 10;
    this->route = new Route(Vector3(), Vector3(), 0, this);
    auto
        tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, (*(this->vertexes[0])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::Clockwise, (*(this->vertexes[1])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, (*(this->vertexes[6])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    tmpPtr = std::shared_ptr<Rotor>(new Rotor(SpinDirection_t::CounterClockwise, (*(this->vertexes[7])) + VectorZ * this->dimentions[2], rotorScale, this));
    this->rotors.push_back(std::move(tmpPtr));
    if (DISPLAY)
        if (this->route != nullptr)
            Scene::AddToDrawable(this->route);
    for (auto &rotor : this->rotors) {
        rotor->Update();
        if (DISPLAY) {
            Scene::AddToDrawable(rotor.get());
        }
    }
    this->Left(90);
}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    // std::cout << "KAT: " << this->eulerAngles[2] << std::endl;
    Vector3 direction = {cos(this->eulerAngles[2] * M_PI / 180), sin(this->eulerAngles[2] * M_PI / 180 ), 0};
    this->animation.SetTranslateGoal(this->localPosition + direction * length);
}
void Drone::TookOff(const double &length) {
    this->animation.SetTranslateGoal(this->localPosition + VectorZ * length);
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

bool Drone::Translated(){
    auto translateDiff = this->animation.goalPosition - this->localPosition;
    if (translateDiff.Length() > this->animation.translateStep.Length()){
        this->Translate(this->animation.translateStep);
    // std::cout << this->localPosition << "  " << translateDiff << std::endl;
    }
    else if (translateDiff.Length() <= this->animation.translateStep.Length())
    {
        this->Translate((translateDiff - this->animation.translateStep));
        this->Translate(this->animation.translateStep);
        // std::cout << this->localPosition << "  " << translateDiff << std::endl;
        return true;
    }
    return false;
}

bool Drone::Rotated(){
    auto angleDiff = this->eulerAngles[2] - this->animation.goalRotation;
    // std::cout << eulerAngles[2] << "  "<<this->animation.goalRotation << std::endl;
    if (std::fabs(angleDiff) >= this->animation.rotateStep)
    {
        if (angleDiff < 0)
            this->Rotate(this->animation.rotateStep, VectorZ);
        else if (angleDiff > 0)
            this->Rotate(-this->animation.rotateStep, VectorZ);
    }
    else if (eulerAngles[2] == this->animation.goalRotation)
    {
        return true;
    }
    else if (std::fabs(this->eulerAngles[2] - this->animation.goalRotation) <= this->animation.rotateStep)
    {
        this->Rotate(-angleDiff, VectorZ);
    }
    return false;
}

void Drone::FlyTo(const Vector3 &position, const double &height) {
    Vector3 moving = position - this->localPosition;

    // double angle = atan((position[1] - this->localPosition[1]) / (position[0] - this->localPosition[0]));
    // std::cout << "TAN = " << (position[1] - this->localPosition[1]) / (position[0] - this->localPosition[0]) << std::endl;

    // std::cout << (position & this->localPosition) / (position.Length() * this->localPosition.Length())<< ;
    // double angle = 0;
    // if(this->localPosition != Vector3())
    //     angle = acos((position & this->localPosition) / (position.Length() * this->localPosition.Length()));
    // else
    // angle = angle * 180 / M_PI;
    Vector3 direction = {cos(this->eulerAngles[2] * M_PI / 180 ), sin(this->eulerAngles[2] * M_PI / 180 ), 0};
    double inAcos = (direction[0] * moving[0] + direction[1] * moving[1]) / moving.Length();
    double angle = acos(inAcos) * 180 / M_PI;
    // this->MakeRoute(moving, height);

    std::cout << "SAVED KAT: " << this->eulerAngles[2] << " INACOS "<< inAcos << std::endl;
    std::cout << "KAT " << angle << " MOVING: "<<moving << " DIR: " << direction<< std::endl;
    this->moves.push([height, this]()
                     {
                         this->TookOff(height);});
    
    this->moves.push([angle, this]()
                     { this->Left(angle); });
    this->moves.push([moving, this]()
                     { this->Forward(moving.Length()); });
    this->moves.push([height, this]()
                     { this->TookOff(-height); });
}
void Drone::MakeRoute(const Vector3 landPosition, const double &height) {
    this->route->startPoint = Vector3();
    this->route->finishPoint = landPosition;
    this->route->height = height;
    this->route->Update();
}
void Drone::Update() {


    // std::cout << "Chce latać" << std::endl;
    if (this->Translated() && this->Rotated())
    {
        if (!this->moves.empty()){
            this->moves.front()();
            this->moves.pop();
        }
    }

    this->UpdatePoints();
    
    for (auto &rotor : this->rotors) {
        rotor->Update();
    }
}
