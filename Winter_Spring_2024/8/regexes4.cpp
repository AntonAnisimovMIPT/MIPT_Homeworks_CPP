#include <iostream>
#include <regex>
#include <string>

auto formatted(const std::string& input_date) {
    return std::regex_replace(input_date, std::regex(R"(\b(\d{4})/(0[1-9]|1[0-2])/(0[1-9]|[1-2][0-9]|3[0-1])\b)"), "$1.$2.$3");
}

int main() {
    std::string original_format = "2024/04/24";

    std::string formatted_text = formatted(original_format);
    std::cout << formatted_text << "\n";
}
