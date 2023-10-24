#include "ratio.hpp"
#include <iostream>
#include <numeric>

namespace rt{

    Ratio::Ratio(int_t n, int_t d ) : // good: no explicit constructor
    m_numerator(n), m_denominator(d)
    {
        if (m_denominator == 0) // note: primitive error handling
        {
            std::cout << "invalid denominator" << std::endl;
        }

        if (m_denominator < 0) // note: numerator keeps ratio sign
        {
            m_numerator   *= -1;
            m_denominator *= -1;
        }

        reduce();
    }

    Ratio::operator double() const // good: explicit cast operator
    {
        return 1.0 * m_numerator / m_denominator;
    }

    void Ratio::reduce()
    {
        auto gcd = std::gcd(m_numerator, m_denominator);

        m_numerator   /= gcd;
        m_denominator /= gcd;
    }

    auto Ratio::numerator() const
    {
        return m_numerator;
    }

    auto Ratio::denominator() const
    {
        return m_denominator;
    }

    void Ratio::print() const // note: function instead of output operator
    {
        std::cout << m_numerator << '/' << m_denominator << std::endl;
    }

    Ratio & Ratio::operator+=(Ratio other)
    {
        auto lcm = std::lcm(m_denominator, other.m_denominator);

        m_numerator = m_numerator * (lcm /       m_denominator) +
                      other.m_numerator * (lcm / other.m_denominator);

        m_denominator = lcm;

        reduce();

        return *this;
    }

    Ratio & Ratio::operator-=(Ratio other)
    {
        return (*this += (other.m_numerator *= -1));
    }

    Ratio & Ratio::operator*=(Ratio other)
    {
        m_numerator   *= other.m_numerator;
        m_denominator *= other.m_denominator;

        reduce();

        return *this;
    }

    Ratio & Ratio::operator/=(Ratio other)
    {
        return (*this *= Ratio(other.m_denominator, other.m_numerator));
    }

    Ratio & Ratio::operator++()
    {
        m_numerator += m_denominator;

        return *this;
    }

    Ratio & Ratio::operator--()
    {
        m_numerator -= m_denominator;

        return *this;
    }

    Ratio Ratio::operator++(int)
    {
        Ratio tmp(*this);

        ++(*this);

        return tmp;

    }

    Ratio Ratio::operator--(int)
    {
        Ratio tmp(*this);

        --(*this);

        return tmp;
    }



    Ratio operator+(Ratio lhs, Ratio rhs) // good: free function
    {
        return (lhs += rhs);
    }

    Ratio operator-(Ratio lhs, Ratio rhs) // good: free function
    {
        return (lhs -= rhs);
    }

    Ratio operator*(Ratio lhs, Ratio rhs) // good: free function
    {
        return (lhs *= rhs);
    }

    Ratio operator/(Ratio lhs, Ratio rhs) // good: free function
    {
        return (lhs /= rhs);
    }

    bool operator<(Ratio lhs, Ratio rhs)
    {
        return static_cast < double > (lhs) < static_cast < double > (rhs);
    }

    bool operator>(Ratio lhs, Ratio rhs)
    {
        return (rhs < lhs);
    }

    bool operator>=(Ratio lhs, Ratio rhs)
    {
        return !(lhs < rhs);
    }

    bool operator<=(Ratio lhs, Ratio rhs)
    {
        return !(lhs > rhs);
    }

    bool operator==(Ratio lhs, Ratio rhs)
    {
        return (lhs.numerator  () == rhs.numerator  () && lhs.denominator() == lhs.denominator());
    }

    bool operator!=(Ratio lhs, Ratio rhs)
    {
        return !(lhs == rhs);
    }

}