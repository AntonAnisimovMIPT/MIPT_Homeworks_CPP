#include <iostream>
#include <complex>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(1);
    std::complex<double> z1(1.0, 1.0);
    std::complex<double> z2(3.0, 4.0);
    std::complex<double> i(0.0, 1.0);
    std::cout << "Re z1: " << z1.real() << "\tIm z1: " << z1.imag();
    std::cout << "\nRe z2: " << z2.real() << "\tIm z2: " << z2.imag();
    std::cout << "\nabs(z2): " << std::abs(z2);
    std::cout << "\nz1 + z2: " << z1 + z2;
    std::cout << "\nz1 * z2: " << z1 * z2;
    std::cout << "\ni^2: " << std::pow(i, 2);
    std::cout << "\nsin(z1): " << std::sin(z1);
    std::cout << "\nlog(z2): " << std::log(z2);

}
