/**
 * @file Vector.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief File describes template class Vector which simulates mathematical vector.
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <initializer_list>
#include <iostream>
#include <vector>
/**
 * @brief Dynamic any type Vector class.
 * @tparam T type of Vector
 * @tparam dim how many dimention is in the Vector
 */
template <typename T, std::size_t dim>
class Vector {
  protected:
    /**
     * @brief Values of sent type.
    */
    std::vector<T> cord;

    /**
     * @brief How many Vector3 actually are in Scene.
     */
    inline static std::size_t HMO = 0;

    /**
     * @brief How many Vector3 have created are in Scene.
     */
    inline static std::size_t allHMO = 0;

  public:
    /**
     * @brief Construct a new empty Vector.
    */
    Vector();

    /**
     * @brief Construct a new Vector object.
     * @param v Vector to copy.
    */
    Vector(const Vector &v);

    /**
     * @brief Construct a new Vector with parameters.
     * Dimention depends how many arguments put.
    */
    Vector(const std::initializer_list<T> &list);

    /**
     * @brief Destroy the Vector object
     */
    ~Vector();

    /**
     * @brief Count length of Vector
     * @return T length of vector
    */
    T Length() const;

    /**
     * @brief Acces to variables vector.
    */
    T operator[](const std::size_t &i) const;

    /**
     * @brief Acces to variables vector.
    */
    T &operator[](const std::size_t &i);

    /**
     * @brief Compare two Vectors. Dimention and values
     * @param u compare Vector
     * @return True when dimention and values are the same,
                False when  not.
    */
    bool operator==(const Vector &u) const;

    /**
     * @brief Compare two Vectors. Dimention and values.
     * @param v Compare Vector.
     * @return False when dimention and values are the same,
                true when  not.
    */
    bool operator!=(const Vector &v) const;

    /**
     * @brief Check if all values are 0
     * @return true if all values are 0
     * @return false if there are some values
     */
    bool operator!() const;

    /**
     * @brief Assignment operator
    */
    Vector &operator=(const Vector &v);

    /**
     * @brief Additaion operator
    */
    Vector operator+(const Vector &v) const;

    /**
     * @brief Additaion operator
    */
    Vector &operator+=(const Vector &v);

    /**
     * @brief Substraction operator
    */
    Vector operator-(const Vector &v) const;

    /**
     * @brief Substraction operator
    */
    Vector &operator-=(const Vector &v);

    /**
     * @brief Multiplication by number
    */
    Vector operator*(const T &k) const;

    /**
     * @brief Multiplication by number
    */
    Vector &operator*=(const T &k);

    /**
     * @brief Division by number
    */
    Vector operator/(const T &k) const;

    /**
     * @brief Division by number
    */
    Vector &operator/=(const T &k);

    /**
     * @brief Dot product 
    */
    T operator&(const Vector &v) const;

    /**
     * @brief Dot product 
    */
    T &operator&=(const Vector &v) const;

    /**
     * @brief How many Vectors are now.
     * @return std::size_t HMO
     */
    inline static std::size_t HowManyObjects() { return HMO; };

    /**
     * @brief How many Vectors have been created.
     * @return std::size_t allHMO
     */
    inline static std::size_t AllHowManyObjects() { return allHMO; };
};

/**
 * @brief Output stream operator 
 * @return std::ostream& cout [x, y, ...]
 */
template <typename T, std::size_t dim>
std::ostream &operator<<(std::ostream &cout, const Vector<T, dim> &v);

/**
 * @brief Input stream operator
 * @return std::istream& cin with [x1, x2, x3...]
 */
template <typename T, std::size_t dim>
std::istream &operator>>(std::istream &cin, Vector<T, dim> &v);

/**
 * @brief include definitions.
*/
#include "Vector.tpp"
#endif  // __VECTOR_HPP__
