#ifndef AWESOME_PROJECT_VECTOR_TPP
#define AWESOME_PROJECT_VECTOR_TPP
#include "Vector.h"
#include <cmath>

// Constructors
template<typename T>
Vector<T>::Vector(unsigned int size)
: Matrix<T>(1,size,size) // A row vector
{}
template<typename T>
Vector<T>::Vector(std::vector<T> std_vector)
: Matrix<T>(1,std_vector.size(),std_vector.size()) // A row vector
{
    for (int i = 0; i < this->GetSize(); i++) {
        (*this)(i) = std_vector[i];
    }
}
// Operator round bracket overloading
template <typename T>
T& Vector<T>::operator()(unsigned int x) {
    return this->Matrix<T>::operator()(0,x);
}
// Operator round bracket overloading with const
template <typename T>
T Vector<T>::operator()(unsigned int x) const {
    return this->Matrix<T>::operator()(0,x);
}
// Plus operator between two vector
template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &vec) const {
    if (this->GetSize() != vec.GetSize()) {
        throw std::out_of_range("Vector size incompatible");
    }
    Vector<T> result(this->GetSize());
    for (int i = 0; i < this->GetSize(); i++) {
        result(i) = (*this)(i) + vec(i);
    }
    return result;
}
// Minus operator between two vector
template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &vec) const {
    if (this->GetSize() != vec.GetSize()) {
        throw std::out_of_range("Vector size incompatible");
    }
    Vector<T> result(this->GetSize());
    for (int i = 0; i < this->GetSize(); i++) {
        result(i) = (*this)(i) - vec(i);
    }
    return result;
}
// Multiplication operator between a vector and a scalar
template<typename T>
Vector<T> Vector<T>::operator*(const T &d) const {
    Vector<T> result(this->GetSize());
    for (int i = 0; i < this->GetSize(); i++) {
        result(i) = (*this)(i)*d;
    }
    return result;
}
// Multiplication operator between a matrix and a scalar
template<typename T>
Vector<T> Vector<T>::operator*(Matrix<T> &m) const {
    if (this->GetSize() != m.GetColSize()) {
        throw std::out_of_range("Matrix and vector size incompatible");
    }
    Vector<T> result(this->GetSize());
    for (int i = 0; i < m.GetRowSize(); ++i) {
        T sum = 0;
        for (int j = 0; j < m.GetColSize(); ++j) {
            sum += m(i,j)*(*this)(j);
        }
        result(i) = sum;
    }
    return result;
}
// Scalar product
template<typename T>
T Vector<T>::DotProduct(Vector<T> &vec) const {
    if (this->GetSize() != vec.GetSize()) {
        throw std::out_of_range("Vector size incompatible");
    }
    T result = 0;
    for (int i = 0; i < this->mCols; i++) {
        result += (*this)(i)*vec(i);
    }
    return result;
}
// Norm of a vector
template<typename T>
T Vector<T>::Norm() {
    return std::sqrt((*this).DotProduct((*this)));
}
/* To improve in future work
// Get the diagonal of a matrix as a vector
template <typename T>
Vector<T> Vector<T>::GetDiag(Matrix<T> &m){
    if (m.GetColSize() != m.GetRowSize()) {
        throw std::out_of_range("Matrix is not squared");
    }
    Vector<T> Diag(m.GetRowSize());
    for (int i = 0; i < m.GetRowSize(); i++) {
        Diag(i) = m(i,i);
    }
    return Diag;
}
 */

#endif //AWESOME_PROJECT_VECTOR_TPP
