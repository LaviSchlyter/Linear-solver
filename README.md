# Linear solver - Implementation of direct and iterative methods for solving linear systems

PCSC Semester Project - 2020
---
---


AUTHORS: Lavinia Schlyter and Romain Van Mol

## Table of contents
* [Introduction](#introduction)
* [Technologies](#technologies)
* [How to compile the program](#how-to-compile-the-program)
* [Architecture](#architecture)
* [Typical execution](#typical-program-execution-and-use)
* [List of inputs](#list-of-inputs)
* [List of features](#list-of-features)
* [List of tests](#list-of-test)
* [Documentation](#doxygen-documentation-and-html)
* [Limitations](#limitation-and-problem)
* [TODO's and perspectives](#todos-and-perspective)
* [Numerical Analysis](#numerical-analysis)

## Introduction
Awesome_project is a project who's aim is to solve linear systems of the form A**x**=**b** with A, a squared matrix, **x** and **b**, vectors 
using either direct methods such as Cholesky and LU decomposition
or indirect methods such as conjugate gradient, Jacobi, Gauss-Seidel and Richardson.

### Technologies
We created a CMake (version 3.17) project coded in C++17.


## How to compile the program

### Compilation using Clion
In order to compile this program you must follow the following steps:

- Step 0: Make sure your googletest folder is complete in the project directory (Clone the folder from  [GitHub](https://github.com/google/googletest) into the ***awesome_project*** as it will not be cloned from *Gitlab*)
- Step 1: Go into `src` folder into the `all_info.dat`
- Step 2: Fill in the file with relevant information (more info in section **List of inputs**)
- Step 3: in **Clion** go to `Run --> Edit Configurations`
- Step 4: ***Target*** and ***Executable*** should be set to *main* 
- Step 5: ***Program arguments*** takes only *all_info.dat* (contains the different parameters the user wishes to input)
- Step 6: ***Working Directory*** select the `src` folder


**You may now run the project by going to `Run --> Run'main''`**

If you want to run tests (more information about what are the different tests in section **List of tests**) change the run configuration selector (to the left of the the green play button) to the test you want to perform (for example *Matrix_1000_all_test*)

### Compilation using the terminal
In order to compile the project using the terminal you may use the following commands:

**Note**: *The steps 0 to 2 (included) from the steps above are the same*

- Step 0: Make sure to install Cmake (pre-installed on ubuntu)
- Step 1: From the root path (awesome_project), `mkdir build` (make a directory named build)
- Step 2: `cd build` (go into the newly created directory)
- Step 3: `cmake ..` 
- Step 4: `make`
- Step 5: `cd ../src` 
- Step 6: `../build/main all_info.dat`
- Step 7: `cat ../examples/Output.dat` (prints the result on screen)

In order to run the tests (these will be executables) and may be run from the `build` folder using `./`

### Architecture
```
awesome_project
│   README.md
│   Output.dat    
│   .gitignore   
|   CMakeLists.txt
|   
└───googletest
│      ...
└───src
|       all_info.dat
|       Cholesky.h   
|       main.cpp
|       ...
└───examples
│      MatrixA1.dat
│      MatrixA2.dat
|      MatrixA3.dat
│      MatrixA_1000_all.dat
|      MatrixP.dat
|      Ouput.dat
|      VectorB.dat
|      VectorB_1000_all.dat
|      VectorX_1000_all.dat
|
└───test
|       Matrix_A2_3by3_test.cpp
|       Matrix_A1_3by3_test.cpp
|       Matrix_1000x10000_all.cpp

```
### Files and methods
The *Documentation* folder contains the Doxyfile. Please refer to **Doxygen documentation and html** for further information

The *Examples* folder contains a list of matrices and vector that may be solved using the provided code.

The *src* folder contains the source files. One `main.cpp`, the `all_info.dat` with the variables that may be inputted by the user, please refer to **List of inputs** and classes.

To solve the linear systems, we needed a matrix class (*Matrix.h* and *Matrix.tpp*) and its daughter class Vector (*Vector.h* and *Vector.tpp*).

The abstract mother class *LinearSolver*, has two daughters (*IndirectMethods* and *DirectMethods*) which each their respective daughter classes.

For the direct methods (LU and Cholesky), you find their respective class (*Cholesky.h* and *LUMethod.h*), which inherit from *DirectMethods*.

For the indirect methods (Conjugate Gradient, Richardson, Jacobi and Gauss-Seidel), you may find two different classes. *ConjugateGradient.h* and *Richardson.h*, as Jacobi and Gauss-Seidel are special cases of the Richardson method
they were implemented within the same class:

- Jacobi is a Richardson with a special preconditioner (P = Diagonal of A)
- Gauss-Seidel is a Richardson with a special preconditioner (P = Diagonal of A + Strictly lower diagonal of A)

The *test* folder contains three different test that may be run using **googletest**, further details are given in **List of test**


### Typical program execution and usage

In the main, the first thing is to set the template type. 

using T = double; 
further work is needed in order to expand the project to work on complex linear systems.

Flow:

```
Main
|
Read_file (all_info.dat)
|
Solve system according to given method
|
Output the solution (x) to the given output file
```



### List of inputs
To solve the linear equation, the user may input several parameters listed below:

Mandatory fields are "Matrix A file", "Vector b file", "Method Chosen", "Output file", these must be
written in the `all_info.dat` followed by ':' as shown below. 

The default preonditioner is the identity matrix
with the same size as A (which corresponds to not using a preconditioner). 

For the iterative methods, if either the "Tolerance" or "Iterations" is not found in the the `all_info.dat` file, the default values are "100" and "10^(-3)" respectively 

- Matrix A file: `../examples/MatrixA.dat`
- Vector b file: `../examples/VectorB.dat`
- Method chosen: `LU`
- Output file: `../examples/Output.dat`
- Preconditioner: `../examples/MatrixP.dat`
- Tolerance: `0.001`
- Iterations: `10000` 

The matrix files should be given in the same form as in 
[The matrix market](https://math.nist.gov/MatrixMarket/)

The vector is to be entered with one element per line.

*Please refer to the `examples` folder for examples*

### List of features

#### Solving linears systems

This program enables the user to:
- Solve linear systems using 6 different methods (2 direct and 4 indirect methods)
- Test the program
- Input specific parameters
- Output the solution onto a file


#### Managing errors
The program can manage the following warning:
- If the maximum number of iteration is reach before the tolerance in an iterative method a message is shown to the user. This may indicate that either the method does not converge or that the number of iterations must be increased to obtain the desired tolerance.

The program can manage the following errors:
- The incorrect numbers of arguments have been inputted
- The user give the wrong name of a method
- The user give a matrix which is not square
- The user give a matrix with missing or without elements
- The user give incompatible size of matrix or vector (A, P or b)
- A file given by the user cannot be open


## List of test

This project have three cpp file using GoogleTest, the tests performs in this file are listed below:
- Matrix_A1_3by3_test.cpp: This file gathers three tests to verify the correct functioning of the LU, Cholesky and Conjugate Gradient algorithms. It take a simple 3 by 3 matrix A and vector b 3 by 1 and compute the solution of th system Ax = b. The correct solution x was computed using Matlab.

- Matrix_A2_3by3_test.cpp: This file gathers three tests to verify the correct functioning of the Richardson, Jacobi and Gauss-Seidel algorithms. It take a simple 3 by 3 matrix A and vector b 3 by 1 and compute the solution of th system Ax = b. The correct solution x was computed using the method LU which give an exact solution.

- Matrix_1000x1000_all.cpp: Given a diagonally dominant matrix, the idea is to test the computaitonal speed of the Jacobi, LU, Cholesky, Gauss-Seidel and Conjugate method. The Richardson may also converge given an "appropriate" preconditioner. 

## Doxygen documentation and html 

In order to better visualize the program, we added a "Documentation" folder which contains a Doxyfile. To generate the html, run the following commands on the terminal (from the root directory):

``cd Documentation`` (you should find a "Doxyfile")


``doxygen Doxyfile`` (this wil generate a html directory)

``cd html`` (enter html directory)

``firefox index.html`` (to open the html on firefox)

This will open a tab on firefox which assembles all the comments, generated class graphs and other useful ressources


## Limitation and problem

The following limitation and problem have been encountered:
- The way the Matrix class was coded prevents an optimum factorization of the code for the transpose function and does not allow to have a transpose method in the UpperTriangular class.
- For the same reasons it implies a not very intuitive writing when multiplying a matrix with a vector.
- For the stopping criterion of the iterative methods we used the relative residual, this may be an unsatisfactory criterion for some matrices (if A is ill-conditioned for example). Different 
stopping criteria such as difference between successive iterates could be used depending on the inputted matrix
- One must be aware that the stopping criterion for iterative methods is here defined as the relative residual. So when the tolerance is entered by the user it is important to remember that it is the relative residual which must be smaller than the set tolerance. This implies that in the tests, when the difference between the true 'x vector' and the approximation by the tested method is calculated and compared (Assert near) with an "absolute error" of 1e-6 which does not correspond to the tolerance initially defined.
## TODOs and perspective

- In order to ensure better inheritance and polymorphism in the Matrix class it would be necessary to completely rethink the hierarchy. It would be required to have a first abstract class that defines only the bracket overloading operator to access the elements of a matrix. Then via a set of pointers it would be possible to allow more advanced things such as covariant return types.
- Precise the format and the way the solution is outputted (scientific, precision)
- Estimate the condition number and say if the matrix is ill-conditioned
- Make sure that the code can also work with other types than double (e.g. complex numbers). It should be able to since everything has been coded with templated classes and functions but this has never been properly verified. 
- For the LU method, an upgrade would be to use pivoting in order to solve matrices with possible 
diagonal entries equal to zero
- Upgrade Richardson method to have a dynamic precondition Richardson with alpha is not = 1

  
**In order to get a better idea of where the improvement points are in the code, you can search for the keywords TODO and FIXME**


## Numerical Analysis 
For all questions relating to whether your given matrix will/should converge or not 
please refer to: "Numerical mathematics / Alfio Quarteroni, Riccardo Sacco, Fausto Saleri". Year: 2007. 
