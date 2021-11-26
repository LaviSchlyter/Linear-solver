#ifndef AWESOME_PROJECT_LOWERTRIANGULAR_TPP
#define AWESOME_PROJECT_LOWERTRIANGULAR_TPP
#include "LowerTriangular.h"
#include "UpperTriangular.h"

// Constructor
template<typename T>
LowerTriangular<T>::LowerTriangular(unsigned int Rows)
: UpperTriangular<T>(Rows)
{}
// Operator round bracket overloading
template<typename T>
T& LowerTriangular<T>::operator()(unsigned int x, unsigned int y) {
    if (x >= this->mRows || y >= this->mCols) {
        throw std::out_of_range("Matrix indices out of range");
    } else if (y > x) {
        throw std::out_of_range("Cannot write to null side of lower triangular matrix");
    }
    // Here the function is not factorized to be sure to no divide something that would be not an integer
    return this->mData[(x*x+x)/2 + y];
}
// Operator round bracket overloading with const
template<typename T>
T LowerTriangular<T>::operator()(unsigned int x, unsigned int y) const {
    if (x >= this->mRows || y >= this->mCols) {
        throw std::out_of_range("Matrix indices out of range");
    } else if (y > x) {
        return 0;
    }
    // Here the function is not factorized to be sure to no divide something that would be not an integer
    return this->mData[(x*x+x)/2 + y];
}
// Method to get the lower triangular part of a matrix
template<typename T>
void LowerTriangular<T>::GetLowerTriangularPart(Matrix<T> &m) {
    if (m.GetColSize() != m.GetRowSize()) {
        throw std::out_of_range("Matrix not square");
    } else if (m.GetColSize() != this->mRows) {
        throw std::out_of_range("Matrix size incompatible");
    }
    for (int i = 0; i < this->mRows; i++) {
        for (int j = 0; j < i; j++) {
            (*this)(i,j) = m(i,j);
        }
    }
}
// Transpose a matrix
template<typename T>
UpperTriangular<T> LowerTriangular<T>::transpose() const {
    UpperTriangular<T> upper(this->mRows);
    for (int i = 0; i < this->mRows; i++) {
        for (int j = 0; j <= i; j++) {
            upper(j,i) =  (*this)(i,j);
        }
    }
    return upper;
}

#endif //AWESOME_PROJECT_LOWERTRIANGULAR_TPP
