#include <iostream>

struct Print {
    Print() { std::cout << "I could for third!!!"; }
};

Print print;
int main() {
    return 0;
}