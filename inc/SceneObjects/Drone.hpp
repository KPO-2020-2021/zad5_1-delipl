#ifndef __DRONE_HPP__
#define __DRONE_HPP__
#include <queue>
#include <functional>
#include "SceneObject.hpp"
#include "Animation.hpp"
#include "Rotor.hpp"
#include "Cuboid.hpp"
#include "Route.hpp"


class Drone : public Cuboid {
  private:
    std::vector<std::shared_ptr<Rotor>> rotors;
    std::vector<std::shared_ptr<Cuboid>> eyes;
    Animation animation;
    std::shared_ptr<Route> route;

    Vector3 directionVec;

  public:
    std::queue<std::function<void(void)>> moves;

    Drone(const Vector3 &position = Vector3(), const Vector3 &scale = Vector3({2, 2, 1}));

    ~Drone();

    void Update() override;

    bool CanLand() override { return false; };

    void Forward(const double &lenght);

    void TookOff(const double &height);

    void Left(const double &angle);

    void Right(const double &angle);

    void ReconFlight();

    void Draw();

    bool Rotated();

    bool Translated();

    void FlyTo(const Vector3 &position, const double &height = 100);

    void MakeRoute(const double &height, const double &angle, const double &length);
};
#endif 