#include <iostream>
#include <boost/multi_array.hpp>

struct Point{
    double x;
    double y;
    double z;
};

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
    typedef boost::multi_array<double, 2> array_type;

    array_type matrix1(boost::extents[3][3]);
    std::vector <Point> init1 = {
        {1, 21, 3},
        {61, 5, 4},
        {7, 83, 9}
    };

    for (std::size_t i = 0; i < init1.size(); ++i) {
        matrix1[i][0] = init1[i].x;
        matrix1[i][1] = init1[i].y;
        matrix1[i][2] = init1[i].z;
    }

    auto det1 = det(matrix1);
    std::cout << "Determinant: " << det1 << " --> Not lineary dependent." << "\n";

    array_type matrix2(boost::extents[3][3]);
    std::vector <Point> init2 = {
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3}
    };

    for (std::size_t i = 0; i < init2.size(); ++i) {
        matrix2[i][0] = init2[i].x;
        matrix2[i][1] = init2[i].y;
        matrix2[i][2] = init2[i].z;
    }

    auto det2 = det(matrix2);
    std::cout << "Determinant: "  << det2 << " --> Lineary dependent.";

    return 0;
}
