#include "Transform.hpp"

Transform::Transform(Transform *const &pin = nullptr) :
    pinnedTransform{pin} {
    this->position = Vector3();
    this->localRotation = MatrixRot();
    this->scale = MatrixRot();
    this->anglesRPY = Vector3();
}

Transform::~Transform() {}

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
