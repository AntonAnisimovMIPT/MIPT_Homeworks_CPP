#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

void delete_older(const std::string& Path, const std::string& Time_str) {

    std::tm inputTime = {};
    std::istringstream ss(Time_str);
    ss >> std::get_time(&inputTime, "%Y-%m-%d %H:%M:%S");

    auto input_time = std::chrono::system_clock::from_time_t(std::mktime(&inputTime)).time_since_epoch();

    for (const auto& entry : std::filesystem::recursive_directory_iterator(Path)) {

        auto file_time = std::filesystem::last_write_time(entry).time_since_epoch();
    
        if (file_time < input_time) {
           
                if (std::filesystem::is_regular_file(entry)) {
                    std::filesystem::remove(entry);
                }
        }
    }
}

int main() {

    std::string path;
    std::cin >> path;

    std::string time;
    std::cin >> time;

    delete_older(path, time);
   
}
