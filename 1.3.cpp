#include <iostream>

int main() {
    char input{};
    std::cout << "Input symbol: " << "\n";
    std::cin >> input;

    switch (input) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            std::cout << "Decimal digit entered" << "\n";
            break;

        case '+': case '-': case '*': case '/':
            std::cout << "Arithmetic operator entered" << "\n";
            break;

        case '(': case ')':
            std::cout << "Parenthesis entered" << "\n";
            break;

        default:
            std::cout << "Other symbols entered" << "\n";
            break;
    }

}
