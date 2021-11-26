#ifndef AWESOME_PROJECT_RICHARDSON_H
#define AWESOME_PROJECT_RICHARDSON_H

#include "IndirectMethods.h"

/** \brief Richardson class
 *
 * Class which enables to solve a given linear system using the Richardson iterative method.
 * Jacobi and Gauss-Seidel are special cases of the Richardson method.
 *
 * @tparam T Template parameter
 */
template<typename T>
class Richardson : protected IndirectMethods<T> {
public:
    /** \brief Constructor of Richardson class
     * @param A : Matrix of the linear system such as Ax = b
     * @param b : Vector of the linear system such as Ax = b
     * @param P : Preconditionner matrix
     * @param iteration_num : Maximum number of iterations
     * @param tol : Tolerance for convergence
     * @param choice : Integer which determines if the user choose Richardson (1), Jacobi (2) or Gauss-Seidel (3), may reduce computation time
     */
    Richardson(Matrix<T> &A, Vector<T> &b, Matrix<T> &P, unsigned int iteration_num, double tol, unsigned int choice);
    /** \brief Abstract function to solve the linear system
     *
     * Function override in children class to solve the linear system
     * Ax = b and to output it on screen or in a file
     *
     * @param stream How to output the solution of the linear system
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
    /** \brief Richardson computation
     *
     * Algorithm to solve the linear system iteratively
     */
    void RichardsonComputation();

private:
    /// Parameter to store whether the linear systems is solved by Richardson, Jacobi or Gauss-Seidel
    unsigned int mMethod;
};

#include "Richardson.tpp"

#endif //AWESOME_PROJECT_RICHARDSON_H
