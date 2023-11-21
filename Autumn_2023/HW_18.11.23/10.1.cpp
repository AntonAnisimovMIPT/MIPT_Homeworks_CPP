#include <iostream>
#include <variant>
#include <cmath>

std::variant <std::monostate, double, std::pair<double, double>> roots(double a, double b, double c) {

    auto D = b*b-4*a*c;
    if (D < 0) {
        return std::monostate();
    }
    else if (D == 0) {
        return -b/(2*a);
    }
    else {
        return std::pair((-b+std::sqrt(D))/(2*a), (-b-std::sqrt(D))/(2*a));
    }

}

int main() {
    double a,b,c = 1.0;
    std::cin >> a >> b >> c;

    if (std::holds_alternative<std::monostate>(roots(a,b,c))) {
        std::cout << "no roots!!!";
    }
    else if (std::holds_alternative<double>(roots(a,b,c))) {
        std::cout << "one root: " <<  std::get<double>(roots(a,b,c));
    }
    else {
        std::cout << "first root: " <<  std::get<std::pair<double, double>>(roots(a,b,c)).first << "\n";
        std::cout << "second root: " <<  std::get<std::pair<double, double>>(roots(a,b,c)).second;
    }

}
