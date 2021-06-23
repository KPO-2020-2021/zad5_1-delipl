/**
 * @file Vectors.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief File describes specifications for template class Vector
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __VECTORS_HPP__
#define __VECTORS_HPP__
#include "Vector.hpp"

#ifndef MIN_DIFF
    /**
     * @brief Minimal difference between two double numbers. It might be included from config.hpp
     */
    #define MIN_DIFF 0.000000001 
#endif // !MIN_DIFF

/**
 * @brief Specified Vector (double) for compare double values with MIN_DIFF
 * @tparam dim dimention of dVector
 */
template<std::size_t dim>
class dVector : public Vector<double, dim>{
    

public:
   

    /**
         * @brief Construct a new dVector object
         */
    dVector() : Vector<double, dim>() {

    }

    /**
         * @brief Construct a new d Vector object
         * @param list of points
         */
    dVector(const std::initializer_list<double> &list) : Vector<double, dim>(list) {

    }

    /**
         * @brief Construct a new d Vector object
         * @param v copied Vector
         */
    dVector(const Vector<double, dim> &v) : Vector<double, dim>(v) {
 
     }

    /**
         * @brief Checks if every diffrence is bigger  than MIN_DIFF
         * @param v compared dVector
         * @return true if is lower
         * @return false if is bigger 
         */
    bool operator==(const dVector &v) const
    {
        for (std::size_t i = 0; i < dim; ++i)
            if (std::abs(this->cord[i] - v[i]) > MIN_DIFF)
                return false;
        return true;
    }

    /**
     * @brief Checks if every diffrence is bigger  than MIN_DIFF
     * @param v compared dVector
     * @return true if is lower
     * @return false if is bigger 
     */
    bool operator==(const Vector<double, 3> &v) const {
        for (std::size_t i = 0; i < dim; ++i)
            if (std::abs(this->cord[i] - v[i]) > MIN_DIFF)
                return false;
        return true;
    }

    /**
     * @brief Checks if every diffrence is bigger than MIN_DIFF
     * @param v compared dVector
     * @return true if is bigger 
     * @return false if is less
     */
    bool operator!=(const dVector &v) const{
        for (std::size_t i = 0; i < dim; ++i)
            if (std::abs(this->cord[i] - v[i]) <= MIN_DIFF)
                return false;
        return true;
    }

    /**
     * @brief Checks if every value is lower than MIN_DIFF
     * @return true if is lower
     * @return false if is bigger 
     */
    bool operator!() const{
        for (double x: this->cord)
            if (std::abs(x) >= MIN_DIFF)
                return false;
        return true;
    }
};

/**
 * @brief four dimentional double Vector
 */
typedef dVector<4> Vector4;

/**
 * @brief three dimentional double Vector
 */
typedef dVector<3> Vector3;

/**
 * @brief two dimentional double Vector
 */
typedef dVector<2> Vector2;

/**
 * @brief X axis Vector3 (1, 0, 0)
 */
static Vector3 VectorX = {1, 0, 0};

/**
 * @brief Y axis Vector3 (0, 1, 0)
 */
static Vector3 VectorY = {0, 1, 0};

/**
 * @brief Z axis Vector3 (0, 0, 1)
 */
static Vector3 VectorZ = {0, 0, 1};

#endif // __VECTORS_HPP__