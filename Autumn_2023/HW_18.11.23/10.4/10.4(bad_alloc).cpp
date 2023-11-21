#include <iostream>

int main() {
    try {
        auto arr = new int[1000000000000000];

        delete[] arr;
    }
    catch (const std::bad_alloc& exception) {

        std::cout << "Allocation failed: " << exception.what() ;
    }

    return 0;
}
