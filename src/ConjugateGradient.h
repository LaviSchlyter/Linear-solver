#ifndef AWESOME_PROJECT_CONJUGATEGRADIENT_H
#define AWESOME_PROJECT_CONJUGATEGRADIENT_H

#include "IndirectMethods.h"

/** \brief Conjugate Gradient class
 *
 * Class to solve the linear system with the gradient method, may use a preconditioner or not (then P = identity matrix)
 *
 * @tparam T Template parameter
 */
template<typename T>
class ConjugateGradient : protected IndirectMethods<T>{
public:
    /** \brief Conjugate Gradient Constructor
     * @param A : Matrix of the linear system such as Ax = b
     * @param b : Vector of the linear system such as Ax = b
     * @param P : Preconditionner matrix
     * @param iteration_num : Maximum number of iterations
     * @param tol : Tolerance for convergence
     */
    ConjugateGradient(Matrix<T> &A, Vector<T> &b, Matrix<T> &P, unsigned int iteration_num, double tol);
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
    /** \brief Conjugate gradient computation
     *
     * Algorithm to solve the linear system iteratively
     */
    void ConjugateComputation();
};

#include "ConjugateGradient.tpp"

#endif //AWESOME_PROJECT_CONJUGATEGRADIENT_H
