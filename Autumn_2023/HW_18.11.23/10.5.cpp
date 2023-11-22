#include <iostream>
#include <numeric>

class Ratio
{
public:

    using int_t = int;

public:

    /*explicit*/ Ratio(int_t n = 0, int_t d = 1) : // good: no explicit constructor
            m_numerator(n), m_denominator(d)
    {
        if (m_denominator == 0) // note: primitive error handling
        {
            throw std::invalid_argument("Denominator cannot be zero!!!");
        }

        if (m_denominator < 0) // note: numerator keeps ratio sign
        {
            m_numerator   *= -1;
            m_denominator *= -1;
        }

        reduce();
    }

    explicit operator double() const // good: explicit cast operator
    {
        return 1.0 * m_numerator / m_denominator;
    }

private:

    void reduce()
    {
        auto gcd = std::gcd(m_numerator, m_denominator);

        m_numerator   /= gcd;
        m_denominator /= gcd;
    }

public:

    auto numerator() const
    {
        return m_numerator;
    }

    auto denominator() const
    {
        return m_denominator;
    }

public:

    void print() const noexcept // note: function instead of output operator
    {
        std::cout << m_numerator << '/' << m_denominator << std::endl;
    }

public:

    auto & operator+=(Ratio other)noexcept
    {
        auto lcm = std::lcm(m_denominator, other.m_denominator);

        m_numerator = m_numerator * (lcm /       m_denominator) +
                      other.m_numerator * (lcm / other.m_denominator);

        m_denominator = lcm;

        reduce();

        return *this;
    }

    auto & operator-=(Ratio other) noexcept
    {
        return (*this += (other.m_numerator *= -1));
    }

    auto & operator*=(Ratio other)noexcept
    {
        m_numerator   *= other.m_numerator;
        m_denominator *= other.m_denominator;

        reduce();

        return *this;
    }

    auto & operator/=(Ratio other)
    {
        if (other.m_numerator == 0) {
            throw std::invalid_argument("Division by zero!!!");
        }
        return (*this *= Ratio(other.m_denominator, other.m_numerator));
    }

public:

    auto & operator++()noexcept
    {
        m_numerator += m_denominator;

        return *this;
    }

    auto & operator--()noexcept
    {
        m_numerator -= m_denominator;

        return *this;
    }

    auto operator++(int)noexcept
    {
        Ratio tmp(*this);

        ++(*this);

        return tmp;

    }

    auto operator--(int)noexcept
    {
        Ratio tmp(*this);

        --(*this);

        return tmp;
    }

private:

    int_t m_numerator;
    int_t m_denominator;

}; // class Ratio

auto operator+(Ratio lhs, Ratio rhs)noexcept  // good: free function
{
    return (lhs += rhs);
}

auto operator-(Ratio lhs, Ratio rhs) noexcept // good: free function
{
    return (lhs -= rhs);
}

auto operator*(Ratio lhs, Ratio rhs)noexcept  // good: free function
{
    return (lhs *= rhs);
}

auto operator/(Ratio lhs, Ratio rhs) // good: free function
{
    return (lhs /= rhs);
}

auto operator<(Ratio lhs, Ratio rhs)noexcept
{
    return static_cast < double > (lhs) < static_cast < double > (rhs);
}

auto operator>(Ratio lhs, Ratio rhs)noexcept
{
    return (rhs < lhs);
}

auto operator<=(Ratio lhs, Ratio rhs)noexcept
{
    return !(lhs > rhs);
}

auto operator>=(Ratio lhs, Ratio rhs)noexcept
{
    return !(lhs < rhs);
}

auto operator==(Ratio lhs, Ratio rhs)noexcept
{
    return (!(lhs < rhs) && !(rhs < lhs));
}

auto operator!=(Ratio lhs, Ratio rhs)noexcept
{
    return !(lhs == rhs);
}

int main()
{
    Ratio r2(2);
    Ratio r6(0);
    try {

        //Ratio r5(1,0);

        //r2 /= r6;
    }
    catch (const std::invalid_argument& exception) {
        std::cout<<exception.what();
    }
    catch (const std::invalid_argument& exception) {
        std::cout<<exception.what();
    }


    return 0;
}