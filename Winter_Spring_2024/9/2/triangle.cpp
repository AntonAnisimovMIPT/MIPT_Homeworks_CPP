#include <iostream>
#include <vector>
#include <iomanip>

void triangle(int height) {
    std::vector<std::vector<int>> elements(height, std::vector<int>(height, 0));

    for (int i = 0; i < height; ++i) {
        elements[i][0] = 1; 
        for (int j = 1; j <= i; ++j) {
            elements[i][j] = elements[i - 1][j - 1] + elements[i - 1][j]; 
        }
    }


    for (int i = 0; i < height; ++i) {
    
        std::cout << std::string((height - i - 1) * 3, ' ');
        for (int j = 0; j <= i; ++j) {

            std::cout << std::setw(4) << elements[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

int main() {
    triangle(10);
}
