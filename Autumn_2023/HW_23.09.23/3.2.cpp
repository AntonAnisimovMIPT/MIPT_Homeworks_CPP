#include <iostream>

class Circle {
private:
    double r{};

public:
    [[maybe_unused]] inline double perimeter() {

        return 2*3.14*r;

    }

    [[maybe_unused]] inline double area() {

        return 2*3.14*r*r;

    }

public:
    Circle(double radius) : r(radius) {}

    // т.к мы работали с копиями объектов, то утечек памяти и т.п не будет, но для формализма все равно прописал везде деструкторы (чтобы показать, что они работают, а инструкции им можно будет дописать потом при необходимости)
    ~Circle() {
        std::cout << "circle destructor called!!!\n";
    }

public:

    [[maybe_unused]] double Get_radius() const {
        return r;
    }

};

struct Sides {

    double tr_a{};
    double tr_b{};
    double tr_c{};

};

class Triangle {

private:
    Sides sides;

public:
    [[maybe_unused]] inline double perimeter() {

        return sides.tr_a + sides.tr_b + sides.tr_c;

    }

    [[maybe_unused]] inline double area() {

        double semiperimeter = (sides.tr_a + sides.tr_b + sides.tr_c) / 2;

        return std::sqrt(semiperimeter * (semiperimeter - sides.tr_a) * (semiperimeter - sides.tr_b) * (semiperimeter - sides.tr_c));

    }
public:
    Triangle(Sides sides) : sides(sides) {}

    ~Triangle() {
        std::cout << "triangle destructor called!!!\n";
    }

public:

    [[maybe_unused]] double Get_a() const {
        return sides.tr_a;
    }

    [[maybe_unused]] double Get_b() const {
        return sides.tr_b;
    }

    [[maybe_unused]] double Get_c() const {
        return sides.tr_c;
    }

};

class Square {
private:
    double a{};

public:
    [[maybe_unused]] inline double perimeter() {

        return 4*a;

    }

    [[maybe_unused]] inline double area() {

        return a*a;

    }

public:
    Square(double side) : a(side) {}

    ~Square() {
        std::cout << "square destructor called!!!\n";
    }

public:

    [[maybe_unused]] double Get_side() const {
        return a;
    }

};



int main() {
    // круг
    Circle circle(10);

    std::cout << "CIRCLE: \n" << "radius = " << circle.Get_radius() << "\n";
    std::cout << "area = " << circle.area() << "\n" << "perimeter = " << circle.perimeter() << "\n\n";


    // треугольник
    Sides sides(3, 4, 5);
    Triangle triangle(sides);

    std::cout << "TRIANGLE: \n" << "a = " << triangle.Get_a() << ", b = " << triangle.Get_b() << ", c = " << triangle.Get_c() << "\n";
    std::cout << "area = " << triangle.area() << "\n" << "perimeter = " << triangle.perimeter() << "\n\n";


    // квадрат
    Square square(11);

    std::cout << "SQUARE: \n" << "side = " << square.Get_side() << "\n";
    std::cout << "area = " << square.area() << "\n" << "perimeter = " << square.perimeter() << "\n\n";


}
