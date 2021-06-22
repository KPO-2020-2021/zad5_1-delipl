#include "Route.hpp"

Route::Route(const Vector3 &startPoint, const Vector3 &finishPoint, const double &height, Transform *pin) :
    SceneObject("route.dat", startPoint, Vector3({1, 1, 1}), pin),
    startPoint{startPoint},
    finishPoint{finishPoint},
    height{height} {
    this->originPoints[0] = Vector3();
    this->originPoints[1] = VectorZ * height;
    this->originPoints[2] = this->finishPoint * (-1) + VectorZ * height;
    this->originPoints[3] = this->finishPoint * (-1);

    this->actualPoints = this->originPoints;
    this->UpdatePoints();
}

void Route::Update() {
    this->originPoints[0] = startPoint;
    this->originPoints[1] = startPoint + VectorZ * height;
    this->originPoints[2] = this->finishPoint + VectorZ * height;
    this->originPoints[3] = this->finishPoint;
    this->UpdatePoints();
}

bool Route::CanLand(){
    return true;
}