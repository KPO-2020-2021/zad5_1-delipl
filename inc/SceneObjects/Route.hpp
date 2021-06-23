/**
 * @file Route.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief File describes Route class for Drone
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ROUTE_HPP
#define ROUTE_HPP
#include "SceneObject.hpp"

/**
 * @brief Class Route implement route of Drone. It is created with startPoint (actual Drone position) and finishPoint 
 * (the landing position). 
 */
class Route : public SceneObject {
  public:
    /**
     * @brief First point to drawing route
     */
    Vector3 startPoint;

    /**
     * @brief Last point to drawing route
     */
    Vector3 finishPoint;

    /**
     * @brief height of line from start XY to finish XY
     */
    double height;

    /**
     * @brief Construct a new Route object
     * 
     * @param startPoint drone position
     * @param finishPoint landing position
     * @param height height of flight
     */
    Route(const Vector3 &startPoint, const Vector3 &finishPoint, const double &height, Transform *pin = (Transform *)nullptr);

    /**
     * @brief Empty Update
     */
    void Update() override;

    /**
     * @brief SceneObjects can land on Route
     */
    bool CanLand() override;
};

#endif // !ROUTE_HPP