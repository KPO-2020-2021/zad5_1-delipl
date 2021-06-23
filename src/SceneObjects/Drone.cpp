#include "Drone.hpp"

#include "Scene.hpp"
extern bool DISPLAY;
Drone::Drone(const Vector3 &position, const Vector3 &scale) :
    Cuboid(scale, position, nullptr) {

    this->directionVec = {cos(0), sin(0), 0};
    this->animation.goalRotation = 0;
    this->anglesRPY[2] = this->animation.goalRotation;
    Vector3 rotorScale = scale * 10;
    this->route = std::make_shared<Route>(Vector3(), Vector3(), 0, nullptr);
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
            Scene::AddToDrawable(this->route.get());
    for (auto &rotor : this->rotors) {
        rotor->Update();
        if (DISPLAY) {
            Scene::AddToDrawable(rotor.get());
        }
    }
 
    this->Left(0);

}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    // std::cout << "KAT: " << this->anglesRPY[2] << std::endl;
    // Vector3 direction = {cos(this->anglesRPY[2] * M_PI / 180), sin(this->anglesRPY[2] * M_PI / 180 ), 0};
    this->animation.SetPositionGoal(this->position + this->directionVec * length);
}
void Drone::TookOff(const double &length) {
    this->animation.SetPositionGoal(this->position + VectorZ * length);
}


void Drone::Draw() {
    for (auto &rotor : this->rotors)
        if (DISPLAY)
            Scene::Draw(rotor.get());

    Scene::Draw(this);
}

void Drone::Left(const double &angle) {
    this->animation.SetOrientationGoal(angle);
}

void Drone::Right(const double &angle) {
    this->animation.SetOrientationGoal(-angle);
}

bool Drone::Translated(){
    auto translateDiff = this->animation.goalPosition - this->position;
    // std::cout << this->position.Length() << "  " << translateDiff.Length() << std::endl;
    if (translateDiff.Length() > this->animation.translateStep.Length()){
        this->Translate(this->animation.translateStep);
    }
    else if (translateDiff.Length() <= this->animation.translateStep.Length())
    {
        this->Translate((translateDiff - this->animation.translateStep));
        this->Translate(this->animation.translateStep);

        // std::cout << this->position << "  " << translateDiff << std::endl;
        return true;
    }
    return false;
}

bool Drone::Rotated(){
    auto angleDiff = this->anglesRPY[2] - this->animation.goalRotation;
    //  std::cout << anglesRPY[2] << "  "<<this->animation.goalRotation << std::endl;
    if (std::fabs(angleDiff) >= this->animation.rotateStep)
    {
        if (angleDiff < 0)
            this->Rotate(this->animation.rotateStep, VectorZ);
        else if (angleDiff > 0)
            this->Rotate(-this->animation.rotateStep, VectorZ);
    }
    else if (anglesRPY[2] == this->animation.goalRotation)
    {
        return true;
    }
    else if (std::fabs(this->anglesRPY[2] - this->animation.goalRotation) <= this->animation.rotateStep)
    {
        this->Rotate(-angleDiff, VectorZ);
    }

    this->directionVec = {cos(this->anglesRPY[2] * M_PI / 180), sin(this->anglesRPY[2] * M_PI / 180), 0};

    return false;
}

// TO DO PID
void Drone::FlyTo(const Vector3 &position, const double &height) {
    Vector3 moving = this->position*(-1) + position;
    double inAcos = (this->directionVec[0] * moving[0] + this->directionVec[1] * moving[1]) / moving.Length();
    if(inAcos <= -1)
        inAcos += 1;
    else if (inAcos >= 1)
        inAcos -= 1;
        
    double angle = acos(inAcos) * 180 / M_PI;

    // this->MakeRoute(position, height);
    this->moves.push([height, this]()
                     {
                         this->TookOff(height);});
    
    this->moves.push([angle, this]()
                     { this->Right(angle); });
    this->moves.push([moving, this]()
                     { this->Forward(moving.Length()); });
    this->moves.push([height, this]()
                     { this->TookOff(-height); });
}

void Drone::MakeRoute(const double &height, const double &angle, const double &length)
{
    double angleRad = (this->anglesRPY[2] - angle) * M_PI / 180;
    this->route->startPoint = this->position;
    this->route->finishPoint = Vector3({cos(angleRad), sin(angleRad), 0}) * length + this->position;
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
