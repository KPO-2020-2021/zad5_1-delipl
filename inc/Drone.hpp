#include "SceneObject.hpp"

class Drone : public SceneObject {
   private:
    std::vector<Rotor> rotors;

   public:
    Drone(const Vector3 &position = Vector3(), const Vector3 &scale = Vector3({1, 1, 1}));

    void Forward(const double &lenght);

    void TookOff(const double &height);

    void ReconFlight();

    void Update() override;

    void CanLand() override;
};