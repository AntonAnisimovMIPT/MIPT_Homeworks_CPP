#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

class StartException : public std::exception {
public:
    const char* what() const noexcept override {
        return "to make a start, make a stop!!!";
    }
};

class PauseException : public std::exception {
public:
    const char* what() const noexcept override {
        return "to make a stop, make a start!!!";
    }
};

class MeanException : public std::exception {
public:
    const char* what() const noexcept override {
        return "there were no measurements or you did not make a stop!!!";
    }
};


class Timer
{
public:

    using clock_t = std::chrono::steady_clock;

    using time_point_t = clock_t::time_point;

    explicit Timer() :  is_started(false) {}

    double elapsed() const
    {
        return static_cast < double > (std::chrono::duration_cast < std::chrono::microseconds >
                          (clock_t::now() - m_begin).count()) / 1'000'000.0;
    }

    void start();
    void pause();
    void restart();
    double get_mean_measure();
    void print_measurements();

private:

    time_point_t m_begin;

    std::vector<double> m_measurements;

    bool is_started;

}; // class Timer

void Timer::start() {
    if (!is_started) {
        is_started = true;
        m_begin = clock_t::now();
    }
    else {
        throw StartException();
    }

}

void Timer::pause() {
    if (is_started) {
        is_started = false;
        m_measurements.push_back(elapsed());
    }
    else {
        throw PauseException();
    }
}

void Timer::restart() {
    if (!is_started) {
        m_measurements.clear();
    }
    else {
        throw StartException();
    }
}

double Timer::get_mean_measure() {
    if (!m_measurements.empty() && !is_started) {
        auto res = 0.0;
        for (size_t i = 0; i < m_measurements.size(); ++i) {
            res += m_measurements[i];
        }
        return res/m_measurements.size();
    }
    else {
        throw MeanException();
    }

}

void Timer::print_measurements() {
    if (m_measurements.empty()) {
        std::cout << "no measurements";
    }
    else {
        for (size_t i = 0; i < m_measurements.size(); ++i) {
            std::cout << m_measurements[i] << "\t";
        }
        std::cout << '\n';
    }

}

int main() {

    Timer t1;
    t1.start();

    // что-то вычисляю
    auto a = 0;
    for (auto i = 0; i < 10000; ++i) {
        a += i;
    }

    t1.pause();
    std::cout << "time for first loop: ";
    t1.print_measurements();
    std::cout << "mean time: " << t1.get_mean_measure();

    t1.start();
    // что-то вычисляю
    auto b = 0;
    for (auto i = 0; i < 10000; ++i) {
        b += std::sqrt(i);
    }

    t1.pause();
    std::cout << "\ntime for first and second loops: ";
    t1.print_measurements();
    std::cout << "mean time: " << t1.get_mean_measure();

    t1.restart();
    std::cout << "\nafter restart there will be no measurements: ";
    t1.print_measurements();



    return 0;

}