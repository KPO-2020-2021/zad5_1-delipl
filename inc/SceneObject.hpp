/**
 * @file SceneObject.hpp
 * @author Jakub Delicat
 * @brief Describes SceneObject, Route, Rotor and RotorBlades.
 * @version 0.1
 * @date 2021-06-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include "Object.hpp"
#include "config.hpp"

/**
 * @brief Modeling SceneObject with shadows on every axis. Inplements collision
 * 
 */
class SceneObject : public Object {
  public:
    std::vector<Vector3> shadowX;
    std::vector<Vector3> shadowY;
    std::vector<Vector3> shadowZ;

    SceneObject(const std::string name, const Vector3 &centerPosition,
                const Vector3 &scale, const std::shared_ptr<Transform> &pin);

    void UpdateShadows() {}
    bool IsOverlapping(const SceneObject &obj) {}

    virtual void Update() = 0;
    virtual bool CanLand() = 0;
};

/**
 * @brief Class Route implement route of Drone. It is created with startPoint (actual Drone localPosition) and finishPoint 
 * (the landing localPosition). 
 */
class Route : public Object {
  private:
    /**
     * @brief First point to drawing route
     */
    const Vector3 startPoint;

    /**
     * @brief Last point to drawing route
     */
    const Vector3 finishPoint;

    /**
     * @brief height of line from start XY to finish XY
     */
    const double height;

  public:
    /**
     * @brief Construct a new Route object
     * 
     * @param startPoint drone localPosition
     * @param finishPoint landing localPosition
     * @param height height of flight
     */
    Route(const Vector3 &startPoint, const Vector3 &finishPoint, const double &height);

    /**
     * @brief Empty Update
     */
    void Update() override{};
};

/**
     * @brief SpinDirection_t enum which descibes spin direction of Blade
     * 
     */
enum class SpinDirection_t : int {
    Clockwise = 1,
    CounterClockwise = -1
};

/**
 * @brief Rotor of the Drone. It needs to be pinnedTransform to Drone
 */
class Rotor : public Object {
  private:
    /**
     * @brief Spinning speed 0 - 255
     */
    uint8_t spinSpeed;

    /**
     * @brief Direction of spinnig
     */
    const SpinDirection_t spinDirection;

  public:
    /**
     * @brief Construct a new Rotor object
     * @param localPosition local localPosition of Rotor to Drone 
     * @param pin pinnedTransform Drine Transform
     */
    Rotor(const Vector3 &localPosition, const std::shared_ptr<Transform> &pin, const SpinDirection_t &spinDirection);

    /**
     * @brief Spin blades every frame
     */
    void Update() override;
};

#endif  // !SCENEOBJECT_HPP