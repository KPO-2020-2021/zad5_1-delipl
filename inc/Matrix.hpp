/**
 * @file Matrix.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief  File describes template Matrix class
 * @version 0.1
 * @date 2021-06-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "Vector.hpp"

/**
 * @brief Matematical dynamic any type Matrix built with table of Vectors which are built with data type.
 * @tparam T Type of values collected in Vector3
 * @tparam dimN rows Vector<Vector<T,dimM>, dimN>
 * @tparam dimM columns Vector<T, dimM>
 */
template <typename T, std::size_t dimN, std::size_t dimM>
class Matrix {
protected:    
    /**
     * @brief Table of rows in Matrix. Vector of Vectors.
     */
    std::vector<Vector<T, dimM>> vector;

public:
    /**
     * @brief Construct a new Matrix object
     */
    Matrix();

    /**
     * @brief Construct a new Matrix object.
     * @param list of Vector as rows
     */
    Matrix(const std::initializer_list<Vector<T, dimM>> &list);

    /**
     * @brief Construct a new Matrix object
     * @param M Matrix to copy
     */
    Matrix(const Matrix &M);

    /**
     * @brief Destroy the Matrix object
     */
    ~Matrix();

    /**
     * @brief Determinate of square Matrix
     * @param sum previous sum.
     * @return T determinate.
     */
    T Det() const;

    /**
     * @brief Flip void creating new Matrix which has columns changed to rows
     * @return Matrix channged colums with rows
     */
    Matrix<T, dimM, dimN> Flip() const;

    /**
     * @brief Operator [] acces to read to row.
     * @param index of row.
     * @return Vector row in index;
     */
    Vector<T, dimM> operator[](const std::size_t &index) const;

     /**
     * @brief Operator [] acces ro read and write to row.
     * @param index of row.
     * @return Vector row in index;
     */
    Vector<T, dimM> &operator[](const std::size_t &index); 

    /**
     * @brief Multiplar operator Matrix by Vector.
     * @param v Vector.
     * @return Vector<T> result. 
     */
    Vector<T, dimM> operator*(const Vector<T, dimM> &v) const;

     /**
     * @brief Multiplar operator Matrix by Matrux.
     * @param M matrix.
     * @return Matrix result. 
     */
    Matrix<T, dimN, dimN> operator*(const Matrix<T, dimM, dimN> &M) const;

    /**
     * @brief Multiplar operator Matrix by Matrux.
     * @param M matrix.
     * @return Matrix result. 
     */
    Matrix<T, dimN, dimN> &operator*=(const Matrix<T, dimM, dimN> &M);

    /**
     * @brief Copy values from M to this
     * @param M copied values
     * @return Matrix& 
     */
    Matrix &operator=(const Matrix &M);

    /**
     * @brief Checks if this and Matrix are the same
     * @return true if they are
     * @return false if not
     */
    bool operator==(const Matrix &M) const;

     /**
     * @brief Checks if this and Matrix are not the same
     * @return false if they are
     * @return true if not
     */
    bool operator!=(const Matrix &M) const;
};

/**
 * @brief Input stream operator
 * @return std::istream& cin with 
 */
template <typename T, std::size_t dimN, std::size_t dimM>
std::ostream &operator<<(std::ostream &cout, const Matrix<T, dimN, dimM> &M);

#include "Matrix.tpp"

#endif // __MATRIX_H__