#include <iostream>
#include <variant>
#include <cmath>

std::variant<std::monostate, double, std::pair<double, double>> roots(double a, double b, double c) {
    auto D = b * b - 4 * a * c;
    if (D < 0) {
        return std::monostate();
    } else if (D == 0) {
        return -b / (2 * a);
    } else {
        return std::make_pair((-b + std::sqrt(D)) / (2 * a), (-b - std::sqrt(D)) / (2 * a));
    }
}


class Tester_Roots {
    public:
    void operator()(const std::monostate) const {
        std::cout << "no roots!!!\n";
    }

    void operator()(const double root) const {
        std::cout << "one root: " << root << "\n";
    }

    void operator()(const std::pair<double, double> roots) const {
        std::cout << "first root: " << roots.first << "\n"
                  << "second root: " << roots.second << "\n";
    }
};



struct Point {
    explicit Point(double x, double y) : m_x(x), m_y(y) {}
    double m_x, m_y;
};

struct Line {
    explicit Line(double a, double b, double c) : m_a(a), m_b(b), m_c(c) {}
    double m_a, m_b, m_c;
};

std::variant<std::monostate, Point, Line> location(const Line &ln1, const Line &ln2) {
    auto det = ln1.m_a * ln2.m_b - ln1.m_b * ln2.m_a;

    if (det == 0) {
        if (ln1.m_c == ln2.m_c) {
            return ln1;
        } else {
            return std::monostate();
        }
    } else {
        return Point((ln2.m_c * ln1.m_b - ln1.m_c * ln2.m_b) / det, (ln1.m_c * ln2.m_a - ln2.m_c * ln1.m_a) / det);
    }
}


class Tester_Location {
    public:
    void operator()(const std::monostate) const {
        std::cout << "no common points!!!";
    }

    void operator()(const Point point) const {
        std::cout << "one point:\n"
                  << "x = " << point.m_x << "\ny = " << point.m_y;
    }

    void operator()(const Line line) const {
        std::cout << "common line:\n"
                  << "a = " << line.m_a << "\nb = " << line.m_b << "\nc = " << line.m_c;
    }
};

int main() {
    auto a = 1.0;
    auto b = 2.0;
    auto c = 1.0;

    auto rts = roots(a, b, c);
    std::visit(Tester_Roots{}, rts);

    Line line1(1, 1, 1);
    Line line2(1, 2, 3);

    auto loc = location(line1, line2);
    std::visit(Tester_Location{}, loc);

    return 0;
}
