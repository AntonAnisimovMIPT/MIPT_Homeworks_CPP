#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <timer.h>

int main() {
    constexpr size_t N = 1000000;

    std::set<int> Set;

    std::vector<int> Vector;
    Vector.reserve(N);

    Timer timer;

    timer.start();
    for (size_t i = 1; i <= N; ++i) {
        Set.insert(i);
    }
    timer.pause();
    auto Time_Insert_Set = timer.get_mean_measure();
    timer.restart();

   
    timer.start();
    for (size_t i = 1; i <= N; ++i) {
        Vector.push_back(i);
    }
    timer.pause();
    auto Time_Insert_Vector = timer.get_mean_measure();
    timer.restart();


 
    timer.start();
    std::sort(Vector.begin(), Vector.end(), std::less<int>());
    timer.pause();
    auto Time_Sort_Vector = timer.get_mean_measure();
    timer.restart();


    std::cout << "Inserting Set: " << Time_Insert_Set <<
                 "\nInserting Vector: "<< Time_Insert_Vector<<
                 "\nSorting Vector: " << Time_Sort_Vector;
}