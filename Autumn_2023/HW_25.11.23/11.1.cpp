#include <iostream>

template <int n, int k>
struct Binom {
    static const int value = Binom<n-1, k-1>::value + Binom<n-1, k>::value;
};

template <int n>
struct Binom<n, 0> {
    static const int value = 1;
};

template <int n>
struct Binom<n, n> {
    static const int value = 1;
};

int main() {

    std::cout << Binom<5, 3>::value << "\n";

    return 0;
}
