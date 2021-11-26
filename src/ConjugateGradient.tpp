#ifndef AWESOME_PROJECT_CONJUGATEGRADIENT_TPP
#define AWESOME_PROJECT_CONJUGATEGRADIENT_TPP
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include "Warning.h"
#include "ConjugateGradient.h"
#include "IndirectMethods.h"
#include "LUMethod.h"

// Constructor
template<typename T>
ConjugateGradient<T>::ConjugateGradient(Matrix<T> &A, Vector<T> &b, Matrix<T> &P, unsigned int iteration_num, double tol)
:IndirectMethods<T>(A, b,P, iteration_num, tol)
{}
// Solvers
template<typename T>
void ConjugateGradient<T>::Solver(std::ostream &stream) {
    ConjugateComputation();

    // We have now solved x
    this->PrintX(stream);
}
template<typename T>
Vector<T> ConjugateGradient<T>::Solver_X() {
    ConjugateComputation();
    return this->x;
}
// Computation with conjugate method
template <typename T>
void ConjugateGradient<T>::ConjugateComputation() {
    /// x was initialized to zero in LinearSolver constructor

    // tmp_Ax = A*x
    //TODO(Romain) Get better polymorphism here to avoid this strange writing
    // Vector<T> tmp_Ax = (this->A)*(this->x)
    auto tmp_Ax = (this->x)*(this->A);

    // r = b - A*x
    auto r = this->b - tmp_Ax;

    // norm of b vector
    double norm_b = this->b.Norm();

    // Solving the equation using LU (choice)
    LUMethod<double> solve_z(this -> mPreconditioner, r);

    auto z = solve_z.Solver_X();
    auto p = z;

    // Arbitrary assignment
    double rz_old = 1;

    // If b vector is equal to zero
    if (std::fabs(norm_b - 0.0) < std::numeric_limits<double>::epsilon()) {
        norm_b = 1.0;
    }

    // Relative residual, used as stopping criterion
    auto rel_res = r.Norm()/norm_b;

    unsigned int k = 0;
    while (k < this->mIt_num && rel_res > this->mTol) {
        // Solving P*z = r;
        // TODO Upgrade this method for diagonal matrices (Jacobi, identity or diag)
        LUMethod<double> solve_rP(this->mPreconditioner, r);
        z = solve_rP.Solver_X();

        // Dot product of two vectors
        auto rz = r.DotProduct(z);
        if (k == 0) {
            p = z;
        } else {
            auto beta = rz / rz_old;

            p = z + p*beta;
        }

        // q = A*p
        //TODO(Romain) Get better polymorphism here to avoid this strange writing
        auto q = p*(this->A);

        auto alpha = rz/(p.DotProduct(q));
        // x = x + p*alpha
        this->x = this->x + p*alpha;
        // r = r - q*alpha
        r = r - q*alpha;
        // update rz_old to rz (new)
        rz_old = rz;
        // Increasing iteration by one
        k++;
        // Update the relative residual
        rel_res = r.Norm() / norm_b;
    }
    // Verify that number of iterations has not exceeded
    if (k == this->mIt_num) {
        WarningIteration();
    }
}

#endif //AWESOME_PROJECT_CONJUGATEGRADIENT_TPP
