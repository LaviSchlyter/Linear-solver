#ifndef AWESOME_PROJECT_LINEARSOLVER_H
#define AWESOME_PROJECT_LINEARSOLVER_H
#include "Matrix.h"
#include "Vector.h"
#include <iostream>

/** \brief This is the mother class LinearSolver
 *
 * @tparam T Template parameter
 */
template <typename T>
class LinearSolver {
public:
    /** \brief Constructor of LinearSolver
     * @param A : Matrix of the linear system such as Ax = b
     * @param b : Vector of the linear system such as Ax = b
     */
    LinearSolver(Matrix<T> &A, Vector<T> &b);
    /// Destructor of linearSolver
    virtual ~LinearSolver() = default;
    /** \brief Abstract function to solve the linear system
     *
     * Function override in children class to solve the linear system
     * Ax = b and to output it on screen or in a file
     *
     * @param stream How to output the solution of the linear system
     */
    virtual void Solver(std::ostream &stream) = 0;
     /** \brief Abstract function to solve the linear system
      *
      * Function override in children class to solve the linear system
      * Ax = b and to return the value of x
      *
      * @return The vector x solution of Ax = b
      */
    virtual Vector<T> Solver_X() = 0;
    /** \brief Forward substitution in linear system solving Ly = b
     * @param L : Lower triangular matrix, b a vector
     * @return The vector y solution of Ly = b
     */
    Vector<T> ForwardSubstitution(Matrix<T> &L, Vector<T> b);

    /** \brief Backward substitution in linear system solving Ux = y
     * @param U : Upper triangular matrix
     * @param y : Vector found with forward substitution
     * @return The vector x solution of Ux = y
     */
    Vector<T> BackwardSubstitution(Matrix<T> &U, Vector<T> y);
    /** \brief Nicely print the vector x
     * @param stream How to output the solution of the linear system
     */
     void PrintX(std::ostream &stream);

protected:
    /// Matrix A of the linear system*/
    Matrix<T> A;
    /// Vector x of the linear system*/
    Vector<T> x;
    /// Vector b of the linear system*/
    Vector<T> b;
};

#include "LinearSolver.tpp"

#endif //AWESOME_PROJECT_LINEARSOLVER_H
