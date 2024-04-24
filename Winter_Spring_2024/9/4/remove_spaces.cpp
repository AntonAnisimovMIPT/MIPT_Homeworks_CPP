#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

void remove_spaces(const std::string& input_file) {
    
    std::ifstream inputFile(input_file);

    std::ofstream output_file("without_spaces.txt");

    std::string readable_line;
    while (std::getline(inputFile, readable_line)) {

        if (!readable_line.empty() && !std::all_of(readable_line.begin(), readable_line.end(), [](unsigned char c) { return std::isspace(c); }))
        {
            output_file << readable_line << std::endl;
        }
        
    }

    inputFile.close();
    output_file.close();

}

int main() {
    std::string input_file = "with_spaces.txt";
    remove_spaces(input_file);
}
