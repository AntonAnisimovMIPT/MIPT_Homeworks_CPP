/*
Как написано на cpp reference: 
Return value
1) f
2) (none)

f might not be applied in order. The algorithm is executed according to policy

т.о. это говорит о том, что функциональный объект может применяться не по порядку, что приведет к неопределенному  поведению в случае распараллеливания.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <numeric>

template<typename iter, typename f>
void advanced_for_each(iter begin, iter end, f func) {
    auto size = std::distance(begin, end);
    auto min_size = 100; 

    if (size <= min_size) {
        std::for_each(begin, end, func);
    } else {
    
        iter middle = std::next(begin, size / 2);
        std::future<void> result = std::async(advanced_for_each<iter, f>, begin, middle, func);
        advanced_for_each(middle, end, func);
        result.wait(); 
    }
}

int main() {
    std::vector<int> sequence(111);
    std::iota(sequence.begin(), sequence.end(), 1);

    advanced_for_each(sequence.begin(), sequence.end(), [](int& x) { ++x; });

    for (auto x : sequence) {
        std::cout << x << " ";
    }
    
}