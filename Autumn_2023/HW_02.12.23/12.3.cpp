#include <iostream>
#include <random>
#include <cmath>

struct Point {
    double x{};
    double y{};
};

double det_A (const Point& P, const Point& B, const Point& C) {
    return P.x * B.y + B.x * P.y + C.x * P.y - C.x * B.y - P.x * C.y - B.x * P.y;
}

double det_B (const Point& A, const Point& P, const Point& C) {
    return A.x * P.y + P.x * C.y + C.x * A.y - C.x * P.y - A.x * C.y - P.x * A.y;
}

double det_C (const Point& A, const Point& B, const Point& P) {
    return A.x * B.y + B.x * P.y + P.x * A.y - P.x * B.y - A.x * P.y - B.x * A.y;
}

Point A{1, 0}; // сразу зафикисровал точку А, чтобы потом не забыть
Point P{1, 1}; // аналогично для центра окружности

std::size_t Count_dropped_dots() {

    std::random_device device; // note: make seed only once

    std::mt19937 engine(device());

    std::uniform_real_distribution distribution(0.0, 2 * 3.14); // note: [a; b)

    const std::size_t size = 10'000'000; // note: try in release mode

    std::size_t counter = 0;
    auto r = 1.0;

    for (std::size_t i = 0; i < size; ++i) {
        Point B{1 + r * std::cos(distribution(engine)), 1 + r * std::sin(distribution(engine))};
        Point C{1 + r * std::cos(distribution(engine)), 1 + r * std::sin(distribution(engine))};
        if (det_A(P, B, C) >= 0 && det_B(A, P, C) >= 0 && det_C(A, B, P) >= 0) {
            ++counter;
        }
    }
    return counter;

}

int main() {
    auto num_points = Count_dropped_dots();
    std::cout << num_points << " of 10'000'000 throws satisfy (near " << num_points/100000 << "%)";
}

