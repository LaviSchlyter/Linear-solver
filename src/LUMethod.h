#ifndef AWESOME_PROJECT_LUMETHOD_H
#define AWESOME_PROJECT_LUMETHOD_H
#include "DirectMethods.h"
#include "LowerTriangular.h"
#include "UpperTriangular.h"

/** \brief LU method class for solving linear systems
 *
 * Class which enables to solve the linear system using the LU method, by first decomposing into a lower triangular matrix 'L' and
 * an upper triangular matrix 'U'
 * @tparam T Template parameter
 */
template<typename T>
class LUMethod : protected DirectMethods<T> {
public:
    /** \brief LUMethod constructor
     * @param A : Matrix of the linear system such as Ax = b
     * @param b : Vector of the linear system such as Ax = b
     */
    LUMethod(Matrix<T> &A, Vector<T> &b);
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
    /**\brief Factorizes A into L and U
     *
     * Factorizes A into L and U, where L is the lower triangular (with one as diagonals) matrix and U is the lower triangular matrix
     *
     * @param L : Lower triangular matrix of same size as A, initialized at zero
     * @param U : Upper triangular matrix of same size as A, initialized at zero
     */
    void LUFactorization(LowerTriangular<T> &L, UpperTriangular<T> &U);
};

#include "LUMethod.tpp"

#endif //AWESOME_PROJECT_LUMETHOD_H
