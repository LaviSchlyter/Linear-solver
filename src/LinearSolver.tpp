#ifndef AWESOME_PROJECT_LINEARSOLVER_TPP
#define AWESOME_PROJECT_LINEARSOLVER_TPP
#include "Matrix.h"
#include "LinearSolver.h"

// Constructor
template <typename T>
LinearSolver<T>::LinearSolver(Matrix<T> &A, Vector<T> &b)
: A(A), b(b), x(b.GetSize())
{}
// Forward substitution solving the lower triangular system Ly = b
template<typename T>
Vector<T> LinearSolver<T>::ForwardSubstitution(Matrix<T> &L, Vector<T> b) {
    auto size = this->A.GetRowSize();
    Vector<T> y(size);

    y(0) = (b(0))/L(0,0);
    for(int i = 1; i < size; i++) {
        double sum = 0;
        for(int j = 0; j < i; j++) {
            sum+= L(i,j)*y(j);
        }
        y(i) = (b(i) - sum)/L(i,i);
    }
    return y;
}

// Backward substitution to solve Ux = y
template<typename T>
Vector<T> LinearSolver<T>::BackwardSubstitution(Matrix<T> &U, Vector<T> y) {
    auto size = this->A.GetRowSize();
    Vector<T> result(size);

    result(size - 1) = y(size - 1)/U(size - 1, size - 1);
    for(int i = size - 2; i >= 0; i--) {
        double sum = 0;
        for(int j = i; j < size; j++) {
            sum += U(i,j)*result(j);
        }
        result(i) = (y(i) - sum)/U(i,i);
    }
    return result;
}
// Print method
template<typename T>
void LinearSolver<T>::PrintX(std::ostream &stream) {
    stream.setf(std::ios::scientific);
    stream.setf(std::ios::showpos);
    stream.precision(6);
    auto size = this->x.GetSize();
    for (int i = 0; i < size; i++) {
        stream << this->x(i) << std::endl;
    }
}

#endif //AWESOME_PROJECT_LINEARSOLVER_TPP