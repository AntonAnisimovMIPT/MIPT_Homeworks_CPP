#include <iostream>
#include <string>
#include <cctype>

auto convert_token(const std::string& token) {
    if (token.empty()) {
        return std::string("");
    }

    std::string result_token = token;
    result_token[0] = std::toupper(result_token[0]);

    for (size_t i = 1; i < result_token.length(); ++i) {
        result_token[i] = std::tolower(result_token[i]);
    }
    return result_token;
}

void convert() {
    std::string input;
    std::getline(std::cin, input);

    bool is_prev_alpha = false; 

    std::string sequence;

    for (char c : input) {
        if (std::isalpha(c)) {

            sequence += c;
            is_prev_alpha = true; 

        } else {
            if (is_prev_alpha) { 

                std::cout << convert_token(sequence);
                sequence.clear();
                is_prev_alpha = false; 

            }
            std::cout << c;
        }
    }
    if (is_prev_alpha) { 
        std::cout << convert_token(sequence);
    }
}

int main() {
    convert();
 
}
