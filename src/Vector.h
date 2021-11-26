#ifndef AWESOME_PROJECT_VECTOR_H
#define AWESOME_PROJECT_VECTOR_H

#include "Matrix.h"

/** \brief Class Vector to store vector in a matrix with only one rows
 * @tparam T : Template parameter
 */
template <typename T>
class Vector : public Matrix<T> {
public:
    /** \brief Constructor of Vector
     * @param size : The size of the vector
     */
    explicit Vector(unsigned int size);
    /** \brief Constructor of Vector
     * @param std_vector : A standard vector form stl library
     */
    explicit Vector(std::vector<T> std_vector);
    /** \brief Operator round bracket overloading
     *
     * Accessor method for assigning the value at row = x
     *
     * @param x : Index of the row
     * @return The value of the vector at the position x with zero-indexing basis
     */
    T& operator()(unsigned int x);
    /** \brief Operator round bracket overloading with const
     *
     * Accessor method for fetching the value at row = x
     *
     * @param x : Index of the row
     * @return The value of the vector at the position x with zero-indexing basis
     */
    T operator()(unsigned int x) const;
    /** \brief Operator plus overloading between two vectors
     * @param vec : The right hand side vector
     * @return A result vector of the difference between the two
     */
    Vector<T> operator+(const Vector<T> &vec) const;
    /** \brief Operator minus overloading between two vectors
     * @param vec : The right hand side vector
     * @return A result vector of the difference between the two
     */
    Vector<T> operator-(const Vector<T> &vec) const;
    /** \brief Multiplication operator overloading between a vector and a scalar
     * @param d : The scalar by which we multiply the vector
     * @return A result vector of the multiplication between the two
     */
    Vector<T> operator*(const T &d) const;
    /** \brief Multiplication operator overloading between a matrix of size nxn with a vector nx1
     * @param m : The multiplication matrix
     * @return The vector issued from the multiplication
     */
    Vector<T> operator*(Matrix<T> &m) const;
    /** \brief Scalar product between two vector
     * @param vec : The other vector (right hand side)
     * @return The result of a scalar product between two vectors
     */
    T DotProduct(Vector<T> &vec) const;
    /** \brief Euclidean norm of a vector
     * @return The euclidean norm of the given vector
     */
    T Norm();
    // TODO: Update to save memory
    //  static Vector<T> GetDiag(Matrix<T> &m);
};

#include "Vector.tpp"

#endif //AWESOME_PROJECT_VECTOR_H