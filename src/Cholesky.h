#ifndef AWESOME_PROJECT_CHOLESKY_H
#define AWESOME_PROJECT_CHOLESKY_H
#include "DirectMethods.h"
#include "LowerTriangular.h"

/** \brief Cholesky class to solve with Cholesky substitution
 *
 * Class to solve the linear system by the Cholesky method which computes 'R' the lower triangular matrix such that
 * A = R*R' (with R' the transposed of R)
 * @tparam T Template parameter
 */
template<typename T>
class Cholesky : protected DirectMethods<T> {
public:
    /** \brief Constructor of Cholesky class
     * @param A : Matrix of the linear system such as Ax = b
     * @param b : Vector of the linear system such as Ax = b
     */
    Cholesky(Matrix<T> &A, Vector<T> &b);
    /** \brief Abstract function to solve the linear system
     *
     * Function override in children class to solve the linear system
     * Ax = b and to output it on screen or in a file
     *
     * @param stream : How to output the solution of the linear system
     */
    void Solver(std::ostream &stream) override;
    /** \brief Abstract function to solve the linear system
     *
      * Function override in children class to solve the linear system
      * Ax = b and to return the value of x
      *
      * @return The vector x solution of Ax = b
      */
    Vector<T> Solver_X() override;
    /** \brief Cholesky decomposition
     * @return The lower matrix from Cholesky decomposition
     */
    LowerTriangular<T> CholeskyDecomposition();
};

#include "Cholesky.tpp"

#endif //AWESOME_PROJECT_CHOLESKY_H
