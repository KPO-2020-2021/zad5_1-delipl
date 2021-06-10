#include <iostream>
#include <memory>
struct Transform {
  public:
    /**
         * @brief Pinned Transform
         */
    const std::shared_ptr<Transform> pinnedTransform;

    /**
         * @brief Center local Position
         */
    int localPosition;

    /**
         * @brief Center global position
         */
    int globalPosition;

    /**
         * @brief Local Rotation Matrix
         */
    double localRotation;

    /**
         * @brief Global Rotation Matrix
         */
    double globalRotation;

    /**
         * @brief Euler angles in 3 axis
         */
    int eulerAngles;

    /**
         * @brief Scale as a unit matrix
         */
    double scale;

    /**
         * @brief Construct a new Transform object
         */
    Transform(const std::shared_ptr<Transform> &pin = nullptr) :
        pinnedTransform{pin} {
        this->localPosition = int();
        this->localRotation = double();
        this->scale = double();
        this->eulerAngles = int();
    }
};

    int main(int argc, char const *argv[]) {
        Transform x;
        Transform y(std::make_shared<Transform>(x));

        return 0;
    }
