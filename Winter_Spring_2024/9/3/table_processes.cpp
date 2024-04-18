#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct Process_Info {
    std::string name;
    int id;
    std::string status;
    std::string owner;
};

void processes_table(const std::vector<Process_Info>& processes) {

    std::cout << std::setw(15) << std::left << "Name"
              << std::setw(10) << std::left << "ID"
              << std::setw(15) << std::left << "Status"
              << std::setw(15) << std::left << "Owner" << "\n";

    for (const auto& process : processes) {
        
        std::cout << std::setw(15) << std::left << process.name;
        std::cout << std::setw(10) << std::left << process.id;
        std::cout << std::setw(15) << std::left << process.status;
        std::cout << std::setw(15) << std::left << process.owner << "\n";
    }

}

int main() {

    std::vector<Process_Info> processes = {
        {"telegram", 1, "running", "Anton"},
        {"powershell", 2, "running", "Anton"},
        {"vs code", 3, "running", "Anton"},
    };

    processes_table(processes);
}
