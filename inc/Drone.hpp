#ifndef __DRONE_HPP__
#define __DRONE_HPP__
#include "SceneObject.hpp"

class Drone : public Cuboid {
  private:
    std::vector<std::shared_ptr<Rotor>> rotors;
    std::vector<std::shared_ptr<Cuboid>> eyes;

    Route *route;

  public:
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