#include <iostream>
#include <regex>
#include <string>
#include <vector>

auto emails_search(const std::string& input_string) {
    std::vector<std::string> result;
    std::smatch match;

    auto begin = input_string.begin();
    auto end = input_string.end();

    while (std::regex_search(begin, end, match, std::regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"))) {
        result.push_back(match.str());
        begin = match.suffix().first;
    }

    return result;
}

int main() {
    std::string string = R"( first email is anisimov.av@phystech.edu, but second email @gmail.com is incorrect, third email is anton2051991@mail.ru)";

    auto emails = emails_search(string);

    for (auto email : emails) {
        std::cout << email << std::endl;
    }
}
