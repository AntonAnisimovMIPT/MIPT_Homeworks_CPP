#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <execution>
#include <random>
#include <fstream>
#include <chrono>
#include <iomanip>

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
        return  static_cast < double >(std::chrono::duration_cast < std::chrono::microseconds >
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

        return std::accumulate(m_measurements.begin(), m_measurements.end(), 0.0)/m_measurements.size();
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

auto do_calculations(int size) {

    std::vector<double> data(size);

    std::random_device device; // note: make seed only once
    std::mt19937 engine(device());
    std::uniform_real_distribution<double> distribution(0.0, 100.0); // note: [a; b)

    std::generate(data.begin(), data.end(), [&]() { return distribution(engine); });

    auto very_comlexity_operation = [](double x, double y) { return sqrt(std::cos(pow(x, 2) + pow(y, 3))); };

    Timer par_timer;
    Timer seq_timer;

    struct times {
        double pr;
        double sq;
    };

    std::vector<double> par_oper_result(size);

    par_timer.start();
    std::inclusive_scan(std::execution::par, data.begin(), data.end(), par_oper_result.begin(), very_comlexity_operation);
    par_timer.pause();

    std::vector<double> seq_oper_result(size);

    seq_timer.start();
    std::partial_sum(data.begin(), data.end(), seq_oper_result.begin(), very_comlexity_operation);
    seq_timer.pause();

    times tm {.pr = par_timer.get_mean_measure(), .sq = seq_timer.get_mean_measure()};

    par_timer.restart();
    seq_timer.restart();

    return tm;

}

int main() {
   
    std::ofstream results_file("results.txt");
    std::vector<int> sizes = {10, 100, 1000, 10000, 1'000'000, 10'000'000};

    for (size_t i = 0; i < sizes.size(); i++) {

        results_file << std::fixed << std::setprecision(6) <<
         "number_elements: " << sizes[i] << 
         ",    time_par = " << do_calculations(sizes[i]).pr << 
         ",     time_seq = " << do_calculations(sizes[i]).sq << "\n";
    }
}
