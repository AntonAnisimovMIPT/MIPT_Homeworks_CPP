#include <iostream>

// x xor y c помощью стандартных логических операций можно записать как (x | y) - (x & y)

int main() {
    int x{};
    int y{};
    std::cout << "Input x:" << "\n";
    std::cin >> x;
    std::cout << "Input y:" << "\n";
    std::cin >> y;


    auto result = (x | y) - (x & y);
    std::cout << "result = " << result;
}