#include <iostream>

template <typename F, typename... Types>
auto to_call(F&& f, Types&&... args) {
    return f(std::forward <Types> (args)...);
}

double multiplication(double a, double b, double c) {
    return a*b*c;
}

int main() {

    
    std::cout << to_call(multiplication, 1.0, 2.0, 3.0);
    
}
