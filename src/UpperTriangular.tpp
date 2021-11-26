#ifndef AWESOME_PROJECT_UPPERTRIANGULAR_TPP
#define AWESOME_PROJECT_UPPERTRIANGULAR_TPP
#include "UpperTriangular.h"

// Constructor
template<typename T>
UpperTriangular<T>::UpperTriangular(unsigned int Rows)
: Matrix<T>(Rows,Rows,(Rows*Rows+Rows)/2)
{}
// Operator round bracket overloading
template<typename T>
T& UpperTriangular<T>::operator()(unsigned int x, unsigned int y) {
    if (x >= this->mRows || y >= this->mCols) {
        throw std::out_of_range("Matrix indices out of range");
    } else if (x > y) {
        throw std::out_of_range("Cannot write to null side of upper triangular matrix");
    }
    // Here the function is not factorized to be sure to no divide something that would be not an integer
    return this->mData[(this->mRows*x - (x*x+x)/2)  + y];
}
// Operator round bracket overloading with const
template<typename T>
T UpperTriangular<T>::operator()(unsigned int x, unsigned int y) const {
    if (x >= this->mRows || y >= this->mCols) {
        throw std::out_of_range("Matrix indices out of range");
    } else if (x > y) {
        return 0;
    }
    // Here the function is not factorized to be sure to no divide something that would be not an integer
    return this->mData[(this->mRows*x - (x*x+x)/2) + y];
}

#endif //AWESOME_PROJECT_UPPERTRIANGULAR_TPP
