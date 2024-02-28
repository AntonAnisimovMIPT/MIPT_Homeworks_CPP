#include <iostream>
#include <boost/multi_array.hpp>

auto det(const boost::multi_array<double, 2>& matrix) {

    auto matrix_size = matrix.shape()[0];
    
    if (matrix_size == 1) {
        return matrix[0][0];
    }
    
    double dt = 0;
    
    for (auto i = 0; i < matrix_size; ++i) {

        boost::multi_array<double, 2> minor(boost::extents[matrix_size - 1][matrix_size - 1]);
        for (auto j = 1; j < matrix_size; ++j) {
            for (int k = 0, col = 0; k < matrix_size; ++k) {
                if (k != i) {
                    minor[j - 1][col++] = matrix[j][k];
                }
            }
        }
        
        auto det_minor = det(minor);
        if (i % 2 == 0) {
            dt += matrix[0][i] * det_minor;
        } else {
            dt -= matrix[0][i] * det_minor;
        }
    }
    
    return dt;
}

int main() {

    boost::multi_array<double, 2> matrix1(boost::extents[5][5]);
    matrix1[0][0] = 1; matrix1[0][1] = 1; matrix1[0][2] = 1; matrix1[0][3] = 1; matrix1[0][4] = 2;
    matrix1[1][0] = 2; matrix1[1][1] = 8; matrix1[1][2] = 6; matrix1[1][3] = 5; matrix1[1][4] = 5;
    matrix1[2][0] = 7; matrix1[2][1] = 1; matrix1[2][2] = 10; matrix1[2][3] = 7; matrix1[2][4] = 4;
    matrix1[3][0] = 10; matrix1[3][1] = 11; matrix1[3][2] = 9; matrix1[3][3] = 2; matrix1[3][4] = 11;
    matrix1[4][0] = 3; matrix1[4][1] = 13; matrix1[4][2] = 2; matrix1[4][3] = 15; matrix1[4][4] = 14;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << matrix1[i][j] << " ";
        }
        std::cout << "\n";
    }

    auto det1 = det(matrix1);
    std::cout << "Determinant: " << det1 << "--> Not lineary dependent." << "\n";

    boost::multi_array<double, 2> matrix2(boost::extents[5][5]);
    matrix2[0][0] = 1; matrix2[0][1] = 1; matrix2[0][2] = 1; matrix2[0][3] = 1; matrix2[0][4] = 1;
    matrix2[1][0] = 2; matrix2[1][1] = 2; matrix2[1][2] = 2; matrix2[1][3] = 2; matrix2[1][4] = 2;
    matrix2[2][0] = 3; matrix2[2][1] = 3; matrix2[2][2] = 3; matrix2[2][3] = 3; matrix2[2][4] = 3;
    matrix2[3][0] = 4; matrix2[3][1] = 4; matrix2[3][2] = 4; matrix2[3][3] = 4; matrix2[3][4] = 4;
    matrix2[4][0] = 5; matrix2[4][1] = 5; matrix2[4][2] = 5; matrix2[4][3] = 5; matrix2[4][4] = 5;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << matrix2[i][j] << " ";
        }
        std::cout << "\n";
    }

    auto det2 = det(matrix2);
    std::cout << "Determinant: "  << det2 << "--> Lineary dependent.";

}