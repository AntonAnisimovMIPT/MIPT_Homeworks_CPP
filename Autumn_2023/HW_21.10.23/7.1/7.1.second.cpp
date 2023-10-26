#include <iostream>

class Print {
public:
    ~Print() {std::cout << "I could for twice!!!" << "\n";}
};

Print print;
int main() {
    return 0;
}

