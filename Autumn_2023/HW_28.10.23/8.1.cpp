#include <iostream>
#include <string>

class Person {
public:

    Person() : name("no name"), age(0), height(0) {}

    void SetName(const std::string& name) {
        this->name = name;
    }

    void SetAge(int age) {
        this->age = age;
    }

    void SetHeight(double height) {
        this->height = height;
    }

    void show() const {
        std::cout << "Name: " << name << "\nAge: " << age << "\nHeight: " << height << "\n";
    }

private:
    std::string name;
    int age;
    double height;
};

class Builder {
public:

    Builder& name(const std::string& name) {
        m_p.SetName(name);
        return *this;
    }

    Builder& age(int age) {
        m_p.SetAge(age);
        return *this;
    }

    Builder& height(double height) {
        m_p.SetHeight(height);
        return *this;
    }

    [[nodiscard]] Person get() const {
        return m_p;
    }

private:
    Person m_p;
};

int main() {
    std::cout << "empty person: " << "\n";
    Person empty_person;
    empty_person.show();

    std::cout << "built person: " << "\n";
    Builder builder;
    Person p= builder.name("Ivan").age(26).height(180).get();
    p.show();

    return 0;
}