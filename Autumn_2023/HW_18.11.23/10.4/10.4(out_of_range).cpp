#include <iostream>
#include <vector>
#include <stdexcept>


int main()
{

    try
    {
        std::vector<int> vec(5);
        vec.at(6)=42;

    }
    catch (const std::out_of_range& exception)
    {
        std::cout << "range failure: std::out_of range" ;
    }
}