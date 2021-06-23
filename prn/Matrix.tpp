#include <cmath>
#include <iomanip>
#include "Matrix.hpp"
/**
 * @file Definitions for template class Matrix
 */

/* -------------------------------------------------------------------------- */
/*                                CONSTRUCTORS                                */
/* -------------------------------------------------------------------------- */
template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimN, dimM>::Matrix() {
    this->vector = std::vector<Vector<T, dimM>> (dimN, Vector<T, dimM>());
}

template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimN, dimM>::Matrix(const std::initializer_list<Vector<T, dimM>> &list): Matrix(){
    if(list.size() != dimN)
        throw std::out_of_range("To many or less argumets");
    std::size_t i = -1;
    for(auto x: list)
        this->vector[++i] = x;
}

template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimN, dimM>::Matrix(const Matrix &M): Matrix() {
    std::size_t i = -1;
    for(auto &x: this->vector)
        x = M[++i];
}

template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimN, dimM>::~Matrix() {
    this->vector.clear();
}

/* -------------------------------------------------------------------------- */
/*                                   METHODS                                  */
/* -------------------------------------------------------------------------- */
template <typename T, std::size_t dimN, std::size_t dimM>
T Matrix<T, dimN, dimM>::Det() const{
    T det = T(1);
    Matrix M(*this);
    for(std::size_t i = 0; i < dimM; ++i){           // po wierszach
        for(std::size_t j = i; j < dimN; ++j){
            if(M[j][i] != 0){
                T x = M[j][i];
                // dzielenie wiersza
                M[i] = M[i]/x;
                det = det * x;
                det = (i-j % 2 == 0)? det: T(-1) * det; // zamiana wierszy zmienia znak w zależności od parzystości
                Vector<T, dimM> buff(M[i]);
                M[i] = M[j];
                M[j] = buff;
                // niższe wiersze odjęte żeby było 0
                for(std::size_t k = j+1; k < dimN; ++k){
                    T y = M[k][j];
                    M[k] = M[k] - M[j] * y; 
                }
            }
        }
    }
    return det;
}
template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimM, dimN> Matrix<T, dimN, dimM>::Flip() const{
    Matrix<T, dimM, dimN> Mat;
    for(std::size_t j = 0; j < dimM; j++){
        Vector<T, dimN> column;
        for(std::size_t i = 0; i < dimN; i++)
            column[i] = (*this)[i][j];
        Mat[j] = column;
    }
    return Mat;
}
/* -------------------------------------------------------------------------- */
/*                                  OPERATORS                                 */
/* -------------------------------------------------------------------------- */
template <typename T, std::size_t dimN, std::size_t dimM>
Vector<T, dimM> Matrix<T, dimN, dimM>::operator[](const std::size_t &index) const {
    if(index >= dimN)
        throw std::out_of_range("Matrix out of range");
    return this->vector[index];
}

template <typename T, std::size_t dimN, std::size_t dimM>
Vector<T, dimM> &Matrix<T, dimN, dimM>::operator[](const std::size_t &index){
    if(index >= dimN)
        throw std::out_of_range("Matrix out of range");
    return  this->vector[index];
}

template <typename T, std::size_t dimN, std::size_t dimM>
Vector<T, dimM> Matrix<T, dimN, dimM>::operator*(const Vector<T, dimM> &v) const {
    Vector<double, dimM> u(v);
    std::size_t i = -1;
    for (auto &row: this->vector) 
        u[++i] = (row & v);

    return u;
}
template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimN, dimN> Matrix<T, dimN, dimM>::operator*(const Matrix<T, dimM, dimN> &M) const{
    Matrix<T, dimN, dimN> Mat;
    Matrix<T, dimN, dimM> flippedMatrix = M.Flip();
    for(std::size_t i = 0; i < dimN; ++i)
        for(std::size_t j = 0; j < dimN; ++j)
            Mat [i][j] = ((*this)[i] & flippedMatrix[j]);
    
    return Mat;
}

template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimN, dimN> &Matrix<T, dimN, dimM>::operator*=(const Matrix<T, dimM, dimN> &M){
    static_assert(dimM != dimN, "Cannot define this! And cannot change dimention template");
    Matrix<T, dimN, dimM> flippedMatrix = M.Flip();
    for(std::size_t i = 0; i < dimN; ++i)
        for(std::size_t j = 0; j < dimN; ++j)
            (*this) [i][j] = ((*this)[i] & flippedMatrix[j]);
    
    return (*this);
}

template <typename T, std::size_t dimN, std::size_t dimM>
std::ostream &operator<<(std::ostream &cout, const Matrix<T, dimN, dimM> &M){
    for (std::size_t i = 0; i < dimN; ++i){
        cout << "| ";
        for (std::size_t j = 0; j < dimM; j++) {
            cout << std::setw(16) << std::fixed << std::setprecision(10) << M[i][j] << 0;
        }
        cout << "|" << std::endl;
    }
    return cout;
}

template <typename T, std::size_t dimN, std::size_t dimM>
Matrix<T, dimN, dimM> &Matrix<T, dimN, dimM>::operator=(const Matrix<T, dimN, dimM> &M){
    for(std::size_t i = 0; i < dimN; ++i)
        for(std::size_t j = 0; j < dimM; ++j)
            this->vector[i][j] = M[i][j];

    return *this;
}

template <typename T, std::size_t dimN, std::size_t dimM>
bool Matrix<T, dimN, dimM>::operator==(const Matrix<T, dimN, dimM> &M) const{
    std::size_t i = -1;
    for(auto &x: this->vector)
        if(x != M[++i]) return false;
    
    return true;
}

template <typename T, std::size_t dimN, std::size_t dimM>
bool Matrix<T, dimN, dimM>::operator!=(const Matrix<T, dimN, dimM> &M) const{
    std::size_t i = -1;
    for(auto &x: this->vector)
        if(x == M[++i]) return false;
    
    return true;
}