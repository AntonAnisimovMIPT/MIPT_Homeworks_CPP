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

auto simulation(int threads_number, int throws_number, double side_size = 1) {

    auto all_hits = 0;
    auto points_interval = throws_number / threads_number;

    {
		std::vector < std::jthread > threads(threads_number - 1);

		for (std::size_t i = 0; i < std::size(threads); ++i)
		{

			threads[i] = std::jthread([&all_hits, points_interval]() {
                all_hits += count_hit_points(points_interval);
            });
		}
	}

	all_hits += count_hit_points(points_interval);

    auto relative_hits = static_cast<double>(all_hits) / throws_number;

    return relative_hits * 4;

}


int main() {

    std::vector<int> number_throws = {10, 100, 1000, 10000, 100000, 1000000};
    std::ofstream results_file("results.txt");

    for (size_t i = 0; i < number_throws.size(); i++) {

        results_file << "number_throws: " << number_throws[i] << ",    pi = " << simulation(4, number_throws[i], 1) << "\n";
    }
    
}