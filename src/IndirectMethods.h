#ifndef AWESOME_PROJECT_INDIRECTMETHODS_H
#define AWESOME_PROJECT_INDIRECTMETHODS_H
#include "LinearSolver.h"
#include <cmath>

/// Indirect methods mother class
template<typename T>
class IndirectMethods : protected LinearSolver<T>{
public:
    /** \brief Constructor of IndirectMethods
     * @param iteration_num : Maximum number of iterations, specified by user // default value = 1000
     * @param tol : Maximum tolerance for error, specified by user // default value = 10^(-6)
     */
    IndirectMethods(Matrix<T> &A, Vector<T> &b, Matrix<T> &P, unsigned int iteration_num = 1000, double tol = pow(10, -6));
    /** \brief Diagonal solver
     * @param diag : The matrix diagonal
     * @param vec : The vector b such as Ax = b
     * @return The vector x such as Ax = b
     */
    Vector<T> DiagSolver(Matrix<T> &diag, Vector<T> &vec);

protected:
    /// Maximum number of iterations*/
    unsigned int mIt_num;
    /// Maximum tolerance for error on the result*/
    double mTol;
    /// Precondioner matrix, specified by user*/
    Matrix<T> mPreconditioner;
};

#include "IndirectMethods.tpp"

#endif //AWESOME_PROJECT_INDIRECTMETHODS_H
