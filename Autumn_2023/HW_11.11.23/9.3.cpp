#include <iostream>

class Color_v1 {
public:
    explicit Color_v1(int rgb) { std::cout << "Color_v1 in rgb: " << rgb << "\n"; }
};

class Label_v1 {
public:
    explicit Label_v1(char lb) { std::cout << "Label_v1: " << lb << "\n"; }
};

template <typename... Bases>
class Point_v1 : public Bases... {
public:
    template<typename... Args>
    explicit Point_v1(double x, double y, Args... args) : Bases(args)..., m_x(x), m_y(y) {
        std::cout << sizeof...(Bases) << std::endl;
    }

private:
    double m_x;
    double m_y;
};



int main() {
    std::cout << "Point_v1:" << std::endl;
    [[maybe_unused]] Point_v1<Color_v1, Label_v1> p1_v1(1.0, 1.0, 512, 'a');
    [[maybe_unused]] Point_v1<Color_v1> p2_v1(2.0, 2.0, 256);
    [[maybe_unused]] Point_v1<> p3_v1(3.0, 3.0);


    return 0;
}
