#include <iostream>

 int lower_bound(int first, int last, int comp_value, const int* arr)
{
    auto count = last - first;

    while (count > 0)
    {
        auto iter = first;
        auto step = count / 2;
        iter += step;

        if (arr[iter] < comp_value)
        {
            first = ++iter;
            count -= step + 1;
        }
        else
            count = step;
    }

    return first;
}


bool binary_search(int first, int last, int comp_value, int* arr)
{
    first = lower_bound(first, last, comp_value, arr);
    return ((first != last) and !(comp_value < arr[first]));
}

int main() {
    const auto SIZE = 10;
    int arr[SIZE] = {1, 4, 7, 8, 10, 12, 13, 16, 100, 123};

    auto find = 1;

    if (binary_search(0, SIZE, find, arr)) {
        std::cout << "Index of a given number in an array: " << lower_bound(0, SIZE, find, arr);
    }
    else {
        std::cout << "There is no given number!!!";
    }
}
