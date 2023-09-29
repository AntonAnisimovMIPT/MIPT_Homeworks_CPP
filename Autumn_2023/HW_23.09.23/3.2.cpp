#include <iostream>


class Circle {

public:
    [[nodiscard]] inline double perimeter() const {

        return 2*pi*r;

    }

    [[nodiscard]] inline double area() const {

        return 2*pi*r*r;

    }

public:
    Circle(double radius) : r(radius) {}

    // т.к мы работали с копиями объектов, то утечек памяти и т.п не будет, но для формализма все равно прописал везде деструкторы (чтобы показать, что они работают, а инструкции им можно будет дописать потом при необходимости)
    ~Circle() {
        std::cout << "circle destructor called!!!\n";
    }

public:

    [[nodiscard]] double Get_radius() const {
        return r;
    }

private:
    double r{};
    static inline const double pi = 3.1428;

};

class Triangle {

public:
    [[nodiscard]] double perimeter() const {

        return tr_a + tr_b + tr_c;

    }

    [[nodiscard]] double area() const{

        double semiperimeter = (tr_a + tr_b + tr_c) / 2;

        return std::sqrt(semiperimeter * (semiperimeter - tr_a) * (semiperimeter - tr_b) * (semiperimeter - tr_c));

    }
public:
    Triangle(double a, double b, double c) : tr_a(a), tr_b(b), tr_c(c) {}

    ~Triangle() {
        std::cout << "triangle destructor called!!!\n";
    }

public:

    [[nodiscard]] double Get_a() const {
        return tr_a;
    }

    [[nodiscard]] double Get_b() const {
        return tr_b;
    }

    [[nodiscard]] double Get_c() const {
        return tr_c;
    }

private:
    double tr_a{};
    double tr_b{};
    double tr_c{};

};

class Square {

public:
    [[nodiscard]] double perimeter() const {

        return 4*a;

    }

    [[nodiscard]] double area() const {

        return a*a;

    }

public:
    Square(double side) : a(side) {}

    ~Square() {
        std::cout << "square destructor called!!!\n";
    }

public:

    [[nodiscard]] double Get_side() const {
        return a;
    }

private:
    double a{};


};



int main() {
    // круг
    Circle circle(10);

    std::cout << "CIRCLE: \n" << "radius = " << circle.Get_radius() << "\n";
    std::cout << "area = " << circle.area() << "\n" << "perimeter = " << circle.perimeter() << "\n\n";


    // треугольник
    Triangle triangle(3, 4, 5);

    std::cout << "TRIANGLE: \n" << "a = " << triangle.Get_a() << ", b = " << triangle.Get_b() << ", c = " << triangle.Get_c() << "\n";
    std::cout << "area = " << triangle.area() << "\n" << "perimeter = " << triangle.perimeter() << "\n\n";


    // квадрат
    Square square(11);

    std::cout << "SQUARE: \n" << "side = " << square.Get_side() << "\n";
    std::cout << "area = " << square.area() << "\n" << "perimeter = " << square.perimeter() << "\n\n";


}
