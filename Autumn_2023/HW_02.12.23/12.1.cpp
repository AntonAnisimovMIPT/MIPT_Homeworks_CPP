#include <iostream>
#include <limits>
#include <stdexcept>

class overflow : public std::exception {
public:
    const char* what() const noexcept override {
        return "overflow!!!";
    }
};

bool mult_overed(int a, int b) {
    return (b != 0 && a > std::numeric_limits<int>::max() / b);
}

bool pow_overed(int a, int x) {
    if (x == 0) {
        return false;
    }

    int result = 1;

    for (int i = 0; i < x; ++i) {
        if (mult_overed(result, a)) {
            return true;
        }

        result *= a;
    }

    return false;
}


int pow(int a, int x) {

    if (pow_overed(a, x)) {
        throw overflow();

    }

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

    result = pow(2, 50);
    std::cout << result << "\n";


    return 0;
}
