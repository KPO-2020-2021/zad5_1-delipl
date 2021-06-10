#include "Drone.hpp"

Drone::Drone(const Vector3 &position = Vector3(), const Vector3 &scale = Vector3({1, 1, 1})):
Object("cuboid.dat", position, scale){
    this->rotors.push_back(Rotor({30, 20, 0}, this, SpinDirection_t::Clockwise));
    this->rotors.push_back(Rotor({30, -20, 0}, this, SpinDirection_t::CounterClockwise));
    this->rotors.push_back(Rotor({-30, -20, 0}, this, SpinDirection_t::Clockwise));
    this->rotors.push_back(Rotor({-30, 20, 0}, this, SpinDirection_t::CounterClockwise));

    
}
