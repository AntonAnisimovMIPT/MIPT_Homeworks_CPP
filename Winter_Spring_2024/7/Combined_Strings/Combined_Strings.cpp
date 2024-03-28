#include <iostream>
#include <vector>
#include <string>

auto combine(const std::vector<std::string>& input_strings, const std::string& delimiter) {
    if (std::size(input_strings) == 0) {
        return std::string("");
    }

    auto output_string = input_strings[0]; 
    for (size_t i = 1; i < std::size(input_strings); ++i) {
        output_string += delimiter;
        output_string += input_strings[i];
    }

    return output_string;
}

int main() {
    std::vector<std::string> strings = {"I", "combined", "URA!"};
    std::string delimiter = "---";

    auto comb = combine(strings, delimiter);
    std::cout << "Combined string: " << comb;

    return 0;
}
