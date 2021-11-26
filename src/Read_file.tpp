#ifndef AWESOME_PROJECT_READ_FILE_TPP
#define AWESOME_PROJECT_READ_FILE_TPP
#include <sstream>
#include <fstream>
#include <iterator>
#include <set>
#include <cmath>
#include <map>
#include <string>
#include "LUMethod.h"
#include "Cholesky.h"
#include "ConjugateGradient.h"
#include "Read_file.h"
#include "Richardson.h"
#include "Vector.h"

// Read a file an extract a Vector from it
template<typename T>
Vector<T> Read_file<T>::Read_file_vector(std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::ifstream::failure("Couldn't open vector b file");
    }
    std::istream_iterator<T> start(file), end;
    std::vector<T> vector_from_file(start, end);
    Vector<T> result(vector_from_file);
    return result;
}
// Read a file an extract a Matrix from it
template<typename T>
Matrix<T> Read_file<T>::Read_file_Matrix(std::string &file_path) {
    std::ifstream file(file_path);
    int num_row, num_col, num_lines;

    if (!file.is_open()) {
        throw std::ifstream::failure("Couldn't open Matrix file: " + file_path);
    }

    // Ignore comments headers
    while (file.peek() == '%') file.ignore(2048, '\n');

    // Read number of rows and columns
    file >> num_row >> num_col >> num_lines;
    if (num_row != num_col) {
        throw std::invalid_argument("The matrix is not squared, please verify: " + file_path);
    } else if (num_col * num_row != num_lines) {
        throw std::invalid_argument("Matrix is squared but with missing elements: " + file_path);
    } else if (num_lines == 0) {
        throw std::invalid_argument("Matrix has no elements: " + file_path);
    }

    // Create a Matrix
    Matrix<T> matrix_from_file(num_row, num_col);
    // Fill the matrix with data
    for (int l = 0; l < num_lines; l++) {
        T data;
        int row, col;
        file >> row >> col >> data;
        matrix_from_file(row - 1, col - 1) = data; // Because user will start at (1,1)
    }
    file.close();
    return matrix_from_file;
}
// Checking input argument enter by the user
template<typename T>
void Read_file<T>::Checking_input(std::map<std::string, std::string> &tmpmap) {
    std::set<std::string> Methods;
    Methods = {"Jacobi", "Gauss-Seidel", "Conjugate", "Richardson", "LU", "Cholesky"};
    // Default numbers
    unsigned int max_iter = 100;
    double tolerance =pow(10,-3);

    std::string matrix_file_name = tmpmap["Matrix A file"];
    std::string vector_file_name = tmpmap["Vector b file"];
    std::string arg_method = tmpmap["Method chosen"];
    std::string preconditioner_file = tmpmap["Preconditioner"]; // verify later that we have something there, make eye matrix
    std::string iter = tmpmap["Iterations"];
    std::string toler = tmpmap["Tolerance"];

    if (iter.empty() == 0) {
        max_iter = std::stoi(iter);
    }
    if (toler.empty() == 0) {
        tolerance = std::stod(toler);
    }

    try {
        if (tmpmap.size() > 8) {
            throw std::invalid_argument("Too many input arguments were entered");
        } else if (Methods.find(arg_method) == Methods.end()) {
            throw std::invalid_argument("Please enter the methods name correctly");
        }
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }

    // File where answer should be outputted
    std::string name_answer_file = tmpmap.find("Output file")->second;
    // Create and write on answer_file
    std::ofstream answer_file(name_answer_file);

    // Declare matrix and vector of size 1 just to have access in the try
    Matrix<T> A(1, 1);
    Vector<T> b(1);
    /// TODO: Find a way to initialize the preconditioner with an identity matrix after having received size
    Matrix<T> P(1, 1);
    try {
        A = Read_file_Matrix(matrix_file_name);
        b = Read_file_vector(vector_file_name);

        // Not optimal
        if (preconditioner_file.empty() == 0) { // Meaning we have a preconditioner file
            P = Read_file_Matrix(preconditioner_file);
        } else {
            P = Matrix<T>::Identity(A.GetRowSize()); /// Identity matrix
        }
        if (b.GetSize() != A.GetColSize()) {
            throw std::invalid_argument("Size of A and b are incompatible");
        } else if (P.GetColSize() != A.GetColSize()) {
            throw std::invalid_argument("Size of A and P are incompatible");
        }
    } catch (const std::ifstream::failure &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    } catch (const std::invalid_argument &i) {
        std::cerr << "Error: " << i.what() << std::endl;
        exit(1);
    }

    // Show to the user what he has chosen
    std::cout << "You have enter the following parameters:" << std::endl;
    std::cout << "Matrix file: " << matrix_file_name << std::endl;
    std::cout << "Vector b file: " << vector_file_name << std::endl;
    std::cout << "Method chosen: " << arg_method << std::endl;
    std::cout << "Output file: " << name_answer_file << std::endl;
    std::cout << "Number of iterations if indirect method: " << max_iter << std::endl;
    std::cout << "Tolerance if indirect method: " << tolerance << std::endl;


    try {
        if (arg_method == "LU") {
            LUMethod<T> LU_solver(A,b);
            LU_solver.Solver(answer_file);
        } else if (arg_method == "Cholesky") {
            Cholesky<T> Cholesky_solver(A, b);
            Cholesky_solver.Solver(answer_file);
        } else if (arg_method == "Conjugate") {
            ConjugateGradient<T> Conjugate_solver(A, b, P, max_iter, tolerance);
            Conjugate_solver.Solver(answer_file);
        } else if (arg_method == "Richardson") {
            Richardson<T> Rich_solver(A, b, P, max_iter, tolerance,1);
            Rich_solver.Solver(answer_file);
        } else if (arg_method == "Jacobi") {
            /// Jacobi is a Richardson with a special preconditioner (P = Diagonal of A)
            // TODO: Use vector for diagonal matrix
            //  Vector<T> D = Vector<T>::GetDiag(A);
            Matrix<T> D = A.GetDiag();
            Richardson<T> Rich_solver(A, b, D, max_iter, tolerance,2);
            Rich_solver.Solver(answer_file);
        } else { // arg_method == "Gauss-Seidel"
            /// Gauss-Seidel is a Richardson with a special preconditioner (P = Diagonal(A) + Strictly lower diagonal of A)
            // TODO: Use vector for diagonal matrix
            //  Vector<T> D = Vector<T>::GetDiag(A);
            Matrix<T> D = A.GetDiag();
            LowerTriangular<T> E(A.GetColSize());
            E.GetLowerTriangularPart(A);
            Matrix<T> Pre_Gauss = D + E;
            Richardson<T> Rich_solver(A, b, Pre_Gauss, max_iter, tolerance,3);
            Rich_solver.Solver(answer_file);
        }
    } catch (const std::exception &exc) { // Catch exceptions
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}
// Reading input argument from argv
template<typename T>
void Read_file<T>::Reading_input_argument(char *argv[]) {
    std::string file_sum = argv[1];
    std::ifstream file(file_sum);
    std::string argument, input, line;
    std::vector<std::string> arguments;
    std::vector<std::string> inputs;

    // Make a map
    std::map<std::string, std::string> strMap;
    while (!file.eof()) {
        getline(file, argument, ':');
        getline(file, input);
        std::stringstream sstr(input);
        sstr >> input;
        // Remove space in input name
        strMap.insert(std::pair<std::string, std::string>(argument,input));
    }

    Read_file<T>::Checking_input(strMap);
}

#endif //AWESOME_PROJECT_READ_FILE_TPP