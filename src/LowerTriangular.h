#ifndef AWESOME_PROJECT_LOWERTRIANGULAR_H
#define AWESOME_PROJECT_LOWERTRIANGULAR_H
#include "Matrix.h"
#include "UpperTriangular.h"

/** \brief Class for lower triangular matrix
 *
 * This class is used to store a matrix in a vector. It has public methods and private members
 *
 * It stores in an efficient way a lower triangular matrix
 *
 * @tparam T Template parameter
 */
template <typename T>
class LowerTriangular: public UpperTriangular<T> {
public:
    /** \brief Constructor of Matrix
     * @param Rows Number of rows in the matrix = number of columns (square matrix)
     */
    explicit LowerTriangular(unsigned int Rows);
    /** \brief Operator round bracket overloading
     * Accessor method for assigning the value at row = x and column = y
     * @param x : Index of the rows
     * @param y : Index of the columns
     * @return The value of the matrix at the position (x,y) with zero-indexing basis
     */
    T& operator()(unsigned int x, unsigned int y) override;
    /** \brief Operator round bracket overloading with const
    * Accessor method for fetching the value at row = x and column = y
    * @param x : Index of the rows
    * @param y : Index of the columns
    * @return The value of the matrix at the position (x,y) with zero-indexing basis
    */
    T operator()(unsigned int x, unsigned int y) const override;
    /** \brief Get the lower triangular part of a matrix
     * @param m : The matrix from which you want to get the lower part
     */
    void GetLowerTriangularPart(Matrix<T> &m);
    /** \brief Transpose a matrix
    * @return The transpose of a matrix
    */
    UpperTriangular<T> transpose() const;
};

#include "LowerTriangular.tpp"

#endif //AWESOME_PROJECT_LOWERTRIANGULAR_H
