#pragma once
#include <iostream>

namespace rt {

    class Ratio {
    public:

        using int_t = int;
        Ratio(int_t n = 0, int_t d = 0);

        explicit operator double() const;

        auto numerator() const;
        auto denominator() const;


        void print() const;

        Ratio & operator+=(Ratio other);
        Ratio & operator-=(Ratio other);
        Ratio & operator*=(Ratio other);
        Ratio & operator/=(Ratio other);

        Ratio & operator++();
        Ratio & operator--();
        Ratio operator++(int);
        Ratio operator--(int);

    private:
        void reduce();
        int_t m_numerator;
        int_t m_denominator;
    };


    Ratio operator+(Ratio lhs, Ratio rhs);
    Ratio operator-(Ratio lhs, Ratio rhs);
    Ratio operator*(Ratio lhs, Ratio rhs);
    Ratio operator/(Ratio lhs, Ratio rhs);

    bool operator<(Ratio lhs, Ratio rhs);
    bool operator>(Ratio lhs, Ratio rhs);
    bool operator<=(Ratio lhs, Ratio rhs);
    bool operator>=(Ratio lhs, Ratio rhs);
    bool operator==(Ratio lhs, Ratio rhs);
    bool operator!=(Ratio lhs, Ratio rhs);

}



