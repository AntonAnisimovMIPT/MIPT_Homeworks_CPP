#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

auto convert_word(const std::string& input_word) {

    if (std::size(input_word) == 0)
    {
        return std::string("");
    }

    auto output_word = input_word;

    auto begin = output_word.begin();
    *begin = std::toupper(*begin);

    for (auto i = std::next(output_word.begin(), 1); i != output_word.end(); i++)
    {
        *i = std::tolower(*i);
    }
    return output_word;
    
}

void convert_input() {
    std::string input_word;

    bool isFirstly = true;
    while (std::cin >> input_word) {
        if (!isFirstly) {
            std::cout << " "; 
        }
        isFirstly = false;
        std::cout << convert_word(input_word); 
    }
}

int main() {
    std::cout << "your string: ";
    convert_input();
    std::cout << "\n";
}