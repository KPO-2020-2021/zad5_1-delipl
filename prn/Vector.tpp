#include <cmath>
#include <limits>
#include <iomanip> 
#include "Vector.hpp"
/**
 *  @
 */

/* -------------------------------------------------------------------------- */
/*                                CONSTRUCTORS                                */
/* -------------------------------------------------------------------------- */
template <typename T, std::size_t dim>
Vector<T, dim>::Vector() {
    this->cord = std::vector<T>(dim, T());
}
template <typename T, std::size_t dim>
Vector<T, dim>::Vector(const Vector &v): Vector() {
    for (std::size_t i = 0; i < dim; ++i)
        this->cord[i] = v[i];
}
template <typename T, std::size_t dim>
Vector<T, dim>::Vector(const std::initializer_list<T> &list): Vector() {
    if(list.size() != dim)
        throw std::out_of_range("To many or less argumets");
    std::size_t i = std::numeric_limits<std::size_t>().max();
    for(const T x: list)
        this->cord[++i] = x;
}
/* -------------------------------------------------------------------------- */
/*                                   METHODS                                  */
/* -------------------------------------------------------------------------- */

template <typename T, std::size_t dim>
T Vector<T, dim>::Length() const {
    T x = T();
    for (const T y: this->cord)
        x += y * y; 
    return sqrt(x);
}

/* -------------------------------------------------------------------------- */
/*                                  OPERATORS                                 */
/* -------------------------------------------------------------------------- */
template <typename T, std::size_t dim>
T Vector<T, dim>::operator[](const std::size_t &i) const {
    if (i >= dim)
        throw std::out_of_range("Vector out of range");
    return cord[i];
}
template <typename T, std::size_t dim>
T &Vector<T, dim>::operator[](const std::size_t &i){
    if (i >= dim)
        throw std::out_of_range("Vector out of range");
    return cord[i];
}

template <typename T, std::size_t dim>
bool Vector<T, dim>::operator==(const Vector &v) const {
    for (std::size_t i = 0; i < dim; ++i)
        if (this->cord[i] != v[i])
            return false;
    return true;
}

template <typename T, std::size_t dim>
bool Vector<T, dim>::operator!=(const Vector &v) const {
    for (std::size_t i = 0; i < dim; ++i)
        if (this->cord[i] == v[i])
            return false;
    return true;
}

template <typename T, std::size_t dim>
bool Vector<T, dim>::operator!() const{
    for (std::size_t i = 0; i < dim; ++i)
        if (this->cord[i] != T())
            return false;
    return true;
}

template <typename T, std::size_t dim>
Vector<T, dim> &Vector<T, dim>::operator=(const Vector &v) {
    for (std::size_t i = 0; i < dim; ++i)
        this->cord[i] = v[i];
    return *this;
}

template <typename T, std::size_t dim>
Vector<T, dim> Vector<T, dim>::operator+(const Vector &v) const {
    Vector u(v);
    for (std::size_t i = 0; i < dim; ++i)
        u[i] += this->cord[i];
    return u;
}

template <typename T, std::size_t dim>
Vector<T, dim> &Vector<T, dim>::operator+=(const Vector &v) {
    for (std::size_t i = 0; i < dim; ++i)
        this->cord[i] += v[i];
    return *this;
}

template <typename T, std::size_t dim>
Vector<T, dim> Vector<T, dim>::operator-(const Vector &v) const {
    Vector u(v);
    for (std::size_t i = 0; i < dim; ++i)
        u[i] =  this->cord[i] - u[i];
    return u;
}

template <typename T, std::size_t dim>
Vector<T, dim> &Vector<T, dim>::operator-=(const Vector &v) {
    for (std::size_t i = 0; i < dim; ++i)
        this->cord[i] -= v[i];
    return *this;
}

template <typename T, std::size_t dim>
Vector<T, dim> Vector<T, dim>::operator*(const T &k) const{
    Vector u(*this);
    for (std::size_t i = 0; i < dim; ++i)
        u[i] =  this->cord[i] * k;
    return u;
}

template <typename T, std::size_t dim>
Vector<T, dim> &Vector<T, dim>::operator*=(const T &k) {
    for (std::size_t i = 0; i < dim; ++i)
        this->cord[i] *= k;
    return *this;
}

template <typename T, std::size_t dim>
Vector<T, dim> Vector<T, dim>::operator/(const T &k) const{
    Vector u(*this);
    for (std::size_t i = 0; i < dim; ++i)
        u[i] =  this->cord[i] / k;
    return u;
}

template <typename T, std::size_t dim>
T Vector<T, dim>::operator&(const Vector &v) const{
    T y = T();
    for (std::size_t i = 0; i < dim; ++i)
        y += this->cord[i] * v[i];
    return y;
}

template <typename T, std::size_t dim>
std::ostream &operator<<(std::ostream &strm, const Vector<T, dim> &v) {
    for (std::size_t i = 0; i < dim; ++i)
        strm << std::setw(16) << std::fixed << std::setprecision(10) << v[i];
    return strm;
}

template <typename T, std::size_t dim>
std::istream &operator>>(std::istream &strm, Vector<T, dim> &v) {
    for (std::size_t i = 0; i < dim; ++i){
        strm >> v[i];
        if(!strm)
            throw(std::logic_error("Vector input error"));
    }
    return strm;
}

