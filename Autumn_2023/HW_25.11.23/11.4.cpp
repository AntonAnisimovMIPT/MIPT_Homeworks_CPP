#include <iostream>

constexpr bool bool_simple(int n, int i = 2) {
    return (i * i > n) ? true : ((n % i == 0) ? false : bool_simple(n, i + 1));
}

constexpr int simple(int n, int s = 2, int k = 0) {
    return (k == n) ? s - 1 : simple(n, s + 1, bool_simple(s) ? k + 1 : k);
}

int main() {
    constexpr int N = 3;
    constexpr int result = simple(N);

    std::cout << result << std::endl;

    return 0;
}
