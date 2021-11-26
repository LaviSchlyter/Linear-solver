#include <gtest/gtest.h>
#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "Cholesky.h"
#include "LUMethod.h"
#include "ConjugateGradient.h"
#include "Read_file.h"

/** Google test on 3x3 matrix
 *
 * This google test verifies the results the Cholesky, LU and Conjugate gradient method
 */

using T = double;
Matrix<T> A(3, 3);
Vector<T> b(3);
std::vector<T> x_Matlab_computed;
int rows;

int main(int argc, char* argv[]) {

    std::string matrix_file_name = "../examples/MatrixA1.dat";
    std::string b_file_name = "../examples/VectorB.dat";

    A = Read_file<T>::Read_file_Matrix(matrix_file_name);
    b = Read_file<T>::Read_file_vector(b_file_name);

    x_Matlab_computed = {28.5833333, -7.6666667, 1.3333333};
    rows = 3;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Cholesky, real_doubles) {
    Cholesky<double> cholesky(A, b);
    Vector<double> x = cholesky.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed[i], x(i), 1e-6);
    }
}

TEST(LU, real_doubles) {
    LUMethod<double> LU(A, b);
    Vector<double> x = LU.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed[i], x(i), 1e-6);
    }
}

TEST(ConjugateGradient, real_doubles) {

    double tolerance = 1e-6;
    Matrix<double> P = Matrix<T>::Identity(rows);
    ConjugateGradient<double> conjugate(A,b,P, 100, tolerance);

    Vector<double> x = conjugate.Solver_X();

    for (int i = 0; i < rows; i++) {
        ASSERT_NEAR(x_Matlab_computed[i], x(i), 1e-6);
    }
}