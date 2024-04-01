#include <iostream>
#include <string>
#include <vector>

auto split(const std::string& input_string, const std::vector<std::string>& delimiters) {
    
    std::vector<std::string> output_vector;
    std::string element;

    for (auto s : input_string) {
        bool isDelimiter = false;
        for (auto delimiter : delimiters) {
            if (std::string(1, s) == delimiter) {
                isDelimiter = true;
                break;
            }
        }
        if (isDelimiter) {
            if (!element.empty()) {
                output_vector.push_back(element);
                element.clear();
            }
        } else {
            element += s;
        }
    }
    if (!element.empty()) {
        output_vector.push_back(element);
    }
    return output_vector;
}

int main() {
    std::string str = "I should split-splitted string";
    std::vector<std::string> delimiters = {" ", "-"};

    auto split_str = split(str, delimiters);

    std::cout << "Split: ";
    for (auto i : split_str) {
        std::cout << i << " ";
    }

}
