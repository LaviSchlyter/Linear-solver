#include <gtest/gtest.h>
#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LUMethod.h"
#include "Richardson.h"
#include "Read_file.h"


/** Google test on 3x3 (what kind of matrix ) // Fixme
 * This google test verifies the Richardson Jacobi and Gauss-Seidel method
 *
 * Instead of computing the correct answer using Matlab we compute it using the LU method (x_LU_computed) to compare with the iterative methods
 */
using T = double;
Matrix<T> A2(3, 3);
Vector<T> b(3);
Vector<T> x_LU_computed(3);
Matrix<T> P(3, 3);
int rows;
int max_iter = 1000;
double tolerance = 1e-7;

int main(int argc, char* argv[]) {

    std::string matrix_file_name = "../examples/MatrixA2.dat";
    std::string b_file_name = "../examples/VectorB.dat";

    A2 = Read_file<T>::Read_file_Matrix(matrix_file_name);
    b = Read_file<T>::Read_file_vector(b_file_name);
    LUMethod<T> LU(A2, b);
    x_LU_computed = LU.Solver_X();
    rows = 3;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Richardson, real_doubles) {
    // Random preconditioner

    P(0,0) = 5.0;   P(0,1) = 0.0;  P(0,2) = 0.0;
    P(1,0) = 0.0;   P(1,1) = 1.0;  P(1,2) = 0.0;
    P(2,0) = 0.0;   P(2,1) = 0.0;  P(2,2) = 1.0;
    Richardson<T> richardson(A2, b, P, max_iter, tolerance,1);
    Vector<T> x = richardson.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_LU_computed(i), x(i), 1e-6);
    }
}

TEST(Jacobi, real_doubles) {
    // The preconditionner is the diagonal of the Matrix A2
    Matrix<T> P = A2.GetDiag();
    Richardson<T> richardson(A2, b, P, max_iter, tolerance,2);
    Vector<T> x = richardson.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_LU_computed(i), x(i), 1e-6);
    }
}

TEST(Gauss_Seidel, real_doubles) {
    // The preconditionner is P = D + E
    Matrix<T> D = A2.GetDiag();
    LowerTriangular<T> E(A2.GetColSize());
    E.GetLowerTriangularPart(A2);
    Matrix<T> P = D + E;
    Richardson<T> richardson(A2, b, P, max_iter, tolerance,3);
    Vector<T> x = richardson.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_LU_computed(i), x(i), 1e-6);
    }
}
