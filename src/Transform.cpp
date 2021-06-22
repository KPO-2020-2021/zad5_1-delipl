#include "Transform.hpp"

Transform::Transform(Transform *const &pin) :
    pinnedTransform{pin} {
    this->position = Vector3();
    this->localRotation = MatrixRot();
    this->scale = MatrixRot();
    this->anglesRPY = Vector3();
}

Transform::~Transform() {}

void Transform::Translate(const Vector3 &v)
{
    this->position += v;
}

void Transform::Rotate(const double &angle, const Vector3 &v)
{
    if (v != VectorX && v != VectorY && v != VectorZ)
        throw std::logic_error("Cannot rotate");
    this->anglesRPY += v * angle;
    if (this->anglesRPY[0] > 360)
        this->anglesRPY[0] -= 360;
    if (this->anglesRPY[1] > 360)
        this->anglesRPY[1] -= 360;
    if (this->anglesRPY[2] > 360)
        this->anglesRPY[2] -= 360;

    this->localRotation = this->localRotation * MatrixRot(angle, v);
}

Vector3 Transform::UpdatePoint(Vector3 &point) const {
    return this->localRotation * this->scale * point + this->position;
}

Vector3 Transform::ConvertToPinned(Vector3 &point) const {
    if (this->pinnedTransform != nullptr) {
        point = this->UpdatePoint(point);
        return this->pinnedTransform->ConvertToPinned(point);
    }
    return this->UpdatePoint(point);
}
