#ifndef AWESOME_PROJECT_UPPERTRIANGULAR_H
#define AWESOME_PROJECT_UPPERTRIANGULAR_H

/** \class UpperTriangular
 * \brief Class for upper triangular matrix
 *
 * This class is used to store a matrix in a vector. It has public methods and private members
 *
 * It stores in an efficient way a upper triangular matrix, because it only stores the part of the matrix which is complete
 *
 * @tparam T Template parameter
 */
template <typename T>
class UpperTriangular: public Matrix<T> {
public:
    /** \brief Constructor of Matrix
     * @param Rows : Number of rows in the matrix = number of columns (square matrix)
     */
    explicit UpperTriangular(unsigned int Rows);
    /** \brief Operator round bracket overloading
     *
     * Accessor method for assigning the value at row = x and column = y
     *
     * @param x : Index of the row
     * @param y : Index of the column
     * @return The value of the matrix at the position (x,y) with zero-indexing basis
     */
    T& operator()(unsigned int x, unsigned int y) override;
    /** \brief Operator round bracket overloading with const
     *
    * Accessor method for fetching the value at row = x and column = y
     *
    * @param x : Index of the row
    * @param y : Index of the column
    * @return The value of the matrix at the position (x,y) with zero-indexing basis
    */
    T operator()(unsigned int x, unsigned int y) const override;
};

#include "UpperTriangular.tpp"

#endif //AWESOME_PROJECT_UPPERTRIANGULAR_H
