#ifndef AWESOME_PROJECT_READ_FILE_H
#define AWESOME_PROJECT_READ_FILE_H
#include "Matrix.h"
#include "Vector.h"
#include <map>
#include <string>

/** \brief Static class for reading file
 * @tparam T Template parameter
 */
template<typename T>
class Read_file {
public:
    /** \brief Read from a file to a vector
     * @tparam T : Template parameter
     * @param file_path : Full file path
     * @return The vector in the file as vector
     */
    static Vector<T> Read_file_vector(std::string &file_path);
    /** \brief Read from a file to a Matrix
     * @tparam T : Template parameter
     * @param file_path : Full file path
     * @return The matrix in the file
     */
    static Matrix<T> Read_file_Matrix(std::string &file_path);
    /** \brief Checking valid argument
     * @param tmpmap Map of the input argument
     */
    static void Checking_input(std::map<std::string, std::string> &tmpmap);
    /** \brief Function that read input argument from the main
     * @param argv List or argument from the main (only all_info.dat)
     */
    static void Reading_input_argument(char *argv[]);
};

#include "Read_file.tpp"

#endif //AWESOME_PROJECT_READ_FILE_H
