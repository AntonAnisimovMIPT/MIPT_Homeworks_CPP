#include <iostream>
#include "boost/numeric/ublas/matrix.hpp"
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <timer.h>

auto LU_det(const boost::numeric::ublas::matrix<double>& matrix) {
    
    boost::numeric::ublas::permutation_matrix<> perm(matrix.size1());
    boost::numeric::ublas::matrix<double> SavedA(matrix);

    boost::numeric::ublas::lu_factorize(SavedA, perm);

    auto det = 1.0;

    for (std::size_t i = 0; i < SavedA.size1(); ++i) {
        det *= SavedA(i, i);
    }

    
    if ((perm.size()) % 2 == 0) {
        det = -det;
    }

    return det;
}

auto My_det(const boost::numeric::ublas::matrix<double>& matrix) {

    auto matrix_size = matrix.size1();
    
    if (matrix_size == 1) {
        return matrix(0, 0);
    }
    
    double dt = 0;
    
    for (auto i = 0; i < matrix_size; ++i) {

        boost::numeric::ublas::matrix<double> minor(matrix_size - 1, matrix_size - 1);
        for (auto j = 1; j < matrix_size; ++j) {
            for (int k = 0, col = 0; k < matrix_size; ++k) {
                if (k != i) {
                    minor(j - 1, col++) = matrix(j, k);
                }
            }
        }
        
        auto det_minor = My_det(minor);
        if (i % 2 == 0) {
            dt += matrix(0, i) * det_minor;
        } else {
            dt -= matrix(0, i) * det_minor;
        }
    }
    
    return dt;
}

int main() {

    boost::numeric::ublas::matrix<double> matrix1(5, 5);
    matrix1(0, 0) = 1; matrix1(0, 1) = 1; matrix1(0, 2) = 1; matrix1(0, 3) = 1; matrix1(0, 4) = 2;
    matrix1(1, 0) = 2; matrix1(1, 1) = 8; matrix1(1, 2) = 6; matrix1(1, 3) = 5; matrix1(1, 4) = 5;
    matrix1(2, 0) = 7; matrix1(2, 1) = 1; matrix1(2, 2) = 10; matrix1(2, 3) = 7; matrix1(2, 4) = 4;
    matrix1(3, 0) = 10; matrix1(3, 1) = 11; matrix1(3, 2) = 9; matrix1(3, 3) = 2; matrix1(3, 4) = 11;
    matrix1(4, 0) = 3; matrix1(4, 1) = 13; matrix1(4, 2) = 2; matrix1(4, 3) = 15; matrix1(4, 4) = 14;

    Timer timer;

    timer.start();
    auto det1 = LU_det(matrix1);
    timer.pause();
    std::cout << "LU_det:\nDeterminant (5x5): " << det1 << ", time: " << timer.get_mean_measure() << "\n";
    timer.restart();

    timer.start();
    det1 = My_det(matrix1);
    timer.pause();
    std::cout << "My_det:\nDeterminant (5x5): " << det1 << ", time: " << timer.get_mean_measure() << "\n";
    timer.restart();

    boost::numeric::ublas::matrix<double> matrix2(6, 6);
    matrix2(0, 0) = 1; matrix2(0, 1) = 1; matrix2(0, 2) = 1; matrix2(0, 3) = 1; matrix2(0, 4) = 2; matrix2(0, 5) = 5;
    matrix2(1, 0) = 2; matrix2(1, 1) = 8; matrix2(1, 2) = 6; matrix2(1, 3) = 5; matrix2(1, 4) = 5; matrix2(1, 5) = 5;
    matrix2(2, 0) = 7; matrix2(2, 1) = 1; matrix2(2, 2) = 10; matrix2(2, 3) = 7; matrix2(2, 4) = 4; matrix2(2, 5) = 81;
    matrix2(3, 0) = 10; matrix2(3, 1) = 11; matrix2(3, 2) = 9; matrix2(3, 3) = 2; matrix2(3, 4) = 11; matrix2(3, 5) = 13;
    matrix2(4, 0) = 3; matrix2(4, 1) = 13; matrix2(4, 2) = 2; matrix2(4, 3) = 15; matrix2(4, 4) = 14; matrix2(4, 5) = 14;
    matrix2(5, 0) = 9; matrix2(5, 1) = 76; matrix2(5, 2) = 45; matrix2(5, 3) = 84; matrix2(5, 4) = 24; matrix2(5, 5) = 47;

    timer.start();
    auto det2 = LU_det(matrix2);
    timer.pause();
    std::cout << "LU_det:\nDeterminant (6x6): " << det2 << ", time: " << timer.get_mean_measure() << "\n";
    timer.restart();

    timer.start();
    det2 = My_det(matrix2);
    timer.pause();
    std::cout << "My_det:\nDeterminant (6x6): " << det2 << ", time: " << timer.get_mean_measure() << "\n";
    timer.restart();

    boost::numeric::ublas::matrix<double> matrix3(7, 7);
    matrix3(0, 0) = 1; matrix3(0, 1) = 1; matrix3(0, 2) = 1; matrix3(0, 3) = 1; matrix3(0, 4) = 2; matrix3(0, 5) = 5; matrix3(0, 6) = 51;
    matrix3(1, 0) = 2; matrix3(1, 1) = 8; matrix3(1, 2) = 6; matrix3(1, 3) = 5; matrix3(1, 4) = 5; matrix3(1, 5) = 5; matrix3(1, 6) = 13;
    matrix3(2, 0) = 7; matrix3(2, 1) = 1; matrix3(2, 2) = 10; matrix3(2, 3) = 7; matrix3(2, 4) = 4; matrix3(2, 5) = 81; matrix3(2, 6) = 24;
    matrix3(3, 0) = 10; matrix3(3, 1) = 11; matrix3(3, 2) = 9; matrix3(3, 3) = 2; matrix3(3, 4) = 11; matrix3(3, 5) = 13; matrix3(3, 6) = 74;
    matrix3(4, 0) = 3; matrix3(4, 1) = 13; matrix3(4, 2) = 2; matrix3(4, 3) = 15; matrix3(4, 4) = 14; matrix3(4, 5) = 14; matrix3(4, 6) = 89;
    matrix3(5, 0) = 9; matrix3(5, 1) = 76; matrix3(5, 2) = 45; matrix3(5, 3) = 84; matrix3(5, 4) = 24; matrix3(5, 5) = 47; matrix3(5, 6) = 2;
    matrix3(6, 0) = 92; matrix3(6, 1) = 77; matrix3(6, 2) = 78; matrix3(6, 3) = 91; matrix3(6, 4) = 54; matrix3(6, 5) = 87; matrix3(6, 6) = 29;

    timer.start();
    auto det3 = LU_det(matrix3);
    timer.pause();
    std::cout << "LU_det:\nDeterminant (7x7): " << det3 << ", time: " << timer.get_mean_measure() << "\n";
    timer.restart();

    timer.start();
    det2 = My_det(matrix3);
    timer.pause();
    std::cout << "My_det:\nDeterminant (7x7): " << det3 << ", time: " << timer.get_mean_measure() << "\n";
    timer.restart();


    

}