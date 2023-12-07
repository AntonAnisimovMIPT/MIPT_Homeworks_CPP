#include <iostream>
#include <random>
#include <cmath>
#include <numbers>

struct Point {
    double x{};
    double y{};
};

double det (Point A, Point B, Point C) {
    return A.x * B.y + C.x * A.y + B.x * C.y - C.x * B.y - A.x * C.y - B.x * A.y;
}



std::size_t Count_dropped_dots(Point A, Point P) {

    std::random_device device; // note: make seed only once

    std::mt19937 engine(device());

    std::uniform_real_distribution distribution(0.0, 2 * std::numbers::pi); // note: [a; b)

    const std::size_t size = 10'000'000; // note: try in release mode

    std::size_t counter = 0;

    for (std::size_t i = 0; i < size; ++i) {
        Point B{1 + 1.0 * std::cos(distribution(engine)), 1 + 1.0 * std::sin(distribution(engine))};
        Point C{1 + 1.0 * std::cos(distribution(engine)), 1 + 1.0 * std::sin(distribution(engine))};
        if (det(P, B, C) >= 0 && det(A, P, C) >= 0 && det(A, B, P) >= 0 || (det(P, B, C) < 0 && det(A, P, C) < 0 && det(A, B, P) < 0)) {
            ++counter;
        }
    }
    return counter;

}

int main() {

    Point A{1, 0};
    Point P{1, 1};

    auto num_points = Count_dropped_dots(A, P);
    std::cout << num_points << " of 10'000'000 throws satisfy (near " << static_cast<double>(num_points)/100000 << "%)";
}

