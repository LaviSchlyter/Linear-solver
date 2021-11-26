#ifndef AWESOME_PROJECT_MATRIX_H
#define AWESOME_PROJECT_MATRIX_H
#include <vector>
#include <iostream>

/** \class Matrix
 * \brief Practical class for matrix
 *
 * This class is used to store a matrix in a vector. It has public methods and private members
 *
 * @tparam T
 */
template <typename T>
class Matrix {
public:
    /** \brief Constructor of Matrix full with 0
     * @param Rows : Number of rows in the matrix
     * @param Cols : Number of columns in the matrix
     */
    Matrix(unsigned int Rows, unsigned int Cols);
    /** \brief Constructor of Matrix full with 0
     * @param Rows : Number of rows in the matrix
     * @param Cols : Number of columns in the matrix
     * @param size : Number of element non-zero in the matrix (useful in children class)
     */
    Matrix(unsigned int Rows, unsigned int Cols, unsigned int size);
    /// \brief Virtual destructor
    virtual ~Matrix() = default;
    /** \brief Operator round bracket overloading
     *
     * Accessor method for assigning the value at row = x and column = y
     *
     * @param x : Index of the rows
     * @param y : Index of the columns
     * @return The value of the matrix at the position (x,y) with zero-indexing basis
     */
    virtual T& operator()(unsigned int x, unsigned int y);
    /** \brief Operator round bracket overloading with const
     *
    * Accessor method for fetching the value at row = x and column = y
     *
    * @param x : Index of the rows
    * @param y : Index of the columns
    * @return The value of the matrix at the position (x,y) with zero-indexing basis
    */
    virtual T operator()(unsigned int x, unsigned int y) const;
    /** \brief Operator minus overloading
     *
     * Computes the difference between Matrix of column 1 (vector) and vector
     *
     * @param rhs : Right hand side of the minus sign
     * @return The binary minus operation
     */
    std::vector<T> operator-(const std::vector<T> &rhs);
    /** \brief Operator plus overloading between two matrix
     * @param m : The right hand side matrix
     * @return A result matrix of the addition between the two
     */
    Matrix<T> operator+(const Matrix<T> &m) const;
    /** \brief Operator minus overloading between two matrix
     * @param m : The right hand side matrix
     * @return A result matrix of the difference between the two
     */
    Matrix<T> operator-(const Matrix<T> &m) const;
    /** \brief Static method to get the matrix identity
     * @param size : The size of the matrix identity i.e. number of columns = size = number of rows
     * @return A matrix identity
     */
    static Matrix<T> Identity(const unsigned int &size);
    /** \brief Method to return the diagonal of a matrix as a matrix
     * @return Matrix containing the diagonal of a matrix
     */
    Matrix<T> GetDiag();
    /** \brief Friend function to nicely print the matrix
     * @param output : The ostream flow
     * @param m : The matrix to print
     * @return Ostream operator
     */
    template<class Y> friend std::ostream &operator<<(std::ostream &output, const Matrix<Y> &);
    /** \brief Transpose a matrix
     * @return The transpose of a matrix
     */
    Matrix<T> transpose() const;
    /** \brief Accessor to number of rows in matrix
     * @return Number of rows in matrix
     */
    [[nodiscard]] unsigned int GetRowSize() const {return mRows;}
    /**
     * \brief Accessor to number of columns in matrix
     * @return Number of columns in matrix
     */
    [[nodiscard]] unsigned int GetColSize() const {return mCols;}
    /**
     * \brief Accessor to number of elements in matrix
     * @return Number of elements in matrix
     */
    [[nodiscard]] unsigned int GetSize() const {return mSize;}

protected:
    /// Vector storing the matrix data*/
    std::vector<T> mData;
    /// Number of rows in the matrix*/
    unsigned int mRows;
    /// Number of columns in the matrix*/
    unsigned int mCols;
    /// Number of elements in the matrix*/
    unsigned int mSize;
};

#include "Matrix.tpp"

#endif // AWESOME_PROJECT_MATRIX_H