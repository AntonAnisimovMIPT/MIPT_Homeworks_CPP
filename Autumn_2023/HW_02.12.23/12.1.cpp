#include <iostream>
#include <limits>
#include <stdexcept>

using ull = unsigned long long;

class overflow : public std::exception {
public:
    const char* what() const noexcept override {
        return "overflow!!!";
    }
};

bool mult_overed(ull a, ull b) {
    return (a > std::numeric_limits<ull>::max() / b);
}



int pow(ull a, ull x) {


    int result = 1;

    while (x > 0) {
        if (x % 2 == 1) {
            if (mult_overed(result, a)) {
                throw overflow();
            }

            result *= a;
        }

        if (mult_overed(a, a)) {
            throw overflow();
        }

        a *= a;
        x /= 2;
    }

    return result;
}

int main() {


    int result = pow(0, 100000000000000);
    std::cout << result << "\n";

    result = pow(2, 10);
    std::cout << result << "\n";

    result = pow(2, 50000000000);
    std::cout << result << "\n";


    return 0;
}
