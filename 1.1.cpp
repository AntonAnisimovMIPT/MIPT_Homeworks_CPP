#include <iostream>

int main() {
    int x{};
    int y{};

    std::cout << "input x:" << "\n";
    std::cin >> x;

    std::cout << "input y:" << "\n";
    std::cin >> y;

    x = x + y;
    y = x - y;
    x = x - y;
    std::cout << "new x = " << x << "\n" << "new y = " << y;
}