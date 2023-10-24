#include "ratio.hpp"

int main() {
    rt::Ratio r1(1, 2);
    rt::Ratio r2(-2, 5);
    (r1 += r2).print();

    rt::Ratio r3(1, 3);
    rt::Ratio r4(-3, 1);
    (r3 /= r4).print();

    rt::Ratio r5(1, 4);
    (++r5).print();

    rt::Ratio r6(1, 4);
    rt::Ratio r7(1, 2);
    (r6 < r7) ? (std::cout << '<' << "\n") : (std::cout << '>' << "\n");

    return 0;
}
