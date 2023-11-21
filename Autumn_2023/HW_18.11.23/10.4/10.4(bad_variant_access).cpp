#include <iostream>
#include <variant>

int main()
{
    std::variant<int, double> number;
    number = 111.11;
    try
    {
        std::get<int>(number);
    }
    catch (const std::bad_variant_access& exception)
    {
        std::cout << "Variant access failure: " << exception.what() ;
    }
}