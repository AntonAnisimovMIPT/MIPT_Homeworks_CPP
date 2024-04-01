#include <iostream>
#include <regex>
#include <string>

auto formatted(const std::string& input_date) {

    return std::regex_replace(input_date, std::regex(R"(\b(\d{2})/(\d{2})/(\d{4})\b)"), "$3.$2.$1");
}

int main() {
    std::string original_format = "01/04/2024";

    std::string formatted_text = formatted(original_format);
    std::cout << formatted_text << "\n";
}
