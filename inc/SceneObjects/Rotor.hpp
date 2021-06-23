/**
 * @file Rotor.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief File describes Rotor class which is implementted in Drone
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ROTOR_HPP
#define ROTOR_HPP
#include "SceneObject.hpp"

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


  public:
    /**
     * @brief Direction of spinnig
     */
    const SpinDirection_t spinDirection;
    
    /**
     * @brief Construct a new Rotor object
     * @param position local position of Rotor to Drone 
     * @param pin pinnedTransform Drine Transform
     */
    // Rotor(const Vector3 &position,const std::shared_ptr<Transform> & pin, const SpinDirection_t &spinDirection);
    Rotor(const SpinDirection_t &direction, const Vector3 &position = Vector3(), const Vector3 &scale = {1, 1, 1}, Transform *const pin = nullptr);

    /**
     * @brief Destroy the Rotor object
     */
    ~Rotor();

    /**
     * @brief Spin blades every frame
     */
    void Update() override;

    /**
     * @brief Cannot land on 
     */
    bool CanLand() override { return false; };
};

#endif // !ROTOR_HPP