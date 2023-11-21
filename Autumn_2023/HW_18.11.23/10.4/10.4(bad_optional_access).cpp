#include <iostream>
#include <optional>


int main()
{

    try
    {
        std::optional<double> opt;
        auto a = opt.value();
    }
    catch (const std::bad_optional_access& exception)
    {
        std::cout << "Optional access failure: " << exception.what() ;
    }
}