#ifndef AWESOME_PROJECT_MATRIX_TPP
#define AWESOME_PROJECT_MATRIX_TPP
#include "Matrix.h"
// Constructors
template <typename T>
Matrix<T>::Matrix(unsigned int Rows, unsigned int Cols)
: mRows(Rows), mCols(Cols)
{
    mSize = mRows*mCols;
    mData.resize(mSize,0);
}
template <typename T>
Matrix<T>::Matrix(unsigned int Rows, unsigned int Cols, unsigned int size)
: mRows(Rows), mCols(Cols), mSize(size)
{
    mData.resize(mSize,0);
}
// Operator round bracket overloading
template <typename T>
T& Matrix<T>::operator()(unsigned int x, unsigned int y) {
    if (x >= mRows || y >= mCols) {
        throw std::out_of_range("matrix indices out of range");
    }
    return mData[mRows*x + y];
}
// Operator round bracket overloading with const
template <typename T>
T Matrix<T>::operator()(unsigned int x, unsigned int y) const {
    if (x >= mRows || y >= mCols) {
        throw std::out_of_range("matrix indices out of range");
    }
    return mData[mRows*x + y];
}
// Friend function to print the matrix
template <typename T>
std::ostream &operator<<(std::ostream &output, const Matrix<T> &m) {
    output.setf(std::ios::scientific);
    output.setf(std::ios::showpos);
    output.precision(2);
    for (int i = 0; i < m.mRows; i++) {
        for (int j = 0; j < m.mCols; j++) {
            output << m(i,j) << "  ";
        }
        output << std::endl;
    }
    return output;
}
// Transpose a matrix
template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> transpose(mCols, mRows);
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            transpose(i,j) = (*this)(j,i);
        }
    }
    return transpose;
}
// Operators minus overloading overloading
template<typename T>
std::vector<T> Matrix<T>::operator-(const std::vector<T> &rhs) {
    std::vector<T> temp = (*this).mData;
    auto size = this -> A.GetRowSize();

    for (int i = 0; i < size; i++) {
        temp[i] = temp[i] - rhs[i];
    }
    return temp;
}
// Plus operator between two matrix
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) const {
    if (m.GetColSize() != this->mCols && m.GetRowSize() != this->mRows) {
        throw std::out_of_range("Matrix size incompatible");
    }
    Matrix<T> result(this->mRows, this->mCols);
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            result(i,j) = (*this)(i,j) + m(i,j);
        }
    }
    return result;
}
// Minus operator between two matrix
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &m) const {
    if (m.GetColSize() != this->mCols && m.GetRowSize() != this->mRows) {
        throw std::out_of_range("Matrix size incompatible");
    }
    Matrix<T> result(this->mRows, this->mCols);
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            result(i,j) = (*this)(i,j) - m(i,j);
        }
    }
    return result;
}
// Get the diagonal of a matrix
template <typename T>
Matrix<T> Matrix<T>::GetDiag() {
    Matrix<T> Diag(this->mRows, this->mCols);
    for (int i = 0; i < this -> mRows; i++) {
        Diag(i,i) = (*this)(i,i);
    }
    return Diag;
}
// Identity matrix
template<typename T>
Matrix<T> Matrix<T>::Identity(const unsigned int &size) {
    Matrix<T> result(size,size);
    for (int i = 0; i < size; i++) {
        result(i,i) = 1;
    }
    return result;
}

#endif // AWESOME_PROJECT_MATRIX_TPP
