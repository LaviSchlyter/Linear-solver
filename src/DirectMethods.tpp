#ifndef AWESOME_PROJECT_DIRECTMETHODS_TPP
#define AWESOME_PROJECT_DIRECTMETHODS_TPP
#include <iostream>
#include "DirectMethods.h"

// Constructor
template<typename T>
DirectMethods<T>::DirectMethods(Matrix<T> &A, Vector<T> &b)
: LinearSolver<T>(A, b)
{}

#endif // AWESOME_PROJECT_DIRECTMETHODS_TPP