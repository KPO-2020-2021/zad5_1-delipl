#ifndef __DRONE_HPP__
#define __DRONE_HPP__


#include "SceneObject.hpp"
struct Animate {
    Vector3 goalPosition = Vector3();
    double goalRotation = 0;


    Vector3 translateStep;
    double rotateStep;
    uint8_t speed = 10;
    void SetTranslateGoal(const Vector3 &vec){
        goalPosition += vec;
        translateStep = {5, 5, 5};
    }

    void SetRotationGoal(const double &d){
      goalRotation +=d;
      if (this->goalRotation >= 360)
        goalRotation -= 360;
      // if (this->goalRotation <= 0)
      //   goalRotation += 360;

      rotateStep = 5;
    }
};

class Drone : public Cuboid {
  private:
    std::vector<std::shared_ptr<Rotor>> rotors;
    std::vector<std::shared_ptr<Cuboid>> eyes;
    Animate animation;
    Route *route;
    

  public:
    bool isMoving = false;

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

    void FlyTo(const Vector3 &position, const double &height = 100);

    void MakeRoute(const Vector3 &startPosition, const Vector3 landPosition, const double &height);
};
#endif 