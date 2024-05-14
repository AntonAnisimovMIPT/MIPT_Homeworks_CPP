#include <iostream>
#include <fstream>
#include <random>
#include <thread>
#include <cmath>
#include <vector>

auto generate(double limit) {

    std::random_device device; // note: make seed only once
    std::mt19937 engine(device());
    std::uniform_real_distribution<double> distribution(0.0, limit); // note: [a; b) 
    return distribution(engine);
}

auto count_hit_points(int throws_number, double side_size = 1) {

    auto hits_number = 0;
    for (size_t i = 0; i < throws_number; i++) {

        auto x = generate(side_size);
        auto y = generate(side_size);
        auto distance = sqrt(x*x + y*y);
        
        if (distance <= side_size) {

            hits_number += 1;

        }
    }

    return hits_number;
    
}

auto simulation(int throws_number, double side_size = 1) {

    auto min_per_thread = 25;
    auto max_threads = (throws_number + min_per_thread - 1) / min_per_thread;
    auto hardware_threads = std::thread::hardware_concurrency();
    auto num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, static_cast<unsigned int>(max_threads)); // Приведение типов
    auto block_size = throws_number / num_threads;
    auto all_hits = 0;

    {
		std::vector < std::jthread > threads(num_threads - 1);

		for (std::size_t i = 0; i < std::size(threads); ++i)
		{

			threads[i] = std::jthread([&all_hits, block_size]() {
                all_hits += count_hit_points(block_size);
            });
		}
	}

	all_hits += count_hit_points(block_size);

    auto relative_hits = static_cast<double>(all_hits) / throws_number;

    return relative_hits * 4;

}


int main() {

    std::vector<int> number_throws = {10, 100, 1000, 10000, 100000, 1000000};
    std::ofstream results_file("results.txt");

    for (const auto& throws : number_throws) {
        results_file << "number_throws: " << throws << ",    pi = " << simulation(throws, 1) << "\n";
    }
    
}