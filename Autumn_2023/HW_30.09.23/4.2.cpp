#include <iostream>
#include <cmath>

class Shape{
public:
    virtual ~Shape() {};

public:
    [[nodiscard]] virtual double perimeter() const = 0;
    [[nodiscard]] virtual double area() const = 0;

protected:
    static inline const double pi = 3.1428;

};

class Polygon : public Shape{

};

class Rectangle : public Polygon{
public:
    Rectangle(double a, double b) : m_a(a), m_b(b) {}

public:

    [[nodiscard]] double perimeter() const override {

        return 2 * (m_a + m_b);

    }

    [[nodiscard]] double area() const override {

        return m_a * m_b;

    }

private:
    double m_a;
    double m_b;

};

class Square final : public Rectangle{
public:
    Square(double a) : Rectangle(a, a) {}

};

class Triangle final : public Polygon{
public:
    Triangle(double a, double b, double c) : m_a(a), m_b(b), m_c(c) {}

public:
    [[nodiscard]] double perimeter() const override {

        return m_a + m_b + m_c;

    }

    [[nodiscard]] double area() const override {

        double semiperimeter = (m_a + m_b + m_c) / 2;

        return std::sqrt(semiperimeter * (semiperimeter - m_a) * (semiperimeter - m_b) * (semiperimeter - m_c));

    }

private:
    double m_a{};
    double m_b{};
    double m_c{};

};



class Ellipse : public Shape{
public:
    Ellipse(double a, double b) : m_a(a), m_b(b) {}

public:
    [[nodiscard]] double area() const override{

        return pi * m_a * m_b;

    }

    [[nodiscard]] double perimeter() const override {

        return 4 * (pi * m_a * m_b + (m_a - m_b)) / (m_a + m_b);

    }

private:
    double m_a{};
    double m_b{};

};

class Circle final : public Ellipse{
public:

    Circle(double r) : Ellipse(r, r) {}

};

int main() {

    const auto size = 5;
    Shape* ar_ptr[size] {

        new Rectangle(10.0, 20.0),
        new Square(10.0),
        new Triangle(3.0, 4.0, 5.0),
        new Ellipse(4.0, 6.0),
        new Circle(3.0)

    };

    for (auto i = 0; i != size; i++) {

        std::cout << i << ": Area = " << ar_ptr[i]->area() << ", Perimeter = " << ar_ptr[i]->perimeter() << "\n";
        delete ar_ptr[i];

    }


}
