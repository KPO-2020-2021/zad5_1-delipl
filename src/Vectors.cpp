#include "Vectors.hpp"
// template<>
// Vector<double, 3> Vector<double, 3>::operator*(const Vector<double, 3> &v) const{
//     auto u = Vector<double, 3>(v);
//     u[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
//     u[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
//     u[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
//     return u;
// }
// template<>
// Vector<double, 3> &Vector<double, 3>::operator*=(const Vector<double, 3> &v) {
//     (*this)[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
//     (*this)[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
//     (*this)[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
//     return *this;
// }
