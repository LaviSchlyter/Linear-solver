cmake_minimum_required(VERSION 3.17)
project(awesome_project)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
include_directories(googletest/include)
include_directories( ./src )

set(PROJECT_HEADERS
        src/Matrix.h
        src/LinearSolver.h
        src/IndirectMethods.h
        src/ConjugateGradient.h
        src/Richardson.h
        src/LUMethod.h
        src/Cholesky.h
        src/DirectMethods.h
        src/LowerTriangular.h
        src/UpperTriangular.h
        src/Read_file.h
        src/Vector.h
        src/Warning.h)
set(PROJECT_SOURCES
        src/main.cpp
        src/LinearSolver.tpp
        src/IndirectMethods.tpp
        src/ConjugateGradient.tpp
        src/Cholesky.tpp
        src/Matrix.tpp
        src/DirectMethods.tpp
        src/LUMethod.tpp
        src/LowerTriangular.tpp
        src/UpperTriangular.tpp
        src/Read_file.tpp
        src/Richardson.tpp
        src/Vector.tpp)

add_executable(main ${PROJECT_SOURCES} ${PROJECT_HEADERS})

add_executable(Matrix_A1_3by3_test test/Matrix_A1_3by3_test.cpp)
target_link_libraries(Matrix_A1_3by3_test gtest gtest_main)
add_executable(Matrix_A2_3by3_test test/Matrix_A2_3by3_test.cpp)
target_link_libraries(Matrix_A2_3by3_test gtest gtest_main)
add_executable(Matrix_10000_all_test test/Matrix_1000x1000_all.cpp)
target_link_libraries(Matrix_10000_all_test gtest gtest_main)