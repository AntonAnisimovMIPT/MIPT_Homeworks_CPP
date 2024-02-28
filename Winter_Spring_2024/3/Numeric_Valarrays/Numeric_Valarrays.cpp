#include <iostream>
#include <valarray>
#include <cmath>

auto norm(const std::valarray<double>& vec) {
    auto result = 0.0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        result += vec[i] * vec[i];
    }
    
    return result;
}

std::valarray<double> projection(const std::valarray<double>& vec, const std::valarray<double>& axis) {
    auto scal_multipl = 0.0;
    for (size_t i = 0; i < vec.size(); ++i) {
        scal_multipl += vec[i] * axis[i];
    }
    auto norm_of_axis = norm(axis);
    
    std::valarray<double> result(axis.size());
    for (size_t i = 0; i < axis.size(); ++i) {
        result[i] = (scal_multipl / norm_of_axis) * axis[i];
    }
    return result;
}

int main() {
    std::valarray<double> vec1 = {1, 1, 1};
    std::valarray<double> axis1 = {2, 2, 2};

    std::valarray<double> proj1 = projection(vec1, axis1);

    for (size_t i = 0; i < proj1.size(); i++)
    {
        std::cout << proj1[i] << " ";
    }

    std:: cout << "\n";

    std::valarray<double> vec2 = {1, 0, 0};
    std::valarray<double> axis2 = {0, 0, 1};

    std::valarray<double> proj2 = projection(vec2, axis2);

    for (size_t i = 0; i < proj2.size(); i++)
    {
        std::cout << proj2[i] << " ";
    }
    
    return 0;
}

/*
    Причины:
    1. Есть много намного более функциональных альтернатив (в библиотеках uBLAS, Eigen, xTensor и др.).
    2. В основном заточен на обработку чисел, что урезает область применения (в то время std::vector позволяет работать не только с числами).

*/
