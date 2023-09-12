#include <iostream>

int main() {
    for (auto i = 100; i < 1000 ; ++i) {
        auto hundreds = i/100;
        auto tens = (i - 100*hundreds)/10;
        auto units = (i - 100*hundreds - 10*tens);

        auto result = hundreds*hundreds*hundreds + tens*tens*tens + units*units*units;
        if (result == i) {
            std::cout << i << '\n';
        }
    }
}