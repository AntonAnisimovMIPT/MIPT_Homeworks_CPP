#include <iostream>
#include <string>
#include <optional>

class Person {
public:
    Person(const std::string& name, int age) : m_name(name), m_age(age) {}

    void SetWeight(double weight) {
        this->m_weight = weight;
    }

    std::optional<double> GetWeight() const {
        return m_weight;
    }

    void DataOfHuman() const {
        std::cout << "name: " << m_name << ", age: " << m_age;
        if (GetWeight().has_value()) {
            std::cout << ", weight: " << GetWeight().value();
        }
        std::cout << "\n";
    }

private:
    std::string m_name;
    int m_age;
    std::optional<double> m_weight;
};

int main() {

    Person boris("Boris", 25);
    boris.DataOfHuman();
    boris.SetWeight(111.11);
    boris.DataOfHuman();

    return 0;
}