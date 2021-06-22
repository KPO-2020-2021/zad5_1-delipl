#ifndef __DRONE_HPP__
#define __DRONE_HPP__
#include <queue>
#include <functional>

#include "SceneObject.hpp"
struct Animate {
    Vector3 goalPosition = Vector3();
    double goalRotation = 0;


    Vector3 translateStep;
    double rotateStep;
    uint8_t speed = 5;
    void SetTranslateGoal(const Vector3 &vec){
      translateStep = vec - goalPosition;
      translateStep = translateStep / translateStep.Length();
      translateStep = translateStep * speed;
      goalPosition = vec;
    }

    void SetRotationGoal(const double &d){
      goalRotation +=d;
      if (this->goalRotation >= 360)
        goalRotation -= 360;

      rotateStep = 5;
    }
};

class Drone : public Cuboid {
  private:
    std::vector<std::shared_ptr<Rotor>> rotors;
    std::vector<std::shared_ptr<Cuboid>> eyes;
    Animate animation;
    std::shared_ptr<Route> route;

    Vector3 directionVec;

  public:
    std::queue<std::function<void(void)>>
        moves;

    Drone(const Vector3 &position = Vector3(), const Vector3 &scale = Vector3({2, 2, 1}));

    ~Drone();

    void Forward(const double &lenght);

    void TookOff(const double &height);

    void Left(const double &angle);

    void Right(const double &angle);

    void ReconFlight();

    void Update() override;

    bool CanLand() override { return false; };

    void Draw();

    bool Rotated();

    bool Translated();

    void FlyTo(const Vector3 &position, const double &height = 100);

    void MakeRoute(const double &height, const double &angle, const double &length);
};
#endif 