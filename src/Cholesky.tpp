#ifndef AWESOME_PROJECT_CHOLESKY_TPP
#define AWESOME_PROJECT_CHOLESKY_TPP
#include "DirectMethods.h"
#include "Cholesky.h"
#include "cmath"

// Constructor
template<typename T>
Cholesky<T>::Cholesky(Matrix<T> &A, Vector<T> &b)
: DirectMethods<T>(A, b)
{}
// Linear solver
template<typename T>
void Cholesky<T>::Solver(std::ostream &stream) {
    auto L = CholeskyDecomposition();
    auto L_transpose = L.transpose();
    auto y = this->ForwardSubstitution(L, this -> b);
    this->x = this->BackwardSubstitution(L_transpose, y);

    // We have now solved x
    this->PrintX(stream);
}
template<typename T>
Vector<T> Cholesky<T>::Solver_X() {
    auto L = CholeskyDecomposition();
    auto L_transpose = L.transpose();
    auto y = this->ForwardSubstitution(L, this -> b);
    this->x = this->BackwardSubstitution(L_transpose, y);
    return this->x;
}
// Cholesky decomposition in a lower triangular matrix
template<typename T>
LowerTriangular<T> Cholesky<T>::CholeskyDecomposition() {
    auto size = this->A.GetRowSize();
    LowerTriangular<T> lower(size);

    // Decomposing a matrix into Lower Triangular
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            // Checking if the matrix is symmetric
            if (std::fabs(this->A(i,j) - this->A(j,i)) > std::numeric_limits<double>::epsilon()) {
                throw std::invalid_argument("Cholesky factorization needs a symmetric matrix");
            }
            double sum = 0;
            if (j == i) { // summation for diagonals
                for (int k = 0; k < j; k++) {
                    sum += pow(lower(j,k), 2);
                }
                // Verify singularity of matrix using machine difference
                if (std::fabs((this->A(j,j) - sum)) < std::numeric_limits<double>::epsilon()) { // * std::fabs(x+y) we can add this for extra precision when numbers are extremely small
                    throw std::invalid_argument("Singular matrix, cannot solve linear equation using Cholesky");
                }
                lower(j,j) = sqrt(this->A(j,j) - sum);
            } else { // Evaluating L(i, j) using L(j, j)
                for (int k = 0; k < j; k++) {
                    sum += (lower(i,k) * lower(j,k));
                }
                lower(i,j) = (this->A(i,j) - sum)/lower(j,j);
            }
        }
    }
    return lower;
}

#endif // AWESOME_PROJECT_CHOLESKY_TPP