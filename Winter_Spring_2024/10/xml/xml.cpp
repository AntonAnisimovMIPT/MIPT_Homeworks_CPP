#include <cassert>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <pugixml.hpp>

// =================================================================================================

void save(const std::filesystem::path& path, const pugi::xml_document& doc)
{
    if (doc.save_file(path.string().c_str()))
    {
        std::cout << path.string() << std::endl;
    }
    else
    {
        throw std::runtime_error("Failed to save XML " + path.string());
    }
}

// =================================================================================================

[[nodiscard]] pugi::xml_document load(const std::filesystem::path& path)
{
    pugi::xml_document doc;
    if (doc.load_file(path.string().c_str()))
    {
        return doc;
    }
    else
    {
        throw std::runtime_error("Failed to load XML " + path.string());
    }
}

// =================================================================================================

struct Example
{
    bool b{};
    std::vector<int> vector;

    struct S
    {
        std::string string;
        double d{};
    } s;
};

// =================================================================================================

struct Key
{
    static constexpr auto b = "b";
    static constexpr auto vector = "vector";
    static constexpr auto s = "s";
    static constexpr auto string = "string";
    static constexpr auto d = "d";
};

// =================================================================================================

int main()
{
    const Example example{true, {1, 2, 3, 4, 5}, {"hello", 3.14}};

    constexpr auto file = "13.12.serialization.xml.example.xml";

    {
        pugi::xml_document doc;

        auto root = doc.append_child("Example");

        root.append_attribute(Key::b).set_value(example.b ? "true" : "false");

        auto vNode = root.append_child(Key::vector);
        for (const auto& item : example.vector)
        {
            vNode.append_child("item").text().set(std::to_string(item).c_str());
        }

        auto sNode = root.append_child(Key::s);
        sNode.append_child(Key::string).text().set(example.s.string.c_str());
        sNode.append_child(Key::d).text().set(std::to_string(example.s.d).c_str());

        save(file, doc);
    }

    {
        const auto doc = load(file);

        auto root = doc.child("Example");

        
        std::vector<int> loaded;
        for (auto item : root.child(Key::vector).children("item"))
        {
            loaded.push_back(std::stoi(item.text().get()));
        }   
    }

    std::cout << "Enter any character to continue: "; char c{}; std::cin >> c;

    std::filesystem::remove(file);

    return 0;
}
