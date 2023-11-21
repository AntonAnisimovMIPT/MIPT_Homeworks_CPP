#include <iostream>
#include <variant>

struct Point {
    Point(double x, double y) : m_x(x), m_y(y) {}
    double m_x,m_y;
};

struct Line {
    Line(double a, double  b, double c) : m_a(a), m_b(b), m_c(c) {}
    double m_a,m_b,m_c;
};

std::variant<std::monostate, Point, Line> location (const Line& ln1, const Line& ln2) {
    auto det = ln1.m_a*ln2.m_b - ln1.m_b*ln2.m_a;

    if (det == 0) {
        if (ln1.m_c == ln2.m_c) {
            return ln1;
        }
        else {
            return std::monostate();
        }
    }
    else {
        return Point((ln2.m_c*ln1.m_b - ln1.m_c*ln2.m_b)/det, (ln1.m_c*ln2.m_a - ln2.m_c*ln1.m_a)/det);
    }

}

int main() {

    Line line1(1, 1, 1);
    Line line2(1, 2, 3);

    if (std::holds_alternative<std::monostate>(location(line1, line2))) {
       std::cout << "no common points!!!";
    }
    else if (std::holds_alternative<Point>(location(line1, line2)))  {
        std::cout << "one point:\n" << "x = " << std::get<Point>(location(line1, line2)).m_x << "\ny = " << std::get<Point>(location(line1, line2)).m_y;

    }
    else {
        std::cout << "common line:\n" << "a = " << std::get<Line>(location(line1, line2)).m_a << "\nb = " << std::get<Line>(location(line1, line2)).m_b << "\nc = " << std::get<Line>(location(line1, line2)).m_c;
    }


}