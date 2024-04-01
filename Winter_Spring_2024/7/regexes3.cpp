#include <iostream>
#include <regex>
#include <string>

struct parts {
    std::string protocol;
    std::string domain;
    std::string port;
    std::string path;
};

auto getted_parts(const std::string& url) {
   
    std::smatch match;
    std::regex_match(url, match, std::regex(R"((\w+):\/\/([^:/]+)(?::(\d+))?\/?(.*))"));

    parts components;
    components.protocol = match[1];
    components.domain = match[2];
    components.port = match[3];
    components.path = match[4];
    

    return components;
}

int main() {
    std::string example_url = "https://developer.mozilla.org:4097/en-US/docs/Web/API/URL/host";
    auto components = getted_parts(example_url);

    std::cout << "protocol: " << components.protocol << "\n";
    std::cout << "domain: " << components.domain << "\n";
    std::cout << "port: " << components.port << "\n";
    std::cout << "path: " << components.path << "\n";

    return 0;
}
