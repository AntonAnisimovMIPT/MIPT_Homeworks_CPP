#include <iostream>
#include <vector>


int main()
{

    try
    {
        std::vector<int> vec;
        vec.resize(vec.max_size()+1);

    }
    catch (const std::length_error& exception)
    {
        std::cout << "length error failure: std::length_error " << exception.what() ;
    }
}
