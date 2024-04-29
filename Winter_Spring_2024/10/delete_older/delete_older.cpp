#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

std::chrono::seconds convert(const std::string& time_str) {
   
    std::tm time = {};
    std::istringstream ss(time_str);
    ss >> std::get_time(&time, "%Y.%m.%d-%H:%M");

    auto time_p = std::chrono::system_clock::from_time_t(std::mktime(&time));
    auto seconds_p = std::chrono::duration_cast<std::chrono::seconds>(time_p.time_since_epoch());

    return seconds_p;
}

void delete_older(const std::string& Path, const std::string& Time_str) {

    auto res_tp = convert(Time_str).count();

    for (const auto& entry : std::filesystem::directory_iterator(Path)) {

        auto file_time = std::filesystem::last_write_time(entry);
        auto file_tp = std::chrono::time_point_cast<std::chrono::seconds>(file_time).time_since_epoch().count();
    
        if (file_tp < res_tp) {
           
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