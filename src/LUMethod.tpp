#ifndef AWESOME_PROJECT_LUMETHOD_TPP
#define AWESOME_PROJECT_LUMETHOD_TPP
#include "LUMethod.h"
#include "DirectMethods.h"
#include <cmath>

// Constructors
template<typename T>
LUMethod<T>::LUMethod(Matrix<T> &A, Vector<T> &b)
        : DirectMethods<T>(A,b)
{}
// Solvers
template<typename T>
void LUMethod<T>::Solver(std::ostream &stream) {
    auto size = this -> A.GetRowSize();
    LowerTriangular<T> L(size);
    UpperTriangular<T> U(size);

    LUFactorization(L,U);
    auto y = this->ForwardSubstitution(L, this -> b);
    this->x = this->BackwardSubstitution(U, y);

    // We have now solved x
    this->PrintX(stream);
}
template<typename T>
Vector<T> LUMethod<T>::Solver_X() {
    auto size = this -> A.GetRowSize();
    LowerTriangular<T> L(size);
    UpperTriangular<T> U(size);

    LUFactorization(L,U);
    auto y = this->ForwardSubstitution(L, this -> b);
    this->x = this->BackwardSubstitution(U, y);

    return this->x;
}
// LU factorization
template<typename T>
void LUMethod<T>::LUFactorization(LowerTriangular<T> &L, UpperTriangular<T> &U) {
    auto size = this->A.GetRowSize();
    double sum;
    for (int i = 0; i < size; i++) {
        // Upper
        for (int j = i; j < size; j++) {
            sum = 0.0;
            for (int k = 0; k < i; k++) {
                sum+= L(i,k)*U(k,j);
            }
            if (i == j && std::fabs(this->A(i,j) - 0.0 < std::numeric_limits<double>::epsilon())) {
                std::cerr <<"Pivot is equal to zero, cannot solve linear equation using LU \n";
                exit(EXIT_FAILURE);
            }
            U(i,j) = this->A(i,j) - sum;
        }
        // Lower
        for (int j = i; j < size; j++) {
            if (i == j) {
                L(i,i) = 1;
            } else {
                sum = 0.0;
                for (int k = 0; k < i; k++) {
                    sum += L(j,k)*U(k,i);
                }
                L(j, i) = (this->A(j, i) - sum) / U(i, i);
            }
        }
    }
}

#endif //AWESOME_PROJECT_LUMETHOD_TPP
