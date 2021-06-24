/**
 * @file Drone.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief Describes Drone class.
 * @version 0.1
 * @date 2021-06-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __DRONE_HPP__
#define __DRONE_HPP__
#include <queue>
#include <functional>
#include "config.hpp"
#include "Animation.hpp"
#include "Rotor.hpp"
#include "Cuboid.hpp"
#include "Route.hpp"

/**
 * @brief Drawable and drivable Drone. 
 */
class Drone : public SceneObject {
  private:
    /**
     * @brief Animation interface and properties
     */
    Animation animation;

    /**
     * @brief Unit Vector3 where Drone is aimed to.
     */
    Vector3 directionVec;

    /**
     * @brief Cuboid as a body for drone
     */
    std::shared_ptr<Cuboid> body;

    /**
     * @brief Rotor which are rotating
     */
    std::vector<std::shared_ptr<Rotor>> rotors;
    // std::vector<std::shared_ptr<Cuboid>> eyes;

    /**
     * @brief Route of Drone moving
     */
    std::shared_ptr<Route> route;

  public:
    /**
     * @brief Queue of moves for split stages of Animation.
     */
    std::queue<std::function<void(void)>> moves;

    /**
     * @brief Construct a new Drone object.
     * 
     * @param position on Scene.
     * @param scale dimention of Drone.
     */
    Drone(const Vector3 &position = Vector3(), const Vector3 &scale = Vector3({2, 2, 1}));

    /**
     * @brief Destroy the Drone object
     */
    ~Drone();

    /**
     * @brief Apply Update() for every SceneObject inside Drone
     */
    void Update() override;

    /**
     * @brief Cannot land on Drone
     */
    bool CanLand() override { return false; };

    /**
     * @brief Go Drone forward.
     * @param lenght how far Drone has to go.
     */
    void Forward(const double &lenght);

    /**
     * @brief Verdical movement of Drone.
     * @param height how high Drone has to go, it can be minus to Land.
     */
    void GoVerdical(const double &height);

    /**
     * @brief Turn left Drone by angle.
     * @param angle to turn.
     */
    void Left(const double &angle);

    /**
     * @brief Turn right Drone by angle.
     * @param angle to turn.
     */
    void Right(const double &angle);

    /**
     * @brief Drone is making recognition flight.
     * 
     */
    void ReconFlight();

    /**
     * @brief Draw Drone with all SceneObjects inside
     */
    void Draw();

    /**
     * @brief Checks if rotate animation has finished.
     * @return true if it finished
     * @return false if not
     */
    bool Rotated();

    /**
     * @brief Checks if translate animation has finished.
     * @return true if it finished
     * @return false if not
     */
    bool Translated();

    /**
     * @brief TODO Fly to position
     * 
     * @param position 
     * @param height 
     */
    void FlyTo(const Vector3 &position, const double &height = 100);

    /**
     * @brief Implements parameters for Route
     * @param height of Route
     * @param angle  of Route
     * @param length  of Route
     */
    void MakeRoute(const double &height, const double &angle, const double &length);

    /**
     * @brief Change color of Drone
     * @param x choosed color
     */
    void ChangeColor(const int &x);
};
#endif 