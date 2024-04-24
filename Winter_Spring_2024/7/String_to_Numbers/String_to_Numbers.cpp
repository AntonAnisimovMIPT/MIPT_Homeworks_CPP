#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <string_view>

auto hexchar_to_int(char const ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    throw std::invalid_argument("Invalid hexadecimal character");
}

auto convert(std::string_view input_str) {

    std::vector<unsigned char> output;
    for (size_t i = 0; i + 1 < input_str.size(); i += 2) {
        output.push_back((hexchar_to_int(input_str[i]) << 4) | hexchar_to_int(input_str[i + 1]));
    }

    return output;
}

int main() {
    std::string source_str = "BAAD";
    auto converted = convert(source_str);

    for (std::size_t i = 0; i < std::size(converted); ++i) {
        std::cout << std::uppercase << std::showbase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(converted[i]) << " ";
    }
}
