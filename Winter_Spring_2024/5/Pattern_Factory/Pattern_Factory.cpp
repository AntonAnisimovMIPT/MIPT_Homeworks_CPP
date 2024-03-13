#include <iostream>
#include <functional>
#include <unordered_map>

class Computer {
public:
    virtual ~Computer() = default; // note: polymorphic base class
    virtual void run() const = 0;
};

struct Mobile : public Computer { void run() const override { std::cout << "Mobile" << std::endl; }; };
struct Tablet : public Computer { void run() const override { std::cout << "Tablet" << std::endl; }; };
struct Laptop : public Computer { void run() const override { std::cout << "Laptop" << std::endl; }; };

class Factory {
public:
    Factory() {
        package_of_instructions["Mobile"] = []() { return new Mobile; };
        package_of_instructions["Tablet"] = []() { return new Tablet; };
        package_of_instructions["Laptop"] = []() { return new Laptop; };
    }

    Computer* create(const std::string& type) const {
        auto it = package_of_instructions.find(type);
        if (it != package_of_instructions.end()) {
            return (it->second)();
        }
        return nullptr; 
    }

private:
    std::unordered_map<std::string, std::function<Computer*()>> package_of_instructions;

};

int main() {
    Factory factory;
    
    {
        Computer* mobile = factory.create("Mobile");
        mobile->run();
    }
    
    {
        Computer* tablet = factory.create("Tablet");
        tablet->run();
    }

    {
        Computer* laptop = factory.create("Laptop");
        laptop->run();
    }

    return 0;
}
