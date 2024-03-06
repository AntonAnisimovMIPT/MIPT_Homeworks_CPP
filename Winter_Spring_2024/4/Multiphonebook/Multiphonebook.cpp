#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <iostream>
#include <string>

using namespace boost::multi_index;

struct Entry {
    Entry(const std::string& name, const std::string& phone) : Person_Name(name), Phone_Number(phone) {}

    std::string Person_Name;
    std::string Phone_Number;
};

using container_t = multi_index_container< Entry, indexed_by<
        random_access<>,
        ordered_unique<member<Entry, std::string, &Entry::Person_Name>>,
        hashed_unique<member<Entry, std::string, &Entry::Person_Name>> >>;

void Add(container_t& container, const std::string& name, const std::string& phone) {
    container.push_back(Entry(name, phone));
}

std::vector<Entry> SortEntries(const container_t& directory) {
    std::vector<Entry> sorted;

    const auto& index = directory.get<1>();
    std::copy(index.begin(), index.end(), std::back_inserter(sorted));
    return sorted;
}

const Entry* FindName(const container_t& directory, const std::string& name) {
    auto& index = directory.get<2>();
    auto it = index.find(name);
    return it != index.end() ? &(*it) : nullptr;
}

int main() {
    container_t log;

    Add(log, "Ivanov", "8-905-111-22-33");
    Add(log, "Sidorov", "8-495-111-22-33");
    Add(log, "Antonov", "8-905-111-22-33");

    std::cout << "Random access:   \n";
    for (const auto& entr : log) {
        std::cout << "Name: " << entr.Person_Name << ", Phone number: " << entr.Phone_Number << std::endl;
    }
    
    std::cout << "Sorted:   \n";
    std::vector<Entry> sorted = SortEntries(log);
    for (const auto& entr : sorted) {
        std::cout << "Name: " << entr.Person_Name << ", Phone number: " << entr.Phone_Number << std::endl;
    }

    std::cout << "Found:   \n";
    auto person = FindName(log, "Sidorov");
    if (person) {
        std::cout << person->Person_Name << " found! Phone number: " << person->Phone_Number << "\n";
    } else {
        std::cout << "Entry doesn't exists!!!\n";
    }

    return 0;
}
