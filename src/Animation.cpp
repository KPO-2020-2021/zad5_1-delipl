#include "Animation.hpp"

void Animation::SetPositionGoal(const Vector3 &vec) {
    translateStep = vec - goalPosition;
    translateStep = translateStep / translateStep.Length();
    translateStep = translateStep * speed;
    goalPosition = vec;
}

void Animation::SetOrientationGoal(const double &d) {
    goalRotation += d;
    if (this->goalRotation >= 360)
        goalRotation -= 360;

    rotateStep = 5;
}