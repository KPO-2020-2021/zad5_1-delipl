#include "Matrixes.hpp"

MatrixRot::MatrixRot(): Matrix3x3() {
    for(std::size_t i = 0; i < 3; ++i)
        (*this)[i][i] = 1;
}

MatrixRot::MatrixRot(double angle, const Vector3 &axis){
    angle *= M_PI/180;
    if(axis == VectorX){
        (*this)[0] = Vector3({1.0, 0.0         , 0.0    });
        (*this)[1] = Vector3({0, cos(angle), -sin(angle)});
        (*this)[2] = Vector3({0, sin(angle),  cos(angle)});
    }
    else if(axis == VectorY){
        (*this)[0] = Vector3({cos(angle) , 0, sin(angle)});
        (*this)[1] = Vector3({0          , 1, 0         });
        (*this)[2] = Vector3({-sin(angle), 0, cos(angle)});
    }
    else if(axis == VectorZ){
        (*this)[0] = Vector3({cos(angle) , -sin(angle), 0});
        (*this)[1] = Vector3({sin(angle) , cos(angle), 0});
        (*this)[2] = Vector3({0          , 0         , 1});
    }   
    else{
        throw std::logic_error("Can't make MatrixRot. Wrong axis.");
    }
}

MatrixTransform::MatrixTransform(){
    for (std::size_t i = 0; i < 4; ++i)
        this->vector[i][i] = 1;
}

MatrixTransform::MatrixTransform(const Vector3 &translate, const Vector3 &angles, const Vector3 &scale){
    double a = angles[2] * M_PI / 180; // Yaw
    double b = angles[1] * M_PI / 180; // Pitch
    double c = angles[0] * M_PI / 180; // Roll
    this->vector = {{   cos(a)*cos(b)*scale[0]  ,  cos(a)*sin(b)*sin(c)-sin(a)*cos(c)         ,   cos(a)*sin(b)*cos(c)+sin(a)*sin(c), translate[0]},
                    {   sin(a)*cos(b)           ,  sin(a)*sin(b)*sin(c)+cos(a)*cos(c)*scale[1],   sin(a)*sin(b)*cos(c)-cos(a)*sin(c), translate[1]},
                    {   -sin(b)                 ,  cos(b)*sin(c)                              ,   cos(b)*cos(c)*scale[2]            , translate[2]},                   
                    {   0                       ,  0                                          ,   0                                 , 1           }
    };
}
