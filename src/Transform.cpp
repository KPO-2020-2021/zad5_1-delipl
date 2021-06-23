#include "Transform.hpp"

Transform::Transform(Transform *const &pin) :
    pinnedTransform{pin} {
    this->position = Vector3();
    this->orientation = MatrixRot();
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
    

    this->orientation = this->orientation * MatrixRot(angle, v);
}

Vector3 Transform::UpdatePoint(Vector3 &point) const {
    return this->orientation * this->scale * point + this->position;
}

Vector3 Transform::ConvertToGlobal(Vector3 &point) const {
    if (this->pinnedTransform != nullptr) {
        point = this->UpdatePoint(point);
        return this->pinnedTransform->ConvertToGlobal(point);
    }
    return this->UpdatePoint(point);
}
