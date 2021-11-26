#include <gtest/gtest.h>
#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "Cholesky.h"
#include "LUMethod.h"
#include "Read_file.h"

/** Google test on 1000x1000 diagonally dominant matrix
 * This google test tests the LU, Cholesky, Conjugate, Jacobi and Gauss-Seidel method
 *
 * It should converge for all 5 methods according to the theory
 */
using T = double;
std::string matrix_file_name = "../examples/MatrixA_1000_all.dat";
std::string b_file_name = "../examples/VectorB_1000_all.dat";
std::string solution_file_name = "../examples/VectorX_1000_all.dat";

Matrix<double> A = Read_file<T>::Read_file_Matrix(matrix_file_name);
Vector<double> b = Read_file<T>::Read_file_vector(b_file_name);
Vector<double> x_Matlab_computed =  Read_file<T>::Read_file_vector(solution_file_name);
int rows = A.GetRowSize();
Matrix<double> P = Matrix<T>::Identity(rows);

unsigned int max_iter = 5000;
double tolerance = 1e-7;
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Cholesky, real_doubles) {
    Cholesky<double> cholesky(A, b);
    Vector<double> x = cholesky.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed(i), x(i), 1e-6);
    }
}

TEST(LU, real_doubles) {
    LUMethod<double> LU(A, b);
    Vector<double> x = LU.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed(i), x(i), 1e-6);
    }
}

TEST(Conjugate, real_doubles) {
    ConjugateGradient<double> conjugate(A,b,P, max_iter, tolerance);
    Vector<double> x = conjugate.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed(i), x(i), 1e-6);
    }
}

TEST(Gauss_Seidel, real_doubles) {
    Matrix<T> D = A.GetDiag();
    LowerTriangular<T> E(A.GetColSize());
    E.GetLowerTriangularPart(A);
    Matrix<T> Pre_Gauss = D + E;
    Richardson<double> richardson(A, b, Pre_Gauss, max_iter, tolerance,3);
    Vector<double> x = richardson.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed(i), x(i), 1e-6);
    }
}

TEST(Jacobi, real_doubles) {
    // The preconditionner is the diagonal of the Matrix A
    Matrix<T> Pre_Jacobi = A.GetDiag();
    Richardson<double> richardson(A, b, Pre_Jacobi, max_iter, tolerance,2);
    Vector<double> x = richardson.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed(i), x(i), 1e-6);
    }
}

/* Malheuresement pas possible car il faudrait trouver un bon pre-conditioner
TEST(Richardson, real_doubles) {
    // Random preconditioner (diagonal...)
    Matrix<T> D = A.GetDiag();
    Matrix<T> Pre_Rich = D;
    //Matrix<double> Pre_Rich = Matrix<T>::Identity(rows);
    Richardson<double> richardson(A, b, Pre_Rich, max_iter, tolerance,1);
    Vector<double> x = richardson.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed(i), x(i), 1e-6);
    }
}
 */
