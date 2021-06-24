#include "Drone.hpp"

#include "Scene.hpp"
extern bool DISPLAY;
Drone::Drone(const Vector3 &position, const Vector3 &scale) : 
SceneObject("point.dat", position, scale, nullptr)
{
    /* ============[Shake]=========== */
    // banan
    // 200ml mleka
    // milkyway
    // jagody 100g
    // lyzka masla orzechowego

    /* =========[Naleśniczki]======== */
    // 4jajka
    // 180ml mleka
    // 200g mąki
    // 1 łyżeczka proszku do pieczenia
    // 2 łyżki cukru lub miodu
    // 1 banan
    // 1/2 łyżeczki cynamonu


    this->directionVec = {cos(0), sin(0), 0};
    this->animation.goalOrientation = 0;
    this->anglesRPY[2] = this->animation.goalOrientation;
    Vector3 rotorScale = scale * 10;

    this->body = std::make_shared<Cuboid>(scale*0.5 + VectorZ*0.5, Vector3(), this);
    this->route = std::make_shared<Route>(Vector3(), Vector3(), 0, nullptr);
    auto tmpPtr1 = std::make_shared<Rotor>(SpinDirection_t::Clockwise, (*(this->body->vertexes[0])) + VectorZ * this->body->dimentions[2], rotorScale, this);
    this->rotors.push_back(std::move(tmpPtr1));
    auto tmpPtr2 = std::make_shared<Rotor>(SpinDirection_t::Clockwise, (*(this->body->vertexes[1])) + VectorZ * this->body->dimentions[2], rotorScale, this);
    this->rotors.push_back(std::move(tmpPtr2));
    auto tmpPtr3 = std::make_shared<Rotor>(SpinDirection_t::CounterClockwise, (*(this->body->vertexes[6])) + VectorZ * this->body->dimentions[2], rotorScale, this);
    this->rotors.push_back(std::move(tmpPtr3));

    auto tmpPtr4 = std::make_shared<Rotor>(SpinDirection_t::CounterClockwise, (*(this->body->vertexes[7])) + VectorZ * this->body->dimentions[2], rotorScale, this);
    this->rotors.push_back(std::move(tmpPtr4));
    
    // if(tmpPtr1 == nullptr)
    //     exit(-1);
    if (DISPLAY){
        Scene::AddToDrawable(this->route.get());
        Scene::AddToDrawable(this->body.get());
    }
            
    for (auto &rotor : this->rotors) {
        rotor->Update();
        if (DISPLAY) {
            Scene::AddToDrawable(rotor.get());
        }
    }
 
    this->Left(0);
    this->body->UpdatePoints();
    this->animation.SetGoalPosition(this->position);
    this->animation.SetGoalOrientation(this->anglesRPY[2]);
}

Drone::~Drone() {}

void Drone::Forward(const double &length) {
    // std::cout << "KAT: " << this->anglesRPY[2] << std::endl;
    // Vector3 direction = {cos(this->anglesRPY[2] * M_PI / 180), sin(this->anglesRPY[2] * M_PI / 180 ), 0};
    this->animation.SetGoalPosition(this->position + this->directionVec * length);

    // rotors[0]->Rotate(15, VectorY);
    // rotors[2]->Rotate(15, VectorX);
    
    // rotors[1]->Rotate(-15, VectorX);
    // rotors[3]->Rotate(-15, VectorY);

    // this->body->Rotate(15, VectorY);
}
void Drone::GoVerdical(const double &length) {
    this->animation.SetGoalPosition(this->position + VectorZ * length);
    // rotors[0]->Rotate(0, VectorY);
    // rotors[1]->Rotate(0, VectorX);

    // rotors[2]->Rotate(0, VectorX);

    // rotors[3]->Rotate(0, VectorY);
    // this->body->Rotate(0, VectorY);
}


void Drone::Draw() {
    for (auto &rotor : this->rotors)
        if (DISPLAY)
            Scene::Draw(rotor.get());

    Scene::Draw(this);
}

void Drone::Left(const double &angle) {
    this->animation.SetGoalOrientation(angle);
}

void Drone::Right(const double &angle) {
    this->animation.SetGoalOrientation(-angle);
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
    auto angleDiff = this->anglesRPY[2] - this->animation.goalOrientation;
    //  std::cout << anglesRPY[2] << "  "<<this->animation.goalOrientation << std::endl;
    if (std::fabs(angleDiff) >= this->animation.rotateStep)
    {
        if (angleDiff < 0)
            this->Rotate(this->animation.rotateStep, VectorZ);
        else if (angleDiff > 0)
            this->Rotate(-this->animation.rotateStep, VectorZ);
    }
    else if (anglesRPY[2] == this->animation.goalOrientation)
    {
        return true;
    }
    else if (std::fabs(this->anglesRPY[2] - this->animation.goalOrientation) <= this->animation.rotateStep)
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
                         this->GoVerdical(height);});
    
    this->moves.push([angle, this]()
                     { this->Right(angle); });
    this->moves.push([moving, this]()
                     { this->Forward(moving.Length()); });
    this->moves.push([height, this]()
                     { this->GoVerdical(-height); });
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

    this->body->UpdatePoints();
    for (auto &rotor : this->rotors) {
        rotor->Update();
    }
}
void Drone::ChangeColor(const int &x){
    
    Scene::api.UsunNazwePliku(this->body->Name());
    PzG::InfoPlikuDoRysowania *wInfoPliku1 = &Scene::api.DodajNazwePliku((std::string(TMP_FOLDER) + this->body->Name()).c_str());
    wInfoPliku1->ZmienKolor(x);
    for(auto &rotor: this->rotors){
        Scene::api.UsunNazwePliku(rotor->Name());
        wInfoPliku1 = &Scene::api.DodajNazwePliku((std::string(TMP_FOLDER) + rotor->Name()).c_str());
        wInfoPliku1->ZmienKolor(x);
    }
   
}