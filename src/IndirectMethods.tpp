#ifndef AWESOME_PROJECT_INDIRECTMETHODS_TPP
#define AWESOME_PROJECT_INDIRECTMETHODS_TPP
#include <cmath>
#include <numeric>
#include <algorithm>
#include "IndirectMethods.h"

//Constructor
template<typename T>
IndirectMethods<T>::IndirectMethods(Matrix<T> &A, Vector<T> &b, Matrix<T> &P, unsigned int iteration_num, double tol)
        : LinearSolver<T>(A,b), mPreconditioner(P), mIt_num(iteration_num), mTol(tol)
{}
// Solve a linear system A*x = b; when A is diagonal. A is any matrix
template<typename T>
Vector<T> IndirectMethods<T>::DiagSolver(Matrix<T> &diag, Vector<T> &vec) {
    if (diag.GetColSize() != vec.GetSize()) {
        throw std::out_of_range("Vector size incompatible");
    }
    Vector<T> result(diag.GetColSize());
    for (int i = 0; i < diag.GetColSize(); i++) {
        result(i) = vec(i)/diag(i,i);
    }
    return result;
}

#endif //AWESOME_PROJECT_INDIRECTMETHODS_TPP
