#ifndef AWESOME_PROJECT_DIRECTMETHODS_H
#define AWESOME_PROJECT_DIRECTMETHODS_H

#include "LinearSolver.h"

/// Direct methods mother class
template <typename T>
class DirectMethods: protected LinearSolver<T> {
protected:
    /** \brief The constructor of DirectMethods class
     * @param A : Matrix of the linear system such as Ax = b
     * @param b : Vector of the linear system such as Ax = b
     */
    DirectMethods(Matrix<T> &A, Vector<T> &b);
};

#include "DirectMethods.tpp"

#endif //AWESOME_PROJECT_DIRECTMETHODS_H
