#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>
#include <string>
#include <deque>
#include <timer.h>
#include <random>
#include <array>
/*
template <typename Container_Type>
auto Sort_Time (Container_Type& container, Timer& timer) {

    timer.start();
    std::sort(container.begin(), container.end());
    timer.pause();

    return timer.get_mean_measure();
    timer.restart();
    
}
*/
template <typename Container_Type>
void Fill_Container_Randoms(Container_Type& container, std::size_t size, int min, int max) {

    std::random_device device; // note: make seed only once
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> distribution(min, max); // note: [a; b)

    container.clear();
    for (size_t i = 0; i < size; ++i) {
        container.insert(container.end(), distribution(engine));
    }
}

int main() {

    const std::size_t cont_size = 100000;
    int min = 0;
    int max = 100;

    Timer timer;

    std::vector<int> vec;
    Fill_Container_Randoms(vec, cont_size, min, max);

    std::array<int, cont_size> arr;
    std::copy(vec.begin(), vec.end(), arr.begin());

    std::deque<int> deq(vec.begin(), vec.end());
    std::forward_list<int> forw_lst(vec.begin(), vec.end());
    std::list<int> lst(vec.begin(), vec.end());

    timer.start();
    std::sort(vec.begin(), vec.end());
    timer.pause();
    std::cout << "vector: " << timer.get_mean_measure() << "\n";
    timer.restart();

    timer.start();
    std::sort(arr.begin(), arr.end());
    timer.pause();
    std::cout << "array: " << timer.get_mean_measure() << "\n";
    timer.restart();

    timer.start();
    std::sort(deq.begin(), deq.end());
    timer.pause();
    std::cout << "deque: " << timer.get_mean_measure() << "\n";
    timer.restart();

    timer.start();
    forw_lst.sort();
    timer.pause();
    std::cout << "forward list: " << timer.get_mean_measure() << "\n";
    timer.restart();

    timer.start();
    lst.sort();
    timer.pause();
    std::cout << "list: " << timer.get_mean_measure() << "\n";
    timer.restart();
        


}