#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>
#include <timer.h>

const char* StartException::what() const noexcept {
    return "to make a start, make a stop!!!";
}

const char* PauseException::what() const noexcept {
    return "to make a stop, make a start!!!";
}

const char* MeanException::what() const noexcept {
    return "there were no measurements or you did not make a stop!!!";
}


double Timer::elapsed() const
    {
        return  static_cast < double >(std::chrono::duration_cast < std::chrono::microseconds >
                (clock_t::now() - m_begin).count()) / 1'000'000.0;
    }


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

