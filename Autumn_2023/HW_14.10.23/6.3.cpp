#include <iostream>

int SizeWithConvolution() { return 0; };

template<typename... Arguments>
int SizeWithConvolution(Arguments... args) {
    return (sizeof(args) + ...);
}

int SizeWithoutConvolution() { return 0; };

template<typename T, typename... Arguments>
int SizeWithoutConvolution(T t, Arguments... arguments) {
    return sizeof(t) + SizeWithoutConvolution(arguments...);
}

int main() {
    auto first = 1;
    auto second = 1.0;
    auto third = 'a';
    std::cout << "with convolution for empty pack: " << SizeWithConvolution() << "\n";
    std::cout << "without convolution for empty pack: " << SizeWithoutConvolution() << "\n";

    std::cout << "with convolution: " << SizeWithConvolution(first, second, third) << "\n";
    std::cout << "without convolution: " << SizeWithoutConvolution(first, second, third) << "\n";
}
