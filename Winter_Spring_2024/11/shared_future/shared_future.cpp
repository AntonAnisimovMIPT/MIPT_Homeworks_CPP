#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <execution>
#include <random>
#include <fstream>
#include <iomanip>
#include <future>
#include <thread>

auto do_calculations = [](int size = 1'000'000) {

    std::vector<double> data(size);

    std::random_device device; // note: make seed only once
    std::mt19937 engine(device());
    std::uniform_real_distribution<double> distribution(0.0, 100.0); // note: [a; b)

    std::generate(data.begin(), data.end(), [&]() { return distribution(engine); });

    auto very_comlexity_operation = [](double x, double y) { return sqrt(std::cos(pow(x, 2) + pow(y, 3))); };

    std::vector<double> seq_oper_result(size);
    std::partial_sum(data.begin(), data.end(), seq_oper_result.begin(), very_comlexity_operation);
    auto sum = std::accumulate(seq_oper_result.begin(), seq_oper_result.end(), 0);

    return sum;
};

int main()
{
    std::future<int> future = std::async(std::launch::async, do_calculations);

    std::shared_future<int> shared_future_calc = future.share();

    std::jthread thread_1([&shared_future_calc]() {
        auto calc = shared_future_calc.get();
    });

    std::jthread thread_2([&shared_future_calc]() {
        auto calc = shared_future_calc.get(); 
    });

}
