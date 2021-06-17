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

#include "config.hpp"
#include "Object.hpp"

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
                const Vector3 &scale = {1, 1 ,1}, Transform *const pin= nullptr);
    virtual ~SceneObject(){};

    void UpdateShadows() {}
    bool IsOverlapping(const SceneObject &obj) {
        obj.Name();
        return true;
    }

    virtual void Update() = 0;
    virtual bool CanLand() = 0;

    virtual void Draw();
};

/**
 * @brief Class Route implement route of Drone. It is created with startPoint (actual Drone localPosition) and finishPoint 
 * (the landing localPosition). 
 */
class Route : public SceneObject {
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

    // ~Route();

    /**
     * @brief Empty Update
     */
    void Update() override{};

    bool CanLand() override { return true; };
};

class Cuboid : public SceneObject {
  protected:
   
    std::vector<Vector3*> vertexes;
    std::vector<Vector3*> centers;

  public:
    const Vector3 dimentions;
    Cuboid(const Vector3 &dimentions, const Vector3 &localPositio = Vector3(), Transform *const pin = nullptr);
    virtual void Update() override{};

    virtual bool CanLand() override { return true; };

    // friend std::ostream &operator<<(std::ostream &strm, const Cuboid &cub);
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
class Rotor : public SceneObject {
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
    // Rotor(const Vector3 &localPosition,const std::shared_ptr<Transform> & pin, const SpinDirection_t &spinDirection);
    Rotor(const SpinDirection_t &direction, const Vector3 &localPosition = Vector3(), const Vector3 &scale = {1, 1,1 } ,  Transform *const pin = nullptr);

    ~Rotor(){};
    /**
     * @brief Spin blades every frame
     */
    void Update() override;

    bool CanLand() override { return true; };
};

#endif  // !SCENEOBJECT_HPP