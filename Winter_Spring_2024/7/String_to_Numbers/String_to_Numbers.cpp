#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>

auto convert(const std::string& input_string) {
    std::vector<std::uint8_t> output;
    for (std::size_t i = 0; i < input_string.length(); i += 2) {
        auto tmp = input_string.substr(i, 2);
        auto element = std::stoul(tmp, nullptr, 16);
        output.push_back(element);
    }
    return output;
}

int main() {
    std::string source_str = "BAAD";
    auto converted = convert(source_str);

    for (std::size_t i = 0; i < std::size(converted); ++i) {
        std::cout << std::uppercase << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(converted[i]) << " ";
    }
}
