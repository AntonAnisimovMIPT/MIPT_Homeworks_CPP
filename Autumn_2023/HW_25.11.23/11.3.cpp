#include <iostream>

constexpr auto e (double input) {
    auto x_n = 1.0; // это n-й член ряда
    auto sum = 1.0; // т.к по формуле Маклорена самый первый член ряда = 1

    int n = 0;
    while (x_n >= input) {
        ++n;
        x_n /= n;
        sum += x_n;
    }
    return sum;

}

int main() {
    constexpr double precesion = 0.000001;
    std::cout << e(precesion);
    }

