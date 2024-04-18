#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>


std::string to_hex(const std::vector<uint8_t>& bytes) {
    std::ostringstream oss;

    oss << std::hex << std::uppercase << std::setfill('0');

    for (uint8_t byte : bytes) {
        oss << std::setw(2) << static_cast<int>(byte);
    }

    return oss.str();
}

int main() {

    std::string hex = to_hex({0xBA, 0xAD});

    std::cout << hex;

}
