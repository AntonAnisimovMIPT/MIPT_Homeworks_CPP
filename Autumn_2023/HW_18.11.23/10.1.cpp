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
        return std::make_pair((-b+std::sqrt(D))/(2*a), (-b-std::sqrt(D))/(2*a));
    }

}

int main() {
    double a,b,c;
    std::cin >> a >> b >> c;

    auto rts = roots(a,b,c);
    if (std::holds_alternative<std::monostate>(rts)) {
        std::cout << "no roots!!!";
    }
    else if (std::holds_alternative<double>(rts)) {
        std::cout << "one root: " <<  std::get<double>(rts);
    }
    else {
        auto pr = std::get<std::pair<double, double>>(rts);
        std::cout << "first root: " <<  pr.first << "\n";
        std::cout << "second root: " <<  pr.second;
    }

}
