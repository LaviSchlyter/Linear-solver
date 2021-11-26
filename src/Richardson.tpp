#ifndef AWESOME_PROJECT_RICHARDSON_TPP
#define AWESOME_PROJECT_RICHARDSON_TPP
#include "Richardson.h"
#include "LUMethod.h"
#include "Warning.h"
#include "IndirectMethods.h"

// Constructors
template<typename T>
Richardson<T>::Richardson(Matrix<T> &A, Vector<T> &b, Matrix<T> &P, unsigned int iteration_num, double tol, unsigned int method) // std::string
:IndirectMethods<T>(A, b, P, iteration_num, tol), mMethod(method)
{}
// Solvers
template<typename T>
void Richardson<T>::Solver(std::ostream &stream) {
    RichardsonComputation();

    // We have now solved x
    this->PrintX(stream);
}
template<typename T>
Vector<T> Richardson<T>::Solver_X() {
    RichardsonComputation();
    return this->x;
}
// Richardson computation
//TODO Upgrade method to have a dynamic precondition Richardson with alpha is not = 1
template<typename T>
void Richardson<T>::RichardsonComputation() {
    // Choice will define the most efficient solver to use
    enum Choice {RICHARDSON = 1, JACOBI = 2, GAUSS_SEIDEL = 3};
    int choice = mMethod;
    // x was initialized to zero in LinearSolver constructor

    //TODO(Romain) Get better polymorphism here to avoid this strange writing
    // r = b - A*x
    auto r = this->b - (this->x)*(this->A);

    double norm_b = this->b.Norm();
    // If b vector is zero
    if(std::fabs(norm_b - 0.0) < std::numeric_limits<double>::epsilon()) {
        norm_b = 1.0;
    }

    // Relative residual, used as stopping criterion
    auto rel_res = r.Norm() / norm_b;

    Vector<T> z(this->b.GetSize()); // Initialize vector z
    unsigned int k = 0;
    while (k < this->mIt_num && rel_res > this->mTol) {
        // Need to initialize before the switch
        LUMethod<double> solve_rP(this->mPreconditioner, r);

        // Chooses a solver depending on the method
        switch(choice) {
            case RICHARDSON:
                z = solve_rP.Solver_X();
                break;
            case JACOBI:
                z = this->DiagSolver(this->mPreconditioner, r);
                break;
            case GAUSS_SEIDEL:
                z = this->ForwardSubstitution(this->mPreconditioner, r);
                break;
        }
        this->x = (this->x + z);
        //TODO(Romain) Get better polymorphism here to avoid this strange writing
        // r = b - Ax
        r = this->b - this->x*(this->A);
        // Update relative residual
        rel_res = r.Norm() / norm_b;
        k++;
    }
    if (k == this->mIt_num) {
        WarningIteration();
    }
}

#endif //AWESOME_PROJECT_RICHARDSON_TPP