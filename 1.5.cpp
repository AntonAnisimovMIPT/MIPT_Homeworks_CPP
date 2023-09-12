#include <iostream>

int main() {
    std::cout << "Input epsilon: " << "\n";
    auto input_epsilon = 0.0; // специально сделал тип double, а не float, чтобы точность была побольше
    std::cin >> input_epsilon;
    const auto epsilon = input_epsilon;

    double x_n = 1; // это n-й член ряда
    double sum = 1; // т.к по формуле Маклорена самый первый член ряда = 1

    int n = 0;
    while (x_n >= epsilon) {
        ++n;
        x_n /= n;
        sum += x_n;
    }

    std::cout << "e = " << sum;
}
