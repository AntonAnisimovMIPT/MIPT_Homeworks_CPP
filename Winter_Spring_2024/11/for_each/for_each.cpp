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
auto advanced_for_each(iter first, iter last, f F) {

    auto interval_size = std::distance(first, last);
    if (interval_size == 0) return;

    auto number_threads = std::thread::hardware_concurrency();
    auto chunk_size = interval_size / number_threads;
    auto last_chunk_size = interval_size % number_threads == 0 ? chunk_size : chunk_size + (interval_size % number_threads);

    std::vector<std::future<void>> futures;
    futures.reserve(number_threads);

    for (int i = 0; i < number_threads; ++i) {
        if (i != number_threads - 1) {
            auto part_first = first + i * chunk_size;
            auto part_last = part_first + chunk_size;
            futures.emplace_back(std::async(std::launch::async, [=]() { std::for_each(part_first, part_last, F); }));
        }
        else {
            auto part_first = first + i * last_chunk_size;
            auto part_last = part_first + last_chunk_size;
            futures.emplace_back(std::async(std::launch::async, [=]() { std::for_each(part_first, part_last, F); }));
        }
        
    }

    // без этого кода почему-то не работает, насколько я понял из-за неверной последовательности отработки потоков
    for (auto& future : futures) {
        future.wait();
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
